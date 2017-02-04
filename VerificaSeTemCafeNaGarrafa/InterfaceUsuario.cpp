#include "InterfaceUsuario.h"

LiquidCrystal lcd = LiquidCrystal(12, 11, 5, 4, 3, 2);
byte blocoBarra1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 };
byte blocoBarra2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 };
byte blocoBarra3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C };
byte blocoBarra4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E };
byte blocoBarra5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

int piscaLed = 0;
bool silenciaAlarme = true;
unsigned long momentoAlarmeSilenciadoAte;

void InterfaceUsuarioClass::iniciar()
{
	lcd.begin(20, 4);
	lcd.setCursor(0, 0);
	pinMode(PINO_LED_STATUS, OUTPUT);

	lcd.print("INICIANDO");
	for (auto i = 0; i <= 10; i++) {
		delay(100);
		lcd.print(".");
	}
}

void InterfaceUsuarioClass::criarCaracteresBarraProgresso()
{
	lcd.createChar(1, blocoBarra1);
	lcd.createChar(2, blocoBarra2);
	lcd.createChar(3, blocoBarra3);
	lcd.createChar(4, blocoBarra4);
	lcd.createChar(5, blocoBarra5);
}

void InterfaceUsuarioClass::imprimirBlocosCheios(int linha_lcd, int blocos)
{
	if (blocos > 0) {
		for (auto bloco = 0; bloco < blocos; bloco++)
		{
			lcd.setCursor(bloco, linha_lcd);
			lcd.write(5);
		}
	}
}

void InterfaceUsuarioClass::imprimirUltimoBloco(int linha_lcd, int blocos, int colunasUltimoBloco)
{
	auto ultimoBloco = blocos;
	lcd.setCursor(ultimoBloco, linha_lcd);
	if (colunasUltimoBloco > 0)
	{
		lcd.write(colunasUltimoBloco);
	}
}

void InterfaceUsuarioClass::imprimirBarraProgresso(int linha_lcd, float porcentagem)
{
	criarCaracteresBarraProgresso();
	int porcentagemSemVirgula = porcentagem * 100;
	int blocos = map(porcentagemSemVirgula, 0, 100, 0, 20);
	int linha = map(porcentagemSemVirgula, 0, 100, 0, 80);
	auto colunasUltimoBloco = (linha - (blocos * 5));

	imprimirBlocosCheios(linha_lcd, blocos);
	imprimirUltimoBloco(linha_lcd, blocos, colunasUltimoBloco);
}

void InterfaceUsuarioClass::imprimirBarraProgresso(int linha_lcd, int valor, int valor_minimo, int valor_maximo)
{
	criarCaracteresBarraProgresso();
	int blocos = map(valor, valor_minimo, valor_maximo, 0, 20);
	int linha = map(valor, valor_minimo, valor_maximo, 0, 80);
	auto colunasUltimoBloco = (linha - (blocos * 5));

	imprimirBlocosCheios(linha_lcd, blocos);
	imprimirUltimoBloco(linha_lcd, blocos, colunasUltimoBloco);
}

void checarBotoesPararAlarme()
{
	auto botaoCalibrarBalanca = digitalRead(PINO_IO_CALIBRACAO_BALANCA);
	auto botaoCalibrarGarrafaVazia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_VAZIA);
	auto botaoCalibrarGarrafaCheia = digitalRead(PINO_IO_CALIBRACAO_GARRAFA_CHEIA);

	auto algumBotaoPressionado = botaoCalibrarBalanca == BOTAO_PRESSIONADO ||
		botaoCalibrarGarrafaVazia == BOTAO_PRESSIONADO ||
		botaoCalibrarGarrafaCheia == BOTAO_PRESSIONADO;

	if (algumBotaoPressionado)
	{
		momentoAlarmeSilenciadoAte = millis() + (500 * 60);
		silenciaAlarme = true;
		Serial.print("Alarme silenciado ate: ");
		Serial.println(momentoAlarmeSilenciadoAte);
	}

	if (millis() > momentoAlarmeSilenciadoAte)
	{
		silenciaAlarme = false;
	};

	if (silenciaAlarme)
	{
		Serial.print("millis: ");
		Serial.print(millis());
		Serial.print(" / ");
		Serial.println(momentoAlarmeSilenciadoAte);
	}
}

