#include "Balanca.h"
#include <HX711.h>

HX711 celulaDeCarga;

void Balanca::parametros(int pinDt, int pinSck, int fatorDeCalibracao, int atrasoNoLoopDeAquisicaoDeDados)
{
	this->_pinDt = pinDt;
	this->_pinSck = pinSck;
	this->_fatorDeCalibracao = fatorDeCalibracao;
	this->_atrasoNoLoopDeAquisicaoDeDados = atrasoNoLoopDeAquisicaoDeDados;
}

float Balanca::lerValorDoPeso()
{
	celulaDeCarga.power_down();
	delay(_atrasoNoLoopDeAquisicaoDeDados);
	celulaDeCarga.power_up();
	float peso = celulaDeCarga.get_units() * 0.1;
	peso = (peso < 0.01 && peso > -0.01) ? 0.0 : peso;
	return peso;
}

void Balanca::inicializar()
{
	celulaDeCarga = HX711(this->_pinDt, this->_pinSck);
	celulaDeCarga.set_scale(_fatorDeCalibracao);
	celulaDeCarga.tare();
}
