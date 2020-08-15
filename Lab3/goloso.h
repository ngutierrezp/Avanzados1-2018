
/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE ESTRUCTURAS						   #
	#																	   #
	########################################################################
  
*/

typedef struct 
{
	int quarry;
	int gold;

}mine;

typedef struct 
{
	mine* mines;
	int count;
	int trucks;

}listMines;

typedef struct nodo
{
	int initial;
	int final;
	int cost;
}move;


typedef struct 
{
	move* moves;
	int count;
}listMoves;


/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE CABECERAS						   #
	#																	   #
	########################################################################
  
*/

