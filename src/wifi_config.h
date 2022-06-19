#include <WiFi.h>

//********** Network Credentials **********//
#define AP_Mode false //TRUE = AP mode //FALSE = WiFi Mode

#if AP_Mode
  const char* ssid = "HelloWorld";
  const char* password = "987654321";
#elif !AP_Mode
  const char* ssid = "YOUR WIFI SSID";
  const char* password = "YOUR PASSWORD";

#endif

void setup_wifi() {

  if(AP_Mode) { // Hotspot
    // Set Static IP address
    IPAddress local_IP(192, 168, 157, 254);
    IPAddress gateway(192, 168, 157, 254);
    IPAddress subnet(255, 255, 0, 0);
    WiFi.softAPConfig(local_IP, local_IP, subnet);

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("WiFi Started");
    Serial.print("http://");
    Serial.println(myIP);
    

  } else { // WiFi
  
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("http://");
    Serial.println(WiFi.localIP());
  }
}
