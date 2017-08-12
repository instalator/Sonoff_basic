# Sonoff_basic

## Arduino IDE

In the Arduino IDE for sonoff select from Tools Board Generic ESP8266 Module ( Tools Board Generic ESP8285 Module for CH4 version) and set the following options:

Upload Using: Serial
Flash Mode: DOUT
Flash Frequency: 40MHz
CPU Frequency: 80MHz
Flash Size: 1M (64K SPIFFS) ⚠️️**If Version 5.x.x -> Flash Size: "1M (no SPIFFS)"**⚠️️
Debug Port: Disabled
Debug Level: None
Reset Method: ck
Upload Speed: 115200
Port: Your COM port connected to sonoff
