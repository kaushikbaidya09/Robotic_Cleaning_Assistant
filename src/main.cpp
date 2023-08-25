#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include "wifi_config.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// PINS
const int LED_Pin = 4;
const int FAN_Pin = 16;
const int En_Pin1 = 12;
const int En_Pin2 = 13;
const int M_Pin1 = 15;
const int M_Pin2 = 14;
const int Power_ON = 33;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int FAN_Channel = 1;
const int M1_Channel  = 2;
const int M2_Channel  = 3;
const int Power_channel = 4;
// PWM 8
// const int resolution = 8;

String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";
String sliderValue3 = "50";

int dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
int dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
int dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
int dutyCycle_M1;
int dutyCycle_M2;

//Json Variable to Hold Slider Values
JSONVar sliderValues;

//Get Slider Values
String getSliderValues(){
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);

  String jsonString = JSON.stringify(sliderValues);
  return jsonString;
}

// Initialize SPIFFS
void initFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else{
   Serial.println("SPIFFS mounted successfully");
  }
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      // Serial.println(dutyCycle1);
      // Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      // Serial.println(dutyCycle2);
      // Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }    
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      // Serial.println(dutyCycle3);
      // Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (strcmp((char*)data, "getValues") == 0) {
      notifyClients(getSliderValues());
    }

    // Motor Controlls
    if (strcmp((char*)data, "forward") == 0) {
      // Serial.println("Forward");
      digitalWrite(M_Pin1, 1);
      digitalWrite(M_Pin2, 0);
      dutyCycle_M1 = dutyCycle3; 
      dutyCycle_M2 = dutyCycle3;
    }
    if (strcmp((char*)data, "left") == 0) {
      // Serial.println("Left");
      digitalWrite(M_Pin1, 1);
      digitalWrite(M_Pin2, 0);
      dutyCycle_M1 = dutyCycle3;
      dutyCycle_M2 = (dutyCycle3/2);
    }
    if (strcmp((char*)data, "right") == 0) {
      // Serial.println("Right");
      digitalWrite(M_Pin1, 1);
      digitalWrite(M_Pin2, 0);
      dutyCycle_M1 = (dutyCycle3/2);
      dutyCycle_M2 = dutyCycle3;
    }
    if (strcmp((char*)data, "backward") == 0) {
      // Serial.println("Backward");
      digitalWrite(M_Pin1, 0);
      digitalWrite(M_Pin2, 1);
      dutyCycle_M1 = dutyCycle3; 
      dutyCycle_M2 = dutyCycle3;
    }
    if (strcmp((char*)data, "stop") == 0) {
      // Serial.println("Stop");
      digitalWrite(M_Pin1, 0);
      digitalWrite(M_Pin2, 0);
      dutyCycle_M1 = 0;
      dutyCycle_M2 = 0;
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() {
  SPIFFS.begin(true);
  Serial.begin(115200);

  // Motor Driver Pins
  pinMode(LED_Pin, OUTPUT);
  pinMode(FAN_Pin, OUTPUT);
  pinMode(En_Pin1, OUTPUT);
  pinMode(En_Pin2, OUTPUT);
  pinMode(M_Pin1, OUTPUT);
  pinMode(M_Pin2, OUTPUT);
  pinMode(Power_ON, OUTPUT);

  initFS();
  setup_wifi();

  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, 8);
  ledcSetup(FAN_Channel, freq, 8);
  ledcSetup(M1_Channel, freq, 8);
  ledcSetup(M2_Channel, freq, 8);
  ledcSetup(Power_channel, freq, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_Pin, ledChannel1);
  ledcAttachPin(FAN_Pin, FAN_Channel);
  ledcAttachPin(En_Pin1, M1_Channel);
  ledcAttachPin(En_Pin2, M2_Channel);
  ledcAttachPin(Power_ON, Power_channel);

  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.serveStatic("/", SPIFFS, "/");

  // Start server
  server.begin();
}

void loop() {
  ledcWrite(Power_channel, 10);
  ledcWrite(ledChannel1, dutyCycle1);
  ledcWrite(FAN_Channel, dutyCycle2);
  ledcWrite(M1_Channel, dutyCycle_M1);
  ledcWrite(M2_Channel, dutyCycle_M2);
  ws.cleanupClients();
}
