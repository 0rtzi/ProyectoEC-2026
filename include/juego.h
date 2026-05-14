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

/**
 * @brief Detecta colisión entre dos objetos basándose en su posición en píxeles
 * 
 * Comprueba si dos objetos comparten la misma celda de la matriz (16×16 píxeles).
 * Convierte las coordenadas de píxeles a índices de matriz (dividiendo entre 16)
 * y compara si pertenecen a la misma celda.
 * 
 * @param[in] x1 Posición horizontal del primer objeto en píxeles
 * @param[in] y1 Posición vertical del primer objeto en píxeles
 * @param[in] x2 Posición horizontal del segundo objeto en píxeles
 * @param[in] y2 Posición vertical del segundo objeto en píxeles
 * 
 * @return 1 si hay colisión (en la misma celda), 0 si no hay colisión
 */
extern int DetectarColision(int x1, int y1, int x2, int y2);

/**
 * @brief Inicializa todas las variables necesarias para el comienzo de una nueva partida
 * 
 * Establece los valores iniciales de:
 * 
 * - prota.vidas = 3 (número máximo de vidas)
 * 
 * - prota.puntos = 0 (reinicia la puntuación)
 * 
 * - prota.nivel = 0 (nivel inicial)
 * 
 * - prota.X = CENTRO_HORIZONTAL (posición horizontal central)
 * 
 * - prota.Y = CENTRO_VERTICAL_PROTA (posición vertical inferior)
 * 
 * - Reinicia los contadores de movimiento de enemigos
 * 
 * - Inicia el temporizador del juego mediante PonerEnMarchaTempo()
 * 
 * @note Debe llamarse al inicio de cada partida nueva antes de cambiar a estado PARTIDA
 */
extern void InicializarVariablesPartida();

/**
 * @brief Muestra la pantalla del menú principal y habilita las interrupciones necesarias
 * 
 * Realiza las siguientes operaciones:
 * 
 * - Habilita interrupciones del teclado mediante HabilitarIntTeclado()
 * 
 * - Habilita el temporizador mediante HabilitarIntTempo()
 * 
 * - Habilita el controlador general de interrupciones mediante HabilitarInterrupciones()
 * 
 * - Visualiza el fondo del menú principal mediante VisualizarFondoMenu()
 * 
 * El menú permanece activo hasta que el jugador toque el área de inicio o presione START.
 * Se ejecuta dentro del bucle principal cuando ESTADO == MENU.
 * 
 * @note Debe llamarse para mostrar el menú inicial o después de un game over
 */
extern void MostrarMenu();

/**
 * @brief Muestra la pantalla de fin de juego y habilita entrada del jugador
 * 
 * Realiza las siguientes operaciones:
 * 
 * - Inhibe la tecla A mediante InhibirIntTecla(A) para evitar disparos accidentales
 * 
 * - Habilita interrupciones del teclado mediante HabilitarIntTeclado()
 * 
 * - Habilita el temporizador mediante HabilitarIntTempo() para contar tiempo
 * 
 * - Habilita el controlador general de interrupciones mediante HabilitarInterrupciones()
 * 
 * - Reinicia el contador_tiempo_gameover a 0
 * 
 * - Visualiza la pantalla final mediante VisualizarGameOver()
 * 
 * El jugador puede reiniciar una partida (START), volver al menú (SELECT),
 * o esperar a que contador_tiempo_gameover alcance contador_tiempo_gameover_max
 * para retornar automáticamente al menú.
 * 
 * @note Se llama cuando prota.vidas llega a 0. Se ejecuta dentro de ESTADO == GAMEOVER
 */
extern void MostrarGameOver();

/**
 * @brief Inicia una nueva partida desde cero
 * 
 * Ejecuta la secuencia de inicialización de una nueva partida:
 * 
 * - Llama a InicializarVariablesPartida() para resetear todos los datos
 * 
 * - Cambia ESTADO a PARTIDA para iniciar el estado de juego
 * 
 * - Establece ACCION a CARGANDO_FONDO para iniciar la máquina de estados de partida
 * 
 * Después de esta llamada, el bucle principal comienza a cargar progresivamente:
 * CARGANDO_FONDO → CARGANDO_PROTA → CARGANDO_SETAS → CARGANDO_ENEMIGOS → JUEGO
 * 
 * @note Se llama cuando el jugador presiona START en el menú o reinicia desde game over
 */
extern void IniciarPartida();

extern void MostrarASCIIArt();

extern int contador_tiempo_gameover;
extern int timer_pTactil_gameover;

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
    int nivel;      /**< Nivel actual del juego. Incrementa cada vez que se eliminan todos los ciempiés */
} protagonista;

/**
 * @brief Estructura que representa un indicador de puntos flotante en pantalla
 * 
 * Almacena los datos de un indicador visual temporal que muestra la cantidad
 * de puntos otorgados al jugador cuando destruye setas o ciempiés.
 */
