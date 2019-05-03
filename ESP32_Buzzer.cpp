#include "Arduino.h"
#include "ESP32_Buzzer.h"
#include "esp32-hal-ledc.h"
//#include "Data.h"

bool active = false;
unsigned long toneStopDuration = 0;
int buzzerPin;

ESP32_Buzzer::ESP32_Buzzer() {
	
}

ESP32_Buzzer::ESP32_Buzzer(int Pin) {
	//BuzzerPin = Pin;
	//Serial.begin(115200);
	Serial.println("lib!");
	//Data.setActive(false);
	CompatibleMode = true;
	xTaskCreate(this->StaticBuzzerTaskStart, "UpdateBuzzer", 10000, (void*)&CompatibleToneActive, 1, NULL);
}

void ESP32_Buzzer::BuzzerTask(bool *compatibleToneActive)
{
	for(;;)
	{
		//Serial.println(*compatibleToneActive);
		//Serial.println(String(Data.CompatibleMode) + "\n");

	//	Serial.println(millis());
		//if(CompatibleMode)
		if(true)
		{
				//	Serial.println(active);
					//delay(500);
			//this->noTone(15);
			Serial.println(active);
			Serial.println(toneStopDuration);
			Serial.println(String(millis()) + "\n");
			if(active)
			{
				if(millis() > toneStopDuration)
				{
					Serial.println("not active anymore");
					//Serial.println("Ton aktiv");
					this->noTone(15);
					active = false;
				}
			}
		}
		else
		{
	    	Serial.println("Buzzer updated");
		    delay(2000);
		}
	}
}

 void ESP32_Buzzer::StaticBuzzerTaskStart(void* _this) {
	static_cast<ESP32_Buzzer*>(_this)->BuzzerTask(((bool*)_this));
}

void ESP32_Buzzer::setCompatibleMode(bool useCompatibleMode = true)
{
	CompatibleMode = useCompatibleMode;
}

void ESP32_Buzzer::setCompatibleMode()
{
	CompatibleMode = true;
}

void ESP32_Buzzer::setCompatibleModePin(int pin)
{
	CompatibleBuzzerPin = pin;
	buzzerPin = pin;
	ledcSetup(0, 0, 8);
	ledcWrite(0, 125);
}

void ESP32_Buzzer::tone(int pin, unsigned int frequency)
{
	if(pin == buzzerPin)
	{
		ledcWriteTone(0, frequency);
		ledcAttachPin(pin, 0);
	}
}

void ESP32_Buzzer::tone(int pin, unsigned int frequency, unsigned long duration)
{
	if(pin == buzzerPin)
	{
		ledcWriteTone(0, frequency);
	//	CompatibleToneStartDuration = millis();
		toneStopDuration = millis() + duration;
		CompatibleToneActive = true;
		active = true;
		ledcAttachPin(buzzerPin, 0);
	}
}

void ESP32_Buzzer::noTone(int pin)
{
	if(pin == buzzerPin)
	{
		//Serial.println("noTone fired!");
		ledcDetachPin(buzzerPin);
		if(CompatibleToneActive) CompatibleToneActive = false;
		if(active) active = false;
	}	
}

//[b] static [/b] void ESP32_Buzzer::StaticBuzzerTask(void* _this)
//{
	
//}