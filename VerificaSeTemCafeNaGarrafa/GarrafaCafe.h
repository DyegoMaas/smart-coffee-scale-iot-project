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
	float _maximo_cafe;

	const int PINO_IO_CALIBRACAO_GARRAFA_VAZIA = 9;
	const int PINO_IO_CALIBRACAO_GARRAFA_CHEIA = 10;
	const float PORCENTAGEM_POUCO_CAFE = 0.3f;
	const float FATOR_CONVERSAO_PORCENTAGEM_PARA_ML_CAFE = 1.0f;
	const float FATOR_TOLERANCIA_PORCENTAGEM_CAFE = 0.01f;
	const bool BOTAO_PRESSIONADO = LOW;

	static void FiltrarRuidoSinalBalanca(float& quantidade_cafe_em_ml);

public:
	explicit GarrafaCafeClass();

	const String stringSituacaoGarrafa[4] = {"Fora da balanca", "Alguem pegando cafe", "Cafe acabando", "Tem cafe"};

	enum SituacaoGarrafa
	{
		GarrafaForaDaBalanca = 0,
		AlguemPegandoCafe = 1,
		AcabandoCafe = 2,
		TemCafe = 3
	};

	SituacaoGarrafa VerificarSituacaoCafe();
	
	void ChecarBotoesCalibrarPesoGarrafa();

	float RecalcularPorcentagemCafeNagarrafa();
	float QuantidadeCafeEmMl();

	void atualizarPesoGarrafaVazia()
	{
		_peso_garrafa_vazia = Balanca.lerValorDoPeso();
	}

	float getPesoGarrafaVazia() const
	{
		return _peso_garrafa_vazia;
	}

	void atualizarPesoGarrafaCheia()
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
