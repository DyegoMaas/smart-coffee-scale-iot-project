#include "GarrafaCafe.h"
GarrafaCafeClass GarrafaCafe;

GarrafaCafeClass::GarrafaCafeClass(): _peso_garrafa_vazia(1.0f), _peso_garrafa_cheia(3.0f), _porcentagem_cafe(0.0f), _maximo_cafe(2.0f)
{
	pinMode(PINO_IO_CALIBRACAO_GARRAFA_VAZIA, INPUT_PULLUP);
	pinMode(PINO_IO_CALIBRACAO_GARRAFA_CHEIA, INPUT_PULLUP);
}

GarrafaCafeClass::SituacaoGarrafa GarrafaCafeClass::VerificarSituacaoCafe()
{
	ChecarBotoesCalibrarPesoGarrafa();
	RecalcularPorcentagemCafeNagarrafa();
	SituacaoGarrafa situacaoGarrafa;
	if (_porcentagem_cafe <= 0.00f - FATOR_TOLERANCIA_PORCENTAGEM_CAFE)
	{
		situacaoGarrafa = GarrafaForaDaBalanca;
	}
	else if (_porcentagem_cafe < PORCENTAGEM_POUCO_CAFE)
	{
		situacaoGarrafa = AcabandoCafe;
	}
	else if (_porcentagem_cafe <= 1.00f + FATOR_TOLERANCIA_PORCENTAGEM_CAFE)
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
	auto botaoCalibrarGarrafaVazia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_VAZIA);
	auto botaoCalibrarGarrafaCheia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_CHEIA);

	if (botaoCalibrarGarrafaVazia == BOTAO_PRESSIONADO)
	{
		atualizarPesoGarrafaVazia();
	}

	if (botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO)
	{
		atualizarPesoGarrafaCheia();
	}
}

float GarrafaCafeClass::RecalcularPorcentagemCafeNagarrafa()
{
	auto pesoAtualNaBalanca = Balanca.lerValorDoPeso();
	auto pesoCafe = pesoAtualNaBalanca - _peso_garrafa_vazia;	
	_maximo_cafe = _peso_garrafa_cheia - _peso_garrafa_vazia;
	_porcentagem_cafe = pesoCafe / _maximo_cafe;
	
	return _porcentagem_cafe;
}

void GarrafaCafeClass::FiltrarRuidoSinalBalanca(float& quantidade_cafe_em_ml)
{
	if (quantidade_cafe_em_ml < 0.0f)
		quantidade_cafe_em_ml = 0.0f;
}

float GarrafaCafeClass::QuantidadeCafeEmMl()
{
	RecalcularPorcentagemCafeNagarrafa();

	auto quantidade_cafe_em_ml = _porcentagem_cafe * FATOR_CONVERSAO_PORCENTAGEM_PARA_ML_CAFE;

	FiltrarRuidoSinalBalanca(quantidade_cafe_em_ml);

	return quantidade_cafe_em_ml;
}
