#ifndef _BUZZER_h
#define _BUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Melodias.h"

class BuzzerClass
{
 public:
	BuzzerClass();
	static void tocarMelodia(int s);
	static void buzz(int targetPin, long frequency, long length);
};

extern BuzzerClass Buzzer;

#endif

