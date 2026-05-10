// Curso 2025-2026

/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"
#include "juego.h"

/*=================================================================================
 * VARIABLES
 =================================================================================*/

int ESTADO;
int ACCION;
int tick = 0;

//PROTAGONISTA
protagonista prota;
int prota_cont_espera_mov = 0;
int prota_cont_espera_mov_min = 1;
int prota_pixel_mov = 2;

//DISPAROS
disparo disparos[10] = {{0}};

int disp_cont_espera_mov = 0;
int disp_cont_espera_mov_min = 1;

int disp_pixel_mov = 4;

int disp_cont_espera = 0;
int disp_cont_espera_min = 40;

//SETAS
casillaSeta matriz_setas[9][16] = {{{0}}};

volatile int seta_cont_espera_mostrar = 0;
int seta_cont_espera_mostrar_max = 32; //4 veces por segundo aparece una seta

//ENEMIGOS
int enem_cont_espera_mov=0;
int enem_cont_espera_mov_min=1;

	//CIEMPIES
parteCiempies ciempies[50] = {{0}}; //El ciempies tiene un tamaño de 50 unidades
int ciempies_pixel_mov=2;


/*=================================================================================
 * FUNCIONES GENERALES
 =================================================================================*/

int DetectarColision(int x1, int y1, int x2, int y2) { 
	if(x1/16 == x2/16 && y1/16 == y2/16){
		return 1;
	}
	return 0;
}

int RandomInt(int min, int max) {
	int numAleatorio=rand();
	int dif = max-min+1;
    return min + (numAleatorio % dif);
}

void LimpiarPantalla(){
    int i, j;

    // 1. Ocultar físicamente todos los sprites de la OAM
    oamClear(&oamMain, 0, 127);

	oamUpdate(&oamMain);
    
    // 2. Para ocultar los disparos
    for(i=0; i<10; i++){
        disparos[i].activo = 0;
        disparos[i].X = 0;
        disparos[i].Y = 200; // Fuera de pantalla
    }

    // 3. Para ocultar las setas
    for(i=0; i<9; i++){
        for(j=0; j<16; j++){
            matriz_setas[i][j].vidas = 0;
            matriz_setas[i][j].sprite_id = 0;
        }
    }

    // 4. Reset CIEMPIES (Limpieza profunda)
    for(i=0; i<50; i++){
        ciempies[i].activo = 0;
        ciempies[i].X = 0;
        ciempies[i].Y = 200;
        ciempies[i].direccion = DIR_ABAJO;
        ciempies[i].parte = 0;
    }
    
    // 5. Forzar actualización inmediata del hardware
    oamUpdate(&oamMain);
}


/*=================================================================================
 * FUNCIONES PROTAGONISTA
 =================================================================================*/

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
				MostrarProta(SID_PROTA, prota.X, prota.Y);
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

void DetectarColisionProtaCiempies(){
	int i;

	//Centro del prota
	int centroProtaX=prota.X+8;
	int centroProtaY=prota.Y+8;

	for(i=0;i<50;i++){
		if(ciempies[i].activo==0) continue;

		//Centro de la parte actual del ciempies
		int centroCiempX=ciempies[i].X+8;
		int centroCiempY=ciempies[i].Y+8;

		if(DetectarColision(centroProtaX, centroProtaY, centroCiempX, centroCiempY)){
			//Si existe una colision, el prota pierde 1 vida
			prota.vidas--;
			if(prota.vidas>0){
				//Limpiamos la pantalla y reiniciamos el nivel
				ACCION=MUERTE;
			}
			else{
				//Si pierde todas las vidas, pasamos al estado de GAMEOVER
				ESTADO=GAMEOVER;
			}
			break;
		}
	}
}


/*=================================================================================
 * FUNCIONES DISPARO
 =================================================================================*/

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

void DetectarColisionesDisparo(int idDisparo){
	DetectarColisionesDisparoSetas(idDisparo);
	DetectarColisionesDisparoCiempies(idDisparo);
}

void MoverDisparos(){
	int i;
	for (i = 0; i < 10;i++){
		if (disparos[i].activo == 0){
			continue;
		}
		BorrarDisparo(SID_DISP+i,disparos[i].X,disparos[i].Y);
		disparos[i].Y -= disp_pixel_mov;

		if (disparos[i].Y < -16) { 
			disparos[i].activo = 0;
		} else {
			MostrarDisparo(SID_DISP+i, disparos[i].X, disparos[i].Y);
		}

		DetectarColisionesDisparo(i);

	}
}


/*=================================================================================
 * FUNCIONES SETAS
 =================================================================================*/

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

