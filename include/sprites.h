// Curso 2025-2026

extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaReserva();

extern void EstablecerPaletaPrincipal();
/* Para cada uno de los 256 valores que puede tomar un Píxel le da un color en la pantalla principal. El valor 0 es transparente y los valores sin definir, negros */


extern void EstablecerPaletaSecundaria();
/* Para cada uno de los 256 valores que puede tomar un Píxel le da un color en la pantalla secundaria. El valor 0 es transparente y los valores sin definir negros */


extern void GuardarSpritesMemoria();
/* Carga en memoria los Sprites dibujados */

extern void MostrarProta(int indice, int x, int y);
/* Esta función dibuja una araña en la posición de pantalla x,y.*/

extern void BorrarProta(int indice, int x, int y);
/* Esta función borra de la pantalla al protagonista con el índice que se le indique como parámetro */

extern void MostrarSpider(int indice, int x, int y);
/* Esta función dibuja una araña en la posición de pantalla x,y.*/


extern void BorrarSpider(int indice, int x, int y);
/* Esta función borra de la pantalla la araña con el índice que se le indique como parámetro */

extern void MostrarChampi(int indice, int x, int y);
/* Esta función dibuja una seta en la posición de pantalla x,y.*/


extern void BorrarChampi(int indice, int x, int y);
/* Esta función borra de la pantalla la seta con el índice que se le indique como parámetro */

extern void MostrarCenticuerpo(int indice, int x, int y);
/* Esta función dibuja parte del cuerpo del gusano en la posición de pantalla x,y.*/


extern void BorrarCenticuerpo(int indice, int x, int y);
/* Esta función borra de la pantalla parte del cuerpo con el índice que se le indique como parámetro */

extern void MostrarCabezaIzq(int indice, int x, int y);
/* Esta función dibuja la cabeza mirando hacia la izq del gusano en la posición de pantalla x,y.*/


extern void BorrarCabezaIzq(int indice, int x, int y);
/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */

extern void MostrarCabezaBajo(int indice, int x, int y);
/* Esta función dibuja la cabeza mirando hacia abajo del gusano en la posición de pantalla x,y.*/


extern void BorrarCabezaBajo(int indice, int x, int y);
/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */

extern void MostrarCabezaDrcha(int indice, int x, int y);
/* Esta función dibuja la cabeza mirando hacia la derecha del gusano en la posición de pantalla x,y.*/


extern void BorrarCabezaDrcha(int indice, int x, int y);
/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */

extern void MostrarCabezaRriba(int indice, int x, int y);
/* Esta función dibuja la cabeza mirando hacia arriba del gusano en la posición de pantalla x,y.*/


extern void BorrarCabezaRriba(int indice, int x, int y);
/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */

/***********************2025-2026*******************************/

