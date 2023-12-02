*Connect4 

Cuando inicies el juego, se te pedirá que elijas la dificultad:

->Fácil*: La máquina toma decisiones rápidas con una profundidad de búsqueda baja.
->Medio: La máquina realiza una búsqueda más profunda para tomar decisiones más estratégicas.
->Difícil : La máquina realiza una búsqueda aún más profunda, siendo más desafiante.

main -> Juego:
El juego se basa en turnos, al ser el turno del jugador, se ingresa el número de la columna donde deseas colocar tu ficha, mientras
que cuando sea el de la máquina, esta escogera la mejor opcion de ficha.

Gana el primero en formar una fila de 4 fichas en línea horizontal, vertical o diagonal.

**Minimax sin poda alfa-beta:
se evalua recursivamente todos los posibles movimientos para determinar su puntaje

Connect4 -> minimax: 
Termina cuando se llega a la maxima profundidad o algun jugador gana, devuelve el puntaje.
Para esto se inicializa el mejor puntaje según el jugador actual, en caso de la maquina, se revisa cada movimiento y se le calcula su 
puntaje, luego se actualiza el mejor puntaje segun el jugador

***Minimax con poda alfa-beta:
En la función minimax con poda alfa-beta, se ocupa poda alfa-beta para reducir la cantidad de nodos evaluados, "podando" el arbol si
beta es menor o igual a alfa, ya que no hay necesidad de recorrer dichos nodos "casillas"
             
          +
