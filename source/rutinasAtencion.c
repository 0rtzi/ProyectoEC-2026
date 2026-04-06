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

int ESTADO; // Para controlar el estado del autómata en que esté

void RutAtencionTeclado ()
{
if (ESTADO == MENU)
{	
	if (TeclaPulsada() == A){ 
		ESTADO = PARTIDA;
		visualizarFondoPrueba();
		MostrarSpider(1, 5, 5);
		MostrarChampi(2, 30, 30);
		MostrarChampi(3, 30, 60);
		MostrarChampi(4, 30, 90);
		MostrarCenticuerpo(5, 80, 60);
		MostrarCabeza(6, 60, 60);

	}
}
else if (ESTADO == PARTIDA)
{
	if (TeclaPulsada() == B){ //esto lo he puesto para ver si cambia bien
		ESTADO=GAMEOVER;
		visualizarGameOver();
		BorrarSpider(1, 5, 5);
		BorrarChampi(2, 30, 30);
		BorrarChampi(3, 30, 60);
		BorrarChampi(4, 30, 90);
		BorrarCenticuerpo(5, 80, 60);
		BorrarCabeza(6, 60, 60);

	}
}
else if (ESTADO == GAMEOVER)
{
	if(TeclaPulsada() == START){
		ESTADO = MENU;
		visualizarFondoPrueba();
	}
}
}

/* void RutAtencionTempo()
{
	static int tick=0;
	

	if (ESTADO!=MENU)
	{
		tick++; 
		if (tick==5)
		{
			tick=0;
			if (ESTADO == GAMEOVER)
			{
				visualizarGameOver();
				ESTADO=PARTIDA;
				BorrarSpider(1, 5, 5);
				BorrarChampi(2, 30, 30);
			}
					
		}
	}
	
} */

void EstablecerVectorInt()
{
// A COMPLETAR POR USTEDES
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	// irqSet(IRQ_TIMER0, RutAtencionTempo);
}

/***********************2025-2026*******************************/

