// Curso 2025-2026

/*---------------------------------------------------------------------------------
Código desarrollado basado en el ejemplo "Simple sprite demo" de dovoto y en otro de Jaeden Amero.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxprota;
u16* gfxdisparo;
u16* gfxspider;
u16* gfxchampi;
u16* gfxcenticuerpo;
u16* gfxcabeza;


/* Reservar memoria para cada sprite que se quiera mostrar en pantalla */
void memoriaReserva()
{
	/* Por cada sprite que se quiera incluir en la pantalla principal hay que hacer algo equivalente a lo que sigue */
	gfxprota= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdisparo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxspider= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxchampi= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxcenticuerpo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxcabeza= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un píxel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES */
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); 
	SPRITE_PALETTE[2] = RGB15(0,31,0); 
	SPRITE_PALETTE[3] = RGB15(31,31,31);    
	SPRITE_PALETTE[4] = RGB15(0, 31, 0);       
	SPRITE_PALETTE[5] = RGB15(0, 0, 31);       
	SPRITE_PALETTE[6] = RGB15(0, 0, 0);        
	SPRITE_PALETTE[7] = RGB15(0, 31, 31);      
	SPRITE_PALETTE[8] = RGB15(31, 0, 31);      
	SPRITE_PALETTE[9] = RGB15(16, 16, 16);     
	SPRITE_PALETTE[10] = RGB15(24, 24, 24);    
	SPRITE_PALETTE[11] = RGB15(8, 8, 8);       
	SPRITE_PALETTE[12] = RGB15(31, 16, 0);     
	SPRITE_PALETTE[13] = RGB15(16, 0, 0);      
	SPRITE_PALETTE[14] = RGB15(20, 10, 0);     
	SPRITE_PALETTE[15] = RGB15(16, 0, 31);     
	SPRITE_PALETTE[16] = RGB15(24, 16, 31);    
	SPRITE_PALETTE[17] = RGB15(31, 20, 28);    
	SPRITE_PALETTE[18] = RGB15(16, 24, 31);    
	SPRITE_PALETTE[19] = RGB15(0, 0, 16);      
	SPRITE_PALETTE[20] = RGB15(0, 31, 16);     
	SPRITE_PALETTE[21] = RGB15(0, 16, 0);      
	SPRITE_PALETTE[22] = RGB15(16, 20, 0);     
	SPRITE_PALETTE[23] = RGB15(24, 31, 16);
}

/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho */

u8 sprite_prota[256] =
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	 //	0	0	0	0	0	0	3	0	0	3	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	3	0	0	3	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	0	0	0	0	3	0	0	0	0	0
0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	0	0	0	0	3	0	0	0	0	0
0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	3	0	0	0	0	3	0	0	0	0	0
0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	3	0	0	0	0	0	0	3	0	0	0	0
0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	3	0	0	0	0	0	0	3	0	0	0	0
0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	3	0	0	0	0	0	0	0	0	3	0	0	0
0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	3	0	0	0	0	0	0	0	0	3	0	0	0
0	,	0	,	0	,	3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	3	0	0	0	0	0	0	0	0	0	0	3	0	0
0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	 //	0	0	3	0	0	0	0	0	0	0	0	0	0	3	0	0
0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	 //	0	0	3	0	0	0	0	0	0	0	0	0	0	3	0	0
0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	 //	0	0	0	3	3	3	3	3	3	3	3	3	3	0	0	0
3	,	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0

};

u8 sprite_disparo[256] =
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0
3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	3	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	3	3	0	0	0	0	0	0	0

};

