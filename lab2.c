#include <stdio.h>
#include <stdlib.h>

/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE ESTRUCTURAS						   #
	#																	   #
	########################################################################
  
*/

typedef struct nodo
{
	char* puzzle;
	int moves;

	struct nodo* Up;
	struct nodo* Down;
	struct nodo* Left;
	struct nodo* Right;

}puzzleTree;

typedef struct node 
{
	char* puzzle;
	int count;
	struct node* next;
}listVisit;




/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE DEFINICIONES						   #
	#																	   #
	########################################################################
  
*/

#define TRUE 1
#define FALSE 0
#define SIZE_PUZZLE 9

// valor que representa la cantidad de movimientos que tiene un resultado (GLOBAL)
// el valor -1 representa que no hay resultados
int moves_result = -1;

//Puzzle resultado ideal: es el puzzle resulto con cada valor en su posicion
char puzzle_result[9] = {'1','2','3','4','5','6','7','8','X'};


/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE CABECERAS						   #
	#																	   #
	########################################################################
  
*/

puzzleTree* readFile(char* rute);
void writeFile();
void backTracking(puzzleTree* first, listVisit* list);


int equalsPuzzle(char* puzzle, char* puzzle2);
void imprimir(char* puzzle);
int currentPositionX(char* current_puzzle);


void freeTree(puzzleTree* current);
puzzleTree* moveXUp(puzzleTree* currentPuzzle);
puzzleTree* moveXDown(puzzleTree* currentPuzzle);
puzzleTree* moveXRight(puzzleTree* currentPuzzle);
puzzleTree* moveXLeft(puzzleTree* currentPuzzle);


void printVisit(listVisit* currentVisit);
void freeVisit(listVisit* current);
listVisit* copyVisit(listVisit* currentVisit);
int wasVisited(listVisit* currentLP, char* pzl);
void addPzlvisit(listVisit* current, char* pzl);




/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE FUNCIONES						   #
	#																	   #
	########################################################################
  
*/

/* 
####### Función de lectura de archivo de entrada ########
# 
#  ENTRADA: un string el cual es la ruta o nombre de un
# 			archivo, debe tener la extención.  
#
#  SALIDA:  un un puzzle correspondiente al nodo de un
#		    arbol. Los nodos hijos apuntan a NULL.
# 
#  ACCIÓN:  recorre el archivo de entrada y genera un 
# 			arbol. Sino hay archivo para leer retorna
# 			NULL.
# 
#########################################################
*/
puzzleTree* readFile(char* rute){
	//iniciando valores
	
    

    char* puzzle_read =(char*)malloc(sizeof(char)*SIZE_PUZZLE);

    FILE* fichero =fopen(rute,"r");
  	if (fichero) {
	    #ifdef DEBUG
	    printf("Fichero abierto correctamente\n");
	    #endif

	    int i = 0;
	    while (!feof(fichero)){
	      fscanf(fichero,"%c",&puzzle_read[i]);
	      if (puzzle_read[i]!= ' ' && puzzle_read[i]!= '\n') {
	         i++;
	      }

	    }
	    #ifdef DEBUG //Sentencia de DEBUG
	    for (i = 0; i < SIZE_PUZZLE; i++) {
	      printf(" posicion %i , caracter: %c\n",i,puzzle_read[i]);
	    }
	    #endif
	    fclose(fichero);

	    puzzleTree* inicial = (puzzleTree*)malloc(sizeof(puzzleTree));
		inicial->moves=0;
		inicial->Up=NULL;
		inicial->Down=NULL;
		inicial->Right=NULL;
		inicial->Left=NULL;
	    inicial->puzzle=puzzle_read;
	    return inicial;
	    
  	}
  	else
   	{
	    printf("No se pudo abrir el archivo\n");
	    printf("revise que la ruta o nombre del archivo sea correcto...\n");
	    return NULL;
	    
    }
  
}