void InterfaceUsuarioClass::imprimirInterfaceLCDPadrao(float porcentagem_cafe, float litros_cafe, int situacao_garrafa) const
{
	if (porcentagem_cafe > 1.0f)
	{
		porcentagem_cafe = 1.0f;
	}
	if (porcentagem_cafe < 0.0f)
	{
		porcentagem_cafe = 0.0f;
	}

	lcd.clear();
	lcd.setCursor(0, 0);
	auto str = MensagemStatusGarrafa.stringSituacaoGarrafa[situacao_garrafa];
	auto situacaoGarrafa = str.c_str();
	lcd.print(situacaoGarrafa);


	if (situacao_garrafa == MensagemStatusGarrafa.AcabandoCafe)
	{
		digitalWrite(PINO_LED_STATUS, piscaLed == 5);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, piscaLed == 5);
	}
	else if (situacao_garrafa == MensagemStatusGarrafa.NivelCriticoCafe)
	{
		digitalWrite(PINO_LED_STATUS, piscaLed % 2);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, piscaLed % 2);
	}
	else if (situacao_garrafa == MensagemStatusGarrafa.GarrafaForaDaBalanca)
	{
		digitalWrite(PINO_LED_STATUS, HIGH);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, HIGH);
	}
	else
	{
		digitalWrite(PINO_LED_STATUS, LOW);
		digitalWrite(PINO_BUZZER, LOW);
	}

	if (silenciaAlarme)
	{
		digitalWrite(PINO_BUZZER, LOW);
		lcd.setCursor(0, 2);
		long tempoRestante = momentoAlarmeSilenciadoAte - millis();
		long segundosRestantes = tempoRestante < 1 ? 0 : (momentoAlarmeSilenciadoAte - millis()) / 1000;
		lcd.print("SILENCIADO (");
		lcd.print(segundosRestantes);
		lcd.print(")");
	}
	else {
		if (situacao_garrafa != MensagemStatusGarrafa.AlguemPegandoCafe &&
			situacao_garrafa != MensagemStatusGarrafa.GarrafaForaDaBalanca) {
			lcd.setCursor(0, 2);
			if (litros_cafe >= 1) {
				lcd.print(litros_cafe, 2);
				lcd.print(" L");
			}
			else
			{
				lcd.print(litros_cafe * 1000, 0);
				lcd.print(" mL");
			}
			lcd.print(" (");
			lcd.print(porcentagem_cafe * 100, 0);
			lcd.print(" %)");

			imprimirBarraProgresso(3, porcentagem_cafe);
		}
	}
	if (piscaLed > 6)
	{
		piscaLed = 0;
	}
	else
	{
		piscaLed++;
	}
	checarBotoesPararAlarme();
}

void InterfaceUsuarioClass::imprimirMensagemLCD(String mensagem, int linha, bool clear)
{
	if (clear) lcd.clear();
	lcd.setCursor(0, linha);
	lcd.print(mensagem);
}

byte mario11[8] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B00001,
	B00001,
	B00001,
	B00000,

};
byte mario12[8] = {
	B00001,
	B00001,
	B00001,
	B00001,
	B00000,
	B00000,
	B00000,
	B00000
};
byte mario13[8] = {
	B00000,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,

};
byte mario14[8] = {
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11110
};

byte mario15[8] = {
	B00000,
	B00000,
	B11000,
	B00000,
	B11000,
	B11100,
	B11000,
	B10000,

};

byte mario16[8] = {
	B00000,
	B10000,
	B10000,
	B10000,
	B00000,
	B00000,
	B10000,
	B00000
};

byte mario21[8] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
};

