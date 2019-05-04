#include "Arduino.h"
#include "ESP32_tone.h"
#include "esp32-hal-ledc.h"



bool CompatibleToneActive = false;
unsigned long CompatibleToneStopTime = 0;
int CompatibleBuzzerPin = 1;
bool CompatibleBuzzerPinSet = false;
bool CompatibleMode = false;

ESP32_tone::ESP32_tone()
{
	xTaskCreate(this->StaticBuzzerTaskStart, "UpdateBuzzer", 10000, (void*)this, 1, NULL);
	
	ledcSetup(0, 0, 8);
	ledcWrite(0, 125);
}

void ESP32_tone::StaticBuzzerTaskStart(void* _this)
{
	static_cast<ESP32_tone*>(_this)->BuzzerTask();
}

void ESP32_tone::BuzzerTask()
{
	for(;;)
	{
		if(CompatibleMode)
		{
			if(CompatibleToneActive)
			{
				if(millis() > CompatibleToneStopTime)
				{
					this->noTone(15);
				}
			}
		}
		else
		{
		    delay(20);
		}
		delay(1);
	}
}

void ESP32_tone::setCompatibleMode(bool useCompatibleMode = true)
{
	CompatibleMode = useCompatibleMode;
}

void ESP32_tone::setCompatibleMode()
{
	CompatibleMode = true;
}

void ESP32_tone::setCompatibleModePin(int pin)
{
	CompatibleBuzzerPin = pin;
}

void ESP32_tone::tone(int pin, unsigned int frequency)
{
	if(CompatibleBuzzerPinSet)
	{
		if(pin == CompatibleBuzzerPin || !CompatibleToneActive)
	    {
		    ledcWriteTone(0, frequency);
		    ledcAttachPin(pin, 0);
			CompatibleBuzzerPin = pin;
		    CompatibleToneStopTime = -1;
		    CompatibleToneActive = true;
	    }
	}
	else
	{
		CompatibleBuzzerPin = pin;
		CompatibleBuzzerPinSet = true;
		this->tone(CompatibleBuzzerPin, frequency);
	}

}

void ESP32_tone::tone(int pin, unsigned int frequency, unsigned long duration)
{
	if(CompatibleBuzzerPinSet)
	{
	    if(pin == CompatibleBuzzerPin || !CompatibleToneActive)
	    {
		    ledcWriteTone(0, frequency);
		    CompatibleToneStopTime = millis() + duration;
		    CompatibleToneActive = true;
		    ledcAttachPin(pin, 0);
			CompatibleBuzzerPin = pin;
	    }
	}
	else
	{
		CompatibleBuzzerPin = pin;
		CompatibleBuzzerPinSet = true;
		this->tone(CompatibleBuzzerPin, frequency, duration);
	}
}

void ESP32_tone::noTone(int pin)
{
	if(pin == CompatibleBuzzerPin && CompatibleBuzzerPinSet)
	{
		ledcDetachPin(CompatibleBuzzerPin);
		if(CompatibleToneActive) CompatibleToneActive = false;
	}	
}