u8 spider[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	12	,	0	,	0	,	0	,	0	,	0	,	0	,	12	,	12	,	 //	0	0	0	0	0	0	0	12	12	0	0	0	0	0	0	0
0	,	12	,	0	,	0	,	0	,	0	,	12	,	12	,	12	,	12	,	12	,	0	,	0	,	2	,	23	,	2	,	 //	0	0	0	0	0	0	12	12	12	12	0	0	0	0	0	0
12	,	0	,	12	,	12	,	2	,	23	,	2	,	0	,	14	,	0	,	0	,	2	,	23	,	2	,	23	,	2	,	 //	0	12	0	0	0	0	12	12	12	12	0	0	0	0	12	0
0	,	0	,	0	,	23	,	2	,	23	,	2	,	0	,	0	,	0	,	0	,	2	,	23	,	2	,	23	,	2	,	 //	12	12	12	0	0	2	23	2	23	2	23	0	0	12	12	12
12	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	12	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	12	0	12	12	2	23	2	23	2	23	2	23	12	12	0	12
12	,	12	,	0	,	0	,	0	,	0	,	12	,	0	,	23	,	2	,	23	,	0	,	0	,	12	,	12	,	12	,	 //	0	0	0	2	23	2	23	2	23	2	23	2	23	0	0	0
2	,	23	,	2	,	23	,	12	,	12	,	0	,	12	,	23	,	2	,	23	,	2	,	23	,	0	,	0	,	0	,	 //	0	0	0	23	2	23	2	23	2	23	2	23	2	0	0	0
2	,	23	,	2	,	23	,	2	,	0	,	0	,	0	,	23	,	2	,	23	,	2	,	23	,	0	,	0	,	0	,	 //	0	0	0	2	23	2	23	2	23	2	23	2	23	0	0	0
0	,	0	,	0	,	23	,	2	,	23	,	2	,	23	,	0	,	0	,	0	,	2	,	23	,	2	,	23	,	2	,	 //	0	0	0	23	2	23	2	23	2	23	2	23	2	0	0	0
0	,	0	,	0	,	23	,	2	,	23	,	2	,	23	,	0	,	12	,	0	,	2	,	23	,	2	,	23	,	2	,	 //	0	0	0	2	23	2	23	2	23	2	23	2	23	0	0	0
12	,	12	,	12	,	12	,	2	,	23	,	2	,	23	,	12	,	0	,	0	,	12	,	12	,	2	,	23	,	2	,	 //	0	0	0	23	2	23	2	23	2	23	2	23	2	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	2	,	23	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	2	,	 //	0	12	0	2	23	2	23	2	23	2	23	2	23	0	12	0
2	,	23	,	2	,	23	,	2	,	0	,	0	,	0	,	23	,	2	,	23	,	2	,	23	,	0	,	0	,	0	,	 //	12	12	12	12	2	23	2	23	2	23	2	23	12	12	12	12
2	,	23	,	2	,	23	,	2	,	0	,	0	,	0	,	23	,	2	,	23	,	2	,	23	,	0	,	12	,	0	,	 //	12	0	0	12	12	2	23	2	23	2	23	12	12	0	0	12
2	,	23	,	2	,	23	,	12	,	12	,	12	,	12	,	23	,	2	,	23	,	12	,	12	,	0	,	0	,	12	,	 //	0	0	0	0	0	0	2	23	2	23	0	0	0	0	0	0
2	,	23	,	0	,	0	,	0	,	0	,	0	,	0	,	23	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	0	0	0	2	23	0	0	0	0	0	0	0

};

