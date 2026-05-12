// Curso 2025-2026

/*---------------------------------------------------------------------------------
juego.h
---------------------------------------------------------------------------------*/
void juego();

/*=================================================================================
 * FUNCIONES GENERALES
 =================================================================================*/

/**
 * @brief Limpia la pantalla eliminando todos los sprites visibles
 * 
 * Oculta todos los sprites que se encuentran en pantalla, efectivamente limpiando
 * la visualización del juego. Útil para transiciones entre estados.
 */
extern void LimpiarPantalla();
    
/**
 * @brief Genera un número entero aleatorio entre min y max (incluidos)
 * 
 * @param[in] min Valor mínimo a devolver (incluido)
 * @param[in] max Valor máximo a devolver (incluido)
 * 
 * @return Número entero aleatorio en el rango [min, max]
 * 
 * @note El rango debe cumplir que min <= max
 */
extern int RandomInt(int min, int max);

//TODO: COMENTAR ESTA FUNCIÓN
extern int DetectarColision(int x1, int y1, int x2, int y2);

extern void InicializarVariablesPartida();

extern void MostrarMenu();

extern void MostrarGameOver();

extern void IniciarPartida();

extern int contador_tiempo_gameover;

/*=================================================================================
 * PROTAGONISTA (NAVE DEL JUGADOR)
 =================================================================================*/

/**
 * @brief Estructura que agrupa los datos y estado del protagonista (nave del jugador)
 * 
 * Contiene toda la información necesaria para representar y gestionar la nave
 * controlada por el jugador, incluyendo su posición, vidas y puntuación acumulada.
 */
typedef struct {
    int vidas;      /**< Número de vidas del protagonista. Rango: 0-3 */
    int X;          /**< Posición horizontal del protagonista en píxeles */
    int Y;          /**< Posición vertical del protagonista en píxeles */
    int puntos;     /**< Puntuación acumulada durante la partida. Comienza en 0 */
    int nivel;
} protagonista;


typedef struct {
    int tiempo;
    int tipo;
    int X;
    int Y;
} puntos;

/**
 * @brief Instancia global del protagonista
 */
extern protagonista prota;

/**
 * @brief Contador de ticks actual de espera para el movimiento del protagonista
 * 
 * Registra los ticks transcurridos desde el último movimiento. Se incrementa
 * en cada tick y se reinicia cuando alcanza prota_cont_espera_mov_min.
 */
extern int prota_cont_espera_mov;

/**
 * @brief Número mínimo de ticks antes de permitir un nuevo movimiento del protagonista
 * 
 * Define la velocidad de movimiento del protagonista. Menor valor = movimiento más rápido.
 * 
 * Se reinicia el contador prota_cont_espera_mov cuando alcanza este valor.
 */
extern int prota_cont_espera_mov_min;

/**
 * @brief Distancia en píxeles que se mueve el protagonista en cada acción de movimiento
 * 
 * Define el tamaño del paso de movimiento. Cada vez que el contador alcanza su máximo,
 * el protagonista se desplaza esta cantidad de píxeles en la dirección especificada.
 */
extern int prota_pixel_mov;

/**
 * @brief Inicializa todos los valores del protagonista al comenzar una partida o pantalla
 * 
 * Establece:
 * 
 * - vidas = 3 (número máximo de vidas)
 * 
 * - X = 122 (posición horizontal central)
 * 
 * - Y = 160 (posición vertical inferior)
 * 
 * - puntos = 0 (reinicia la puntuación)
 * 
 * - prota_cont_espera_mov = 0 (reinicia el contador de espera)
 * 
 * Al finalizar, dibuja el sprite del protagonista en pantalla.
 * 
 * @note Se debe llamar al inicio de cada partida
 */
extern void InicializarValoresProta();

/**
 * @brief Actualiza la posición visual del protagonista en la pantalla
 * 
 * Lee el estado actual del protagonista (vidas, X, Y, puntos) y redibuja su sprite
 * en las nuevas coordenadas. Debe llamarse después de modificar la posición X o Y
 * del protagonista para reflejar los cambios en pantalla.
 */
extern void ActualizarPosicionProta();

extern void DetectarColisionProtaCiempies();

/*=================================================================================
 * DISPAROS
 =================================================================================*/

/**
 * @brief Estructura que representa un disparo (proyectil) en el juego
 * 
 * Almacena el estado y la posición de cada proyectil disparado por el protagonista.
 * Se utiliza en un array para gestionar múltiples disparos simultáneos.
 */
typedef struct {
    int activo;     /**< Estado del disparo: 1=activo (visible en pantalla), 0=inactivo */
    int X;          /**< Posición horizontal actual del disparo en píxeles */
    int Y;          /**< Posición vertical actual del disparo en píxeles */
} disparo;

