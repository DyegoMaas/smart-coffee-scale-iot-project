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
private:
	float _peso_garrafa_vazia;
	float _peso_garrafa_cheia;
	float _porcentagem_cafe;
	float _quantidade_cafe_em_ml;
	float _maximo_cafe;

	const float _porcentagem_pouco_cafe = 0.3f;
	const float _fator_conversao_porcentagem_ml_cafe = 1.0f;
public:
	explicit GarrafaCafeClass() : _peso_garrafa_vazia(1.0f), _peso_garrafa_cheia(3.0f), _porcentagem_cafe(0.0f), _quantidade_cafe_em_ml(0.0f), _maximo_cafe(2.0f)
	{}

	const String stringSituacaoGarrafa[4] = { "Fora da balanca", "Alguem pegando cafe", "Cafe acabando", "Tem cafe"};
	enum SituacaoGarrafa
	{
		GarrafaForaDaBalanca,
		AlguemPegandoCafe,
		AcabandoCafe,
		TemCafe
	};

	SituacaoGarrafa VerificaSituacaoCafe();
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

