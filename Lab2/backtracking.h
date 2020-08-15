
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

