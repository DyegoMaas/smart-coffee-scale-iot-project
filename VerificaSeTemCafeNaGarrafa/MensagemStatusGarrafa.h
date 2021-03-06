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
	 const String stringSituacaoGarrafa[5] = { "SEM GARRAFA", "NIVEL CRITICO", "CAFE ACABANDO", "TEM CAFE", "PEGANDO CAFE" };

	 enum SituacaoGarrafa
	 {
		 GarrafaForaDaBalanca = 0,
		 NivelCriticoCafe = 1,
		 AcabandoCafe = 2,
		 TemCafe = 3,
		 AlguemPegandoCafe = 4
	 };
};

extern MensagemStatusGarrafaClass MensagemStatusGarrafa;

#endif

