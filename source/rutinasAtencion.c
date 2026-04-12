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
static unsigned int semilla = 12345;

//Verifica si dos elementos tienen el mismo número en la cuadricula.
int detectarColision(int x1, int y1, int x2, int y2) { 
	if(x1/16 == x2/16 && y1/16 == y2/16){
		return 1; //colisión
	}
	return 0;
}

int randomInt(int min, int max) {
	semilla = semilla * 1103515245 + 12345;

	unsigned int numAleatorio = (semilla / 65536) % 32768;
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
		int teclas = ~TECLAS_DAT & 0x03ff;
		if (teclas & (1 << ARRIBA)){
			if (prota.Y>144){
				BorrarProta(0, prota.X, prota.Y);
				prota.Y-=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << ABAJO)){
			if (prota.Y<176){
				BorrarProta(0, prota.X, prota.Y);
				prota.Y+=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << IZQUIERDA)){
			if (prota.X>0){
				BorrarProta(0, prota.X, prota.Y);
				prota.X-=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << DERECHA)){
			if (prota.X<240){
				BorrarProta(0, prota.X, prota.Y);
				prota.X+=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		
		//iprintf("\x1b[23;5HX: %d  Y: %d",prota.X, prota.Y);
	}
    
}

	//DISPAROS

disparo disparos[10] = {0};

int disp_cont_espera_mov = 0;
int disp_cont_espera_mov_min = 1;

int disp_pixel_mov = 2;

int disp_cont_espera = 0;
int disp_cont_espera_min = 64;

void CrearDisparo(){
	int i = 0;
	while (i < 10 && disparos[i].activo!=0){
		i++;
	}
	if (i < 10){
		disp_cont_espera = 0;
		InhibirIntTecla(A);
		disparos[i].activo = 1;
		disparos[i].X = prota.X;
		disparos[i].Y = prota.Y - 12;
		MostrarDisparo(1+i,disparos[i].X,disparos[i].Y);
	}
	
}

void DetectarColisionesDisparo(){
	int i;
	for(i=0;i<10;i++){
		if (disparos[i].activo==0){
			continue;
		}

		if (DetectarColisionesSetas(i)==1){
			BorrarDisparo(1+i, disparos[i].X, disparos[i].Y);
		}
	}
}

void MoverDisparos(){
	int i;
	for (i = 0; i < 10;i++){
		if (disparos[i].activo == 1){
			BorrarDisparo(1+i,disparos[i].X,disparos[i].Y);
			disparos[i].Y -= disp_pixel_mov;

			if (disparos[i].Y < -16) { 
                disparos[i].activo = 0;
            } else {
                MostrarDisparo(1+i, disparos[i].X, disparos[i].Y);
            }
		}
	}
	DetectarColisionesDisparo();
}

	// SETAS
casillaSeta matriz_setas[12][16] = {0};

volatile int seta_cont_espera_mostrar = 0;
int seta_cont_espera_mostrar_max = 32; //4 veces por segundo aparece una seta

void InicializarValoresSetas() {
	int ultId = 0;
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
				MostrarChampi(11+ultId,j*16,i*16);
				//iprintf("\x1b[23;5HPosición seta: %d",ultId);
				seta_cont_espera_mostrar = 0;
				ultId++;
			}
		}
	}
}

int DetectarColisionesSetas(int idDisparo){
	int r, c;
	for(r=0; r<12; r++){
		for (c=0; c<16; c++){
			if(matriz_setas[r][c].vidas<=0){
				continue;
			}
			if(detectarColision(disparos[idDisparo].X+8, disparos[idDisparo].Y+8, c*16, r*16)){
				matriz_setas[r][c].vidas--;
				disparos[idDisparo].activo=0;
				
				if(matriz_setas[r][c].vidas<=0){
					BorrarChampi(11+matriz_setas[r][c].sprite_id, c*16, r*16);
				}
				else{
					ActualizarChampis(11+matriz_setas[r][c].sprite_id, matriz_setas[r][c].vidas, c*16, r*16);
				}
				return 1;
			}
		}
	}
	return 0;
}

//RUTINAS DE ATENCIÓN
void RutAtencionTeclado ()
{
	int tecla = TeclaPulsada();
	if (tecla == START){
		InhibirIntTeclado();
		ACCION = CARGANDO_FONDO;
	}
	else if (tecla == A){
		CrearDisparo();
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
				prota_cont_espera_mov=0;
				ActualizarPosicionProta();
			}

			if (disp_cont_espera_mov < disp_cont_espera_mov_min){
				disp_cont_espera_mov++;
			}
			else {
				disp_cont_espera_mov = 0;
				MoverDisparos();
			}

			if (disp_cont_espera < disp_cont_espera_min) {
				disp_cont_espera++;
			}
			else {
				HabilitarIntTecla(A);
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

