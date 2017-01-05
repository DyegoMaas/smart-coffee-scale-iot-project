// GarrafaCafe.h

#ifndef _GARRAFACAFE_h
#define _GARRAFACAFE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Balanca.h"

class GarrafaCafeClass
{
	float _peso_garrafa_vazia;
	float _peso_garrafa_cheia;
	float _porcentagem_cafe;
	float _quantidade_cafe_em_ml;
	float _maximo_cafe;

	const int PINO_CALIBRA_GARRAFA_VAZIA = 4;
	const int PINO_CALIBRA_GARRAFA_CHEIA = 5;
	const float PORCENTAGEM_POUCO_CAFE = 0.3f;
	const float FATOR_CONVERSAO_PORCENTAGEM_ML_CAFE = 1.0f;

public:
	explicit GarrafaCafeClass();

	const String stringSituacaoGarrafa[4] = { "Fora da balanca", "Alguem pegando cafe", "Cafe acabando", "Tem cafe"};
	enum SituacaoGarrafa
	{
		GarrafaForaDaBalanca,
		AlguemPegandoCafe,
		AcabandoCafe,
		TemCafe
	};
	SituacaoGarrafa VerificarSituacaoCafe();

	void ChecarBotoesCalibrarPesoGarrafa();

	float PorcentagemCafeNagarrafa();
	float QuantidadeCafeEmMl();

	void setPesoGarrafaVazia()
	{
		_peso_garrafa_vazia = Balanca.lerValorDoPeso();
	}

	float getPesoGarrafaVazia() const
	{
		return _peso_garrafa_vazia;
	}

	void setPesoGarrafaCheia()
	{
		_peso_garrafa_cheia = Balanca.lerValorDoPeso();
	}

	float getPesoGarrafaCheia() const
	{
		return _peso_garrafa_cheia;
	}
};

extern GarrafaCafeClass GarrafaCafe;

#endif