/*
####### Función de escritura de archivo de salida ########
# 
#  ENTRADA:  nada
#  
#  SALIDA:   nada
# 
#  ACCIÓN:   Escribe en un archivo llamado "salida.out" la
# 		     cantidad minima de movimientos que tiene un 
# 			 puzzle-arbol.
# 
##########################################################
*/
void writeFile(){

  FILE* fichero = fopen("salida.out","w");

  if (fichero) {
    #ifdef DEBUG
    printf("Fichero abierto correctamente\n");
    #endif
    if (moves_result == -1)
    {
    	fprintf(fichero, "El puzzle ingresado no tiene solucion\n");	
    }
    else{

    }
    fprintf(fichero, "La cantidad de movimientos minimos para resolver el puzzle es : %i\n",moves_result);
    fclose(fichero);
  }
  else
   {

    printf("No se pudo abrir el archivo\n");
    printf("revise que no exista un archivo con el mismo nombre -> 'Salida.out'\n");
  }

}




/*
####### Función de comparación para puzzles ########
# 
#  ENTRADA: Dos puzzle en formato de cadena de
# 			caracteres.
#  
#  SALIDA:  Entero 1 o 0 representando los valores
# 			booleanos TRUE o FALSE ya definidos.
# 
#  ACCIÓN:  Compara caracter a caracter dos cadenas
# 			si las dos son iguales retorna 1 (TRUE)
# 			si uno no calza, retorna 0 (FALSE).
# 
####################################################
*/
int equalsPuzzle(char* puzzle, char* puzzle2){

  for (int i = 0; i < SIZE_PUZZLE; i++) {
    if (puzzle[i] != puzzle2[i]) {
      return FALSE;
    }
  }
  return TRUE;
}




/*
####### Función de busqueda para puzzles visitados ########
# 
#  ENTRADA: Una lista enlazada de puzzles (visitados) y un
# 			puzzle (cadena de caracteres).
#  
#  SALIDA:  Entero 1 o 0 representando los valores
# 			booleanos TRUE o FALSE ya definidos.
# 
#  ACCIÓN:  Busca en todos los puzzles de la lista de visit
# 			buscando si existe el puzzle de entrada.
# 
###########################################################
*/
int wasVisited(listVisit* currentLP, char* pzl){

	if (currentLP->puzzle!=0)
	{
		
	
	  listVisit* aux = currentLP;

	  while(aux != NULL){

	    if (equalsPuzzle(aux->puzzle, pzl) == TRUE) {
	       return TRUE;
	    }
	    aux = aux->next;
	  }
	  return FALSE;
	}
	else{
		return FALSE;
	}
}





/*
######## Función para agregar puzzle a visit #########
# 
#  ENTRADA: Una lista enlazada de puzzles (visitados) 
#			y un puzzle (cadena de caracteres). 
#  
#  SALIDA:  Nada.
# 
#  ACCIÓN:  agrega el puzzle pasado como entrada al
# 			final de la lista enlazada de visitados.
# 
######################################################
*/
void addPzlvisit(listVisit* current, char* pzl){

  char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
  for (int i = 0; i < SIZE_PUZZLE; i++) {
	   h[i] = pzl[i];
  }

  if (current->count == 0) {
    current->puzzle=h;
    current->count=1;
    current->next=NULL;

  }
  else{

    listVisit* aux = current;

    while (aux->next != NULL) {
      aux = aux->next;
    }
    listVisit* new = (listVisit*)malloc(sizeof(listVisit));
    new->puzzle = h;
    new->count = aux->count+1;
    new->next = NULL;

    aux->next = new;

  }
}







/*
####### Función de encontrar la posicion de X ########
# 
#  ENTRADA: Un puzzle (cadena de caracteres).
#  
#  SALIDA:  La posicion numerica (del 0 al 8) del
#           caracter 'X'. 
# 
#  ACCIÓN:  Recorre la cadena de caracteres (puzzle)
# 			buscando la posicion del caracter 'X'.
# 			Sino lo encuentra, devuelve -1.
# 
######################################################
*/
int currentPositionX(char* current_puzzle){

  for(int i =0; i<SIZE_PUZZLE;i++){
    if(current_puzzle[i] == 'X'){
	return i;
    }
  }
  return -1;
}





