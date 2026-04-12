// Curso 2025-2026

/*---------------------------------------------------------------------------------
juego.h
---------------------------------------------------------------------------------*/
void juego();

//GENERALES


    //Limpiar pantalla
    void LimpiarPantalla();
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

/* TODO: Programar función cargar prota. 
Tras recibir un golpe recarga el personaje en la posición X=122 Y=160;

*/
extern void CargarProta();

//DISPAROS
typedef struct {
    int activo;
    int X;
    int Y;
} disparo;

extern disparo disparos[10];

extern int disp_cont_espera_mov;
extern int disp_cont_espera_mov_min;

extern int disp_cont_espera;
extern int disp_cont_espera_min;

extern int disp_pixel_mov;

extern void CrearDisparo();

extern void MoverDisparos();

extern void DetectarColisionesDisparo();

// SETAS
typedef struct {
    int sprite_id;
    int vidas;
} casillaSeta;

extern casillaSeta matriz_setas[12][16];

extern volatile int seta_cont_espera_mostrar;

extern int seta_cont_espera_mostrar_max;

extern void InicializarValoresSetas();

extern int DetectarColisionesSetas(int idDisparo);

// CIMEPIÉS
typedef struct {

} parteCiempies;

/***********************2025-2026*******************************/

