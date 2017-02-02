#ifndef _ATMEGA328P_h
#define _ATMEGA328P_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "time.h"

#define BOTAO_PRESSIONADO LOW

#define PINO_LED_STATUS A4
#define PINO_BUZZER A5

#define PINO_IO_HX711_DT 7
#define PINO_IO_HX711_SCK 8
#define PINO_IO_CALIBRACAO_BALANCA 6
#define PINO_IO_CALIBRACAO_GARRAFA_CHEIA 9
#define PINO_IO_CALIBRACAO_GARRAFA_VAZIA 10

class Atmega328pClass{};

extern Atmega328pClass Atmega328p;

#endif