/*
####### Función para mover X a la posicion de arriba ########
# 
#  ENTRADA: Un puzzle-arbol.
#  
#  SALIDA:  Una copia del puzzle-Arbol modificado.
# 
#  ACCIÓN:  Crea una copia apartir del puzzle-arbol entregado
# 			e intercambia el caracter 'X' del puzzle por 
# 			el caracter en la posicion de arriba. Sino se 
# 			puede mover el caracter 'X' (determinado por la
# 			definición de abajo) devuelve NULL.
# 
#############################################################

¿X se puede mover hacia arriba? se podra mover si no esta en
 las posiciones [0,1,2] o si:

   sea i = posicion de 'X' en el arreglo
   Si i-3 >= 0, se puede mover la X hacia arriba
*/
puzzleTree* moveXUp(puzzleTree* currentPuzzle){

  char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
  int i;
   for ( i = 0; i < SIZE_PUZZLE; i++) {
		h[i] = currentPuzzle->puzzle[i];
    }
  int currentX = currentPositionX(h);
  if ((currentX -3) >= 0)
  {

  	char aux = h[currentX-3];
  	h[currentX] = aux;
  	h[currentX-3] = 'X';
  	puzzleTree* new = (puzzleTree*)malloc(sizeof(puzzleTree));
  	new->puzzle= h;
  	new->moves= currentPuzzle->moves+1;
  	new->Up=NULL;
  	new->Down=NULL;
  	new->Right=NULL;
  	new->Left=NULL;
  	return new;
  }
  else
  {
  	return NULL;
  }
}






/*
####### Función para mover X a la posicion de abajo ########
# 
#  ENTRADA: Un puzzle-arbol.
#  
#  SALIDA:  Una copia del puzzle-Arbol modificado.
# 
#  ACCIÓN:  Crea una copia apartir del puzzle-arbol entregado
# 			e intercambia el caracter 'X' del puzzle por 
# 			el caracter en la posicion de abajo. Sino se 
# 			puede mover el caracter 'X' (determinado por la
# 			definición de abajo) devuelve NULL.
# 
#############################################################
¿X se puede mover hacia abajo? se podra mover si no esta en
 las posiciones [6,7,8] o si:

   sea i = posicion de 'X' en el arreglo
   Si i+3 <= 8 se puede mover 'X'
*/
puzzleTree* moveXDown(puzzleTree* currentPuzzle){

  char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
  int i;
   for ( i = 0; i < SIZE_PUZZLE; i++) {
		h[i] = currentPuzzle->puzzle[i];
    }
  int currentX = currentPositionX(h);
  if ((currentX +3) <= 8)
  {

  	char aux = h[currentX+3];
  	h[currentX] = aux;
  	h[currentX+3] = 'X';
  	puzzleTree* new = (puzzleTree*)malloc(sizeof(puzzleTree));
  	new->puzzle= h;
  	new->moves= currentPuzzle->moves+1;
  	new->Up=NULL;
  	new->Down=NULL;
  	new->Right=NULL;
  	new->Left=NULL;
  	return new;
  }
  else
  {
  	return NULL;
  }
  
}




/*
####### Función para mover X a la posicion de derecha ########
# 
#  ENTRADA: Un puzzle-arbol.
#  
#  SALIDA:  Una copia del puzzle-Arbol modificado.
# 
#  ACCIÓN:  Crea una copia apartir del puzzle-arbol entregado
# 			e intercambia el caracter 'X' del puzzle por 
# 			el caracter en la posicion de la derecha. Sino se 
# 			puede mover el caracter 'X' (determinado por la
# 			definición de abajo) devuelve NULL.
# 
##############################################################
¿X se puede mover hacia la derecha? se podra mover si no esta en
 las posiciones [2,5,8] o si:

   sea i = posicion de 'X' en el arreglo
   Si (i+1) % 3 != 0 se puede mover 'X'
*/
puzzleTree* moveXRight(puzzleTree* currentPuzzle){

  char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
  int i;
   for ( i = 0; i < SIZE_PUZZLE; i++) {
		h[i] = currentPuzzle->puzzle[i];
    }
  int currentX = currentPositionX(h);
  if (((currentX + 1) % 3) != 0)
  {

  	char aux = h[currentX+1];
  	h[currentX] = aux;
  	h[currentX+1] = 'X';
  	puzzleTree* new = (puzzleTree*)malloc(sizeof(puzzleTree));
  	new->puzzle= h;
  	new->moves= currentPuzzle->moves+1;
  	new->Up=NULL;
  	new->Down=NULL;
  	new->Right=NULL;
  	new->Left=NULL;
  	return new;
  }
  else
  {
  	return NULL;
  }
  
}





