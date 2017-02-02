#include "Buzzer.h"

#define NOTA_B0  31
#define NOTA_C1  33
#define NOTA_CS1 35
#define NOTA_D1  37
#define NOTA_DS1 39
#define NOTA_E1  41
#define NOTA_F1  44
#define NOTA_FS1 46
#define NOTA_G1  49
#define NOTA_GS1 52
#define NOTA_A1  55
#define NOTA_AS1 58
#define NOTA_B1  62
#define NOTA_C2  65
#define NOTA_CS2 69
#define NOTA_D2  73
#define NOTA_DS2 78
#define NOTA_E2  82
#define NOTA_F2  87
#define NOTA_FS2 93
#define NOTA_G2  98
#define NOTA_GS2 104
#define NOTA_A2  110
#define NOTA_AS2 117
#define NOTA_B2  123
#define NOTA_C3  131
#define NOTA_CS3 139
#define NOTA_D3  147
#define NOTA_DS3 156
#define NOTA_E3  165
#define NOTA_F3  175
#define NOTA_FS3 185
#define NOTA_G3  196
#define NOTA_GS3 208
#define NOTA_A3  220
#define NOTA_AS3 233
#define NOTA_B3  247
#define NOTA_C4  262
#define NOTA_CS4 277
#define NOTA_D4  294
#define NOTA_DS4 311
#define NOTA_E4  330
#define NOTA_F4  349
#define NOTA_FS4 370
#define NOTA_G4  392
#define NOTA_GS4 415
#define NOTA_A4  440
#define NOTA_AS4 466
#define NOTA_B4  494
#define NOTA_C5  523
#define NOTA_CS5 554
#define NOTA_D5  587
#define NOTA_DS5 622
#define NOTA_E5  659
#define NOTA_F5  698
#define NOTA_FS5 740
#define NOTA_G5  784
#define NOTA_GS5 831
#define NOTA_A5  880
#define NOTA_AS5 932
#define NOTA_B5  988
#define NOTA_C6  1047
#define NOTA_CS6 1109
#define NOTA_D6  1175
#define NOTA_DS6 1245
#define NOTA_E6  1319
#define NOTA_F6  1397
#define NOTA_FS6 1480
#define NOTA_G6  1568
#define NOTA_GS6 1661
#define NOTA_A6  1760
#define NOTA_AS6 1865
#define NOTA_B6  1976
#define NOTA_C7  2093
#define NOTA_CS7 2217
#define NOTA_D7  2349
#define NOTA_DS7 2489
#define NOTA_E7  2637
#define NOTA_F7  2794
#define NOTA_FS7 2960
#define NOTA_G7  3136
#define NOTA_GS7 3322
#define NOTA_A7  3520
#define NOTA_AS7 3729
#define NOTA_B7  3951
#define NOTA_C8  4186
#define NOTA_CS8 4435
#define NOTA_D8  4699
#define NOTA_DS8 4978

//Tema principal Mario
int tema_mario[] = {
	NOTA_E7, NOTA_E7, 0, NOTA_E7,
	0, NOTA_C7, NOTA_E7, 0,
	NOTA_G7, 0, 0,  0,
	NOTA_G6, 0, 0, 0,

	NOTA_C7, 0, 0, NOTA_G6,
	0, 0, NOTA_E6, 0,
	0, NOTA_A6, 0, NOTA_B6,
	0, NOTA_AS6, NOTA_A6, 0,

	NOTA_G6, NOTA_E7, NOTA_G7,
	NOTA_A7, 0, NOTA_F7, NOTA_G7,
	0, NOTA_E7, 0, NOTA_C7,
	NOTA_D7, NOTA_B6, 0, 0,

	NOTA_C7, 0, 0, NOTA_G6,
	0, 0, NOTA_E6, 0,
	0, NOTA_A6, 0, NOTA_B6,
	0, NOTA_AS6, NOTA_A6, 0,

	NOTA_G6, NOTA_E7, NOTA_G7,
	NOTA_A7, 0, NOTA_F7, NOTA_G7,
	0, NOTA_E7, 0, NOTA_C7,
	NOTA_D7, NOTA_B6, 0, 0
};

