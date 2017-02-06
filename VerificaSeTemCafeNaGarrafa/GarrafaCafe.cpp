#include "GarrafaCafe.h"
GarrafaCafeClass GarrafaCafe;

unsigned long tempoIgnorandoBotaoCalibracao;

GarrafaCafeClass::GarrafaCafeClass()
{
	_peso_garrafa_vazia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_vazia);
	_peso_garrafa_cheia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_cheia);
	_porcentagem_cafe = 1.0f;
	pinMode(PINO_IO_CALIBRACAO_BALANCA, INPUT_PULLUP);
	pinMode(PINO_IO_CALIBRACAO_GARRAFA_VAZIA, INPUT_PULLUP);
	pinMode(PINO_IO_CALIBRACAO_GARRAFA_CHEIA, INPUT_PULLUP);
}

MensagemStatusGarrafaClass::SituacaoGarrafa GarrafaCafeClass::VerificarSituacaoCafe()
{
	ChecarBotoesCalibrarPesoGarrafa();
	RecalcularPorcentagemCafeNagarrafa();
	MensagemStatusGarrafaClass::SituacaoGarrafa situacaoGarrafa;
	if (_porcentagem_cafe <= 0.00f - FATOR_TOLERANCIA_PORCENTAGEM_CAFE)
	{
		situacaoGarrafa = MensagemStatusGarrafaClass::GarrafaForaDaBalanca;
	}
	else if (_porcentagem_cafe < PORCENTAGEM_NIVEL_CRITICO_CAFE)
	{
		situacaoGarrafa = MensagemStatusGarrafaClass::NivelCriticoCafe;
	}
	else if (_porcentagem_cafe < PORCENTAGEM_POUCO_CAFE)
	{
		situacaoGarrafa = MensagemStatusGarrafaClass::AcabandoCafe;
	}
	else if (_porcentagem_cafe <= 1.00f + FATOR_TOLERANCIA_PORCENTAGEM_CAFE)
	{
		situacaoGarrafa = MensagemStatusGarrafaClass::TemCafe;
	}
	else
	{
		situacaoGarrafa = MensagemStatusGarrafaClass::AlguemPegandoCafe;
	}
	return situacaoGarrafa;
}

void GarrafaCafeClass::ChecarBotoesCalibrarPesoGarrafa()
{

	auto botaoCalibrarBalanca = digitalRead(PINO_IO_CALIBRACAO_BALANCA);
	auto botaoCalibrarGarrafaVazia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_VAZIA);
	auto botaoCalibrarGarrafaCheia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_CHEIA);

	if (botaoCalibrarGarrafaVazia == BOTAO_PRESSIONADO && botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO)
	{
		Buzzer.tocarMelodia(1);
		Buzzer.tocarMelodia(2);
	}

	if (_modo_calibracao) {
		InterfaceUsuario.imprimirMensagemLCD("MODO CALIBRACAO", 0, true);
		if (millis() > tempoIgnorandoBotaoCalibracao) {
			InterfaceUsuario.imprimirMensagemLCD("->GARRAFA CHEIA", 1);
			InterfaceUsuario.imprimirMensagemLCD("->GARRAFA VAZIA", 2);
			InterfaceUsuario.imprimirMensagemLCD("->BALANCA VAZIA", 3);
			while (_modo_calibracao)
			{
				botaoCalibrarBalanca = digitalRead(PINO_IO_CALIBRACAO_BALANCA);
				botaoCalibrarGarrafaVazia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_VAZIA);
				botaoCalibrarGarrafaCheia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_CHEIA);

				if (botaoCalibrarBalanca == BOTAO_PRESSIONADO && 
					botaoCalibrarGarrafaVazia != BOTAO_PRESSIONADO &&
					botaoCalibrarGarrafaCheia != BOTAO_PRESSIONADO)
				{
					Balanca.tararBalanca();
					InterfaceUsuario.imprimirMensagemLCD("BALANCA CALIBRADA", 0, true);
					Serial.println("BALANCA CALIBRADA");
					_modo_calibracao = false;
				}

				if (botaoCalibrarBalanca != BOTAO_PRESSIONADO &&
					botaoCalibrarGarrafaVazia == BOTAO_PRESSIONADO &&
					botaoCalibrarGarrafaCheia != BOTAO_PRESSIONADO)
				{
					atualizarPesoGarrafaVazia();
					_modo_calibracao = false;
				}

				if (botaoCalibrarBalanca != BOTAO_PRESSIONADO &&
					botaoCalibrarGarrafaVazia != BOTAO_PRESSIONADO &&
					botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO)
				{
					atualizarPesoGarrafaCheia();
					_modo_calibracao = false;
				}
			}
		}
	}

	if (botaoCalibrarBalanca == BOTAO_PRESSIONADO && botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO)
	{
		tempoIgnorandoBotaoCalibracao = millis();
		tempoIgnorandoBotaoCalibracao += 1000;
		_modo_calibracao = true;
	}
}

float GarrafaCafeClass::RecalcularPorcentagemCafeNagarrafa()
{
	_maximo_cafe = _peso_garrafa_cheia - _peso_garrafa_vazia;
	auto pesoAtualNaBalanca = Balanca.lerValorDoPeso();
	_peso_cafe = pesoAtualNaBalanca - _peso_garrafa_vazia;
	_porcentagem_cafe = _peso_cafe / _maximo_cafe;
	return _porcentagem_cafe;
}

void GarrafaCafeClass::FiltrarRuidoSinalBalanca(float& quantidade_cafe_em_litros)
{
	if (quantidade_cafe_em_litros < 0.0f)
		quantidade_cafe_em_litros = 0.0f;
}

float GarrafaCafeClass::QuantidadeCafeEmMl()
{
	RecalcularPorcentagemCafeNagarrafa();

	auto quantidade_cafe_em_litros = _peso_cafe * FATOR_CONVERSAO_PORCENTAGEM_PARA_ML_CAFE;

	FiltrarRuidoSinalBalanca(quantidade_cafe_em_litros);

	return quantidade_cafe_em_litros;
}

void GarrafaCafeClass::atualizarPesoGarrafaVazia()
{
	auto pesoAtual = Balanca.lerValorDoPeso();
	MemoriaEeprom.gravar(MemoriaEeprom.endereco_garrafa_vazia, pesoAtual);
	_peso_garrafa_vazia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_vazia);

	InterfaceUsuario.imprimirMensagemLCD("GARRAFA VAZIA", 0, true);
	InterfaceUsuario.imprimirMensagemLCD(String(_peso_garrafa_vazia), 1);

	Serial.print("Garrafa vazia: ");
	Serial.println(_peso_garrafa_vazia);
}

void GarrafaCafeClass::atualizarPesoGarrafaCheia()
{
	auto pesoAtual = Balanca.lerValorDoPeso();
	MemoriaEeprom.gravar(MemoriaEeprom.endereco_garrafa_cheia, pesoAtual);
	_peso_garrafa_cheia = MemoriaEeprom.ler(MemoriaEeprom.endereco_garrafa_cheia);

	InterfaceUsuario.imprimirMensagemLCD("GARRAFA CHEIA", 0, true);
	InterfaceUsuario.imprimirMensagemLCD(String(_peso_garrafa_cheia), 1);

	Serial.print("Garrafa cheia: ");
	Serial.println(_peso_garrafa_cheia);
}
