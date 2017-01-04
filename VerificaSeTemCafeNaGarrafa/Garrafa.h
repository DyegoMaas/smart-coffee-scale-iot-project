// Garrafa.h

#ifndef _GARRAFA_h
#define _GARRAFA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Balanca.h"

class GarrafaClass
{
private:
	float _peso_atual;

public:
	explicit GarrafaClass(): _peso_atual(0.0f){}

	void setPesoAtual(float peso_atual)
	{
		_peso_atual = peso_atual;
	}
	float getPesoAtual()
	{
		_peso_atual = balanca.lerValorDoPeso();
		return _peso_atual;
	}

};

extern GarrafaClass Garrafa;

#endif

