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

int detectarColision(int x1, int y1, int x2, int y2) { 
	if(x1/16 == x2/16 && y1/16 == y2/16){
		return 1;
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
			if (randomInt(0,6)==0){
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
			if(detectarColision(disparos[idDisparo].X+8, disparos[idDisparo].Y+8, c*16, r*16)){
				matriz_setas[r][c].vidas--;
				disparos[idDisparo].activo=0;
				BorrarDisparo(1+idDisparo, disparos[idDisparo].X, disparos[idDisparo].Y);
				
				if(matriz_setas[r][c].vidas<=0){
					BorrarSeta(11+matriz_setas[r][c].sprite_id, c*16, r*16);
				}
				else{
					ActualizarSpriteSetas(11+matriz_setas[r][c].sprite_id, matriz_setas[r][c].vidas, c*16, r*16);
				}
			}
		}
	}
}

//ENEMIGOS
int enem_cont_espera_mov=0;
int enem_cont_espera_mov_min=2;

	//CIEMPIÉS
int ciempies_pixel_mov=2;

parteCiempies ciempies[50] = {0}; //El ciempies tiene un tamaño de 50 unidades

void InicializarValoresCiempies() {
	int i;
	int ultInd = 0;
	int ultId = 0;

	int numCiempies = randomInt(1,5); //Números aleatorios entre 1 y 5 para probar

	for (i=0;i<numCiempies;i++){
		int longitud = randomInt(1,10); //Longitud del ciempies generado
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
	//El primer FOR es el que borra los sprites actuales para que al moverse, no se queden sprites congelados por la pantalla
	for(i=0; i<50; i++){
		if(ciempies[i].activo==0) continue; //Esa unidad esta viva?

		int oldX = ciempies[i].X;
		int oldY = ciempies[i].Y;
		int oldDir = ciempies[i].direccion;

		if(ciempies[i].parte==0){ //Estamos con la cabeza?

			if (oldDir == DIR_ABAJO){
				//Si acaba de aparecer en el centro de la pantalla
				if (oldY == BORDE_SUPERIOR){
					ciempies[i].direccion = DIR_DERECHA;
					int newX = oldX + ciempies_pixel_mov;
					ciempies[i].X = newX;
					ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, DIR_DERECHA, newX, 0);
				}
				//Si se encuentra en una de las casillas exactamente
				else if (oldY % PIXELES_SPRITES == 0){
					if (oldX == BORDE_DERECHO){
						ciempies[i].direccion = DIR_IZQUIERDA;
						int newX = oldX - ciempies_pixel_mov;
						ciempies[i].X = newX;
						ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, DIR_IZQUIERDA, newX, oldY);
					}
					else if (oldX == BORDE_IZQUIERDO){
						ciempies[i].direccion = DIR_DERECHA;
						int newX = oldX + ciempies_pixel_mov;
						ciempies[i].X = newX;
						ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, DIR_DERECHA, newX, oldY);
					}
				}
				else {
					int newY = oldY + ciempies_pixel_mov;
					
					if (newY >=BORDE_INFERIOR + PIXELES_SPRITES){
						BorrarCabezaBajo(SID_CIEMPIES+i, oldX, oldY);
						ciempies[i].activo=0;
						continue;
					}
					
					ciempies[i].Y = newY;
					ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, DIR_ABAJO, oldX, newY);
				}
				
			}

			// FIXME: Falta corregir esta parte
			else if(oldDir==DIR_DERECHA) {//Si estamos hacia la derecha
				if(ciempies[i].X==BORDE_DERECHO){
					ciempies[i].direccion=DIR_ABAJO;
					int newY =  oldY + ciempies_pixel_mov;
					ciempies[i].Y += newY;
					ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, DIR_ABAJO, oldX, newY);
				}
			}
			else if(oldDir==DIR_IZQUIERDA){//Si estamos hacia la izquierda
				if (ciempies[i].X==BORDE_IZQUIERDO){
					ciempies[i].Y +=16; //Baja 1 linea
					ciempies[i].direccion=DIR_ABAJO;
				}
			}
			else if(oldDir==DIR_ABAJO){
				if(ciempies[i].X+16>BORDE_DERECHO){
					ciempies[i].X -= 16;
				}
				else if(ciempies[i].X-16<BORDE_IZQUIERDO){
					ciempies[i].X += 16;
				}
			}

			

			//Impide que salga de la pantalla por debajo
			//if(ciempies[i].Y>176){ 
				//ciempies[i].Y=176; //Con eso hace un zigzag infino (temporario hasta programar la colision con disparos)
			//}
			//Camino libre
			//else { 
			//	ciempies[i].X=newX;
			//}
		}

		else{ //Estamos con otra parte del cuerpo
			BorrarCenticuerpo(SID_CIEMPIES+i,ciempies[i].X,ciempies[i].Y);
			int guardaX = ciempies[i].X;
			int guardaY = ciempies[i].Y;
			ciempies[i].X=oldX;
			ciempies[i].Y=oldY;
			oldX = guardaX;
			oldY = guardaY;
		}
		
	}

	//Dibujar los sprites en las nuevas posiciones
	for(i=0; i<50; i++){
		if(ciempies[i].activo==1){
			if(ciempies[i].parte==0){ //Dibujar la cabeza
				if(ciempies[i].direccion==2){
					MostrarCabezaDrcha(51+i, ciempies[0].X, ciempies[0].Y);
				}
				else if(ciempies[i].direccion==2){
					MostrarCabezaIzq(51+i, ciempies[0].X, ciempies[0].Y);
				}
				else if(ciempies[i].direccion==3){
					MostrarCabezaBajo(51+i, ciempies[0].X, ciempies[0].Y);
				}
			}
			else{
				MostrarCenticuerpo(51+i, ciempies[i].X, ciempies[i].Y);
			}
		}
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

