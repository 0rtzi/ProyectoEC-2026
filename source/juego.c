// Curso 2025-2026

/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		// Librería de la NDS
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "juego.h"
#include "sprites.h"

void juego()
{	
	// Definiciones de variables
	int tecla=0;
	ESTADO=MENU;
	ACCION=CARGANDO_FONDO;
	PALETA=PALETA1;

/* Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas */
	//iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);
	//ConfigurarTemporizador(57344, 0x0041); //Temporizador a 64 ticks por segundo.
	ConfigurarTemporizador(61440,0x0041); //Temporizador a 128 ticks por segundo.
	EstablecerVectorInt();
	ConfigurarTeclado(0x400D);
	MostrarMenu();

	// --- CIEMPIÉS (Lado izquierdo) ---
	iprintf("\x1b[2;3H\\ /");
	iprintf("\x1b[3;2H(O.O)");
	iprintf("\x1b[4;2H,( )");
	iprintf("\x1b[5;3H( ),");
	iprintf("\x1b[6;4H( ),");
	iprintf("\x1b[7;5H( ),");
	iprintf("\x1b[8;4H( ),");
	iprintf("\x1b[9;3H( ),");
	iprintf("\x1b[10;2H,( )");
	iprintf("\x1b[11;1H,( )");
	iprintf("\x1b[12;2H,( )");
	iprintf("\x1b[13;3H( ),");
	iprintf("\x1b[14;4H( )");
	iprintf("\x1b[15;4H( )");
	iprintf("\x1b[16;3H( )");
	iprintf("\x1b[17;3H v");

	// --- TÍTULO "CENTI" (Lado derecho superior) ---
	iprintf("\x1b[5;11H ### ### # # ### ###");
	iprintf("\x1b[6;11H #   #   # #  #   # ");
	iprintf("\x1b[7;11H #   ##  ###  #   # ");
	iprintf("\x1b[8;11H #   #   # #  #   # ");
	iprintf("\x1b[9;11H ### ### # #  #  ###");

	// --- TÍTULO "PEDE" (Lado derecho inferior) ---
	iprintf("\x1b[11;13H ### ### ### ###");
	iprintf("\x1b[12;13H # # #   # # #  ");
	iprintf("\x1b[13;13H ### ##  # # ## ");
	iprintf("\x1b[14;13H #   #   # # #  ");
	iprintf("\x1b[15;13H #   ### ### ###");


	while(1)
	{	
		if (ESTADO == MENU){
			if (TeclaDetectada()) {
				tecla = TeclaPulsada();
				//iprintf("\x1b[23;5HSe ha pulsado la tecla: %d", tecla);
				if (tecla == START){ 
					ESTADO=PARTIDA;
					ACCION=CARGANDO_FONDO;
					InicializarVariablesPartida();
				}
			}
			touchRead(&PANT_DAT);
			if (PANT_DAT.px >=50 && PANT_DAT.px <=200 && PANT_DAT.py >=100 && PANT_DAT.py <=180){
				ESTADO=PARTIDA;
				ACCION=CARGANDO_FONDO;
				InicializarVariablesPartida();
			}
		}
		else if (ESTADO==GAMEOVER){
			touchRead(&PANT_DAT);
			//Botón RESTART
			if(PANT_DAT.px>=20 && PANT_DAT.px<=110 && PANT_DAT.py>=120 && PANT_DAT.py<=170){
				ESTADO=PARTIDA;
				ACCION=CARGANDO_FONDO;
				InicializarVariablesPartida();
			}
			//Botón MENU
			if(PANT_DAT.px>=140 && PANT_DAT.px<=230 && PANT_DAT.py>=120 && PANT_DAT.py<=170){
				ESTADO=MENU;
				MostrarMenu();
			}
			//Botón START
			if(TeclaDetectada() && TeclaPulsada()==START){
				ESTADO=PARTIDA;
				ACCION=CARGANDO_FONDO;
				InicializarVariablesPartida();
			}
		}
		else if (ESTADO == PARTIDA){
			switch(ACCION) {
				case CARGANDO_FONDO:
					iprintf("\x1b[22;1H                                ");
					PonerEnMarchaTempo();
					visualizarFondoPrueba();
					ACCION = CARGANDO_PROTA;
					break;
				
				case CARGANDO_PROTA:
					InicializarValoresProta();
					ACCION = CARGANDO_SETAS;
					break;

				case CARGANDO_SETAS:
					HabilitarIntTempo();
					InicializarValoresSetas();
					ACCION = CARGANDO_ENEMIGOS;
					break;
					
				case CARGANDO_ENEMIGOS:
					InicializarValoresCiempies();
					ACCION=JUEGO;
					HabilitarIntTecla(A);
					break;
				
				case JUEGO:

					break;

				case MUERTE:
					ACCION=LIMPIANDO_PANTALLA;
					prota.X=CENTRO_HORIZONTAL;
					prota.Y=CENTRO_VERTICAL_PROTA;
					break;

				case ENEMIGOS_MUERTOS:
					ACCION=LIMPIANDO_PANTALLA;
					CambiarPaleta();
					prota.nivel++;
					break;

				case LIMPIANDO_PANTALLA:
					//Pause temporario
					InhibirIntTempo();

					//Limpia los sprites y arrays
					LimpiarPantalla();

					if (prota.vidas>0){
						ACCION=CARGANDO_FONDO;
					}
					else {
						ESTADO=GAMEOVER;
						iprintf("\x1b[22;1H                                ");
						MostrarGameOver();
					}
					break;
			}
		}
	}
	DeshabilitarInterrupciones();
}

void MostrarMenu(){
	
	HabilitarIntTeclado();
	HabilitarIntTempo();
	HabilitarInterrupciones();
	visualizarFondoMenu();
}

void MostrarGameOver(){
	InhibirIntTecla(A);
	HabilitarIntTeclado();
	HabilitarIntTempo();
	HabilitarInterrupciones();
	contador_tiempo_gameover=0;
	visualizarGameOver();
}

/***********************2025-2026*******************************/


