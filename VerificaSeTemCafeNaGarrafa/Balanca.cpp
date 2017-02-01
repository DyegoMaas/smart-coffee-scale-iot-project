#include "Balanca.h"

InterfaceHX711 celulaDeCarga;
BalancaClass Balanca;

BalancaClass::BalancaClass()
{
	celulaDeCarga = InterfaceHX711(7, 8);
	celulaDeCarga.set_scale(27000.f);
	//celulaDeCarga.tare();
	this->_atraso_no_loop_de_aquisicao_de_dados = 500;
}

BalancaClass::BalancaClass(int pino_dt, int pino_sck, float fator_de_calibracao, int atraso_no_loop_de_aquisicao_de_dados)
{
	celulaDeCarga = InterfaceHX711(pino_dt, pino_sck);
	celulaDeCarga.set_scale(fator_de_calibracao);
	this->_atraso_no_loop_de_aquisicao_de_dados = atraso_no_loop_de_aquisicao_de_dados;
}

float BalancaClass::lerValorDoPeso()
{
	celulaDeCarga.power_down();
	delay(_atraso_no_loop_de_aquisicao_de_dados);
	celulaDeCarga.power_up();
	float peso = celulaDeCarga.get_units() * 0.1;
	peso = (peso < 0.01 && peso > -0.01) ? 0.0 : peso;
	_peso_atual = peso;
	return peso;
}

void BalancaClass::tararBalanca()
{
	celulaDeCarga.tare();

}
