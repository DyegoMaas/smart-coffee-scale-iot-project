/*
###################################################################
Verificador de quantidade de cafe na garrafa
-------------------------------------------------------------------
Versao: 0.1 Alpha
Desenvolvedor:  Dyego Mass / Alexandre Alvaro
-------------------------------------------------------------------
HARDWARE
Controlador:		ATMega 328p
Celula de carga:    Balanca de precisao SF-400 (ate 10kg)
Conversor de sinal: Amplificador HX711
-------------------------------------------------------------------
DESCRICAO
Atraves do peso da garrafa de cafe e detectado e sinalizado quando
a quantidade de liquido fica abaixo de um valor pre-definido.
###################################################################
*/

#include "GarrafaCafe.h"

void setup()
{
	auto velocidadeComunicacaoSerial = 115200;
	Serial.begin(velocidadeComunicacaoSerial);
}

void loop()
{
	Serial.print("Peso da garrafa vazia: ");
	Serial.print(GarrafaCafe.getPesoGarrafaVazia());
	Serial.println("kg");

	Serial.print("Peso da garrafa cheia: ");
	Serial.print(GarrafaCafe.getPesoGarrafaCheia());
	Serial.println("kg");

	Serial.print("Peso atual na balanca: ");
	Serial.print(Balanca.lerValorDoPeso());
	Serial.println("kg");

	Serial.print("Quantidade de cafe na garrafa: ");
	Serial.print(GarrafaCafe.QuantidadeCafeEmMl() * 100);
	Serial.println("%");
	Serial.println();

	Serial.print("Situacao da garrafa: ");
	Serial.println(GarrafaCafe.stringSituacaoGarrafa[GarrafaCafe.VerificarSituacaoCafe()]);
	Serial.println("---------------------------------------");
}
