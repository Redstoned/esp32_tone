#include "Arduino.h"

class ESP32_tone {
	
	public:
	ESP32_tone();
	
	void tone(int pin, unsigned int frequency);
	void tone(int pin, unsigned int frequency, unsigned long duration);
	void noTone(int pin);
	void setCompatibleMode(bool useCompatibleMode);
	void setCompatibleMode();
	void setCompatibleModePin(int pin);
	
	private:
	
	static void StaticBuzzerTaskStart(void*);
	void BuzzerTask();
	
};