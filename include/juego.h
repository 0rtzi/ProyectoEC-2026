// Curso 2025-2026

/*---------------------------------------------------------------------------------
juego.h
---------------------------------------------------------------------------------*/
void juego();

//GENERALES



    // Random
int randomInt(int min, int max);

//PROTAGONISTA
struct protagonista {
    int vidas;
    int X;
    int Y;
    int puntos;
};

extern int prota_cont_espera_mov;
extern int prota_cont_espera_mov_min;
extern int prota_pixel_mov;

extern struct protagonista prota;

extern void InicializarValoresProta();

extern void ActualizarPosicionProta();


// SETAS
extern int matriz_setas[12][16];

extern int seta_cont_espera_mostrar;

extern int seta_cont_espera_mostrar_max;

extern void InicializarValoresSetas();



/***********************2025-2026*******************************/

