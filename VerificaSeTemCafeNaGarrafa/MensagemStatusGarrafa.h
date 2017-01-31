// MensagemStatusGarrafa.h

#ifndef _MENSAGEMSTATUSGARRAFA_h
#define _MENSAGEMSTATUSGARRAFA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MensagemStatusGarrafaClass
{
 protected:


 public:
	 const String stringSituacaoGarrafa[5] = { "Sem Garrafa", "Pegando cafe", "Nivel Critico", "Cafe acabando", "Tem cafe" };

	 enum SituacaoGarrafa
	 {
		 GarrafaForaDaBalanca = 0,
		 AlguemPegandoCafe = 1,
		 NivelCriticoCafe = 2,
		 AcabandoCafe = 3,
		 TemCafe = 4

	 };
};

extern MensagemStatusGarrafaClass MensagemStatusGarrafa;

#endif

