# El-Juego-Risk-el-mejor-juego-de-mesa-del-mundo-mundial-
# Por Juan Esteban Granada & Hermann Hernandez

Hola jugador, en este archivo encontraras toda la información relacionada para entender en que consiste el juego de mesa Risk

Ademas en este repositorio encontraras las multiples partes que componen el funcionamiento del juego tanto en código funcional como archivos .md para la descripción de la parte asociada

1.0 Ejércitos:

- Para la ocupación de los territorios se utilizan 6 grupos de ejércitos, representados por pequeñas figuras que
representan la infantería (una unidad de ejército), la caballería (una unidad de caballería equivale a 5 unidades de
ejército) y la artillería (una unidad de artillería equivale a 10 unidades de ejército); estos grupos también tienen
colores diferentes que permiten distinguir a los jugadores participantes (verde, azul, rojo, amarillo, negro y gris).
La figura 2 muestra un ejemplo de las figuras, donde el soldado representa la infantería, el caballo la caballería y
el cañón la artillería.

1.1 Tarjetas:

- El juego incluye también 56 cartas: 42 marcadas con un territorio y el dibujo de una infantería, una caballería o
una artillería; 2 cartas “comodín” con los tres dibujos; y 12 cartas de Misión Secreta. Las cartas con los territorios
se entregan en cada turno al jugador que ha ocupado un territorio. Las cartas con los ejércitos pueden usarse para
solicitar unidades de ejército adicionales en el turno del jugador. Las cartas de Misión Secreta se utilizan sólo en
la variante por misiones del juego. La figura 3 presenta algunos ejemplos de las cartas del juego.

1.2 Inicio del juego:

- El juego comienza con la ocupación de los territorios por los jugadores participantes. Para esto, cada jugador
define el color con el que quiere participar, y luego toma una cantidad específica de unidades de infantería, de
acuerdo a cuantas personas vayan a participar. Para 3 jugadores, cada uno toma 35 infanterías; para 4 jugadores,
cada uno toma 30 infanterías; para 5 jugadores, cada uno toma 25 infanterías; y para 6 jugadores, cada uno toma
20 infanterías. Luego, por turnos cada jugador va ubicando una pieza de infantería en un territorio que él escoja,
hasta que todos los territorios hayan sido ocupados por los jugadores, y todas las piezas de infantería asignadas
hayan sido ubicadas en el tablero.

America:   
1. Alaska
2. Alberta
3. America Del Central
4. Estados Unidos Orientales
5. Groenlandia
6. Territorio Noroccidental
7. Ontario
8. Quebec
9. Estados Unidos Orientales

Europa:
1. Gran Bretaña
2. Isalndia
3. Europa Del Norte
4. Escandinavia
5. Esuropa
6. Ucrania
7. Europa Occidental

Asia
1. Afganistan
2. China
3. India
4. Irkutsk
5. Japon
6. Kamchatka
7. Medio Oriente
8. Mongolia
9. Siam
10. Siberia
11. Ural
12. Yakutsk

America del Sur
1. Argetina
2. Brasil
3. Peru
4. Venezuela

Australia
1. Australia Oriental
2. Indonesia
3. Nueva Guinea
4. Australia Occidental

1.4 Reglas Del Juego:

- Una vez ocupados los territorios, comienza el juego, en donde en cada turno el jugador puede escoger atacar
territorios enemigos para reclamarlos. Cada turno implica los siguientes pasos:
1. Obtener y ubicar nuevas unidades de ejército. Los jugadores obtienen nuevas unidades de ejército en cada
turno de acuerdo a: 
• Territorios: se cuentan los territorios que actualmente ocupa el jugador, se divide este número entre 3,
y el resultado es la cantidad de unidades adicionales que puede reclamar.
• Continentes: si el jugador ocupa todos los territorios de un continente, recibe la siguiente cantidad de
unidades adicionales: por América del Sur o Australia, 2 unidades; por África, 3 unidades; por América
del Norte o Europa, 5 unidades; y por Asia, 7 unidades.
• Cartas: al completar 3 cartas en cualquiera de las siguientes combinaciones: con el mismo dibujo de
ejército, con los tres dibujos de ejército, o cualquiera de los dos dibujos junto con una carta comodín;
éstas se pueden intercambiar por una cantidad de unidades adicionales que dependen de cuántos grupos
de cartas se han intercambiado por todos los jugadores: el primer grupo recibe 4 unidades, el segundo
6 unidades, el tercero 8 unidades, el cuarto 10 unidades, el quinto 12 unidades, el sexto 15 unidades, y
de ahí en adelante el número de incrementa en 5 unidades cada vez. Adicionalmente, si al intercambiar
las cartas algunas incluyen territorios ocupados por el jugador, se reciben 2 unidades extra por cada
territorio, las cuales obligatoriamente deben ocuparse en el territorio específico.
2. Atacar un territorio vecino. El jugador debe escoger uno de los territorios que tiene ocupados para iniciar
el ataque, y sólo podrá atacar territorios vecinos (pueden ser también aquellos conectados por líneas). Por
ejemplo, si el jugador decide iniciar el ataque en Brasil podría atacar tanto a Argentina, Perú y Venezuela en
América del Sur como a África del Sur. El resultado del ataque se define a través de los dados: el jugador
atacante lanza 3 dados de color rojo, mientras que el jugador que defiende lanza 2 dados blancos. Los dados
de uno y otro se emparejan y se comparan para determinar cuántas unidades de ejército pierde o gana cada
uno: si el del atacante es mayor que el del defensor, el defensor pierde una unidad de ejército del territorio
atacado; si el del defensor es mayor al del atacante, el atacante pierde una unidad de ejército del territorio
desde el que se ataca; si hay empate, el defensor es quien gana, por lo que el atacante pierde una unidad
de ejército de su territorio. El jugador atacante tiene la ventaja de que puede escoger dos de los tres dados
con mayor valor para hacer la comparación. El proceso se repite mientras el atacante lo decida. Si en el
ataque el territorio queda vacío (sin piezas del ejército del defensor), el atacante puede reclamarlo moviendo
algunas de sus piezas de ejército allí.
3. Fortificar la posición. Antes de finalizar el turno, el jugador puede decidir mover algunas de sus unidades de
ejército desde uno (y solo uno) de sus territorios a otro (sólo uno) de sus territorios vecinos.
Este proceso se repite hasta que un sólo jugador haya tomado control de los 42 territorios del tablero, momento
en el cual se declara como ganador. Dependiendo de la variante del juego, se puede terminar también cuando
un jugador haya cumplido su misión (dada por la tarjeta de Misión Secreta entregada al principio del juego), en
3 cuyo caso éste se declara como ganador.

Las partes del juego se guardaran en el repositorio con el nombre de Entrega <Un numero> y estas partes estaran
almacenadas en la carpeta llamada Risk
