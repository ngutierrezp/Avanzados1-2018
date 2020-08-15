
/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE ESTRUCTURAS						   #
	#																	   #
	########################################################################
  
*/
typedef struct Nodo
{
	char* word;
	char* miniword;
	struct Nodo * next;
	struct Nodo * ant;
}nodo;

typedef struct {
	nodo * inicio;
	nodo * fin;
	int size;
}lista;

/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE CABECERAS						   #
	#																	   #
	########################################################################
  
*/


int getEqualChar(char* word);
char* virusComp(char* first, char* second);
void printMinWords(nodo* current);
int findResult(lista* current, char* word);
char* getResult(lista* current, char* word);
void* insert(lista* current, char* currentWord, char* currentMini);
char* strrev(char *str);
char* pDinamica(char* initial_word, lista* result_words);