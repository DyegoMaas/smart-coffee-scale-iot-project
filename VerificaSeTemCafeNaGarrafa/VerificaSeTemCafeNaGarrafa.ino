/*
###################################################################
Verificador de quantidade de café na garrafa
-------------------------------------------------------------------
Versão: 0.1 Alpha
Desenvolvedor:  Dyego Mass / Alexandre Alvaro
-------------------------------------------------------------------
HARDWARE
Controlador:		ATMega 328p
Célula de carga:    Balança de precisão SF-400 (até 10kg)
Conversor de sinal: Amplificador HX711
-------------------------------------------------------------------
DESCRIÇÃO
Através do peso da garrafa de café é detectado e sinalizado quando
a quantidade de líquido fica abaixo de um valor pré-definido.
###################################################################
*/

#include "Balanca.h"
Balanca balanca;

void setup() {
	Serial.begin(115200);
	balanca.parametros(2, 3, 35600.f, 1000);
	balanca.inicializar();
}

void loop() {
	float peso = balanca.lerValorDoPeso();
	Serial.print("Peso: ");
	Serial.print(peso);
	Serial.println("kg");
}

