# Robotic_Cleaning_Assistant

In today's fast-paced and busy lifestyles, finding time for basic household duties, such as cleaning, can be challenging. Cleaning the main areas of a room might be manageable, but reaching inaccessible spots like under the bed or couch can be difficult and time-consuming. However, imagine having a robot that could handle these tasks for you, allowing you to relax or focus on other work while it takes care of the cleaning. A cleaning robot would provide the convenience and efficiency needed to maintain a clean and tidy living space effortlessly.

## Overview

Cleaning Assistant ESP32 Cam is a controller + L293d bridge motor driver that can drive two DC motors clockwise and counterclockwise rotations with adjustable rotation speed, 18650 battery with 3s 12v 10A BMS and 5v power distribution, a 3-wheeled frame with two active wheels for a differential speed steering mechanism. Controlled wirelessly through wifi with web applications created using HTML, CSS and javascript stored within the ESP32 filesystem hosted to connected wifi can be accessed by browsing IP address. Programmed with PlatformIO VScode.

## Installation

### Hardware
* ESP32 Development Board,
* 12V battery & 5V Power Supply,
* H-Bridge Motor Driver & Motors,
* Suction Fan and necessary components. 


### Software
* VS Code Platform IO

### WiFi Setup
Enter WiFi credentials and configure WiFi setup in [wifi_config.h](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/src/wifi_config.h) file.

Set _AP_Mode_ = True for ESP32 as wiFi host (hotspot).

```C++
#define AP_Mode false //TRUE = AP mode //FALSE = WiFi Mode

#if AP_Mode
  const char* ssid = "HelloWorld";
  const char* password = "987654321";
#elif !AP_Mode
  const char* ssid = "YOUR WIFI SSID";
  const char* password = "YOUR PASSWORD";

#endif
```

_AP_Mode_ can be used to set a static IP address. 
```C++
IPAddress local_IP(192, 168, 157, 254);
IPAddress gateway(192, 168, 157, 254);
IPAddress subnet(255, 255, 0, 0);
WiFi.softAPConfig(local_IP, local_IP, subnet);
```

## Design

![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/image1.jpg?raw=true)  ![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/image2.jpg?raw=true)

## Web Application
### Controlling through mobile and Laptop

<!-- ![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/SC1.jpg?raw=true) -->

![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/SC2.jpg?raw=true)
