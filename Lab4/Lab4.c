#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lab4.h"

/* 
	########################################################################
	#				                                                       #
	#                       ESPACIO DE DEFINICIONES						   #
	#							                                           #
	########################################################################
*/

#define MAX_CHAR 30
#define TRUE 1
#define FALSE 0

/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE FUNCIONES						   #
	#																	   #
	########################################################################
  
*/

int getEqualChar(char* word)
{

	int size = strlen(word);
	char equal=word[0];
	int i;

	for (i = 0; i < size; i++)
	{
		if (equal != word[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

char* virusComp(char* first, char* second)
{
	printf("comparando %s con %s\n",first,second );

	if (strlen(first) > strlen(second))
	{
		return second;
	}
	else if(strlen(first) < strlen(second)){
		return first;
	}
	else{
		int i = strcmp(first,second);
		if (i>0)
		{
			return second;
		}
		else if(i<0)
		{
			return first;
		}
		else{
			return first;
		}
	}
}


void printMinWords(nodo* current)
{
	printf("imprimiendo lista de minimos\n");
	printf("********\n");
	nodo * aux;
	aux = current;
	while(aux->next != NULL){
		printf("%s->%s\n",aux->word,aux->miniword);
		printf("********\n");
		aux = aux->next;
	}
	printf("%s->%s\n",aux->word,aux->miniword);
	printf("********\n");
	printf("\n");
}

int findResult(lista* current, char* word)
{
	nodo * aux = current->inicio;
	int i;
	for (i = 0; i < current->size-1; i++)
	{
		if (strcmp(aux->word ,word)==0)
		{
			return TRUE;
		}
		else{
			aux = aux->next;
		}
	}
	return FALSE;
}

char* getResult(lista* current, char* word)
{
	nodo * aux = current->inicio;
	int i;
	for (i = 0; i < current->size-1; i++)
	{
		if (strcmp(aux->word ,word)==0)
		{
			return aux->miniword;
		}
		else{
			aux = aux->next;
		}
	}
	return NULL;
}

void* insert(lista* current, char* currentWord, char* currentMini)
{


	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	nuevo->word = currentWord;
	nuevo->miniword= currentMini;
	nuevo->next = NULL;
	nuevo->ant = NULL;
	if (current->size == 0)
	{
		current->inicio = nuevo;
		current->fin = nuevo;
		current->size = 1;
	}
	else{
		nodo * aux = current->inicio;
		int i;
		for (i = 0; i < current->size-1; i++){
			if(strcmp(aux->word,currentWord)==0){
				nuevo->miniword = virusComp(currentMini,aux->miniword);
			}
			aux = aux->next;
		}
		aux->next = nuevo;
		nuevo->ant = aux;
		current->fin = nuevo;
		current->size++;
	}
	return current;
}


char* strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char* pDinamica(char* initial_word, lista* result_words)
{
	int i;
	int sizeWord = strlen(initial_word);
	#ifdef DEBUG
	printf("palabra actual : %s\n",initial_word);
	//printMinWords(result_words->inicio);
	#endif

	if (sizeWord == 1)
	{
		return initial_word;
	}
	else if(findResult(result_words,initial_word)==TRUE)
	{
		return getResult(result_words,initial_word); 
	}

	else if(getEqualChar(initial_word)==TRUE)
	{
		return initial_word;
	}
	
	else 
	{
		char* bestword = (char*)malloc(sizeof(char)*MAX_CHAR);
		bestword = "9999999999999999999999999";
		for (i = 1; i < sizeWord; i++)
		{	    
			char word1[MAX_CHAR] = "";
			
			char word2[MAX_CHAR] = "";
			char result1[MAX_CHAR]="";
			char result2[MAX_CHAR]="";
			strncpy( word1, initial_word, i );
			

			strrev(initial_word);
			strncpy( word2, initial_word, sizeWord-i );
			
			strrev(word2);
			strrev(initial_word);
			printf("division:  %s|%s\n",word1,word2);

			strcpy(result1,pDinamica(word1,result_words));
			strcpy(result2,pDinamica(word2,result_words));
			strcat(result1,result2);

			#ifdef DEBUG
			printf("current result : %s\n",result1);
			#endif
			bestword = virusComp(result1,bestword);
			char* NB = (char*)malloc(sizeof(char)*MAX_CHAR);
			strcpy(NB,bestword);
			printf("resultado bestword : %s\n",bestword );

			printf("palabra comparadas : %s  y %s \n",result1,initial_word );
			if (strcmp(result1,initial_word)!=0)
			{
				char result[MAX_CHAR] = "";
				strcpy(result,pDinamica(result1,result_words));
				printf("result post PD: %s\n",result);
				printf(" bestword dentro:  %s\n",NB);
				bestword = virusComp(result,NB);

			}
			
			#ifdef DEBUG
			printf(" bestword:  %s\n",bestword);
			#endif


			#ifdef DEBUG
			printf("Press 'Enter' to continue: ... ");
			while ( getchar() != '\n');
			#endif
		}
		char* newWord = (char*)malloc(sizeof(char)*MAX_CHAR);
		char* newBest = (char*)malloc(sizeof(char)*MAX_CHAR);
		strcpy(newWord,initial_word);
		strcpy(newBest,bestword);
		insert(result_words,newWord,newBest);
		printMinWords(result_words->inicio);

		return bestword;
	}
}



int main(int argc, char const *argv[])
{


	FILE* fichero;
	lista* listMin=(lista*)malloc(sizeof(lista));
	listMin->inicio=NULL;
	listMin->size=0;
	insert(listMin,"12","3");
	insert(listMin,"21","3");
	insert(listMin,"32","1");
	insert(listMin,"23","1");
	insert(listMin,"13","2");
	insert(listMin,"31","2");
	

	#ifdef DEBUG
	printMinWords(listMin->inicio);
	#endif
	

	char word[MAX_CHAR];
	printf("\n");
	printf("\n");

	switch(argc){

		case 1:
			#ifndef DEBUG
			printf("*****************************************\n");
			printf("*  ERROR: no hay parametros de entrada  *\n");
			printf("*****************************************\n");
			printf("\n");
			printf("USO: lab.exe archivo_entrada\n");
			#endif



			break;
		case 2: 

			
			fichero = fopen(argv[1],"r");
  			if (fichero) 
  			{
			    #ifdef DEBUG
			    printf("Fichero abierto correctamente\n");
			    #endif

			    fscanf(fichero,"%s\n",word);
			    fclose(fichero);
			    FILE* fichero_salida = fopen("salida.out","w");
			    fprintf(fichero_salida,"%s->%s\n",word,pDinamica(word,listMin));
			    printMinWords(listMin->inicio);
			    fclose(fichero_salida);
			    
			    while(listMin->inicio!=NULL){
			    	nodo* aux = listMin->inicio;
			    	listMin->inicio= aux->next;
			    	free(aux);

			    }
			    free(listMin);

		

			    printf("*****************************************\n");
				printf("*       Terminado: revisar salida.out   *\n");
				printf("*****************************************\n");
		  	}

		  	else
		   	{
				printf("*****************************************\n");
				printf("*       ERROR: El archivo no existe     *\n");
				printf("*****************************************\n");
  
		    }

			break;

		default:

			printf("*****************************************\n");
			printf("*  ERROR: Uso de parametros incorrectos *\n");
			printf("*****************************************\n");
			printf("\n");
			printf("USO: lab.exe archivo_entrada\n");
	

	}
	return 0;
}