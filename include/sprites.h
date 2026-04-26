// Curso 2025-2026

extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;
extern u16* gfxprota;
extern u16* gfxdisparo;
extern u16* gfxspider;
extern u16* gfxseta;
extern u16* gfxseta_3;
extern u16* gfxseta_2;
extern u16* gfxseta_1;
extern u16* gfxcenticuerpo;
extern u16* gfxcabezaizq;
extern u16* gfxcabezabajo;
extern u16* gfxcabezadrcha;
extern u16* gfxcabezarriba;

extern void memoriaReserva();

/* Para cada uno de los 256 valores que puede tomar un Píxel le da un color en la pantalla principal. El valor 0 es transparente y los valores sin definir, negros */
extern void EstablecerPaleta1();


/* Para cada uno de los 256 valores que puede tomar un Píxel le da un color en la pantalla secundaria. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaleta2();

extern void EstablecerPaleta3();

extern void EstablecerPaleta4();


/* Carga en memoria los Sprites dibujados */
extern void GuardarSpritesMemoria();

/* Esta función dibuja al protagonista en la posición de pantalla x,y.*/
extern void MostrarProta(int indice, int x, int y);

/* Esta función borra de la pantalla al protagonista con el índice que se le indique como parámetro */
extern void BorrarProta(int indice, int x, int y);


/* Esta función dibuja un disparo en la posición de pantalla x,y.*/
extern void MostrarDisparo(int indice, int x, int y);

/* Esta función borra de la pantalla el disparo con el índice que se le indique como parámetro */
extern void BorrarDisparo(int indice, int x, int y);


/* Esta función dibuja una araña en la posición de pantalla x,y.*/
extern void MostrarSpider(int indice, int x, int y);

/* Esta función borra de la pantalla la araña con el índice que se le indique como parámetro */
extern void BorrarSpider(int indice, int x, int y);


/* Esta función dibuja una seta en la posición de pantalla x,y.*/
extern void MostrarSeta(int indice, int x, int y);

/* Esta función borra de la pantalla la seta con el índice que se le indique como parámetro */
extern void BorrarSeta(int indice, int x, int y);

/* Esta función actualiza el sprite de la seta a dibujar dependiendo de las vidas de esta misma*/
extern void ActualizarSpriteSetas(int ind, int vidas, int x, int y);


/* Esta función dibuja parte del cuerpo del gusano en la posición de pantalla x,y.*/
extern void MostrarCenticuerpo(int indice, int x, int y);

/* Esta función borra de la pantalla parte del cuerpo con el índice que se le indique como parámetro */
extern void BorrarCenticuerpo(int indice, int x, int y);


/* Esta función dibuja la cabeza mirando hacia la izq del gusano en la posición de pantalla x,y.*/
extern void MostrarCabezaIzq(int indice, int x, int y);

/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */
extern void BorrarCabezaIzq(int indice, int x, int y);

/* Esta función dibuja la cabeza mirando hacia abajo del gusano en la posición de pantalla x,y.*/
extern void MostrarCabezaBajo(int indice, int x, int y);

/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */
extern void BorrarCabezaBajo(int indice, int x, int y);

/* Esta función dibuja la cabeza mirando hacia la derecha del gusano en la posición de pantalla x,y.*/
extern void MostrarCabezaDrcha(int indice, int x, int y);

/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */
extern void BorrarCabezaDrcha(int indice, int x, int y);

/* Esta función dibuja la cabeza mirando hacia arriba del gusano en la posición de pantalla x,y.*/
extern void MostrarCabezaRriba(int indice, int x, int y);

/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */
extern void BorrarCabezaRriba(int indice, int x, int y);

/***********************2025-2026*******************************/

//Scooby-Doo