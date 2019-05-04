//Sketch that uses the compatibility functions of the ESP32_tone library.
//You can use these functions just like the Arduino equivalents:
//
//ESP32_tone.tone(int pin, unsigned int frequency);                           frequency in Hertz
//ESP32_tone.tone(int pin, unsigned int frequency, unsigned long duration);   frequency in Hertz, duration in ms
//ESP32_tone.noTone(int pin);                                                 Cancel tone-playing on GPIO pin


//include the ESP32_tone library
#include <ESP32_tone.h>

//create an instance named buzzer
ESP32_tone buzzer;

//global variable of the pin connected to the buzzer
int buzzerPin = 15;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32_tone library Arduino_tone example sketch");
  Serial.println("You can use the functions of this library just like the Arduino equivalents\n");

  //initialize buzzer
  buzzer = ESP32_tone();

  //set the compatibleMode of the library
  buzzer.setCompatibleMode(true);

  //now You can use all of the Arduino tone functions (tone() and noTone()) with 'buzzer.' before it:
  buzzer.tone(buzzerPin, 800);
  delay(500);

  buzzer.noTone(buzzerPin);
  buzzer.tone(buzzerPin, 1000);
  delay(750);

  buzzer.tone(buzzerPin, 1500);
  delay(1000);

  buzzer.tone(buzzerPin, 1000, 1500);
  delay(5000);

  Serial.println("Code finished!");
}

void loop() {
  delay(100);
}
