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


extern void MostrarSpider(int indice, int x, int y);
/* Esta función dibuja una araña en la posición de pantalla x,y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126 */


extern void BorrarSpider(int indice, int x, int y);
/* Esta función borra de la pantalla la araña con el índice que se le indique como parámetro */

extern void MostrarChampi(int indice, int x, int y);
/* Esta función dibuja una seta en la posición de pantalla x,y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126 */


extern void BorrarChampi(int indice, int x, int y);
/* Esta función borra de la pantalla la seta con el índice que se le indique como parámetro */

extern void MostrarCenticuerpo(int indice, int x, int y);
/* Esta función dibuja parte del cuerpo del gusano en la posición de pantalla x,y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126 */


extern void BorrarCenticuerpo(int indice, int x, int y);
/* Esta función borra de la pantalla parte del cuerpo con el índice que se le indique como parámetro */

extern void MostrarCabeza(int indice, int x, int y);
/* Esta función dibuja la cabeza del gusano en la posición de pantalla x,y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126 */


extern void BorrarCabeza(int indice, int x, int y);
/* Esta función borra de la pantalla la cabeza con el índice que se le indique como parámetro */

/***********************2025-2026*******************************/

