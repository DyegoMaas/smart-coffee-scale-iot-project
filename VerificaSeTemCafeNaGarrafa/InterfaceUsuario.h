#ifndef _INTERFACEUSUARIO_h
#define _INTERFACEUSUARIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Atmega328p.h"
#include <stdlib.h>
#include <LiquidCrystal.h>
#include "MensagemStatusGarrafa.h"
#include "Mario.h"

class InterfaceUsuarioClass
{
	static void criarCaracteresBarraProgresso();
	static void imprimirBlocosCheios(int linha_lcd, int blocos);
	static void imprimirUltimoBloco(int linha_lcd, int blocos, int colunasUltimoBloco);
public:
	static void iniciar();
	static void imprimirBarraProgresso(int linha_lcd, float porcentagem);
	static void imprimirBarraProgresso(int linha_lcd, int valor, int valor_minimo, int valor_maximo);
	void imprimirInterfaceLCDPadrao(float porcentagem_cafe, float litros_cafe, int situacao_garrafa) const;
	static void imprimirMensagemLCD(String mensagem, int linha, bool clear = false);
	static void mostrarMario();
};

extern InterfaceUsuarioClass InterfaceUsuario;

#endif