/*
####### Función para mover X a la posicion de izquierda ########
# 
#  ENTRADA: Un puzzle-arbol.
#  
#  SALIDA:  Una copia del puzzle-Arbol modificado.
# 
#  ACCIÓN:  Crea una copia apartir del puzzle-arbol entregado
# 			e intercambia el caracter 'X' del puzzle por 
# 			el caracter en la posicion de la izquierda. Sino 
# 			se puede mover el caracter 'X' (determinado por la
# 			definición de abajo) devuelve NULL.
# 
##############################################################
¿X se puede mover hacia la izquierda? se podra mover si no esta en
 las posiciones [0,3,6] o si:

   sea i = posicion de 'X' en el arreglo
   Si i % 3 != 0 se puede mover 'X'
*/
puzzleTree* moveXLeft(puzzleTree* currentPuzzle){

  char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
  int i;
   for ( i = 0; i < SIZE_PUZZLE; i++) {
		h[i] = currentPuzzle->puzzle[i];
    }
  int currentX = currentPositionX(h);
  if ((currentX % 3) != 0)
  {

  	char aux = h[currentX-1];
  	h[currentX] = aux;
  	h[currentX-1] = 'X';
  	puzzleTree* new = (puzzleTree*)malloc(sizeof(puzzleTree));
  	new->puzzle= h;
  	new->moves= currentPuzzle->moves+1;
  	new->Up=NULL;
  	new->Down=NULL;
  	new->Right=NULL;
  	new->Left=NULL;
  	return new;
  }
  else
  {
  	return NULL;
  }
  
}






/*
####### Función de copia de estructura visit ########
# 
#  ENTRADA: Una lista enlazada de puzzles (visitados)
#  
#  SALIDA:  Una lista enlazada de puzzles (visitados)
# 
#  ACCIÓN:  Crea una copia exacta de cada puzzle en
# 			la lista de visitados y las agrega a una
# 			nueva, devolviendo asi, una copia de
# 			la lista enlazada.
# 
#####################################################
*/
listVisit* copyVisit(listVisit* currentVisit){
	listVisit* new = (listVisit*)malloc(sizeof(listVisit));
	new->count=0;
	new->next=NULL;
	listVisit* aux = currentVisit;
	if (currentVisit->count !=0)
	{
		while(aux != NULL){
			char* h = (char*)malloc(sizeof(char)*SIZE_PUZZLE);
		    for (int i = 0; i < SIZE_PUZZLE; i++) {
		        h[i] = aux->puzzle[i];
		    }
		    addPzlvisit(new,h);

		  
		    aux = aux->next;
		}
	}
	return new;
}



/*
####### Función de copia de estructura visit ########
# 
#  ENTRADA: 
#  
#  SALIDA:
# 
#  ACCIÓN:
# 
#####################################################
*/
void freeVisit(listVisit* current){

  while(current != NULL){
    listVisit* aux=current->next;
    free(current->puzzle);
    free(current);
    current= aux;
  }
}






/*
####### Función de copia de estructura visit ########
# 
#  ENTRADA: 
#  
#  SALIDA:
# 
#  ACCIÓN:
# 
#####################################################
*/
void freeTree(puzzleTree* current){

  if (current != NULL)
  {
  	freeTree(current->Up);
  	freeTree(current->Down);
  	freeTree(current->Right);
  	freeTree(current->Left);

  	free(current->puzzle);
  }
}




