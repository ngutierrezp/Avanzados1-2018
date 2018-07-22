#                               BackTracking para Puzzle-8 en C.


## El problema del puzzle-8 
El puzzle 8 es un puzzle de 9 partes a la que le falta 1 (de ahi el nombre). Como le falta una pieza, las demas pueden moverse hasta resolver el puzzle.

<p align="center"><img src="https://i.stack.imgur.com/YQd0a.png"></p>

Para resolver el puzzle todas las piezas deben estar en orden desde el 1 al 8 (dado que el 9 no existe).
El problema en este sentido es encontrar la cantidad minima de movimientos en el puzzle para poder solucionarlo.
(cabe destacar que no se entrega el orden de como se debe solucionar, solo la cantidad minima de movimientos)

## Solución (BackTracking)

Para este problema se ha implementado una solición en C con el algoritmo de Backtrcking. 

### Representación del puzzle
Para representar el un puzzle existen diferentes formas segun la imaginacion y manejo del programador, en este sentido he decido representarlo como un arreglo de caracteres `char* puzzle` siempre con un largo para 9 elementos.

En este sentido si se tiene el siguiente puzzle:

      2 1 3
      4 8 6
      7 5 X
      
Su representación sera: `char puzzle_result[9] = {'2','1','3','4','8','6','7','5','X'};`

Los puedes se pueden modificar dependiendo de los espacios adyacentes de 'X'. Dicho de otro modo, la X puede moverse de a 4 sitios distintdos (dependiendo de su pocision):

| movimiento de X | Logica | Codigo | 
| ------ | ------ | ------ |
| Arriba | se podra mover si no esta en las posiciones [0,1,2] | `if(i-3 >= 0)` |
| Abajo | se podra mover si no esta en las posiciones [6,7,8] | `if(i+3 <= 8)` |
| Izquierda | se podra mover si no esta en las posiciones [2,5,8] | `if(i % 3 != 0)` |
| Derecha | se podra mover si no esta en las posiciones [0,3,6] | `if((i+1) % 3 != 0)` |



### Estructuras del programa

* Arbol 

Para poder hacer backtracking en este problema hay que entender que cada movimiento en un puzzle equivale a crear un nuevo puzzle. Ademas de esto, cada puzzle tiene una cantidad de movimientos necesarios para llegar a ese puzzle.

Entonces, si se toma un puzzle inicial, es posible crear un maximo de 4 puzzles hijos a partir de este. (esto dependiendo del movimiento de las X.

Tomando esta logica, se ha creado una estructura que funcionará como arbol de puzzles: 

<p align="center"><img src="https://i.imgur.com/VzPkcnx.jpg"></p>

* Lista

Para avanzar en el arbol es necesario saber por donde hemos pasado, entonces es necesario disponer de una lista con los puzzles ya visitados.

Por esto se creo una estructura de lista enlazada para solucionar esto: 

<p align="center"><img src="https://i.imgur.com/QY7HBnN.jpg"></p>





### Installation

```sh
$ gcc Lab2.c -o ejecutable
$ ./ejecutable
```


