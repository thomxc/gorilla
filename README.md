## I named my plant "Gorilla"
I like plants. But my plants keep dying and I never understand why. So I built something that measures how my plant is doing. Kind of like Xiaomi's MiFlora but I figured I could make it myself.

I used a ESP8266 NodeMCU board with three sensors:
 1. Temp+humidity sensor (DHT22)
 2. Soil Moisture sensor (https://www.tinytronics.nl/shop/en/sensors/robotdyn-soil-moisture-sensor-module)
 3. Light sensitivity sensor (GY-30)
## Getting started
1. copy config.example to config.h and replace the contents with your own pin settings, wifi settings and domoticz virtual device identifiers
2. Use the Arduino IDE to compile and upload the firmware to a ESP8266 MCU board.

## Dependencies
* ESP8266Wifi library
* DHT sensor libray (for the DHT22 Temp+Hum sensor)
* BH1750 sensor library (for the GY-30 Lightsensitivity sensor)
