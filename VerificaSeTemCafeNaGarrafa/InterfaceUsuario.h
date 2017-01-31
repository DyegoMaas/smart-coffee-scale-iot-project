// InterfaceUsuario.h

#ifndef _INTERFACEUSUARIO_h
#define _INTERFACEUSUARIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <stdlib.h>
#include <LiquidCrystal.h>
#include "MensagemStatusGarrafa.h"

class InterfaceUsuarioClass
{
	static void criarCaracteresBarraProgresso();
	static void ImprimirBlocosCheios(int linha_lcd, int blocos);
	static void ImprimirUltimoBloco(int linha_lcd, int blocos, int colunasUltimoBloco);
public:
	static void Iniciar();
	static void ImprimirBarraProgresso(int linha_lcd, float porcentagem);
	static void ImprimirBarraProgresso(int linha_lcd, int valor, int valor_minimo, int valor_maximo);
	void ImprimirInterfaceLCDPadrao(float porcentagem_cafe, float mls_cafe, int situacao_garrafa) const;
};

extern InterfaceUsuarioClass InterfaceUsuario;

#endif

