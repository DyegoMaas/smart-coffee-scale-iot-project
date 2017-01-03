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

class Balanca
{
public:
	void parametros(int pinDt, int pinSck, int fatorDeCalibracao, int atrasoNoLoopDeAquisicaoDeDados);
	float lerValorDoPeso();
	void inicializar();

private:
	int _pinDt;
	int _pinSck;
	int _fatorDeCalibracao;
	int _atrasoNoLoopDeAquisicaoDeDados;
};
#endif