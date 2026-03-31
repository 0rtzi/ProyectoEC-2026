# ProyectoEC-2026

## **Índice**

1. **Descripción del juego**
    
    1.1. Juego

    1.2. Funcionamiento del juego

2. **Trabajo**

    2.1. Teclado

    2.2. Temporizador

    2.3. Pantalla táctil 

3. **Autómata**

## **1. Descripción del juego**

### **1.1. Juego**
Nuestro juego va a ser una versión adaptada y con posiblemente menos funciones que el juego **Centipede** creado en 1981 para máquinas recreativas y más adelante adaptada para la Atari 2600.

<p align="center">
  <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fi.pinimg.com%2F736x%2F59%2Fd9%2F84%2F59d984e8aab55cab62f73ae6a0a045d7--logo-color-centipedes.jpg&f=1&nofb=1&ipt=096b4644639209c7ffa43e533ea9cac8fa6a68eb1f5e27c00efdb443319ac6a5](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwallpapercave.com%2Fwp%2Fwp10110887.jpg&f=1&nofb=1&ipt=e0c42ce25cd123942dc5fe45694c085694237481f29d94bbbbe3d913c32000fb)" alt="Centipede Logo" width="80%">
</p>

### **1.2. Funcionamiento del juego**

El juego Centipede se basa en un protagonista (una nave) la cual dispara rayos con los que disparar a diferentes elementos en pantalla. El objetivo principal del juego es sobrevivir y conseguir la mayor cantidad de puntos posibles disparando a los enemigos (el ciempiés, la araña, etc.)

Entre los enemigos, el ciempiés, es el primero que implementaremos y en caso de que tengamos tiempo posiblemente la araña también. El ciempiés va bajando por la pantalla cambiando de dirección cada vez que se choca con una seta. La forma de eliminarlos es dispararles a la cabeza para quitarles una unidad de la longitud de su cuerpo. En caso de disparar a cualquier otra parte del cuerpo, esta parte desaparece pero el ciempiés se divide en dos.

El movimiento de la araña en cambio es más errático. Esta se mueve en diagonal por la parte inferior de la pantalla, 

Las setas se generan cuando das un disparo a cualquiera de los enemigos y aparece en la posición donde ha recibido el golpe el enemigo, cuando pierdes una vida (se regeneran las que se habían quitado) o cuando cambias de dificultad (te pasas la pantalla). Puedes hacer desaparecer las setas al dispararles 4 veces. Estas irán cambiando de aspecto cuantas más veces le des disparos.  
La nave puede moverse en dos dimensiones, es decir, arriba, abajo, derecha e izquierda. Cuando recibe un golpe pierde una vida y se reinicia la pantalla en la que ha perdido dicha vida. Cada vez que terminas con un enemigo se te suman puntos al contador el cual indica la calidad de la partida que se ha jugado. Cuantos más puntos mejor.

## **2. Trabajo**

### **2.1. Teclado**

El movimiento del personaje estará manejado por las teclas **arriba, abajo, derecha e izquierda** en modo de **encuesta** ya que el personaje tiene que moverse continuamente.

En cambio el disparo, **tecla A**, se hará mediante sincronización por **interrupción**. Es decir, el jugador decidirá cuándo disparar exactamente, al igual que puede no disparar por toda la partida.

### **2.2. Temporizador**

El temporizador se usará en las siguientes circunstancias:

* **Golpe del personaje:** Cuando el personaje principal (la nave) reciba un golpe y por lo tanto pierda una vida, se activará un timer de 5 segundos por el que la pantalla se actualiza, los enemigos reaparecen y da tiempo a ejecutar una animación de destrucción de la nave.  
* **Estado Gameover:** Cuando el estado del juego sea Gameover, entonces se creará un temporizador que cuente 10 segundos. Cuando pasen los 10 segundos se cambiará al Menú.  
* **Disparos:** Habrá un timer que mida cada cuanto dispara el personaje. A medida que vaya cambiando la dificultad del juego esta irá disminuyendo.  
* **Velocidad de los enemigos:** El timer se tendrá en cuenta también para gestionar la velocidad a la que se moverán los enemigos dependiendo de la dificultad.

      
    Teniendo en cuenta los casos en los que se va a usar el temporizador, podemos pensar que crearemos uno con una frecuencia de 1 segundo o menos (para los enemigos).

### **2.3. Pantalla táctil**

La pantalla táctil la usaremos para el Menú y la pantalla de Gameover, donde habrá varios botones. El de START que iniciará el juego y cambiará al estado Partida, el de RESTART en Gameover para pasar al estado partida, y el de MENÚ en Gameover para pasar al estado Menú.

## **3. Autómata**
<img width="4768" height="3253" alt="Autómata" src="https://github.com/user-attachments/assets/61d66414-4862-4b54-8824-04109728f4de" />
