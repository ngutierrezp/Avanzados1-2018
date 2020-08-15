
# Explicación

Puzzle8 hecho en C en con fuerza bruta (forma del algoritmo)

El puzzle sera representado por una lista de enteros donde el largo de esta
es de 9 elementos siempre:


  puzzle = [1,2,3,4,5,6,7,8,X]  =   1  2  3
                                    4  5  6
                                    7  8  X
   //matriz


Para obtener un elemento de este puzzle es necesario una coordenada (X,Y)
ya que :

    Elemento = Y*N + X  //donde N es el tamaño de la matriz, para este caso
    N es 3 (debido a que la matriz es de 3x3)

    Finalmente para obtener un elemento en (X,Y) sera:

    Elemento = Y*3+X

    la restricción para X es I= [0,2] o X <= 2 y X >= 0
    la restricción para Y es I= [0,2] o Y <= 2 y Y >= 0



# Compilación 
Para la compilación del programa se ha dispuesto de un Makefile con todo lo necesario para compilar los .c, en este sentido basta con poner en la consola: <code> make</code> lo que compilara el programa generando archivos .o 

## Limpieza
Para el caso de que se quiera limpiar los archivos .o de la carpeta contenedora se debe hacer la diferencia si se esta trabajando en linux o en windows.

En caso de linux el comando para limpiar es : <code>$ make cleanL</code>

En caso de Windows el comando para limpiar es : <code>$ make cleanW</code>

## Debug

Para obtar al modo debug del programa basta con compilarlo : <code>$ make debug</code>

