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
	prota.X=122;
	prota.Y=160;
	prota.puntos=0;
	prota_cont_espera_mov = 0;

	MostrarProta(0, prota.X, prota.Y);
}

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

casillaSeta matriz_setas[12][16] = {0};

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
				MostrarChampi(11+ultId,j*16,i*16);
				//iprintf("\x1b[23;5HPosición seta: %d",ultId);
				seta_cont_espera_mostrar = 0;
				ultId++;
			}
		}
	}
}

void DetectarColisionesSetasDisparo(int idDisparo){
	int r, c;
	for(r=0; r<12; r++){
		for (c=0; c<16; c++){
			if(matriz_setas[r][c].vidas<=0){
				continue;
			}
			if(detectarColision(disparos[idDisparo].X+8, disparos[idDisparo].Y+8, c*16, r*16)){
				matriz_setas[r][c].vidas--;
				disparos[idDisparo].activo=0;
				BorrarDisparo(1+idDisparo, disparos[idDisparo].X, disparos[idDisparo].Y);
				
				if(matriz_setas[r][c].vidas<=0){
					BorrarChampi(11+matriz_setas[r][c].sprite_id, c*16, r*16);
				}
				else{
					ActualizarChampis(11+matriz_setas[r][c].sprite_id, matriz_setas[r][c].vidas, c*16, r*16);
				}
			}
		}
	}
}

//ENEMIGOS
int enem_cont_espera_mov=0;
int enem_cont_espera_mov_min=16;

	//CIEMPIÉS


parteCiempies ciempies[50] = {0}; //El ciempies tiene un tamaño de 50 unidades

void InicializarValoresCiempies() {
	int i;
	int ultind = 0;
	int ultid = 0;

	int numCiempies = randomInt(1,5);

	for (i=0;i<numCiempies;i++){
		int longitud = randomInt(5,10);
		if (ultind + longitud > 50) {
			break;
		}

		int XCabeza;
		int existe;
		while (existe == 1){
			XCabeza = randomInt(0,15)*16;
			existe = 0;
			
			int ind;
			for (ind = 0; ind < 50; ind + ciempies[ind].longitud ){
				if (ciempies[ind].activo==0){
					break;
				}
				if ( XCabeza == ciempies[ind].X){
					existe = 1;
					break;
				}
			}
		}
		
		int j;
		for (j = 0;j<longitud; j++){
			ciempies[ultind].activo = 1;
			ciempies[ultind].id = ultid;
			ciempies[ultind].parte = j;
			ciempies[ultind].X = XCabeza;
			ciempies[ultind].Y = (-16)*(j+1);
			ciempies[ultind].direccion = 3;
			ciempies[ultind].longitud = longitud;

			ultind++;
		}
		
		ultid++;
	}

	// for(i=0;i<10;i++){ //Revisa cada unidad del ciempies (posición 0 a 9)
	// 	ciempies[i].activo=1; //Esa unidad se activa
	// 	ciempies[i].X=-(16*i); //Cada unidad del ciempies tiene 16 pixeles, i es el trozo que vamos trabajar y empezamos con el valor negativo para esconder el ciempies en el inicio del juego
	// 	ciempies[i].Y=0; //Cada unidad se encuentra en una linea recta, arriba del todo en la pantalla
	// }

}

// FIXME: Corregir para que no vaya de 16 en 16 pixeles.
void MoverCiempies(){
	int i;
	//El primer FOR es el que borra los sprites actuales para que al movimentarse, no se queden sprites congelados por la pantalla
	for(i=0; i<50; i++){
		if(ciempies[i].activo==1){ //Esa unidad esta viva?
			if(ciempies[i].parte==0){//Estamos con la cabeza
				int posX = ciempies[i].X;
				int posY = ciempies[i].Y;

				if(ciempies[i].X < 0){
					BorrarCabezaBajo(50+i,ciempies[i].X,ciempies[i].Y);
					ciempies[i].direccion = randomInt(1,2)*2;
				}
				else if(ciempies[i].direccion==2) {//Si estamos hacia la derecha
					BorrarCabezaDrcha(51+i,ciempies[i].X,ciempies[i].Y); //110 pues necesitabamos 1 para la cabeza y 9 para el cuerpo
					if(ciempies[i].X+16>240){
						ciempies[i].Y +=16; //Baja 1 linea
						ciempies[i].direccion=3;
					}
				}
				else if(ciempies[i].direccion==4){//Si estamos hacia la izquierda
					BorrarCabezaIzq(51+i,ciempies[i].X,ciempies[i].Y); //primero 50 o 51?? //cuando rompo la serpiente se mueven el resto de elementos para tapar el hueco de la lista??
					if (ciempies[i].X-16<0){
						ciempies[i].Y +=16; //Baja 1 linea
						ciempies[i].direccion=3;
					}
				}
				else if(ciempies[i].direccion==3){
					if(ciempies[i].X+16>240){
						ciempies[i].X -= 16;
					}
					else if(ciempies[i].X-16<0){
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
			
			// FIXME: Qué se supone que es posX y posY?
			else{ //Estamos con otra parte del cuerpo
				BorrarCenticuerpo(51+i,ciempies[i].X,ciempies[i].Y);
				int guardaX = ciempies[i].X;
				int guardaY = ciempies[i].Y;
				ciempies[i].X=posX;
				ciempies[i].Y=posY;
				posX = guardaX;
				posY = guardaY;
			}
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
			if(enem_cont_espera_mov<enem_cont_espera_mov_min){
				enem_cont_espera_mov++;
			}
			else{
				enem_cont_espera_mov=0;
				MoverCiempies();
			}
			// FIXME: Es necesario?
			DetectarColisionesDisparo();
			oamUpdate(&oamMain); //ActualizarSprites

		}
		else if (ACCION == MUERTE){
			// TODO: Deshabilitar interrupciones del teclado
			// TODO: Ejecutar Animación muerte del protagonista
			// TODO: Recargar pantalla si tiene mas de 0 vidas, else ESTADO = GAMEOVER
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

