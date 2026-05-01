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

int ESTADO;
int ACCION;

static unsigned int semilla = 12345;

int DetectarColision(int x1, int y1, int x2, int y2) { 
	if(x1/16 == x2/16 && y1/16 == y2/16){
		return 1;
	}
	return 0;
}

int RandomInt(int min, int max) {
	semilla = semilla * 1103515245 + 12345;

	unsigned int numAleatorio = (semilla / 65536) % 32768;
    int dif = max-min+1;
    return min+ (numAleatorio % dif);
}


	//PROTA

protagonista prota;
int prota_cont_espera_mov = 0;
int prota_cont_espera_mov_min = 1;
int prota_pixel_mov = 2;

void InicializarValoresProta(){
	prota.vidas=3;
	prota.X=CENTRO_HORIZONTAL;
	prota.Y=CENTRO_VERTICAL_PROTA;
	prota.puntos=0;
	prota_cont_espera_mov = 0;

	MostrarProta(SID_PROTA, prota.X, prota.Y);
}

void ActualizarPosicionProta() {
	if (TeclaDetectada()){
		int teclas = ~TECLAS_DAT & 0x03ff;
		if (teclas & (1 << ARRIBA)){
			if (prota.Y>BORDE_SUPERIOR_PROTA){
				BorrarProta(SID_PROTA, prota.X, prota.Y);
				prota.Y-=prota_pixel_mov;
				MostrarProta(0, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << ABAJO)){
			if (prota.Y<BORDE_INFERIOR){
				BorrarProta(SID_PROTA, prota.X, prota.Y);
				prota.Y+=prota_pixel_mov;
				MostrarProta(SID_PROTA, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << IZQUIERDA)){
			if (prota.X>BORDE_IZQUIERDO){
				BorrarProta(SID_PROTA, prota.X, prota.Y);
				prota.X-=prota_pixel_mov;
				MostrarProta(SID_PROTA, prota.X, prota.Y);
			}
		}
		else if (teclas & (1 << DERECHA)){
			if (prota.X<BORDE_DERECHO){
				BorrarProta(SID_PROTA, prota.X, prota.Y);
				prota.X+=prota_pixel_mov;
				MostrarProta(SID_PROTA, prota.X, prota.Y);
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

		DetectarColisionesSetasDisparo(i);
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

casillaSeta matriz_setas[9][16] = {0};

volatile int seta_cont_espera_mostrar = 0;
int seta_cont_espera_mostrar_max = 32; //4 veces por segundo aparece una seta

void InicializarValoresSetas() {
	int ultId = 0;
	int i;
	for (i=0; i<9; i++){
		int j;
		for (j=0; j<16; j++){
			if (RandomInt(0,6)==0){
				while (seta_cont_espera_mostrar < seta_cont_espera_mostrar_max){
					//Hasta que el valor de seta_cont_espera_mostrar sea mayor o igual que seta_cont_espera_mostrar_max
				}
				matriz_setas[i][j].sprite_id=ultId;
				matriz_setas[i][j].vidas=4;
				MostrarSeta(11+ultId,j*16,i*16);
				//iprintf("\x1b[23;5HPosición seta: %d",ultId);
				seta_cont_espera_mostrar = 0;
				ultId++;
			}
		}
	}
}

void DetectarColisionesSetasDisparo(int idDisparo){
	int r, c;
	for(r=0; r<9; r++){
		for (c=0; c<16; c++){
			if(matriz_setas[r][c].vidas<=0){
				continue;
			}
			if(DetectarColision(disparos[idDisparo].X+8, disparos[idDisparo].Y+8, c*16, r*16)){
				matriz_setas[r][c].vidas--;
				disparos[idDisparo].activo=0;
				BorrarDisparo(1+idDisparo, disparos[idDisparo].X, disparos[idDisparo].Y);
				
				if(matriz_setas[r][c].vidas<=0){
					BorrarSeta(SID_SETA+matriz_setas[r][c].sprite_id, c*16, r*16);
				}
				else{
					ActualizarSpriteSetas(SID_SETA+matriz_setas[r][c].sprite_id, matriz_setas[r][c].vidas, c*16, r*16);
				}
			}
		}
	}
}

int primerIdSinSeta(){
	int i, r, c;
	int idSeta = 0;

	for(i=0;i<151;i++) {
		for(r=0;r<9;r++){
			for(c=0;c<16;c++){
				if(matriz_setas[r][c].vidas <= 0) continue;
				if(matriz_setas[r][c].sprite_id > idSeta){
					idSeta++;
					break;
				}
				else {
					return idSeta;
				}
			}
			if(matriz_setas[r][c].sprite_id > idSeta-1) break;
		}
	}
	return idSeta;
}

//ENEMIGOS
int enem_cont_espera_mov=0;
int enem_cont_espera_mov_min=1;

	//CIEMPIÉS
int ciempies_pixel_mov=2;

parteCiempies ciempies[50] = {0}; //El ciempies tiene un tamaño de 50 unidades

void InicializarValoresCiempies() {
	int i;
	for (i = 0; i < 50; i++){
		ciempies[i].activo = 0;
	}

	int ultInd = 0;
	int ultId = 0;

	int numCiempies = RandomInt(1,5); //Números aleatorios entre 1 y 5 para probar

	for (i=0;i<numCiempies;i++){
		int longitud = RandomInt(1,10); //Longitud del ciempies generado
		if (ultInd + longitud > 50) {
			break;
		}

		int j;
		for (j = 0;j<longitud; j++){
			ciempies[ultInd].activo = 1;
			ciempies[ultInd].id = ultId;
			ciempies[ultInd].parte = j;
			ciempies[ultInd].X = CENTRO_HORIZONTAL;
			ciempies[ultInd].Y = (-16)*(ultInd+1);
			ciempies[ultInd].direccion = DIR_ABAJO;
			ciempies[ultInd].longitud = longitud;

			ultInd++;
		}
		
		ultId++;
	}

}

void MoverCiempies(){
	int i;
	//El primer FOR es el que actualiza las posiciones de los ciempiés
	for(i=0; i<50; i++){
		if(ciempies[i].activo==0) continue; //Esa unidad esta viva?

		int oldX = ciempies[i].X;
		int oldY = ciempies[i].Y;
		int oldDir = ciempies[i].direccion;

		int newX = oldX;
		int newY = oldY;
		int newDir = oldDir;

		// FIXME: Por ahora lo probaremos sin que se diferencie entre cabeza y cuerpo y hará lo mismo

		//if (ciempies[i].parte==0){ //Estamos con la cabeza?

			// Si va hacia abajo
			if (oldDir == DIR_ABAJO){

				//Si se encuentra en una de las casillas exactamente
				if (oldY % PIXELES_SPRITES == 0){
					if (oldX == BORDE_DERECHO){
						ciempies[i].direccion = DIR_IZQUIERDA;
						newX = oldX - ciempies_pixel_mov;
						ciempies[i].X = newX;
						newDir = DIR_IZQUIERDA;
					}
					else if (oldY + ciempies_pixel_mov >=BORDE_INFERIOR + PIXELES_SPRITES){
						if (ciempies[i].parte==0){
							BorrarCabezaBajo(SID_CIEMPIES+i, oldX, oldY);
						}
						else {
							BorrarCenticuerpo(SID_CIEMPIES+i, oldX, oldY);
						}
						ciempies[i].activo=0;
						continue;
					}
					else if (oldY < BORDE_SUPERIOR){
						newY = oldY + ciempies_pixel_mov;
						ciempies[i].Y = newY;
					}
					else {
						ciempies[i].direccion = DIR_DERECHA;
						newX = oldX + ciempies_pixel_mov;
						ciempies[i].X = newX;
						newDir = DIR_DERECHA;
					}
				}
				//Seguir moviendose
				else {
					newY = oldY + ciempies_pixel_mov;
					ciempies[i].Y = newY;
				}
				
			}
			// Si va a la derecha
			else if (oldDir == DIR_DERECHA) {
				if (oldX == BORDE_DERECHO) {
					newY = oldY + ciempies_pixel_mov;
					ciempies[i].Y = newY;
					ciempies[i].direccion = DIR_ABAJO;
					newDir = DIR_ABAJO;
				}
				else {
					newX = oldX + ciempies_pixel_mov;
					ciempies[i].X = newX;
				}
			}
			// Si va a la izquierda
			else if (oldDir == DIR_IZQUIERDA) {
				if (oldX == BORDE_IZQUIERDO) {
					newY = oldY + ciempies_pixel_mov;
					ciempies[i].Y = newY;
					ciempies[i].direccion = DIR_ABAJO;
					newDir = DIR_ABAJO;
				}
				else {
					newX = oldX - ciempies_pixel_mov;
					ciempies[i].X = newX;
				}
			}
			
			int j;

			//Recorre el array de disparos
			for(j=0;j<10;j++){
				if(disparos[j].activo == 0) continue;

				int dispX = disparos[j].X;
				int dispY = disparos[j].Y;

				//Si colisiona la bala con el ciempies
				if(DetectarColision(dispX+8, dispY+8, newX+8, newY+8) == 1){
					BorrarDisparo(SID_DISP+j, dispX, dispY);
					disparos[j].activo = 0;

					//Si es la cabeza
					if(ciempies[i].parte = 0){
						BorrarCabezaCiempies(SID_CIEMPIES+i, oldDir, newX, newY);
					} else {
						BorrarCenticuerpo(SID_CIEMPIES+i, newX, newY);
					}
					ciempies[i].activo = 0;

					//Si la siguiente posicion esta dentro de rango de matriz y esta activa
					if(i+1<50 && ciempies[i+1].activo != 0){
						//Borra el cuerpo y crea la cabeza
						BorrarCenticuerpo(SID_CIEMPIES+i+1, ciempies[i+1].X, ciempies[i+1].Y);
						CrearCabezaCiempies(SID_CIEMPIES+i+1, oldDir, ciempies[i+1].X, ciempies[i+1].Y);
					}

					//Si esta en la zona del jugador sale
					if(newY >= BORDE_SUPERIOR_PROTA) break;
					//Crear una nueva seta en esa posición
					matriz_setas[newX/PIXELES_SPRITES][newY/PIXELES_SPRITES].vidas = 4;
					int idSeta = primerIdSinSeta();
					if(idSeta+1 <= SID_SETA_MAX) MostrarSeta(SID_SETA+idSeta+1, (newX/PIXELES_SPRITES)*PIXELES_SPRITES, (newY/PIXELES_SPRITES)*PIXELES_SPRITES);
				}
			}

			if(ciempies[i].activo == 1){
				if (ciempies[i].parte == 0){
					ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, newDir, newX, newY);
				}
				else {
					BorrarCenticuerpo(SID_CIEMPIES+i, oldX, oldY);
					MostrarCenticuerpo(SID_CIEMPIES+i, newX, newY);
				}
			}
		//}
	}
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
	if (ESTADO == MENU){
		InhibirIntTempo();
	}

	else if (ESTADO==PARTIDA){
		switch (ACCION){
			case CARGANDO_SETAS:
				if (seta_cont_espera_mostrar <=seta_cont_espera_mostrar_max){
					seta_cont_espera_mostrar++;
				}
				break;

			case JUEGO:
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
				if(enem_cont_espera_mov<enem_cont_espera_mov_min){
					enem_cont_espera_mov++;
				}
				else{
					enem_cont_espera_mov=0;
					MoverCiempies();
				}
				DetectarColisionesDisparo();
				// FIXME: Es necesario actualizarSprites así?
				oamUpdate(&oamMain); //ActualizarSprites
				break;
			
			case MUERTE:
				break;

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

