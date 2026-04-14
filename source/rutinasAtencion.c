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

	//LOCALIZACIÓN CIEMPIES
struct localCiempies {
	int X; //posición X
	int Y; //posición Y
	int activo; //para saber si esa parte sigue viva o muerta
};

	//CREACIÓN CIEMPIES
struct localCiempies ciempies[10]; //El ciempies tiene un tamaño de 10 unidades
int ciem_dir=1; //1-> Ciempies va hacia la derecha y -1-> Ciempies va hacia la izquierda
int ciem_cont_espera_mov=0; //Freno que hace con que el ciempies solo se movimiente 8 pasos por segundo
int ciem_cont_espera_mov_min=16; //Por cuantas veces dividimos 128 (para controlar la velocidad) 


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

void MoverCiempies(){
	int i;

	//El primer FOR es el que borra los sprites actuales para que al movimentarse, no se queden sprites congelados por la pantalla
	for(i=0; i<10; i++){ 
		if(ciempies[i].activo==1){ //Esa unidad esta viva?
			if(i==0){//Estamos con la cabeza
				if(ciem_dir==1) {//Si estamos hacia la derecha
					BorrarCabezaDrcha(110,ciempies[0].X,ciempies[0].Y); //110 pues necesitabamos 1 para la cabeza y 9 para el cuerpo
				}
				else{//Si estamos hacia la izquierda
					BorrarCabezaIzq(110,ciempies[0].X,ciempies[0].Y);
				}
			}
			else{ //Estamos con otra parte del cuerpo
				BorrarCenticuerpo(110+i,ciempies[i].X,ciempies[i].Y);
			}
		}
	}

	//Movimentación del cuerpo (empieza por el final)
	for(i=9; i>0; i--){ //9 porque no incluye la cabeza
		if(ciempies[i].activo==1){
			ciempies[i].X=ciempies[i-1].X;
			ciempies[i].Y=ciempies[i-1].Y;
		}
	}

	//Movimentación de la cabeza y colisiones
	if (ciempies[0].activo==1){
		int newX=ciempies[0].X+(ciem_dir*16); //calcula la nueva posición de X
		int newY=ciempies[0].Y; //calcula la nueva posición de Y

		//Se choca con el limite de la pantalla o con una seta
		if (newX<0 || newX>240 || detectarColisionesSetas(newX,newY)){
			ciempies[0].Y +=16; //Baja 1 linea
			ciem_dir=-ciem_dir; //Cambia de dirección horizontal
		}

		//Impide que salga de la pantalla por debajo
		if(ciempies[0].Y>176){ 
			ciempies[0].Y=176; //Con eso hace un zigzag infino (temporario hasta programar la colision con disparos)
		}
		//Camino libre
		else { 
			ciempies[0].X=newX;
		}
	}

	//Dibujar los sprites en las nuevas posiciones
	for(i=0; i<10; i++){
		if(ciempies[i].activo==1){
			if(i==0){ //Dibujar la cabeza
				if(ciem_dir==1){
					MostrarCabezaDrcha(110, ciempies[0].X, ciempies[0].Y);
				}
				else{
					MostrarCabezaIzq(110, ciempies[0].X, ciempies[0].Y);
				}
			}
			else{
				MostrarCenticuerpo(110+i, ciempies[i].X, ciempies[i].Y);
			}
		}
	}
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

			//Movimento CIEMPIES
			if(ciem_cont_espera_mov<ciem_cont_espera_mov_min){
				ciem_cont_espera_mov++;
			}
			else{
				ciem_cont_espera_mov=0;
				MoverCiempies();
			}
			detectarColisionesDisparo();
			oamUpdate(&oamMain); //ActualizarSprites

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

void InicializarValoresCiempies() {
	int i;
	ciem_dir=1; //Va hacia la derecha al empezar el juego

	for(i=0;i<10;i++){ //Revisa cada unidad del ciempies (posición 0 a 9)
		ciempies[i].activo=1; //Esa unidad se activa
		ciempies[i].X=-(16*i); //Cada unidad del ciempies tiene 16 pixeles, i es el trozo que vamos trabajar y empezamos con el valor negativo para esconder el ciempies en el inicio del juego
		ciempies[i].Y=0; //Cada unidad se encuentra en una linea recta, arriba del todo en la pantalla
	}
}


/***********************2025-2026*******************************/

