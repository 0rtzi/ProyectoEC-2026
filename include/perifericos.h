// Curso 2025-2026

/*-------------------------------------
perifericos.h
-------------------------------------*/

/**
 * @brief Detecta si hay alguna tecla presionada actualmente
 * 
 * Verifica el estado del teclado y devuelve un valor diferente de cero
 * si hay al menos una tecla siendo presionada en este momento.
 * 
 * @return Valor diferente de cero si hay una tecla presionada, 0 si no hay ninguna
 * 
 * @note Esta función lee el estado instantáneo del teclado sin necesidad de interrupciones
 */
extern int TeclaDetectada();

/**
 * @brief Obtiene la última tecla presionada
 * 
 * Retorna el código de la última tecla que fue presionada. Combinada con
 * la configuración del teclado, permite determinar qué tecla específica
 * fue activada.
 * 
 * @return Código de la tecla presionada (START, SELECT, A, B, etc.)
 * 
 * @see ConfigurarTeclado
 */
extern int TeclaPulsada();

/**
 * @brief Configura el teclado especificando qué teclas generarán interrupciones
 * 
 * Establece la máscara de teclas que activarán interrupciones cuando sean presionadas.
 * Los bits del parámetro Conf_Tec representan las diferentes teclas disponibles
 * en el control pad de la Nintendo DS.
 * 
 * @param[in] Conf_Tec Máscara de bits indicando qué teclas habilitar (ej: 0x400D para START, A, B, Y)
 * 
 * @note Debe llamarse antes de habilitar las interrupciones del teclado
 */
extern void ConfigurarTeclado(int Conf_Tec);

/**
 * @brief Configura el temporizador del hardware con frecuencia y latch específicos
 * 
 * Establece los parámetros de funcionamiento del temporizador 0 de la Nintendo DS,
 * permitiendo controlar la frecuencia de generación de interrupciones de tiempo.
 * 
 * @param[in] Latch Valor inicial del contador del temporizador (determina frecuencia junto con Conf_Tempo)
 * @param[in] Conf_Tempo Configuración del divisor de frecuencia del temporizador
 * 
 * @note Valores típicos:
 * - Latch=61440, Conf_Tempo=0x0041 → 128 interrupciones por segundo
 * - Latch=57344, Conf_Tempo=0x0041 → 64 interrupciones por segundo
 * 
 * @see PonerEnMarchaTempo, PararTempo
 */
extern void ConfigurarTemporizador(int Latch, int Conf_Tempo);

/**
 * @brief Habilita las interrupciones del teclado
 * 
 * Activa el sistema de interrupciones para detectar pulsaciones de teclas
 * configuradas previamente. Las teclas habilitadas según ConfigurarTeclado()
 * ahora generarán llamadas a la rutina de atención (RutAtencionTeclado).
 * 
 * @note Debe llamarse después de ConfigurarTeclado() y estar habilitadas
 * las interrupciones globales mediante HabilitarInterrupciones()
 * 
 * @see ConfigurarTeclado, HabilitarInterrupciones
 */
extern void HabilitarIntTeclado();

/**
 * @brief Habilita la interrupción de una tecla específica
 * 
 * Activa la generación de interrupciones para una única tecla determinada,
 * permitiendo que esa tecla dispare la rutina de atención incluso si
 * había sido previamente inhibida.
 * 
 * @param[in] tecla Código de la tecla a habilitar (ej: A, START, etc.)
 * 
 * @note Esta función permite habilitar selectivamente teclas individuales
 * después de haber inhibido otras con InhibirIntTecla()
 * 
 * @see InhibirIntTecla, HabilitarIntTeclado
 */
extern void HabilitarIntTecla(int tecla);

/**
 * @brief Inhibe (desactiva) todas las interrupciones del teclado
 * 
 * Desactiva completamente el sistema de interrupciones del teclado.
 * Ninguna tecla generará interrupciones hasta que se vuelva a llamar
 * a HabilitarIntTeclado().
 * 
 * @note Útil para evitar entrada del usuario durante ciertos estados del juego
 * 
 * @see HabilitarIntTeclado, InhibirIntTecla
 */
extern void InhibirIntTeclado();

/**
 * @brief Inhibe la interrupción de una tecla específica
 * 
 * Desactiva la generación de interrupciones para una única tecla determinada,
 * permitiendo que otras teclas sigan generando interrupciones normalmente.
 * 
 * @param[in] tecla Código de la tecla a inhibir (ej: A para evitar disparos)
 * 
 * @note Esta función permite inhibir selectivamente teclas individuales
 * sin afectar al resto del teclado
 * 
 * @see HabilitarIntTecla, InhibirIntTeclado
 */
extern void InhibirIntTecla(int tecla);

/**
 * @brief Habilita las interrupciones del temporizador
 * 
 * Activa el sistema de interrupciones para el temporizador configurado
 * previamente. El temporizador generará interrupciones a la frecuencia
 * establecida, llamando a RutAtencionTempo() en cada interrupción.
 * 
 * @note Debe llamarse después de ConfigurarTemporizador() y estar habilitadas
 * las interrupciones globales mediante HabilitarInterrupciones()
 * 
 * @see ConfigurarTemporizador, PonerEnMarchaTempo, HabilitarInterrupciones
 */
extern void HabilitarIntTempo();

/**
 * @brief Inhibe (desactiva) las interrupciones del temporizador
 * 
 * Desactiva el sistema de interrupciones del temporizador, deteniendo
 * las llamadas periódicas a RutAtencionTempo(). El temporizador se detiene
 * de generar interrupciones.
 * 
 * @note Útil para pausar la actualización del juego sin detener el hardware completamente
 * 
 * @see HabilitarIntTempo, PararTempo
 */
extern void InhibirIntTempo();

/**
 * @brief Inicia la ejecución del temporizador
 * 
 * Pone en marcha el temporizador configurado para que comience a generar
 * interrupciones según la frecuencia establecida en ConfigurarTemporizador().
 * 
 * @note Debe llamarse después de ConfigurarTemporizador() y HabilitarIntTempo()
 * 
 * @see ConfigurarTemporizador, HabilitarIntTempo, PararTempo
 */
extern void PonerEnMarchaTempo();

/**
 * @brief Detiene la ejecución del temporizador
 * 
 * Detiene completamente el temporizador, impidiendo que genere más interrupciones.
 * El temporizador se congela en su estado actual hasta que vuelva a iniciarse
 * con PonerEnMarchaTempo().
 * 
 * @note Se utiliza para pausar la lógica del juego
 * 
 * @see PonerEnMarchaTempo, InhibirIntTempo
 */
extern void PararTempo();

/**
 * @brief Habilita todas las interrupciones comunes necesarias para el juego
 * 
 * Función auxiliar que centraliza la habilitación de:
 * 
 * - Interrupciones del teclado mediante HabilitarIntTeclado()
 * 
 * - Interrupciones del temporizador mediante HabilitarIntTempo()
 * 
 * - Interrupciones globales del procesador mediante HabilitarInterrupciones()
 * 
 * Esto evita repetir el mismo código en múltiples funciones como MostrarMenu()
 * y MostrarGameOver().
 * 
 * @note Esta función simplifica la inicialización del sistema de interrupciones
 * asegurando consistencia en toda la aplicación
 * 
 * @see HabilitarIntTeclado, HabilitarIntTempo, HabilitarInterrupciones
 */
extern void HabilitarInterrupcionesComunes();

/***********************2025-2026*******************************/