byte mario22[8] = {
	B00111,
	B00111,
	B00111,
	B00000,
	B00001,
	B00011,
	B00011,
	B00001
};

byte mario23[8] = {
	B00000,
	B01111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B01111,

};

byte mario24[8] = {
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11001,
	B00000,
	B10000
};
byte mario25[8] = {
	B00000,
	B00000,
	B11100,
	B10000,
	B11100,
	B11110,
	B11100,
	B11000,

};

byte mario26[8] = {
	B11111,
	B11111,
	B10110,
	B11110,
	B11110,
	B11110,
	B00000,
	B00000,
};

byte mario31[8] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,

};


byte mario32[8] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B00011,
	B00011,
	B00111,
	B00000
};


byte mario33[8] = {
	B00000,
	B00000,
	B00111,
	B01111,
	B01111,
	B11111,
	B11111,
	B11111,

};

byte mario34[8] = {
	B01111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B00111,
	B00111
};

byte mario35[8] = {
	B00000,
	B00000,
	B10000,
	B11110,
	B11000,
	B11110,
	B11111,
	B11110,

};

byte mario36[8] = {
	B11100,
	B11110,
	B11100,
	B11000,
	B11000,
	B10000,
	B00000,
	B10000,
};

byte mario41[8] = {
	B00000,
	B00011,
	B00111,
	B00111,
	B01111,
	B01111,
	B01111,
	B00011,

};


byte mario42[8] = {
	B01111,
	B01111,
	B01111,
	B01111,
	B00111,
	B00011,
	B00011,
	B00011
};

byte mario43[8] = {
	B00000,
	B11000,
	B11111,
	B11100,
	B11111,
	B11111,
	B11111,
	B11110,
};

byte mario44[8] = {
	B11100,
	B11110,
	B11110,
	B11110,
	B11100,
	B11100,
	B11110,
	B10000
};


byte mario51[8] = {
	B00000,
	B00001,
	B00011,
	B00011,
	B00111,
	B00111,
	B00111,
	B00001,
};

byte mario52[8] = {
	B11111,
	B11111,
	B11011,
	B00111,
	B01111,
	B11111,
	B11100,
	B01110,
};

byte mario53[8] = {
	B00000,
	B11100,
	B11111,
	B11110,
	B11111,
	B11111,
	B11111,
	B11111,
};

byte mario54[8] = {
	B11111,
	B11111,
	B11110,
	B11111,
	B11111,
	B01111,
	B00000,
	B00000,
};



byte mario55[8] = {
	B00000,
	B00000,
	B10000,
	B00000,
	B00000,
	B10000,
	B00000,
	B00000,
};


byte mario56[8] = {
	B11000,
	B11000,
	B10000,
	B10000,
	B10000,
	B10000,
	B00000,
	B00000,
};


byte mario61[8] = {
	B00000,
	B00000,
	B00000,
	B00001,
	B00001,
	B00011,
	B00011,
	B00011,
};

byte mario62[8] = {
	B00001,
	B00011,
	B00111,
	B01111,
	B01111,
	B11111,
	B11000,
	B00000,
};



byte mario63[8] = {
	B00000,
	B00000,
	B11110,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
};

byte mario64[8] = {
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11110,
	B11100,
	B11110,
};

byte mario65[8] = {
	B00000,
	B00000,
	B00000,
	B10000,
	B00000,
	B10000,
	B11000,
	B10000,
};


byte mario66[8] = {
	B00000,
	B10000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
};

byte clean[8] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
	B00000,
};

