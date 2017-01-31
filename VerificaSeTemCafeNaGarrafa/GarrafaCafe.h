#ifndef _GARRAFACAFE_h
#define _GARRAFACAFE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Balanca.h"
#include "MensagemStatusGarrafa.h"
#include "MemoriaEeprom.h"

class GarrafaCafeClass
{
	float _peso_garrafa_vazia;
	float _peso_garrafa_cheia;
	float _maximo_cafe;

	const int PINO_IO_CALIBRACAO_GARRAFA_VAZIA = 9;
	const int PINO_IO_CALIBRACAO_GARRAFA_CHEIA = 10;
	const float PORCENTAGEM_NIVEL_CRITICO_CAFE = 0.1f;
	const float PORCENTAGEM_POUCO_CAFE = 0.3f;
	const float FATOR_CONVERSAO_PORCENTAGEM_PARA_ML_CAFE = 1.0f;
	const float FATOR_TOLERANCIA_PORCENTAGEM_CAFE = 0.1f;
	const bool BOTAO_PRESSIONADO = LOW;

	static void FiltrarRuidoSinalBalanca(float& quantidade_cafe_em_litros);

public:
	float _porcentagem_cafe;

	explicit GarrafaCafeClass();

	MensagemStatusGarrafaClass::SituacaoGarrafa VerificarSituacaoCafe();
	
	void ChecarBotoesCalibrarPesoGarrafa();

	float RecalcularPorcentagemCafeNagarrafa();
	float QuantidadeCafeEmMl();

	void atualizarPesoGarrafaVazia()
	{
		auto pesoAtual = Balanca.lerValorDoPeso();
		MemoriaEeprom.gravar(MemoriaEeprom.endereco_garrafa_vazia, pesoAtual);
		_peso_garrafa_vazia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_vazia);

		Serial.print("Garrafa vazia: ");
		Serial.println(_peso_garrafa_vazia);
	}

	float getPesoGarrafaVazia() const
	{
		return _peso_garrafa_vazia;
	}

	void atualizarPesoGarrafaCheia()
	{
		auto pesoAtual = Balanca.lerValorDoPeso();
		MemoriaEeprom.gravar(MemoriaEeprom.endereco_garrafa_cheia, pesoAtual);
		_peso_garrafa_cheia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_cheia);

		Serial.print("Garrafa cheia: ");
		Serial.println(_peso_garrafa_cheia);
	}

	float getPesoGarrafaCheia() const
	{
		return _peso_garrafa_cheia;
	}
};

extern GarrafaCafeClass GarrafaCafe;

#endif