u8 champi[256] = 
{
0	,	0	,	0	,	0	,	0	,	15	,	15	,	20	,	0	,	0	,	0	,	0	,	15	,	20	,	20	,	15	,	 //	0	0	0	0	0	15	15	20	15	15	20	0	0	0	0	0
0	,	0	,	0	,	20	,	15	,	15	,	15	,	15	,	0	,	0	,	15	,	20	,	15	,	15	,	15	,	15	,	 //	0	0	0	0	15	20	20	15	15	15	20	15	0	0	0	0
0	,	0	,	15	,	20	,	15	,	15	,	15	,	0	,	14	,	15	,	15	,	20	,	15	,	20	,	15	,	15	,	 //	0	0	0	20	15	15	15	15	15	15	20	15	15	0	0	0
0	,	20	,	20	,	15	,	15	,	15	,	15	,	0	,	0	,	15	,	15	,	15	,	15	,	20	,	20	,	20	,	 //	0	0	15	20	15	15	15	15	15	20	15	20	20	20	0	0
15	,	15	,	20	,	0	,	0	,	0	,	0	,	0	,	0	,	15	,	20	,	15	,	0	,	0	,	0	,	0	,	 //	0	0	15	20	15	15	15	15	20	20	20	15	15	15	0	0
15	,	15	,	20	,	15	,	15	,	0	,	0	,	0	,	15	,	20	,	15	,	20	,	20	,	20	,	0	,	0	,	 //	0	15	15	20	15	20	15	15	15	20	15	15	15	15	15	0
20	,	20	,	20	,	15	,	15	,	15	,	0	,	0	,	15	,	20	,	15	,	15	,	15	,	15	,	15	,	0	,	 //	0	20	20	15	15	15	15	15	15	15	15	15	15	20	20	0
15	,	15	,	15	,	15	,	15	,	20	,	20	,	0	,	20	,	15	,	15	,	15	,	20	,	15	,	15	,	15	,	 //	15	15	15	15	15	20	20	20	20	15	15	15	20	15	15	15
15	,	15	,	15	,	15	,	20	,	15	,	15	,	15	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	 //	15	15	15	15	20	15	15	15	15	20	15	15	20	15	15	15
0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
15	,	20	,	15	,	15	,	20	,	15	,	15	,	15	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0
16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	16	,	16	,	16	,	16	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	16	16	16	16	16	16	16	16	0	0	0	0

};

u8 centicuerpo[256] = 
{
0	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	0	,	0	,	0	,	8	,	17	,	17	,	17	,	17	,	 //	0	0	0	0	8	8	8	8	8	8	8	8	0	0	0	0
0	,	0	,	8	,	17	,	8	,	8	,	8	,	8	,	0	,	8	,	17	,	8	,	17	,	17	,	17	,	17	,	 //	0	0	0	8	17	17	17	17	17	17	17	17	8	0	0	0
8	,	17	,	8	,	17	,	17	,	8	,	8	,	0	,	14	,	17	,	8	,	17	,	8	,	8	,	17	,	17	,	 //	0	0	8	17	8	8	8	8	8	8	8	8	17	8	0	0
8	,	17	,	8	,	17	,	8	,	17	,	8	,	0	,	0	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	 //	0	8	17	8	17	17	17	17	17	17	17	17	8	17	8	0
8	,	8	,	8	,	8	,	0	,	0	,	0	,	0	,	0	,	17	,	17	,	17	,	8	,	0	,	0	,	0	,	 //	8	17	8	17	17	8	8	8	8	8	8	17	17	8	17	8
8	,	8	,	8	,	8	,	17	,	8	,	0	,	0	,	17	,	17	,	17	,	17	,	8	,	17	,	8	,	0	,	 //	8	17	8	17	8	8	17	17	17	17	8	8	17	8	17	8
8	,	8	,	8	,	17	,	17	,	8	,	17	,	8	,	17	,	17	,	8	,	8	,	17	,	8	,	17	,	8	,	 //	8	17	8	17	8	17	8	8	8	8	17	8	17	8	17	8
8	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	 //	8	17	8	17	8	17	8	17	17	8	17	8	17	8	17	8
8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	8	,	 //	8	17	8	17	8	17	8	17	17	8	17	8	17	8	17	8
8	,	17	,	8	,	17	,	8	,	8	,	17	,	17	,	8	,	17	,	8	,	17	,	17	,	8	,	8	,	8	,	 //	8	17	8	17	8	17	8	8	8	8	17	8	17	8	17	8
0	,	8	,	17	,	8	,	17	,	17	,	17	,	17	,	0	,	0	,	8	,	17	,	8	,	8	,	8	,	8	,	 //	8	17	8	17	8	8	17	17	17	17	8	8	17	8	17	8
0	,	0	,	0	,	8	,	17	,	17	,	17	,	17	,	0	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	 //	8	17	8	17	17	8	8	8	8	8	8	17	17	8	17	8
17	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	8	,	8	,	17	,	8	,	17	,	8	,	17	,	8	,	 //	0	8	17	8	17	17	17	17	17	17	17	17	8	17	8	0
17	,	17	,	8	,	8	,	17	,	8	,	17	,	8	,	8	,	8	,	8	,	17	,	17	,	8	,	17	,	8	,	 //	0	0	8	17	8	8	8	8	8	8	8	8	17	8	0	0
17	,	17	,	17	,	17	,	8	,	17	,	8	,	0	,	8	,	8	,	8	,	8	,	17	,	8	,	0	,	0	,	 //	0	0	0	8	17	17	17	17	17	17	17	17	8	0	0	0
17	,	17	,	17	,	17	,	8	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	8	8	8	8	8	8	8	8	0	0	0	0

};

