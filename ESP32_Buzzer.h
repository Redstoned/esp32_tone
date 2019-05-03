#include "Arduino.h"

class ESP32_Buzzer {
	
	public:
	ESP32_Buzzer();
	ESP32_Buzzer(int Pin);
	
	void tone(int pin, unsigned int frequency);
	void tone(int pin, unsigned int frequency, unsigned long duration);
	void noTone(int pin);
	void setCompatibleMode(bool useCompatibleMode);
	void setCompatibleMode();
	void setCompatibleModePin(int pin);
	
	private:
	bool CompatibleMode;
	int CompatibleBuzzerPin;
	unsigned long CompatibleToneStartDuration;
	unsigned long CompatibleToneStopDuration;
	bool CompatibleToneActive;
	void BuzzerTask(bool *compatibleToneActive);
	static void StaticBuzzerTaskStart(void*);
	TaskHandle_t TaskHandle;
	
};