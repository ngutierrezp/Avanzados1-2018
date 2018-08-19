#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
	char* valor;
	struct Nodo * sgte;
	struct Nodo * ant;
}nodo;

typedef struct ListaEnlazada{
	nodo * inicio;
	nodo * fin;
	int size;
}lista;


lista insert(lista actual, char* elemento){
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	nuevo->valor = elemento;
	nuevo->sgte = NULL;
	nuevo->ant = NULL;
	if (actual.size == 0)
	{
		actual.inicio = nuevo;
		actual.fin = nuevo;
		actual.size = 1;
	}
	else{
		nodo * aux = actual.inicio;
		int i;
		for (i = 0; i < actual.size-1; i++){
			aux = aux->sgte;
		}
		aux->sgte = nuevo;
		nuevo->ant = aux;
		actual.fin = nuevo;
		actual.size++;
	}
	return actual;
}

lista insertar2(lista actual, char* elemento, int posicion){
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	nuevo->valor = elemento;
	nuevo->sgte = NULL;
	nuevo->ant = NULL;
	if (actual.size == 0)
	{
		actual.inicio = nuevo;
		actual.fin = nuevo;
		actual.size = 1;
	}
	else{
		nodo * aux = actual.inicio;
		int i;
		for (i = 0; i < posicion-1; i++){
			aux = aux->sgte;
		}
		nuevo->sgte = aux;
		nuevo->ant = aux->ant;
		nuevo->ant->sgte = nuevo;
		nuevo->sgte->ant = nuevo;
		actual.size++;
	}
	return actual;
}

lista remover2(lista actual, int posicion){
	nodo * aux = actual.inicio;
	int i;
	for (i = 0; i < posicion-1; i++)
	{
		aux = aux->sgte;
	}
	/*////////Manera 1//////////
	aux->ant->sgte = aux->sgte;
	aux->sgte->ant = aux->ant;
	free(aux);
	actual.size--;*/

	///////Manera 2//////////
	nodo * auxant = aux->ant;
	nodo * auxsgt = aux->sgte;
	auxant->sgte = auxsgt;
	auxsgt->ant = auxant;
	free(aux);
	return actual;
}


lista remover(lista actual, char* elemento){
	nodo * aux = actual.inicio;
	nodo * anterior = actual.inicio;
	int i;
	for (i = 0; i < actual.size-1; i++)
	{
		if (strcmp(aux->valor ,elemento)==0)
		{
			anterior->sgte = aux->sgte;
			free(aux);
			actual.size--;
			return actual;
		}
		else{
			anterior = aux;
			aux = aux->sgte;
		}
	}
	printf("No se encontro el elemento\n");
	return actual;
}

void imprimir(nodo*lista){
	nodo * aux;
	aux = lista;
	while(aux->sgte != NULL){
		printf("%s, ", aux->valor);
		aux = aux->sgte;
	}
	printf("%s, ", aux->valor);
	printf("\n");
}

void imprimir2(nodo*fin){
	nodo * aux;
	aux = fin;
	while(aux->ant != NULL){
		printf("%s, ", aux->valor);
		aux = aux->ant;
	}
	printf("%s, ", aux->valor);
	printf("\n");
}



int main(int argc, char const *argv[])
{
	lista enlazada;
	enlazada.inicio = NULL;
	enlazada.size = 0;
	enlazada = insert(enlazada, "hola");
	enlazada = insert(enlazada, "que");
	enlazada = insert(enlazada, "tal");
	enlazada = insert(enlazada, "jajaja");
	imprimir(enlazada.inicio);
	enlazada = insertar2(enlazada, "insertar", 3);
	imprimir(enlazada.inicio);
	//enlazada = remover2(enlazada, 2);
	imprimir(enlazada.inicio);
	//enlazada = remover(enlazada, 20);
	//enlazada = insert(enlazada, 60);
	//imprimir2(enlazada.fin);
	return 0;
}