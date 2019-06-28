# esp32_tone 

This library adds the Arduino tone() and noTone() functions for the ESP32.
The library is built that You can use Your existing Arduino code with the ESP32 but also adds some other handy functions.

## Setup

1. Download, unpack and copy this library into the 'libraries' folder in your Arduino sketchbook folder.
   If the 'libraries' folder doesn't exist, create a new one.
   
2. Connect a piezo speaker to pin 15(or any other pin) of Your ESP32 and Ground

3. Open the example sketch [Arduino-compatibility-example](https://github.com/Redstoned/esp32_tone/blob/master/examples/Arduino-compatibility-example/Arduino-compatibility-example.ino) and upload it to Your ESP32.

## Functions

### Arduino-compatible Functions:
This library contains Arduino equivalent functions that You can use with Your ESP32 as they don't work on the ESP32. These are:
```
tone(int pin, unsigned int frequency)
tone(int pin, unsigned int frequency, unsigned long duration)
noTone(int pin)
```
They work just as the Arduino functions [tone](https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/) and [noTone](https://www.arduino.cc/reference/en/language/functions/advanced-io/notone/).
For them to work You have to call `setCompatibleMode(true)` or `setCompatibleMode()` first (e.g. in setup()).

**Otherwise the functions won't do anything!**



### Other handy functions:
There is currently one enhanced function:
```
beepForever(int pin, unsigned int frequency, unsigned long toneOnTime, unsigned long toneOggTime, unsigned int repeatTone, unsigned long toneDelay)
```