void InterfaceUsuarioClass::mostrarMario()
{
	int framesSegundo = 30;
	int tempoDelay = 1000 / framesSegundo;
	lcd.clear();
	for (int a = 0; a < 17; a++)
	{
		int b = a + 1;
		int c = a + 2;
		int d = a + 3;
		//int e = a + 4;

		lcd.createChar(1, mario11);
		lcd.createChar(2, mario12);
		lcd.createChar(3, mario13);
		lcd.createChar(4, mario14);
		lcd.createChar(5, mario15);
		lcd.createChar(6, mario16);
		lcd.createChar(7, clean);

		lcd.setCursor(a, 2);
		lcd.write(1);
		lcd.setCursor(a, 3);
		lcd.write(2);
		lcd.setCursor(b, 2);
		lcd.write(3);
		lcd.setCursor(b, 3);
		lcd.write(4);
		lcd.setCursor(c, 2);
		lcd.write(5);
		lcd.setCursor(c, 3);
		lcd.write(6);
		delay(tempoDelay);

		lcd.createChar(1, mario21);
		lcd.createChar(2, mario22);
		lcd.createChar(3, mario23);
		lcd.createChar(4, mario24);
		lcd.createChar(5, mario25);
		lcd.createChar(6, mario26);

		lcd.setCursor(a, 2);
		lcd.write(1);
		lcd.setCursor(a, 3);
		lcd.write(2);
		lcd.setCursor(b, 2);
		lcd.write(3);
		lcd.setCursor(b, 3);
		lcd.write(4);
		lcd.setCursor(c, 2);
		lcd.write(5);
		lcd.setCursor(c, 3);
		lcd.write(6);

		delay(tempoDelay);

		lcd.createChar(1, mario31);
		lcd.createChar(2, mario32);
		lcd.createChar(3, mario33);
		lcd.createChar(4, mario34);
		lcd.createChar(5, mario35);
		lcd.createChar(6, mario36);

		lcd.setCursor(a, 2);
		lcd.write(1);
		lcd.setCursor(a, 3);
		lcd.write(2);
		lcd.setCursor(b, 2);
		lcd.write(3);
		lcd.setCursor(b, 3);
		lcd.write(4);
		lcd.setCursor(c, 2);
		lcd.write(5);
		lcd.setCursor(c, 3);
		lcd.write(6);

		delay(tempoDelay);

		lcd.createChar(1, mario41);
		lcd.createChar(2, mario42);
		lcd.createChar(3, mario43);
		lcd.createChar(4, mario44);
		lcd.createChar(7, clean);
		lcd.setCursor(a, 2);
		lcd.write(7);
		lcd.setCursor(a, 3);
		lcd.write(7);
		lcd.setCursor(b, 2);
		lcd.write(1);
		lcd.setCursor(b, 3);
		lcd.write(2);
		lcd.setCursor(c, 2);
		lcd.write(3);
		lcd.setCursor(c, 3);
		lcd.write(4);

		delay(tempoDelay);

		lcd.createChar(1, mario51);
		lcd.createChar(2, mario52);
		lcd.createChar(3, mario53);
		lcd.createChar(4, mario54);
		lcd.createChar(5, mario55);
		lcd.createChar(6, mario56);
		lcd.createChar(7, clean);
		lcd.setCursor(a, 2);
		lcd.write(7);
		lcd.setCursor(a, 3);
		lcd.write(7);
		lcd.setCursor(b, 2);
		lcd.write(1);
		lcd.setCursor(b, 3);
		lcd.write(2);
		lcd.setCursor(c, 2);
		lcd.write(3);
		lcd.setCursor(c, 3);
		lcd.write(4);
		lcd.setCursor(d, 2);
		lcd.write(5);
		lcd.setCursor(d, 3);
		lcd.write(6);

		delay(tempoDelay);

		lcd.createChar(1, mario61);
		lcd.createChar(2, mario62);
		lcd.createChar(3, mario63);
		lcd.createChar(4, mario64);
		lcd.createChar(5, mario65);
		lcd.createChar(6, mario66);
		lcd.setCursor(b, 2);
		lcd.write(1);
		lcd.setCursor(b, 3);
		lcd.write(2);
		lcd.setCursor(c, 2);
		lcd.write(3);
		lcd.setCursor(c, 3);
		lcd.write(4);
		lcd.setCursor(d, 2);
		lcd.write(5);
		lcd.setCursor(d, 3);
		lcd.write(6);

		delay(tempoDelay);
	}
}

InterfaceUsuarioClass InterfaceUsuario;
