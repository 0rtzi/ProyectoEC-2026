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

void juego()
{	
	// Definiciones de variables
	int tecla=0;
	ESTADO=PARTIDA;
	ACCION=JUEGO;

/* Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas */
	//iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);

	ConfigurarTeclado(0x4009);
	//ConfigurarTemporizador(57344, 0x0041); //Temporizador a 64 ticks por segundo.
	ConfigurarTemporizador(61440,0x0041); //Temporizador a 128 ticks por segundo.
	EstablecerVectorInt();
	HabilitarIntTeclado();
	HabilitarIntTempo();
	HabilitarInterrupciones();
	PonerEnMarchaTempo();

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
				iprintf("\x1b[23;5HSe ha pulsado la tecla: %d", tecla);
				if (tecla == A){ 
					ESTADO = PARTIDA;
				}
			}
		}
		else if (ESTADO == PARTIDA){
			switch(ACCION) {
				case CARGANDO_FONDO:
					InhibirIntTeclado();
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
					HabilitarIntTeclado();
					break;
				
				case JUEGO:

					break;

				case MUERTE:
					ACCION=LIMPIANDO_PANTALLA;
					break;

				case LIMPIANDO_PANTALLA:
					//Pause temporario
					InhibirIntTempo();
					//Limpia los sprites y arrays
					LimpiarPantalla();
					break;
			}
		}
		else if (ESTADO == GAMEOVER){
			tecla = TeclaPulsada();
			if(tecla == START){
				ESTADO = MENU;
				visualizarFondoPrueba();
			}
		}
	}
	DeshabilitarInterrupciones();
}

/***********************2025-2026*******************************/


