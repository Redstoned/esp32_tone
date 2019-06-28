#include "Arduino.h"
#include "ESP32_tone.h"
#include "esp32-hal-ledc.h"



bool CompatibleToneActive = false;
unsigned long CompatibleToneStopTime = 0;
int CompatibleBuzzerPin = 1;
bool CompatibleBuzzerPinSet = false;
bool CompatibleMode = false;

int BuzzerPin = 1;
unsigned int Frequency, RepeatTone;
unsigned long ToneOffTime, ToneOnTime, ToneDelay;
bool BeepActive = false;

uint8_t PWMChannel = 0;


ESP32_tone::ESP32_tone(uint8_t channel)
{
	PWMChannel = channel;
	xTaskCreate(this->StaticBuzzerTaskStart, "UpdateBuzzer", 10000, (void*)this, 1, NULL);
	
	ledcSetup(PWMChannel, 0, 8);
	ledcWrite(PWMChannel, 125);
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
					this->noTone(CompatibleBuzzerPin);
				}
			}
		}
		else
		{
		    if(BeepActive)
			{
				for(int i = 0; i < RepeatTone; i++)
				{
					ledcAttachPin(BuzzerPin, PWMChannel);
					delay(ToneOnTime);
					ledcDetachPin(BuzzerPin);
					delay(ToneOffTime);
					BeepActive? i = i : i = RepeatTone;
				}
				delay(ToneDelay);
			}
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
		    ledcWriteTone(PWMChannel, frequency);
		    ledcAttachPin(pin, PWMChannel);
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
		    ledcWriteTone(PWMChannel, frequency);
		    CompatibleToneStopTime = millis() + duration;
		    CompatibleToneActive = true;
		    ledcAttachPin(pin, PWMChannel);
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
	
	else if(pin == BuzzerPin && BeepActive &&!CompatibleMode)
	{
		BeepActive = false;
		ledcDetachPin(pin);
	}
}

void ESP32_tone::beepForever(int pin, unsigned int frequency, unsigned long toneOnTime, unsigned long toneOffTime, unsigned int repeatTone, unsigned long toneDelay)
{
	if(repeatTone > 0 && !CompatibleMode)
	{
		BuzzerPin = pin;
		Frequency = frequency;
		ToneOnTime = toneOnTime;
		ToneOffTime = toneOffTime;
		RepeatTone = repeatTone;
		ToneDelay = toneDelay;
		BeepActive = true;
		ledcWriteTone(PWMChannel, frequency);
	}
}