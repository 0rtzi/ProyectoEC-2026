// Curso 2025-2026

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación */

#include "fondos.h"
#include "graficos.h"
#include "FondoPrueba.h"
#include "GameOver.h"
#include "definiciones.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria */
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarFondoPrueba() {
	ACCION=CARGANDO_FONDO;
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoPruebaBitmap, // Variable que se genera automáticamente 
                     (uint16 *)BG_BMP_RAM(0), // Dirección del fondo principal 
                     FondoPruebaBitmapLen); // Longitud en bytes, variable que se genera automáticamente 
}

void visualizarGameOver() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     GameOverBitmap, // Variable que se genera automáticamente 
                     (uint16 *)BG_BMP_RAM(0), // Dirección del fondo principal 
                     GameOverBitmapLen); // Longitud en bytes, variable que se genera automáticamente 
}

/***********************2025-2026*******************************/

