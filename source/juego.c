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
	HabilitarInterrupcionesComunes();
	MostrarMenu();
	MostrarASCIIArt();


	while(1)
	{	
		switch (ESTADO){
			case MENU:
			if (timer_pTactil_gameover > 0) break;
			if (touchRead(&PANT_DAT) && PANT_DAT.px >=40 && PANT_DAT.px <=235 && PANT_DAT.py >=110 && PANT_DAT.py <=180){
				IniciarPartida();
			}
			break;

			case PARTIDA:	
			switch(ACCION) {
				case CARGANDO_FONDO:
				VisualizarFondoPrueba();
				ACCION = CARGANDO_PROTA;
				break;
				
				case CARGANDO_PROTA:
				InicializarValoresProta();
				ACCION = CARGANDO_SETAS;
				break;

				case CARGANDO_SETAS:
				InicializarValoresSetas();
				ACCION = CARGANDO_ENEMIGOS;
				break;
					
				case CARGANDO_ENEMIGOS:
				InicializarValoresCiempies();
				HabilitarIntTecla(A);
				iprintf("\x1b[22;4HVIDAS: x%d", prota.vidas);
				iprintf("\x1b[22;17HPUNTOS: %d", prota.puntos);
				ACCION=JUEGO;
				break;
				
				case JUEGO:
					break;

				case MUERTE:
				break;

				case ENEMIGOS_MUERTOS:
				CambiarPaleta();
				prota.nivel++;
				ACCION=LIMPIANDO_PANTALLA;
				break;

				case LIMPIANDO_PANTALLA:
				LimpiarPantalla();

				if (prota.vidas>0){
					ACCION=CARGANDO_FONDO;
				}
				else {
					iprintf("\x1b[22;1H                                ");
					iprintf("\x1b[22;8HPUNTUACION: %d", prota.puntos);
					MostrarGameOver();
					ESTADO=GAMEOVER;
				}
				break;
			}
			break;

			case GAMEOVER:
			//Botón RESTART
			if(touchRead(&PANT_DAT) && PANT_DAT.px>=20 && PANT_DAT.px<=110 && PANT_DAT.py>=120 && PANT_DAT.py<=170){
				IniciarPartida();
			}
			//Botón MENU
			if(touchRead(&PANT_DAT) && PANT_DAT.px>=140 && PANT_DAT.px<=230 && PANT_DAT.py>=120 && PANT_DAT.py<=170){
				MostrarMenu();
				timer_pTactil_gameover = 256;
				ESTADO=MENU;
			}				
			break;
		}
	}
	DeshabilitarInterrupciones();
}

void MostrarMenu(){
	iprintf("\x1b[22;1H                                ");
	VisualizarFondoMenu();
}

void MostrarGameOver(){
	InhibirIntTecla(A);
	contador_tiempo_gameover=0;
	VisualizarGameOver();
}

void IniciarPartida(){
	InicializarVariablesPartida();
	ESTADO=PARTIDA;
	ACCION=CARGANDO_FONDO;
}

void MostrarASCIIArt(){
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
}

/***********************2025-2026*******************************/