/**
 * @brief Array global de disparos activos
 * 
 * Almacena hasta 10 disparos simultáneos. Cada elemento es una estructura disparo
 * que contiene su estado (activo/inactivo) y posición (X, Y).
 */
extern disparo disparos[10];

/**
 * @brief Contador actual de espera para el movimiento de los disparos
 * 
 * Registra los ticks transcurridos desde el último movimiento de los disparos.
 * Se utiliza para controlar la velocidad de los proyectiles.
 */
extern int disp_cont_espera_mov;

/**
 * @brief Número mínimo de ticks antes de permitir un nuevo movimiento de los disparos
 * 
 * Define la velocidad de los proyectiles. Se modifica según la dificultad:
 * 
 * - Mayor valor = movimiento más lento
 * 
 * - Menor valor = movimiento más rápido
 */
extern int disp_cont_espera_mov_min;

/**
 * @brief Contador actual de espera para crear nuevos disparos
 * 
 * Implementa un rate-limiting para evitar que el jugador dispare demasiado rápido.
 * Se incrementa en cada tick y se reinicia cuando alcanza disp_cont_espera_min.
 */
extern int disp_cont_espera;

/**
 * @brief Tiempo mínimo de espera entre disparos consecutivos
 * 
 * Define la cadencia de fuego del protagonista. Valores más pequeños permiten
 * disparar con mayor frecuencia.
 */
extern int disp_cont_espera_min;

/**
 * @brief Distancia en píxeles que se mueven los disparos en cada paso
 * 
 * Define la velocidad de movimiento de cada proyectil en la pantalla.
 */
extern int disp_pixel_mov;

/**
 * @brief Crea un nuevo disparo en la posición actual del protagonista
 * 
 * Si el contador de espera entre disparos lo permite y hay espacio en el array
 * de disparos, crea un nuevo proyectil que comienza en la posición del protagonista
 * y está dirigido hacia arriba (incrementando la pantalla).
 * 
 * @note Solo se puede crear un disparo si ha pasado tiempo suficiente desde el último
 */
extern void CrearDisparo();

/**
 * @brief Actualiza la posición de todos los disparos activos
 * 
 * Mueve cada disparo activo en la pantalla según su velocidad. Los disparos que
 * salen de los límites de la pantalla se desactivan automáticamente.
 */
extern void MoverDisparos();

//TODO: COMENTAR ESTA FUNCIÓN
extern void DetectarColisionesDisparo(int idDisparo);

/**
 * @brief Detecta y procesa colisiones de un disparo específico con las setas
 * 
 * Verifica si el disparo con ID especificado colisiona con alguna seta en la matriz.
 * Si hay colisión:
 * 
 * - Decrementa las vidas de la seta (aumenta su daño)
 * 
 * - Si las vidas llegan a 0, elimina la seta
 * 
 * - Devuelve 1 para indicar colisión
 * 
 * @param[in] idDisparo Índice del disparo a verificar (0-9)
 * 
 * @note Un disparo solo puede colisionar con una seta por llamada
 */
extern void DetectarColisionesDisparoSetas(int idDisparo);

/**
 * @brief Detecta y procesa colisiones de un disparo específico con cada una de las partes del ciempies
 * 
 * Verifica si el disparo con ID especificado colisiona con alguna seta en la matriz.
 * Si hay colisión:
 * 
 * - Decrementa las vidas de la seta (aumenta su daño)
 * 
 * - Si las vidas llegan a 0, elimina la seta
 * 
 * - Devuelve 1 para indicar colisión
 * 
 * @param[in] idDisparo Índice del disparo a verificar (0-9)
 * 
 * @note Un disparo solo puede colisionar con una seta por llamada
 */
extern void DetectarColisionesDisparoCiempies(int idDisparo);

/*=================================================================================
 * SETAS (OBSTÁCULOS)
 =================================================================================*/

/**
 * @brief Estructura que representa una seta en la matriz del juego
 * 
 * Las setas son obstáculos que aparecen cuando se dispara a un enemigo o se pierden vidas.
 * Pueden ser eliminadas disparándoles 4 veces, cambiando de apariencia con cada impacto.
 * El ciempiés las usa para cambiar de dirección.
 */
typedef struct {
    int sprite_id;  /**< ID del sprite visual asociado a la seta. -1 si no existe seta en esta celda */
    int vidas;      /**< Número de impactos que puede recibir la seta antes de desaparecer. Rango: 0-4 */
} casillaSeta;

/**
 * @brief Matriz global que almacena todas las setas del juego
 * 
 * Matriz de 12 filas × 16 columnas que representa la distribución de setas en la pantalla.
 * Cada celda contiene información sobre si hay seta, su sprite y su estado (vidas).
 * Dimensiones:
 * 
 * - Filas (Y): 12 (de arriba a abajo)
 * 
 * - Columnas (X): 16 (de izquierda a derecha)
 */