u8 cabeza[256]=
{
0	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	0	,	0	,	0	,	8	,	17	,	17	,	17	,	17	,	 //	0	0	0	0	8	8	8	8	8	8	8	8	0	0	0	0
0	,	0	,	8	,	17	,	17	,	17	,	17	,	17	,	0	,	8	,	17	,	17	,	6	,	6	,	6	,	17	,	 //	0	0	0	8	17	17	17	17	17	17	17	17	8	0	0	0
8	,	17	,	17	,	17	,	6	,	6	,	6	,	0	,	14	,	8	,	8	,	17	,	6	,	6	,	6	,	17	,	 //	0	0	8	17	17	17	17	17	17	17	17	17	17	8	0	0
0	,	0	,	0	,	8	,	17	,	17	,	17	,	0	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	8	,	 //	0	8	17	17	6	6	6	17	17	17	17	17	17	3	8	0
8	,	8	,	8	,	8	,	0	,	0	,	0	,	0	,	0	,	17	,	17	,	17	,	8	,	0	,	0	,	0	,	 //	8	17	17	17	6	6	6	17	17	8	8	17	3	17	17	8
17	,	17	,	17	,	17	,	17	,	8	,	0	,	0	,	17	,	17	,	17	,	17	,	17	,	3	,	8	,	0	,	 //	0	8	8	17	6	6	6	17	8	8	17	3	17	17	17	8
17	,	8	,	8	,	17	,	3	,	17	,	17	,	8	,	8	,	8	,	17	,	3	,	17	,	17	,	17	,	8	,	 //	0	0	0	8	17	17	17	8	8	17	3	17	17	17	17	8
8	,	17	,	3	,	17	,	17	,	17	,	17	,	8	,	17	,	17	,	17	,	17	,	17	,	17	,	17	,	8	,	 //	0	0	0	8	8	8	8	8	17	17	17	17	17	17	17	8
0	,	0	,	0	,	8	,	8	,	8	,	8	,	8	,	0	,	0	,	0	,	8	,	17	,	17	,	17	,	8	,	 //	0	0	0	8	8	8	8	8	17	17	17	17	17	17	17	8
0	,	8	,	8	,	17	,	6	,	6	,	6	,	17	,	8	,	17	,	17	,	17	,	6	,	6	,	6	,	17	,	 //	0	0	0	8	17	17	17	8	8	17	3	17	17	17	17	8
0	,	8	,	17	,	17	,	6	,	6	,	6	,	17	,	0	,	0	,	8	,	17	,	17	,	17	,	17	,	17	,	 //	0	8	8	17	6	6	6	17	8	8	17	3	17	17	17	8
0	,	0	,	0	,	8	,	17	,	17	,	17	,	17	,	0	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	 //	8	17	17	17	6	6	6	17	17	8	8	17	3	17	17	8
17	,	17	,	17	,	17	,	17	,	17	,	17	,	8	,	8	,	17	,	3	,	17	,	17	,	17	,	17	,	8	,	 //	0	8	17	17	6	6	6	17	17	17	17	17	17	3	8	0
8	,	8	,	17	,	3	,	17	,	17	,	17	,	8	,	17	,	8	,	8	,	17	,	3	,	17	,	17	,	8	,	 //	0	0	8	17	17	17	17	17	17	17	17	17	17	8	0	0
17	,	17	,	17	,	17	,	17	,	3	,	8	,	0	,	17	,	17	,	17	,	17	,	17	,	8	,	0	,	0	,	 //	0	0	0	8	17	17	17	17	17	17	17	17	8	0	0	0
17	,	17	,	17	,	17	,	8	,	0	,	0	,	0	,	8	,	8	,	8	,	8	,	0	,	0	,	0	,	0	,	 //	0	0	0	0	8	8	8	8	8	8	8	8	0	0	0	0

};
/* Carga en memoria cada uno de los sprites que hemos dibujado */

