#include "Balanca.h"
#include <HX711.h>

HX711 celulaDeCarga;
BalancaClass Balanca;

BalancaClass::BalancaClass()
{
	celulaDeCarga = HX711(7, 8);
	celulaDeCarga.set_scale(27000.f);
	celulaDeCarga.tare();
	this->_atraso_no_loop_de_aquisicao_de_dados = 500;
}

BalancaClass::BalancaClass(int pino_dt, int pino_sck, float fator_de_calibracao, int atraso_no_loop_de_aquisicao_de_dados)
{
	celulaDeCarga = HX711(pino_dt, pino_sck);
	celulaDeCarga.set_scale(fator_de_calibracao);
	celulaDeCarga.tare();
	this->_atraso_no_loop_de_aquisicao_de_dados = atraso_no_loop_de_aquisicao_de_dados;
}


float BalancaClass::lerValorDoPeso() const
{
	celulaDeCarga.power_down();
	delay(_atraso_no_loop_de_aquisicao_de_dados);
	celulaDeCarga.power_up();
	float peso = celulaDeCarga.get_units() * 0.1;
	peso = (peso < 0.01 && peso > -0.01) ? 0.0 : peso;
	return peso;
}
