/*
	Balanca.h
	Biblioteca aquisição de dados da balança de café.
*/

#ifndef _BALANCA_h
#define _BALANCA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class BalancaClass
{
	int _atraso_no_loop_de_aquisicao_de_dados;

public:
	BalancaClass();
	BalancaClass(int pin_dt, int pin_sck, float fator_de_calibracao, int atraso_no_loop_de_aquisicao_de_dados);
	float lerValorDoPeso() const;
};

extern BalancaClass Balanca;
#endif