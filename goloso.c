#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "goloso.h"
/* 
	########################################################################
	#				                                                       #
	#                       ESPACIO DE DEFINICIONES						   #
	#							                                           #
	########################################################################
  
*/


#define TRUE 1
#define FALSE 0






/* 
	########################################################################
	#																	   #
	#                       ESPACIO DE FUNCIONES						   #
	#																	   #
	########################################################################
  
*/


listMines updateListMines(listMines list,move currentMove){

	int initialQuarry = currentMove.initial;
	int finalQuarry = currentMove.final;
	int goldInitial=0;

	int i;
	for (i = 0; i < list.count; i++)
	{
		if (list.mines[i].quarry == initialQuarry)
		{
			goldInitial = list.mines[i].gold;
			list.mines[i].gold=0;
		}

	}

	for (i = 0; i < list.count; i++)
	{
		if (list.mines[i].quarry == finalQuarry)
		{
			list.mines[i].gold= list.mines[i].gold + goldInitial;
		}

	}
	return list;
}

int countMinesWithGold(listMines Lm){

	int i;
	int count=0;
	for (i = 0; i < Lm.count; i++)
	{
		if (Lm.mines[i].gold != 0)
		{
			count++;
		}
	}
	return count;
}


void printMoveList(listMoves current){

	
	printf("Imprimiendo movimientos\n");
	int i;
	for(i=0;i<current.count;i++){
		printf("inicial = %i, final = %i , costo = %i\n",current.moves[i].initial,current.moves[i].final,current.moves[i].cost);
	}
}


move selectMinMove(listMoves Lmoves){


	move result;

	int i;
	double min = 99999999999;
	for (i = 0; i < Lmoves.count; i++)
	{
		if (Lmoves.moves[i].cost < min && Lmoves.moves[i].cost != 0)
		{
			min = Lmoves.moves[i].cost;
		}
	}

	for (i = 0; i < Lmoves.count; i++)
	{
		if (Lmoves.moves[i].cost == min)
		{
			result = Lmoves.moves[i];
		}
	}
	return result;

}


int findNerbyQuarry(listMines Lmines,int Mine){

	int result;

	if (Lmines.count != 0)
	{
		
		int i;
		mine* List = Lmines.mines;

		double min = 99999999999;
		for (i = 0; i < Lmines.count; i++)
		{
			if (List[i].quarry != Mine && List[i].gold)
			{
				if (fabs(Mine - min) > fabs(Mine - List[i].quarry))
				{
					min = List[i].quarry;
				}
			}
		}

		for (i = 0; i < Lmines.count; i++)
		{
			if (List[i].quarry == min)
			{
				result = List[i].quarry;
			}
		}
	}
	return result;

}





listMoves createListOptimalMines(listMines currentMines){

	listMoves newMoves;
	newMoves.moves = (move*)malloc(sizeof(move)*currentMines.count);
	newMoves.count = currentMines.count;
	

	int i;
	for (i = 0; i < currentMines.count; i++)
	{

		int init = currentMines.mines[i].quarry;
		int finl = findNerbyQuarry(currentMines,init);
		int cost = fabs(init - finl) * currentMines.mines[i].gold;
		#ifdef DEBUG
		printf("acutales -> ini = %i, fin = %i , cost = %i\n",init,finl,cost);
		//addMoveToList(newMoves,init,finl,cost);
		#endif

	    newMoves.moves[i].initial = init;
	    newMoves.moves[i].final = finl;
	    newMoves.moves[i].cost = cost;

		
	}
	return newMoves;

}


void printMineList(listMines current){

	printf("**Imprimiendo info de mina**\n");
	printf("cantidad de minas : %i\n",current.count);
	printf("cantidad de camiones: %i\n",current.trucks);

	int i;
	for ( i= 0; i < current.count; i++)
	{
		printf("mina: %i, oro %i\n",current.mines[i].quarry,current.mines[i].gold );

	}
	printf("\n");
}


listMines readFile(char* rute){
   
    listMines new;
    new.trucks =0;
    new.count =0;
    new.mines = NULL;

    FILE* fichero =fopen(rute,"r");
  	if (fichero) {

	    #ifdef DEBUG
	    printf("Fichero abierto correctamente\n");
	    #endif


	    fscanf(fichero,"%i %i",&new.count, &new.trucks);

	    new.mines = (mine*)malloc(sizeof(mine)*new.count);
	    int i;
	    for (i = 0; i < new.count; i++)
	    {
	    	fscanf(fichero,"%i %i",&new.mines[i].quarry, &new.mines[i].gold);
	    }
	    return new;
  	}

  	else
   	{
	    printf("No se pudo abrir el archivo\n");
	    printf("revise que la ruta o nombre del archivo sea correcto...\n");
	    return new;
	    
    }
}

void writeFile(move* lmoves, int minesCount){

  FILE* fichero = fopen("salida.out","w");
  int totalCost =0;

  if (fichero) {
    #ifdef DEBUG
    printf("Fichero abierto correctamente\n");
    #endif
    int i;
    for (i = 0; i < minesCount; i++)
    {
    	if (lmoves[i].cost != 0)
    	{
    		fprintf(fichero,"%i -> %i\n",lmoves[i].initial, lmoves[i].final);
    		totalCost=totalCost+lmoves[i].cost;
    	}
    }
    fprintf(fichero,"Costo: %i \n",totalCost );
    fclose(fichero);
  }
  else
   {

    printf("No se pudo abrir el archivo\n");
    printf("revise que no exista un archivo con el mismo nombre -> 'Salida.out'\n");
  }

}



move* goloso(listMines lMines){

	int cost=0;

	move* trazaList = (move*)malloc(sizeof(move)*lMines.count);
	int i=0;
	while(countMinesWithGold(lMines) > lMines.trucks){
		listMoves LM = createListOptimalMines(lMines);
		#ifdef DEBUG
		printMoveList(LM);
		#endif
		move min = selectMinMove(LM);
		#ifdef DEBUG
		printf("*************************************\n");
		printf("* movimiento minimo ( %i, %i, %i)   *\n",min.initial,min.final,min.cost);
		printf("*************************************\n");
		#endif
		trazaList[i]=min;
		cost = cost+min.cost;
		lMines = updateListMines(lMines,min);
		#ifdef DEBUG
		printMineList(lMines);
		#endif
		i++;

		#ifdef DEBUG
		printf("Press 'Enter' to continue: ... ");
		while ( getchar() != '\n');
		#endif

		free(LM.moves);

	}
	#ifdef DEBUG
	printf("Costo total = %i\n",cost);
	#endif

	return trazaList;
}

int main(int argc, char const *argv[])
{
	listMines current = readFile("entrada.in");
	move* traza = goloso(current);
	writeFile(traza, current.count);

	free(current.mines);
	free(traza);
	


	return 0;
}