extern casillaSeta matriz_setas[9][16];

/**
 * @brief Contador volátil actual para controlar la visualización de setas
 * 
 * Se utiliza para sincronizar la renderización de setas con el temporizador.
 * Debe ser volátil porque se modifica desde rutinas de interrupción.
 */
extern volatile int seta_cont_espera_mostrar;

/**
 * @brief Número máximo de ticks entre actualizaciones de visualización de setas
 * 
 * Define cada cuántos ticks se debe actualizar la visualización de las setas.
 * Controla la velocidad de refresco visual de los obstáculos.
 */
extern int seta_cont_espera_mostrar_max;

/**
 * @brief Inicializa la matriz de setas limpiando todas las celdas
 * 
 * Establece todas las setas como inactivas (sprite_id = -1) y vidas = 0.
 * Prepara el juego para una nueva partida o pantalla sin obstáculos.
 * 
 * @note Debe llamarse al inicio de cada pantalla/partida
 */
extern void InicializarValoresSetas();

/*=================================================================================
 * ENEMIGOS
 =================================================================================*/

/**
 * @brief Contador actual de espera para el movimiento de todos los enemigos
 * 
 * Registra los ticks transcurridos desde el último movimiento de los enemigos.
 * Se utiliza para sincronizar el movimiento de todas las entidades enemigas.
 */
extern int enem_cont_espera_mov;

/**
 * @brief Número mínimo de ticks antes de permitir un nuevo movimiento de enemigos
 * 
 * Define la velocidad de los enemigos. Se modifica según la dificultad:
 * - Mayor valor = movimiento más lento
 * - Menor valor = movimiento más rápido (dificultad aumentada)
 */
extern int enem_cont_espera_mov_min;

/*----------------------------------------------------------------------------------
 * CIEMPIÉS (ENEMIGO PRINCIPAL)
 ----------------------------------------------------------------------------------*/

/**
 * @brief Distancia en píxeles que se mueve el ciempiés en cada paso
 * 
 * Define la velocidad visual del movimiento del ciempiés en la pantalla.
 */
extern int ciempies_pixel_mov;

/**
 * @brief Estructura que representa una parte individual del cuerpo del ciempiés
 * 
 * El ciempiés está compuesto por múltiples segmentos conectados. Cada segmento
 * tiene su propia posición, estado y datos. Cuando se dispara a una parte que no
 * es la cabeza, el ciempiés se divide en dos entidades separadas.
 */
typedef struct {
    int activo;     /**< Estado del segmento: 1=vivo (visible), 0=muerto (eliminado) */
    int id;         /**< Identificador único del ciempiés */
    int parte;      /**< Número de parte en el cuerpo: 0=cabeza, 1+=cuerpo */
    int X;          /**< Posición horizontal actual del segmento en píxeles */
    int Y;          /**< Posición vertical actual del segmento en píxeles */
    int direccion;  /**< Dirección del movimiento: 1=arriba, 2=Derecha, 3=Abajo, 4=Izquierda */
    int longitud;   /**< Longitud total del ciempiés desde este segmento (en número de partes) */
} parteCiempies;

/**
 * @brief Inicializa todos los valores del ciempiés al comenzar una pantalla
 * 
 * Crea y posiciona el ciempiés en la pantalla con su configuración inicial:
 * 
 * - Posición en la parte superior central
 * 
 * - Dirección inicial de movimiento
 * 
 * - Longitud inicial completa
 * 
 * - Todos los segmentos marcados como activos
 * 
 * @note Debe llamarse al inicio de cada pantalla/nivel
 */
extern void InicializarValoresCiempies();

/**
 * @brief Actualiza la posición de todos los segmentos del ciempiés
 * 
 * Mueve cada segmento activo del ciempiés en la pantalla según su velocidad y dirección.
 * El movimiento se controla mediante el contador de espera enem_cont_espera_mov.
 * 
 * El ciempiés detecta automáticamente colisiones con las setas de la matriz para cambiar
 * de dirección cuando es necesario. Si choca con los bordes de la pantalla, también invierte
 * su dirección horizontal y baja una posición en el eje Y.
 * 
 * Cada segmento del ciempiés mantiene una relación de posición relativa con el segmento
 * anterior, formando así el cuerpo continuo del enemigo.
 * 
 * @see enem_cont_espera_mov, enem_cont_espera_mov_min, ciempies_pixel_mov
 */
extern void MoverCiempies();

//TODO: Documentar función
extern int QuedanCiempiesVivos();

//TODO: Documentar función
extern void EstablecerPuntos(int cuantosPuntos, int x, int y);

/*=================================================================================
 * FIN DE JUEGO.H - Curso 2025-2026
 =================================================================================*/

