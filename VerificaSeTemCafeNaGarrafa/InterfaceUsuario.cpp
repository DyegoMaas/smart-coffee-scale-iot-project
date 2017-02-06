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
const unsigned long tempoSilenciamento = 600000; //600.000 ms = 10 minutos


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
		momentoAlarmeSilenciadoAte = millis();
		Serial.print("Agora: ");
		Serial.println(momentoAlarmeSilenciadoAte);

		momentoAlarmeSilenciadoAte += tempoSilenciamento;
		Serial.print("Alarme silenciado ate: ");
		Serial.println(momentoAlarmeSilenciadoAte);

		silenciaAlarme = true;
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
		checarBotoesPararAlarme();
		digitalWrite(PINO_LED_STATUS, piscaLed == 5);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, piscaLed == 5);
	}
	else if (situacao_garrafa == MensagemStatusGarrafa.NivelCriticoCafe)
	{
		checarBotoesPararAlarme();
		digitalWrite(PINO_LED_STATUS, piscaLed % 2);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, piscaLed % 2);
	}
	else if (situacao_garrafa == MensagemStatusGarrafa.GarrafaForaDaBalanca)
	{
		checarBotoesPararAlarme();
		digitalWrite(PINO_LED_STATUS, HIGH);
		if (!silenciaAlarme)
			digitalWrite(PINO_BUZZER, HIGH);
	}
	else
	{
		silenciaAlarme = false;
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
}

void InterfaceUsuarioClass::imprimirMensagemLCD(String mensagem, int linha, bool clear)
{
	if (clear) lcd.clear();
	lcd.setCursor(0, linha);
	lcd.print(mensagem);
}

InterfaceUsuarioClass InterfaceUsuario;
