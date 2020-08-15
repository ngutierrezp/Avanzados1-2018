
#include <stdio.h>
#include <stdlib.h>
#ifndef STRUCT_H
#define STRUCT_H
#include "structs.h"
#endif

/*agrega un nuevo resultado a una lista de resultados

Solo agrega los movimientos ya que es lo necesario para entregar el resultado.
No se agrega el arbol de solucion.
*/
void addPzlresult(result* current,int movimientos){

    if (current->count == 0) {
      current->movs=movimientos;
      current->count=1;
      current->next= NULL;

      #ifdef DEBUG

       printf("***La lista resultados no tiene elementos = lista vacia***\n");

      #endif

    }
    else{

      #ifdef DEBUG

      printf("***La lista tiene elementos = Cola NO vacia***\n");

      #endif
      result* aux = current;

      while (aux->next != NULL) {
        aux = aux->next;
      }

      result* new =(result*)malloc(sizeof(result));
      new->movs=movimientos;
      new->count = aux->count+1;
      new->next=NULL;
      aux->next = new;

    }

}

//obtiene la cantidad minima de movimientos de una lista de resultados
int getMinMoves(result* resultados){
  result* aux = resultados;
  int min = aux->movs;
  while(aux != NULL){
    if (aux->movs <= min)
    {
      min = aux->movs;
    }
    aux=aux->next;
  }
  return min;
}

//libera la lista de resultados
void freeResult(result* current){

  while(current->next != NULL){
    result* aux=current->next;
    current->next = aux->next;
    free(aux);
  }
}
