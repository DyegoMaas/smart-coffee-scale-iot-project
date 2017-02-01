#include "MemoriaEeprom.h"

float MemoriaEepromClass::ler(Endereco endereco)
{
	byte loByte = EEPROM.read(endereco);
	byte hiByte = EEPROM.read(endereco + 1);

	int valorInt = word(hiByte, loByte);
	float valor = float(valorInt) / 1000.0f;

	Serial.print("EEPROM lido: ");
	Serial.println(valor);

	return valor;
}

double MemoriaEepromClass::lerDouble(Endereco endereco)
{
	double valor = EEPROM.readDouble(endereco);
	Serial.print("EEPROM lido: ");
	Serial.println(valor);

	return valor;
}

bool MemoriaEepromClass::gravar(Endereco endereco, float valor)
{
	int valorInt = int(valor * 1000);

	byte loByte = lowByte(valorInt);
	byte hiByte = highByte(valorInt);

	EEPROM.write(int(endereco), loByte);
	EEPROM.write(int(endereco) + 1, hiByte);

	Serial.print("EEPROM Gravado: ");
	Serial.println(valorInt);
	return true;
}

bool MemoriaEepromClass::gravar(Endereco endereco, double valor)
{
	EEPROM.writeDouble(endereco, valor);
	return true;
}

MemoriaEepromClass MemoriaEeprom;