void DetectarColisionesDisparoSetas(int idDisparo){
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

int primerIdSinSeta() {
    int idCandidato;
    int r, c;
    int encontrado;
    int maxSetas = SID_SETA_MAX - SID_SETA;

    // Probamos cada ID posible uno por uno
    for (idCandidato = 0; idCandidato < maxSetas; idCandidato++) {
        encontrado = 0; // Asumimos que no está usado
        
        for (r = 0; r < 9; r++) {
            for (c = 0; c < 16; c++) {
                // Si la casilla tiene vida y usa este ID, no nos sirve
                if (matriz_setas[r][c].vidas > 0 && matriz_setas[r][c].sprite_id == idCandidato) {
                    encontrado = 1;
                    break; 
                }
            }
            if (encontrado) break;
        }

        // Si recorrimos toda la matriz y nadie usaba el idCandidato, es nuestro
        if (!encontrado) {
            return idCandidato;
        }
    }
    return -1; // No hay huecos para más sprites de setas
}

/*=================================================================================
 * FUNCIONES ENEMIGOS
 =================================================================================*/

//CIEMPIÉS

void InicializarValoresCiempies() {
	int ultInd = 0;
	int ultId = 0;
	
	int numCiempies = RandomInt(1,5); //Números aleatorios entre 1 y 5 para probar
	
	int i;
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
			ciempies[ultInd].Y = -16;//(-16)*(ultInd+1)
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
					newX = BORDE_IZQUIERDO;
					newY = -PIXELES_SPRITES;
					ciempies[i].X = newX;
					ciempies[i].Y = newY;
				}
				else if (oldY < BORDE_SUPERIOR){
					if (i==0 || (ciempies[i-1].Y == 0 && ciempies[i-1].X % PIXELES_SPRITES !=0) || oldX <= BORDE_IZQUIERDO){
						newY = oldY + ciempies_pixel_mov;
						ciempies[i].Y = newY;
					}
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

		if(ciempies[i].activo == 1){
			if (ciempies[i].parte == 0){
				ActualizarSpritesCiempiesCabeza(SID_CIEMPIES+i, oldDir, oldX, oldY, newDir, newX, newY);
			}
			else {
				BorrarCenticuerpo(SID_CIEMPIES+i, oldX, oldY);
				MostrarCenticuerpo(SID_CIEMPIES+i, newX, newY);
			}
		}
	}
}

void DetectarColisionesDisparoCiempies(int idDisparo) {
    int dispX = disparos[idDisparo].X;
    int dispY = disparos[idDisparo].Y;
	int i;

    for (i = 0; i < 50; i++) {
        if (ciempies[i].activo == 0) continue;

        int ciempX = ciempies[i].X;
        int ciempY = ciempies[i].Y;
        int ciempDir = ciempies[i].direccion;

        if (DetectarColision(dispX + 8, dispY + 8, ciempX + 8, ciempY + 8)) {
            // 1. Borrar disparo
            BorrarDisparo(SID_DISP + idDisparo, dispX, dispY);
            disparos[idDisparo].activo = 0;

            // 2. Borrar parte del ciempiés
            if (ciempies[i].parte == 0) {
                BorrarCabezaCiempies(SID_CIEMPIES + i, ciempDir, ciempX, ciempY);
            } else {
                BorrarCenticuerpo(SID_CIEMPIES + i, ciempX, ciempY);
            }
            ciempies[i].activo = 0;

            // 3. Convertir siguiente parte en cabeza
            if (i + 1 < 50 && ciempies[i + 1].activo == 1) {
                BorrarCenticuerpo(SID_CIEMPIES + i + 1, ciempies[i + 1].X, ciempies[i + 1].Y);
                ciempies[i + 1].parte = 0;
                CrearCabezaCiempies(SID_CIEMPIES + i + 1, ciempies[i+1].direccion, ciempies[i + 1].X, ciempies[i + 1].Y);
            }

            // 4. Generar seta
            if (ciempY < BORDE_SUPERIOR_PROTA && ciempies[i].parte != 0) {
                int fila = ciempY / PIXELES_SPRITES;
                int col = ciempX / PIXELES_SPRITES;
                
                if (fila >= 0 && fila < 9 && col >= 0 && col < 16) {
                    // Solo creamos la seta si no hay una ya allí
                    if (matriz_setas[fila][col].vidas <= 0) {
                        int idSetaLibre = primerIdSinSeta();
                        if (idSetaLibre != -1) {
                            matriz_setas[fila][col].vidas = 4;
                            matriz_setas[fila][col].sprite_id = idSetaLibre;
                            MostrarSeta(SID_SETA + idSetaLibre, col * 16, fila * 16);
                        }
                    }
                }
            }
            break; 
        }
    }
}

/*=================================================================================
 * RUTINAS DE ATENCIÓN
 =================================================================================*/

void RutAtencionTeclado ()
{
	int tecla = TeclaPulsada();
	if (tecla == START){
		InhibirIntTeclado();
		LimpiarPantalla(); //TODO: En el futuro quitamos está función de aquí.
		ACCION = CARGANDO_FONDO;
	}
	else if (tecla == A){
		CrearDisparo();
	}
}

void RutAtencionTempo()
{
	tick++;
	if (tick >= 128){
		tick = 0;
	}

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
				
				DetectarColisionProtaCiempies();
				//NO BORRAR(IMPORTANTE)
				oamUpdate(&oamMain);
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

