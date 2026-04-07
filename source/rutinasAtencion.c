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
int ACCION; // Accion en la que se encuentra en el estado partida

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
	ACCION = CARGANDO_PROTA;
	prota.vidas=3;
	prota.X=122;
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
casillaSeta matriz_setas[12][16];

volatile int seta_cont_espera_mostrar = 0;
int seta_cont_espera_mostrar_max = 32; //4 veces por segundo aparece una seta

void InicializarValoresSetas() {
	int ultId = 1;
	int i;
	for (i=0; i<9; i++){
		int j;
		for (j=0; j<16; j++){
			if (randomInt(0,7)==0){
				while (seta_cont_espera_mostrar < seta_cont_espera_mostrar_max){
					//Hasta que el valor de seta_cont_espera_mostrar sea mayor o igual que seta_cont_espera_mostrar_max
				}
				matriz_setas[i][j].sprite_id=ultId;
				matriz_setas[i][j].vidas=4;
				MostrarChampi(1+ultId,j*16,i*16);
				iprintf("\x1b[23;5HPosición seta: %d",ultId);
				seta_cont_espera_mostrar = 0;
				ultId++;
			}
		}
	}

}

//RUTINAS DE ATENCIÓN
void RutAtencionTeclado ()
{
	if (TeclaPulsada() == A){
		InhibirIntTeclado();
		ACCION = CARGANDO_FONDO;
	}
}

void RutAtencionTempo()
{
	tick++;
	if (tick >128){
		tick = 0;
	}

	if (ESTADO==PARTIDA){
		if (ACCION == CARGANDO_FONDO){

		}
		else if (ACCION == CARGANDO_PROTA){

		}
		else if (ACCION == CARGANDO_SETAS){
			if (seta_cont_espera_mostrar <=seta_cont_espera_mostrar_max){
				seta_cont_espera_mostrar++;
			}
		}
		else if (ACCION == CARGANDO_ENEMIGOS){

		}
		else if (ACCION == JUEGO) {
			if (prota_cont_espera_mov < prota_cont_espera_mov_min){
				prota_cont_espera_mov++;
			}
			else {
				ActualizarPosicionProta();
			}
		}
		else if (ACCION == PAUSA){

		}
		
	}
}

void EstablecerVectorInt()
{
// A COMPLETAR POR USTEDES
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

/***********************2025-2026*******************************/