void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxprota[i] = sprite_prota[i*2] | (sprite_prota[(i*2)+1]<<8);
		gfxspider[i] = spider[i*2] | (spider[(i*2)+1]<<8);		
		gfxchampi[i] = champi[i*2] | (champi[(i*2)+1]<<8);
		gfxcenticuerpo[i] = centicuerpo[i*2] | (centicuerpo[(i*2)+1]<<8);
		gfxcabeza[i]=cabeza[i*2] | (cabeza[(i*2)+1]<<8);
	}
}

void MostrarProta(int indice, int x, int y)
{
oamSet(&oamMain, // main graphics engine context
	indice,           // oam index (0 to 127)  
	x, y,   // x and y pixel location of the sprite
	0,                    // priority, lower renders last (on top)
	0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxprota,// +16*16/2,      // pointer to the loaded graphics
	-1,                  // sprite rotation data  
	false,               // double the size when rotating?
	false,			// hide the sprite?
	false, false, // vflip, hflip
	false	// apply mosaic
	); 
	  
oamUpdate(&oamMain);  
};

void BorrarProta(int indice, int x, int y)
{
oamSet(&oamMain, // main graphics engine context
	indice,           // oam index (0 to 127)  
	x, y,   // x and y pixel location of the sprite
	0,                    // priority, lower renders last (on top)
	0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxprota,// +16*16/2,      // pointer to the loaded graphics
	-1,                  // sprite rotation data  
	false,               // double the size when rotating?
	false,			// hide the sprite?
	false, false, // vflip, hflip
	false	// apply mosaic
	); 
	  
oamUpdate(&oamMain);  
};

void MostrarDisparo(int indice, int x, int y)
{
oamSet(&oamMain, // main graphics engine context
	indice,           // oam index (0 to 127)  
	x, y,   // x and y pixel location of the sprite
	0,                    // priority, lower renders last (on top)
	0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxdisparo,// +16*16/2,      // pointer to the loaded graphics
	-1,                  // sprite rotation data  
	false,               // double the size when rotating?
	false,			// hide the sprite?
	false, false, // vflip, hflip
	false	// apply mosaic
	); 
	  
oamUpdate(&oamMain);  
};

void BorrarDisparo(int indice, int x, int y)
{
oamSet(&oamMain, // main graphics engine context
	indice,           // oam index (0 to 127)  
	x, y,   // x and y pixel location of the sprite
	0,                    // priority, lower renders last (on top)
	0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxdisparo,// +16*16/2,      // pointer to the loaded graphics
	-1,                  // sprite rotation data  
	false,               // double the size when rotating?
	false,			// hide the sprite?
	false, false, // vflip, hflip
	false	// apply mosaic
	); 
	  
oamUpdate(&oamMain);  
};

/* Esta función dibuja una araña en la posición x, y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un índice distinto, un valor entre 0 y 126 */

void MostrarSpider(int indice, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxspider,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta función borra de la pantalla la araña con el índice indicado */
void BorrarSpider(int indice, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxspider,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarChampi(int indice, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxchampi,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void BorrarChampi(int indice, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxchampi,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarCenticuerpo(int indice, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxcenticuerpo,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void BorrarCenticuerpo(int indice, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxcenticuerpo,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarCabeza(int indice, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxcabeza,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void BorrarCabeza(int indice, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,			  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxcabeza,// +16*16/2,      // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}


/***********************2025-2026*******************************/


