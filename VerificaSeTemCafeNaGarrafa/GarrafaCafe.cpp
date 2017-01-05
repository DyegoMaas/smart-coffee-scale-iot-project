#include "GarrafaCafe.h"
GarrafaCafeClass GarrafaCafe;

GarrafaCafeClass::GarrafaCafeClass(): _peso_garrafa_vazia(1.0f), _peso_garrafa_cheia(3.0f), _porcentagem_cafe(0.0f), _quantidade_cafe_em_ml(0.0f), _maximo_cafe(2.0f)
{
	pinMode(PINO_CALIBRA_GARRAFA_VAZIA, INPUT_PULLUP);
	pinMode(PINO_CALIBRA_GARRAFA_CHEIA, INPUT_PULLUP);
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
	else if (_porcentagem_cafe < PORCENTAGEM_POUCO_CAFE)
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
	auto botaoCalibraGarrafaVazia = digitalRead(PINO_CALIBRA_GARRAFA_VAZIA);
	auto botaoCalibraGarrafaCheia = digitalRead(PINO_CALIBRA_GARRAFA_CHEIA);

	if (botaoCalibraGarrafaVazia == BOTAO_PRESSIONADO)
	{
		setPesoGarrafaVazia();
	}

	if (botaoCalibraGarrafaCheia == BOTAO_PRESSIONADO)
	{
		setPesoGarrafaCheia();
	}
}

float GarrafaCafeClass::PorcentagemCafeNagarrafa()
{
	auto pesoAtualNaBalanca = Balanca.lerValorDoPeso();
	auto pesoCafe = pesoAtualNaBalanca - _peso_garrafa_vazia;
	_maximo_cafe = _peso_garrafa_cheia - _peso_garrafa_vazia;
	_porcentagem_cafe = pesoCafe / _maximo_cafe;
	return _porcentagem_cafe;
}

float GarrafaCafeClass::QuantidadeCafeEmMl()
{
	PorcentagemCafeNagarrafa();
	_quantidade_cafe_em_ml = _porcentagem_cafe * FATOR_CONVERSAO_PORCENTAGEM_PARA_ML_CAFE;
	if (_quantidade_cafe_em_ml < 0.0f) _quantidade_cafe_em_ml = 0.0f;
	return _quantidade_cafe_em_ml;
}
