// Curso 2025-2026

/*---------------------------------------------------------------------------------
juego.h
---------------------------------------------------------------------------------*/
void juego();

//PROTAGONISTA
struct protagonista {
    int vidas;
    int X;
    int Y;
};

extern int prota_cont_espera_mov;
extern int prota_cont_espera_mov_min;
extern int prota_pixel_mov;

extern struct protagonista prota;

extern void InicializarValoresProta();

extern void ActualizarPosicionProta();


/***********************2025-2026*******************************/

