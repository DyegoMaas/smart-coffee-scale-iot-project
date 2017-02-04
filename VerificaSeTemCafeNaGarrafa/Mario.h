#ifndef _MARIO_h
#define _MARIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <LiquidCrystal.h>

class MarioClass
{
 protected:

 public:
	 static void mostrarMario(LiquidCrystal lcd);

};

extern MarioClass Mario;

#endif

