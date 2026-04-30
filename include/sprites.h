// Curso 2025-2026

extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;
extern u16* gfx_prota;
extern u16* gfx_disparo;
extern u16* gfx_spider;
extern u16* gfx_seta;
extern u16* gfx_seta3;
extern u16* gfx_seta2;
extern u16* gfx_seta1;
extern u16* gfx_ciempies_cuerpo;
extern u16* gfx_ciempies_cabeza_izquierda;
extern u16* gfx_ciempies_cabeza_abajo;
extern u16* gfx_ciempies_cabeza_derecha;
extern u16* gfx_ciempies_cabeza_arriba;

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

extern void BorrarCabezaCiempies(int id, int oldDir, int X, int Y);

extern void ActualizarSpritesCiempiesCabeza(int id, int oldDir, int X, int Y, int newDir, int newX, int newY);

/***********************2025-2026*******************************/

//Scooby-Doo