/*
####### Función de copia de estructura visit ########
# 
#  ENTRADA: 
#  
#  SALIDA:
# 
#  ACCIÓN:
# 
#####################################################
*/
void printVisit(listVisit* currentVisit){
	listVisit* aux = currentVisit;
	if (currentVisit->count !=0)
	{
		while(aux != NULL){
			imprimir(aux->puzzle);
			printf("  |\n");
			printf("  |\n");
			printf("  V\n");
		    aux = aux->next;
		}
		printf("*FIN*\n");
	}
	
}




/*
####### Función de copia de estructura visit ########
# 
#  ENTRADA: 
#  
#  SALIDA:
# 
#  ACCIÓN:
# 
#####################################################
*/
void imprimir(char* puzzle){

  if (puzzle != NULL)
  {
  	  
	  #ifdef DEBUG
	  int y = 0;
	  for (int i = 0; i < SIZE_PUZZLE; i++) {
	    if (y == 3) {
	      printf("\n" );
	      y=0;
	    }
	    printf("%c ",puzzle[i]);
	    y++;
	  }
	  printf("\n");
	  #endif
  }
}






/*
####### Función de BackTracking para puzzle ########
# 
#  ENTRADA: 
#  
#  SALIDA:
# 
#  ACCIÓN:
# 
####################################################
*/
void backTracking(puzzleTree* first, listVisit* list){

	if (first != NULL)
	{
		#ifdef DEBUG

			//printf("Press 'Enter' to continue: ... ");
			//while ( getchar() != '\n');

			printf("puzzle actual y con el nivel : %i\n",first->moves);
			imprimir(first->puzzle);

			printf("*******imprimiendo visitados*******\n");
			printVisit(list);
			printf("***********************************\n");
			
		#endif

		if (moves_result != -1)//si hay un resultado encontrado
		{
			if (first->moves < moves_result) //nos interesa solo los puzzles con movimientos menores.
			{
				if (equalsPuzzle(first->puzzle,puzzle_result)==TRUE)
				{
					moves_result = first->moves;
				}
				else if (wasVisited(list,first->puzzle)==FALSE)
				{
					listVisit* copyListVisit = copyVisit(list);
					addPzlvisit(copyListVisit,first->puzzle);

					first->Up=moveXUp(first);
					first->Down=moveXDown(first);
					first->Right=moveXRight(first);
					first->Left=moveXLeft(first);

					backTracking(first->Up,copyListVisit);
					backTracking(first->Down,copyListVisit);
					backTracking(first->Right,copyListVisit);
					backTracking(first->Left,copyListVisit);

					freeVisit(copyListVisit);
					
				}
				else
				{
					#ifdef DEBUG
					printf("el puzzle ya ha sido visidado\n");
					#endif
				}
			}
		}
		//quiere decir que no hay resultado
		else
		{
			if (equalsPuzzle(first->puzzle,puzzle_result)==TRUE)
			{
				#ifdef DEBUG
				printf("hay un puzzle resultado en : %i movimientos\n",first->moves);
				#endif
				moves_result = first->moves;
			}
			else if (wasVisited(list,first->puzzle)==FALSE)
			{
				listVisit* copyListVisit = copyVisit(list);
				addPzlvisit(copyListVisit,first->puzzle);

				first->Up=moveXUp(first);
				first->Down=moveXDown(first);
				first->Right=moveXRight(first);
				first->Left=moveXLeft(first);

				backTracking(first->Up,copyListVisit);
				backTracking(first->Down,copyListVisit);
				backTracking(first->Right,copyListVisit);
				backTracking(first->Left,copyListVisit);

				freeVisit(copyListVisit);
				
			}
			else
			{
				#ifdef DEBUG
				printf("el puzzle ya ha sido visidado\n");
				#endif
			}


		}
		

	}

} 



 int main(int argc, char const *argv[])
 {
 	puzzleTree* current = readFile("entrada.in");
 	listVisit* listV = (listVisit*)malloc(sizeof(listVisit));
 	listV->count=0;
 	listV->next=NULL;

 	backTracking(current, listV);
 	freeTree(current);
 	freeVisit(listV);
 	printf("La cantidad de resultado es = %i\n",moves_result);
 	writeFile();
 	return 0;
 }

