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

int tiempo;

void juego()
{	
	// Definiciones de variables
	//int i=9;
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


	while(1)
	{	
		if (ESTADO == MENU){
			if (TeclaDetectada()) {
				tecla = TeclaPulsada();
				iprintf("\x1b[23;5HSe ha pulsado la tecla: %d", tecla);
				if (tecla == A){
					ESTADO = PARTIDA;
					visualizarFondoPrueba();
				}
			}
		}
		else if (ESTADO == PARTIDA){
			switch(ACCION) {
				case CARGANDO_FONDO:
					visualizarFondoPrueba();
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
					ACCION=JUEGO;
					HabilitarIntTeclado();
					break;
				
				case JUEGO:

					break;

				case PAUSA:

					break;

				case LIMPIANDO_PANTALLA:

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
	DeshabilitarInterrrupciones();
}

/***********************2025-2026*******************************/


