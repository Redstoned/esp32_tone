#include "Arduino.h"

class ESP32_tone {
	
	public:
	ESP32_tone(uint8_t channel);
	
	uint8_t PWMChannel;
	
	void tone(int pin, unsigned int frequency);
	void tone(int pin, unsigned int frequency, unsigned long duration);
	void noTone(int pin);
	void setCompatibleMode(bool useCompatibleMode);
	void setCompatibleMode();
	void setCompatibleModePin(int pin);
	
	void beepForever(int pin, unsigned int frequency, unsigned long toneOnTime, unsigned long toneOffTime, unsigned int repeatTone, unsigned long toneDelay);
	
	private:
	
	static void StaticBuzzerTaskStart(void*);
	void BuzzerTask();
	
};