typedef struct {
    int tiempo;     /**< Contador de tiempo de visualización. Rango: -1 a TIEMPO_CARTEL_PUNTOS. -1 indica slot inactivo */
    int tipo;       /**< Tipo de puntos (PUNTOS_SETA, PUNTOS_CIEMPIES_CABEZA, PUNTOS_CENTICUERPO) */
    int X;          /**< Posición horizontal en píxeles donde se muestra el indicador */
    int Y;          /**< Posición vertical en píxeles donde se muestra el indicador */
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

/**
 * @brief Detecta colisiones entre el protagonista y todos los segmentos del ciempiés
 * 
 * Itera sobre todos los ciempiés activos en el array y verifica si alguno colisiona
 * con el protagonista utilizando DetectarColision() en los centros de ambas entidades
 * (offset +8 píxeles).
 * 
 * Si hay colisión:
 * 
 * - Decrementa prota.vidas en 1
 * 
 * - Cambia ACCION a MUERTE para iniciar la secuencia de pérdida de vida
 * 
 * - Interrumpe la búsqueda (break) ya que solo se procesa una colisión por tick
 * 
 * @note Debe llamarse desde RutAtencionTempo() durante ESTADO == PARTIDA && ACCION == JUEGO
 * @see DetectarColision
 */
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

/**
 * @brief Detecta colisiones de un disparo con setas y ciempiés
 * 
 * Realiza las detecciones de colisión en orden:
 * 
 * 1. Verifica colisión con setas
 * 
 * 2. Si el disparo está activo, verifica colisión con ciempiés
 * 
 * Este orden es importante porque un disparo puede colisionar con una seta
 * y desactivarse antes de verificar colisiones con ciempiés.
 * 
 * @param[in] idDisparo Índice del disparo a verificar (0-9)
 * 
 * @note Debe llamarse después de mover los disparos cada tick
 */
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
extern int seta_cont_espera_mostrar_min;

/**
 * @brief Inicializa la matriz de setas limpiando todas las celdas
 * 
 * Establece todas las setas como inactivas (sprite_id = -1) y vidas = 0.
 * Prepara el juego para una nueva partida o pantalla sin obstáculos.
 * 
 * @note Debe llamarse al inicio de cada pantalla/partida
 */
extern void InicializarValoresSetas();

/**
 * @brief Busca el primer identificador de sprite disponible para crear una nueva seta
 * 
 * Recorre secuencialmente todos los IDs de sprite posibles (desde 0 hasta SID_SETA_MAX - SID_SETA)
 * y verifica en la matriz de setas (9×16) si alguno está siendo utilizado actualmente por una seta activa.
 * 
 * Para cada ID candidato:
 * 
 * - Itera sobre toda la matriz de setas buscando una celda con vidas > 0 y sprite_id igual al candidato
 * 
 * - Si encuentra una coincidencia, marca el ID como encontrado y pasa al siguiente candidato
 * 
 * - Si recorre toda la matriz sin encontrar coincidencias, retorna ese ID disponible
 * 
 * Esto permite reutilizar IDs de setas que fueron eliminadas (con vidas <= 0) sin causar
 * conflictos de recursos gráficos.
 * 
 * @return ID de sprite disponible (0 a SID_SETA_MAX-SID_SETA-1), o -1 si no hay espacios disponibles
 * 
 * @note Se utiliza en DetectarColisionesDisparoCiempies() cuando el jugador dispara a un ciempiés
 * no-cabeza para crear la seta que surge del cuerpo eliminado. Sin este mecanismo de reutilización,
 * se agotarían rápidamente los IDs de sprites disponibles después de eliminar varias setas.
 */
extern int PrimerIdSinSeta();

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
 * @brief Array global que almacena todas las partes de ciempies del juego.
 * 
 * Es un array de 50 elementos que almacena estructuras parteCiempies.
 */
extern parteCiempies ciempies[50];

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

/**
 * @brief Verifica si quedan ciempiés activos en el juego
 * 
 * Recorre el array de ciempiés y busca al menos un segmento con activo=1.
 * 
 * @return 1 si hay al menos un ciempiés vivo, 0 si todos han sido eliminados
 * 
 * @note Se utiliza para detectar la victoria en una pantalla
 */
extern int QuedanCiempiesVivos();

/**
 * @brief Establece puntos en una posición de pantalla y actualiza la puntuación
 * 
 * Busca un slot disponible en el array arrayPuntos[10] (slot con tiempo < 0).
 * Si encuentra disponibilidad:
 * 
 * - Incrementa prota.puntos por cuantosPuntos
 * 
 * - Establece el contador de tiempo del punto a 0 (visibilidad actual)
 * 
 * - Almacena el tipo de punto y posición (x, y)
 * 
 * - Dibuja el indicador visual mediante MostrarPuntos()
 * 
 * El indicador permanece visible mientras arrayPuntos[i].tiempo < TIEMPO_CARTEL_PUNTOS.
 * Cuando se alcanza el tiempo máximo, la rutina de atención (RutAtencionTempo) borra 
 * el indicador visual mediante BorrarPuntos() y reinicia el slot (tiempo = -1).
 * 
 * @param[in] cuantosPuntos Cantidad de puntos a otorgar (PUNTOS_SETA, PUNTOS_CIEMPIES_CABEZA, PUNTOS_CENTICUERPO)
 * @param[in] x Posición horizontal en píxeles donde mostrar el indicador
 * @param[in] y Posición vertical en píxeles donde mostrar el indicador
 * 
 * @note Se llama desde DetectarColisionesDisparoSetas() y DetectarColisionesDisparoCiempies()
 * cuando el jugador destruye setas o ciempiés respectivamente
 * @see RutAtencionTempo
 */
extern void EstablecerPuntos(int cuantosPuntos, int x, int y);

/*=================================================================================
 * FIN DE JUEGO.H - Curso 2025-2026
 =================================================================================*/

