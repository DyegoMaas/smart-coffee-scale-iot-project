#ifndef _BALANCA_h
#define _BALANCA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "InterfaceHX711.h"

class BalancaClass
{
	int _atraso_no_loop_de_aquisicao_de_dados;
	
public:
	BalancaClass();
	BalancaClass(int pino_dt, int pino_sck, float fator_de_calibracao, int atraso_no_loop_de_aquisicao_de_dados);
	float lerValorDoPeso();
	static void tararBalanca();
	float _peso_atual;
};

extern BalancaClass Balanca;
#endif
