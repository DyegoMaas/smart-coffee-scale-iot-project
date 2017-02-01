// MemoriaEeprom.h

#ifndef _MEMORIAEEPROM_h
#define _MEMORIAEEPROM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "EEPROMex.h"
#include "EEPROMVar.h"

class MemoriaEepromClass
{
 protected:
	 

 public:
	 enum Endereco
	 {
		 endereco_garrafa_vazia = 0,
		 endereco_garrafa_cheia = 2,
		 endereco_offset_balanca = 4
	 };
	static float ler(Endereco endereco);
	static double lerDouble(Endereco endereco);
	static bool gravar(Endereco endereco, float valor);
	static bool gravar(Endereco endereco, double valor);

};

extern MemoriaEepromClass MemoriaEeprom;

#endif

