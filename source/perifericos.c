// Curso 2025-2026

/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; // Variable para guardar la tecla pulsada; valorar si es necesaria



int TeclaDetectada() 
{
	// Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{

	// Devuelve el código de la tecla pulsada utilizando para ello las constantes definidas en 
	// definiciones.h:  A=0;B=1;SELECT=2;START=3;DERECHA=4;IZQUIERDA=5;
	// ARRIBA=6;ABAJO=7;R=8;L=9;
	// Poned código que sea comprensible al leer.
	
	int teclas = ~TECLAS_DAT & 0x03ff;


	// Mediante (1 << A) hacemos 0000 0001 * 2^A Es decir, el 1 se mueve A veces a la izquierda. Equivalente a lsl en ASSEMBLY
	if (teclas & (1 << A))		return A;
	if (teclas & (1 << B))		return B;
	if (teclas & (1 << SELECT))	return SELECT;
	if (teclas & (1 << START))	return START;
	if (teclas & (1 << DERECHA))	return DERECHA;
	if (teclas & (1 << IZQUIERDA))	return IZQUIERDA;
	if (teclas & (1 << ARRIBA))	return ARRIBA;
	if (teclas & (1 << ABAJO))	return ABAJO;
	if (teclas & (1 << R))		return R;
	if (teclas & (1 << L))		return L;

	return -1;
}

void ConfigurarTeclado(int Conf_Tec)
{
	// Configuración del teclado. Modificar su registro de control en base a los bits
        // activados en el parametro Conf_Tec
	TECLAS_CNT = Conf_Tec;
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	// Configuración del temporizador. El latch es el valor del registro de datos del temporizador
        // Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo
	TIMER0_DAT = Latch;
	TIMER0_CNT = Conf_Tempo;
	
}

void HabilitarIntTeclado()
{
	// Habilitar las interrupciones del teclado
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	DeshabilitarInterrrupciones(); // IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	// |= Realiza una operación OR bit a bit.
	IE |= 0x1000;
	HabilitarInterrupciones(); // IME=1;
}

void HabilitarIntTecla(int tecla){
	DeshabilitarInterrrupciones();
	TECLAS_CNT |= (1 << tecla);
	HabilitarInterrupciones();
}

void InhibirIntTeclado()
{

	// Deshabilitar las interrupciones del teclado
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 

	DeshabilitarInterrrupciones(); // IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	// ~ sirve para hacer el complemento de un valor numérico.
	// &= Hace una asignación AND bit a bit
	IE &= ~0x1000;
	HabilitarInterrupciones(); // IME=1;
}  

void InhibirIntTecla(int tecla){
	DeshabilitarInterrrupciones();
	TECLAS_CNT &= ~(1 << tecla);
	HabilitarInterrupciones();
}

void HabilitarIntTempo()
{


	// Habilitar las interrupciones del temporizador (timer0)
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	DeshabilitarInterrrupciones(); // IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	IE |= 0x0008;
	HabilitarInterrupciones(); // IME=1;
}

void InhibirIntTempo()
{

	// Deshabilitar las interrupciones del temporizador (timer0)
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	DeshabilitarInterrrupciones(); // IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	IE &= ~0x0008;
	HabilitarInterrupciones(); // IME=1;

}

void PonerEnMarchaTempo()
{
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	TIMER0_CNT|=0x0080;
}

void PararTempo()
{
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	TIMER0_CNT &=~ 0x0080;
}

/***********************2025-2026*******************************/

