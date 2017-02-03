// Mario.h

#ifndef _MARIO_h
#define _MARIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MarioClass
{
 protected:


 public:
	void init();
};

extern MarioClass Mario;

#endif

