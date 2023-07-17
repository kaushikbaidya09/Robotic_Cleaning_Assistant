# Room_Cleaning_Robot

## Overview

Room Cleaning Robot ESP32 Cam is a controller + L293d bridge motor driver that can drive two DC motors clockwise and counterclockwise rotations with adjustable rotation speed, 18650 battery with 3s 12v 10A BMS and 5v power distribution, 3-wheeled frame with two active wheels for a differential speed steering mechanism. Controlled wirelessly through wifi with web applications created using HTML, CSS and javascript stored within the ESP32 filesystem hosted to connected wifi can be accessed by browsing IP address. Programmed with PlatformIO VScode.

## Installation

### WiFi Setup
Enter WiFi credentials and configure wiFi setup in [wifi_config.h](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/src/wifi_config.h) file.

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

![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/SC1.jpg?raw=true)

![Image link](https://github.com/kaushikbaidya09/Room_Cleaning_Robot/blob/main/Pics/SC2.jpg?raw=true)
