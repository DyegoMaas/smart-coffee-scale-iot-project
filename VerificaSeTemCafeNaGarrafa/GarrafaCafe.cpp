#include "GarrafaCafe.h"
GarrafaCafeClass GarrafaCafe;

GarrafaCafeClass::GarrafaCafeClass(): _peso_garrafa_vazia(1.0f), _peso_garrafa_cheia(3.0f), _porcentagem_cafe(0.0f), _quantidade_cafe_em_ml(0.0f), _maximo_cafe(2.0f)
{
	pinMode(_pin_calibra_garrafa_vazia, INPUT_PULLUP);
	pinMode(_pin_calibra_garrafa_cheia, INPUT_PULLUP);
}

GarrafaCafeClass::SituacaoGarrafa GarrafaCafeClass::VerificarSituacaoCafe()
{
	ChecarBotoesCalibrarPesoGarrafa();
	PorcentagemCafeNagarrafa();
	SituacaoGarrafa situacaoGarrafa;
	if (_porcentagem_cafe < 0.0f)
	{
		situacaoGarrafa = GarrafaForaDaBalanca;
	}
	else if (_porcentagem_cafe < _porcentagem_pouco_cafe)
	{
		situacaoGarrafa = AcabandoCafe;
	}
	else if (_porcentagem_cafe <= 1.0f)
	{
		situacaoGarrafa = TemCafe;
	}
	else
	{
		situacaoGarrafa = AlguemPegandoCafe;
	}
	return situacaoGarrafa;
}

void GarrafaCafeClass::ChecarBotoesCalibrarPesoGarrafa()
{
	auto botaoCalibraGarrafaVazia = digitalRead(_pin_calibra_garrafa_vazia);
	auto botaoCalibraGarrafaCheia = digitalRead(_pin_calibra_garrafa_cheia);

	if(botaoCalibraGarrafaVazia == LOW)
	{
		setPesoGarrafaVazia();
	}

	if(botaoCalibraGarrafaCheia ==  LOW)
	{
		setPesoGarrafaCheia();
	}
}

float GarrafaCafeClass::PorcentagemCafeNagarrafa()
{
	auto pesoCafe = Balanca.lerValorDoPeso() - _peso_garrafa_vazia;
	_maximo_cafe = _peso_garrafa_cheia - _peso_garrafa_vazia;
	_porcentagem_cafe = pesoCafe / _maximo_cafe;
	return _porcentagem_cafe;
}

float GarrafaCafeClass::QuantidadeCafeEmMl()
{
	PorcentagemCafeNagarrafa();
	_quantidade_cafe_em_ml = _porcentagem_cafe * _fator_conversao_porcentagem_ml_cafe;
	if (_quantidade_cafe_em_ml < 0.0f) _quantidade_cafe_em_ml = 0.0f;
	return _quantidade_cafe_em_ml;
}
