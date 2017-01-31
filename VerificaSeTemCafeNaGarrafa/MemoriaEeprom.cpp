#include "MemoriaEeprom.h"

float MemoriaEepromClass::ler(Endereco endereco)
{
	byte loByte = EEPROM.read(endereco);
	byte hiByte = EEPROM.read(endereco + 1);

	int valorInt = word(hiByte, loByte);
	float valor = float(valorInt) / 100.0f;

	Serial.print("EEPROM lido: ");
	Serial.println(valor);

	return valor;
}

bool MemoriaEepromClass::gravar(Endereco endereco, float valor)
{
	int valorInt = int(valor * 100);

	byte loByte = lowByte(valorInt);
	byte hiByte = highByte(valorInt);

	EEPROM.write(int(endereco), loByte);
	EEPROM.write(int(endereco) + 1, hiByte);

	Serial.print("EEPROM Gravado: ");
	Serial.println(valorInt);
	return true;
}

MemoriaEepromClass MemoriaEeprom;