//Tempos Mario
int tempos_tema_mario[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

//Melodia Underworld
int tema_underworld[] = {
	NOTA_C4, NOTA_C5, NOTA_A3, NOTA_A4,
	NOTA_AS3, NOTA_AS4, 0,
	0,
	NOTA_C4, NOTA_C5, NOTA_A3, NOTA_A4,
	NOTA_AS3, NOTA_AS4, 0,
	0,
	NOTA_F3, NOTA_F4, NOTA_D3, NOTA_D4,
	NOTA_DS3, NOTA_DS4, 0,
	0,
	NOTA_F3, NOTA_F4, NOTA_D3, NOTA_D4,
	NOTA_DS3, NOTA_DS4, 0,
	0, NOTA_DS4, NOTA_CS4, NOTA_D4,
	NOTA_CS4, NOTA_DS4,
	NOTA_DS4, NOTA_GS3,
	NOTA_G3, NOTA_CS4,
	NOTA_C4, NOTA_FS4, NOTA_F4, NOTA_E3, NOTA_AS4, NOTA_A4,
	NOTA_GS4, NOTA_DS4, NOTA_B3,
	NOTA_AS3, NOTA_A3, NOTA_GS3,
	0, 0, 0
};

//Tempos Underworld
int tempos_tema_underworld[] = {
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	6, 18, 18, 18,
	6, 6,
	6, 6,
	6, 6,
	18, 18, 18, 18, 18, 18,
	10, 10, 10,
	10, 10, 10,
	3, 3, 3
};

bool checarBotoesParaInterromper()
{
	auto botaoCalibrarBalanca = digitalRead(PINO_IO_CALIBRACAO_BALANCA);
	auto botaoCalibrarGarrafaVazia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_VAZIA);
	auto botaoCalibrarGarrafaCheia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_CHEIA);

	auto algumBotaoPressionado = botaoCalibrarBalanca == BOTAO_PRESSIONADO ||
		botaoCalibrarGarrafaVazia == BOTAO_PRESSIONADO ||
		botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO;

	return algumBotaoPressionado;
}

BuzzerClass::BuzzerClass()
{
	pinMode(PINO_BUZZER, OUTPUT);
}

void executarMusica(String nome_musica, int notas[], int tempos[], int quantidadeNotas);

void BuzzerClass::tocarMelodia(int musica) {
	int quantidadeNotas;
	switch(musica)
	{
	case 2:
		quantidadeNotas = sizeof(tema_underworld) / sizeof(int);
		executarMusica(" 'Tema Mario Underworld'", tema_underworld, tempos_tema_underworld, quantidadeNotas);

		break;
	default:
		quantidadeNotas = sizeof(tema_mario) / sizeof(int);
		executarMusica(" 'Tema Principal Mario'", tema_mario, tempos_tema_mario, quantidadeNotas);
	}
}

void executarMusica(String nome_musica, int notas[], int tempos[], int quantidadeNotas)
{
	Serial.println(nome_musica);
	Serial.print("Tamanho musica:");
	Serial.println(quantidadeNotas);
	for (int estaNota = 0; estaNota < quantidadeNotas; estaNota++) {
		
		if(estaNota > 6 && checarBotoesParaInterromper()){break;}
		int duracaoNota = 1000 / tempos[estaNota];

		Buzzer.buzz(PINO_BUZZER, notas[estaNota], duracaoNota);

		int pausaEntreNotas = duracaoNota * 1.30;
		delay(pausaEntreNotas);

		Buzzer.buzz(PINO_BUZZER, 0, duracaoNota);
	}
}

void BuzzerClass::buzz(int targetPin, long frequency, long length) {
	long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
											   //// 1 second's worth of microseconds, divided by the frequency, then split in half since
											   //// there are two phases to each cycle
	long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
												//// multiply frequency, which is really cycles per second, by the number of seconds to
												//// get the total number of cycles to produce
	for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
		digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
		delayMicroseconds(delayValue); // wait for the calculated delay value
		digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
		delayMicroseconds(delayValue); // wait again or the calculated delay value
	}
}

BuzzerClass Buzzer;

