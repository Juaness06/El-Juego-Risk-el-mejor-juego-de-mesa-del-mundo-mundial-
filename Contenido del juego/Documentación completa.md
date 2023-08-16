# JUEGO RISK

Descripción del objetivo de la entrega:

La entrega inicial corresponderá únicamente a la interfaz de usuario necesaria para interactuar con el sistema. De
esta forma, se verificará el indicador de línea del comando, y que el sistema realice la validación de los comandos
permitidos y sus parámetros.

Lo primero que tenemos que hacer es compilar y encadenar el código para despues ejecutar el programa, para esto vamos a digitar los siguientes comandos en la terminal:

  - `g++ -std=c++11 -c entreaCero.cpp` = Compilar
  - `g++ -std=c++11 -o ejecutable_entregaCero entregaCero.o` = Encadenar
  - `./ejecutable_entregaCero` = Ejecutar el programa

Es importante decir que la ejecución del programa esta destiana para ejecutarse en una terminal Linux.

Se vera un caracter `$` que inicadara la terminal lista para escribir los comandos.

La lista de comandos es la siguiente: 

 El comando `inicializar` tiene la siguiente función: 

  Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones
  entregadas. De esta forma, el comando debería preguntar la cantidad de jugadores, para cada jugador su
  nombre o identificador, y luego, por turnos, preguntar a cada jugador en qué territorio desea ubicar sus
  unidades de ejército. En cada turno, el jugador sólo puede indicar un único territorio a ocupar. En este
  comando es clave utilizar una interfaz adecuada de asignación de territorios que sea fácil de seguir para los
  jugadores en pantalla.

  Al escribir este comando vamos a ver una salida por pantalla `El juego ya ha sido inicializado` y despues nos preguntara la cantidad de jugadores
  que van a jugar y sucesivamente el programa nos pedira asignar un nombre o identificador para el jugador, el siguiente paso es la repartición de
  los territorios, los turnos para escoger los territorios son de acuerdo al nombre o identificador que se digito en orden. Se desplegara un menu
  con los continentes y dentro de cada continente hay un menu con los territorios disponibles, se escoge el territorio y este dejara de estar disponible
  y no se mostrara mas adelante en los siguientes turnos.

  El comando `guardar <nombre_del_archivo>` tiene la siguiente función:

  - El estado actual del juego es guardado en un archivo de texto. El archivo debe contener la
    cantidad de jugadores, y para cada jugador debe almacenar su nombre, su color de jugador, la cantidad
    de países que ocupa, el identificador de cada país junto con la cantidad de unidades de ejército en él, la
    cantidad de tarjetas que posee y el identificador de cada tarjeta. 

  - Al escribir este comando nos mostrara unos posibles mensajes por pantalla:
    
    `Esta partida no ha sido inicializada correctamente` si el juego no se inicializado correctamente
    
    `La partida ha sido guardada correctamente` si el comando cumplio su función correctamente
    
    `La partida no ha sido guardada correctamente` si el comando no cumplio su funcionalidad

  - Para esta entrega la funcionalidad del comando no ha sido implementada, los mensajes por pantalla si son funcionales dentro
    del código ya que es el objetivo de la entrega

  El comando `guardar_comprimido <nombre_archivo>` tiene la siguiente función:

  - El estado actual del juego es guardado en un archivo binario (con extensión .bin) con la
    información comprimida, utilizando la codificación de Huffman.

    `Esta partida no ha sido inicializada correctamente` si el juego no se inicializado correctamente
    
    `La partida ha sido codificada y guardada correctamente` si el comando cumplio su función correctamente
    
    `La partida no ha sido codificada ni guardada correctamente` si el comando no cumplio su funcionalidad

  - Para esta entrega la funcionalidad del comando no ha sido implementada, los mensajes por pantalla si son funcionales dentro
    del código ya que es el objetivo de la entrega.

  El comando  `inicializar <nombre_archivo>` tiene la siguiente función:

  - Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>.

    `El juego ya ha sido inicializado` si el juego se inicializo correctamente
    
    `“nombre_archivo” no contiene información válida para inicializa el juego.` si cuando leyo el archivo no encontro datos compatibles con una partida Risk

    - Para esta entrega la funcionalidad del comando no ha sido implementada, los mensajes por pantalla si son funcionales dentro
    del código ya que es el objetivo de la entrega.

  El comando `costo_conquista <territorio>` tiene la siguiente función:

  - El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr
    controlar el territorio dado por el usuario. El territorio desde donde debe atacar debe ser aquel que el jugador
    tenga controlado más cerca al dado por el jugador. Esta información se analiza desde el punto de vista del
    jugador que tiene el turno de juego.

    `Esta partida no ha sido inicializada correctamente` Cuando la partida no se ha inicializado
    
    `Esta partida ya tuvo un ganador` Si la partida ya tuvo un ganador
    
    `Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>,
     pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe
     conquistar <n> unidades de ejército.` Cuando el comando funciono correctamente

     - Para esta entrega la funcionalidad del comando no ha sido implementada, los mensajes por pantalla si son funcionales dentro
       del código ya que es el objetivo de la entrega.

  El comando `conquista_mas_barata` tiene la siguiente función:

  - De todos los territorios posibles, calcular aquel que pueda implicar un menor número de
    unidades de ejército perdidas. Esta información se analiza desde el punto de vista del jugador que tiene el
    turno de juego.

    `Esta partida no ha sido inicializada correctamente` Cuando la partida no se ha inicializado
    
    `Esta partida ya tuvo un ganador` Si la partida ya tuvo un ganador
    
    `La conquista más barata es avanzar sobre el territorio <territorio_1>
    desde el territorio <territorio_2>. Para conquistar el territorio <territorio_1>, debe
    atacar desde <territorio_2>, pasando por los territorios <territorio_3>, <territorio_4>,
    ..., <territorio_m>. Debe conquistar <n> unidades de ejército.` Cuando el comando funciono correctamente

     - Para esta entrega la funcionalidad del comando no ha sido implementada, los mensajes por pantalla si son funcionales dentro
       del código ya que es el objetivo de la entrega.

El comando `ayuda` desplegara una lista de todos los comandos nombrados hasta el momento, **_se recomiendda al ejecutar el programa usar este comando. _**

El comando `salir` acabara el programa sin mensaje por pantalla.


    

