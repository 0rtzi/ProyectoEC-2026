// Curso 2025-2026

/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"
#include "juego.h"

//Definición de variables globales.
int ESTADO; // Para controlar el estado del autómata en que esté
int tick = 0;
static unsigned int semilla_interna = 12345;

int randomInt(int min, int max) {
	semilla_interna = semilla_interna * 1103515245 + 12345;

	unsigned int numAleatorio = (semilla_interna / 65536) % 32768;
    int dif = max-min+1;
    return min+ (numAleatorio % dif);
}


	//PROTA
struct protagonista prota;
int prota_cont_espera_mov = 0;
int prota_cont_espera_mov_min = 1;
int prota_pixel_mov = 2;

void InicializarValoresProta(){
	prota.vidas=3;
	prota.X=128;
	prota.Y=160;
	prota.puntos=0;
	prota_cont_espera_mov = 0;

	MostrarProta(0, prota.X, prota.Y);
}

// Actualiza la posición del protagonista
void ActualizarPosicionProta() {
	if (TeclaDetectada()){
		prota_cont_espera_mov=0;
		int tecla = TeclaPulsada();
		if (tecla==ARRIBA){
			if (prota.Y>144){
				BorrarProta(0, prota.X, prota.Y);
				prota.Y-=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (tecla==ABAJO){
			if (prota.Y<176){
				BorrarProta(0, prota.X, prota.Y);
				prota.Y+=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (tecla==IZQUIERDA){
			if (prota.X>0){
				BorrarProta(0, prota.X, prota.Y);
				prota.X-=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (tecla==DERECHA){
			if (prota.X<240){
				BorrarProta(0, prota.X, prota.Y);
				prota.X+=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		
		//iprintf("\x1b[23;5HX: %d  Y: %d",prota.X, prota.Y);
	}
    
}

	// SETAS
int matriz_setas[12][16];

int seta_cont_espera_mostrar = 0;
int seta_cont_espera_mostrar_max = 32; //4 veces por segundo aparece una seta

void InicializarValoresSetas() {
	int ultNumAsig=2;
	int i;
	for (i=0; i<9; i++){
		int j;
		for (j=0; j<16; j++){
			if (randomInt(0,7)==0){
				matriz_setas[i][j]=4;
				MostrarChampi(ultNumAsig,j*16,i*16);
				ultNumAsig++;
			}
			
		}
	}

}

//RUTINAS DE ATENCIÓN
void RutAtencionTeclado ()
{
	// if (ESTADO == MENU)
	// {	
	// 	if (TeclaPulsada() == A){ 
	// 		ESTADO = PARTIDA;
	// 		visualizarFondoPrueba();
	// 		MostrarSpider(1, 5, 5);
	// 		MostrarChampi(2, 30, 30);
	// 		MostrarChampi(3, 30, 60);
	// 		MostrarChampi(4, 30, 90);
	// 		MostrarCenticuerpo(5, 80, 60);
	// 		MostrarCabeza(6, 60, 60);

	// 	}
	// }
	// else if (ESTADO == PARTIDA)
	// {
		// if (TeclaPulsada() == A){
		// 	crear_disparo();
	// }

	// if (TeclaPulsada() == B){ //esto lo he puesto para ver si cambia bien
	// 	ESTADO=GAMEOVER;
	// 	visualizarGameOver();
	// 	BorrarSpider(1, 5, 5);
	// 	BorrarChampi(2, 30, 30);
	// 	BorrarChampi(3, 30, 60);
	// 	BorrarChampi(4, 30, 90);
	// 	BorrarCenticuerpo(5, 80, 60);
	// 	BorrarCabeza(6, 60, 60);

	// 	// }
	// }
	// else if (ESTADO == GAMEOVER)
	// {
	// 	if(TeclaPulsada() == START){
	// 		ESTADO = MENU;
	// 		visualizarFondoPrueba();
	// 	}
	// }

	if (TeclaPulsada() == A){
		InhibirIntTeclado();
		visualizarFondoPrueba();
		InicializarValoresProta();
		InicializarValoresSetas();
		HabilitarIntTeclado();
	}
}

void RutAtencionTempo()
{
	tick++;
	if (tick >128){
		tick = 0;
	}

	if (ESTADO==PARTIDA){
		if (prota_cont_espera_mov < prota_cont_espera_mov_min){
			prota_cont_espera_mov++;
		}
		else{
			ActualizarPosicionProta();
		}
	}

	// if (ESTADO!=MENU)
	// {
	// 	tick++; 
	// 	if (tick==5)
	// 	{
	// 		tick=0;
	// 		if (ESTADO == GAMEOVER)
	// 		{
	// 			visualizarGameOver();
	// 			ESTADO=PARTIDA;
	// 			BorrarSpider(1, 5, 5);
	// 			BorrarChampi(2, 30, 30);
	// 		}
					
	// 	}
	// }
	
}

void EstablecerVectorInt()
{
// A COMPLETAR POR USTEDES
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

/***********************2025-2026*******************************/

