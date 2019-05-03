
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "myGfxShapesLib.h"
#include "myFunctionsLib.h"
#include "gfx2.h"

#define MAXROWS 200
#define MAXCOLS 200
	

//function to sort an array of double using bubble sort
void sortNumbers(double sortArray[], int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (sortArray[j] > sortArray[j + 1])
			{
				double temp = sortArray[j];
				sortArray[j] = sortArray[j + 1];
				sortArray[j + 1] = temp;
			}

		}
	}
}

//function to visually sort an array of double using bubble sort 
void sortVisualize(double sortArray[], int n)
{
	int xsize = 400;
	int ysize = 400;
	int i, j;

	//graphic window
	while (1) {

		gfx_open(xsize, ysize, "Sorting");
		gfx_color(100, 100, 100);

		//Initialis draw bars
		drawBars(sortArray, n, 50, 300, .75*(300 / n), .25*(300 / n));
		gfx_flush();

		//stop for user
		usleep(300000);

		//bubble sort implementation with visualization
		for (i = 0; i < n - 1; i++)
		{
			for (j = 0; j < n - i - 1; j++)
			{
				gfx_clear();
				drawBars(sortArray, n, 50, 300, .75*(300 / n), .25*(300 / n));
				gfx_flush();
				usleep(500000);

				if (sortArray[j] > sortArray[j + 1])
				{	
					double temp = sortArray[j];
					sortArray[j] = sortArray[j + 1];
					sortArray[j + 1] = temp;
				}

			}
		}

		i = gfx_wait();

		// Stop if it is the letter q.
		if (i == 'q') break;

	}
}


//structure of board
typedef struct
{
    char tile;     
    int letter;     
    int word;      
} board_t;
	
// board should be 21x21, one extra added for border
board_t Board[21][22]; 
	

void init_board(void) 
{
    int i, j;
	
        //initialize a board
	    for (i=0; i<21; i++)
	        for (j=0; j<22; j++)
	        {
	            Board[i][j].letter = 0;
	            Board[i][j].word = 0;
	            Board[i][j].tile = ' ';
	            if ((i==0 || i==7 || i==14) && (j==0 || j==7 || j==14))
	                Board[i][j].word = (i==7 && j==7) ? 2 : 3;
	            else if ((i==5 || i==9) && ((j-1)%4==0))
	                Board[i][j].letter = 3;
	            else if ((j==5 || j==9) && ((i-1)%4==0))
	                Board[i][j].letter = 3;
	            else if ((i==6 || i==8) && (j==2 || j==6 || j==8 || j==12))
	                Board[i][j].letter = 2;
	            else if ((j==6 || j==8) && (i==2 || i==6 || i==8 || i==12))
	                Board[i][j].letter = 2;
	            else if ((i==3 || i==11) && (j==0 || j==7 || j==14))
	                Board[i][j].letter = 2;
	            else if ((j==3 || j==11) && (i==0 || i==7 || i==14))
	                Board[i][j].letter = 2;
	            else if (i==j || i==(14-j))
	                Board[i][j].word = 2;
	        }
	}
	

void draw_board(void) 
{
	    int i, j, letter, word;
        //creates numbers at the top
	    printf("    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21\n  "); 
	    for (i=0; i<21; i++)
	    {
	        for (j=0; j<21; j++)
	        {
	            letter = (Board[i][j].letter | ((i)?Board[i-1][j].letter:0));
	            word = (Board[i][j].word | ((i)?Board[i-1][j].word:0));
	        }
	

	        printf("\n%c ",i+0x61); 
	        for (j=0; j<22; j++)
	        {
	            letter = (Board[i][j].letter | ((j)?Board[i][j-1].letter:0));
	            word = (Board[i][j].word | ((j)?Board[i][j-1].word:0));
	            if (letter == 3)
	                printf("  %c ",(j<21)?Board[i][j].tile:i+0x61);
	            else if (word == 3)
	                printf("  %c ",(j<21)?Board[i][j].tile:i+0x61);
	            else
	                printf("  %c ",(j<21)?Board[i][j].tile:i+0x61);
	        }
	        printf("\n  "); 
	

	    }
        //create numbers at botom
	    printf("  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21\n"); 
}


//Prints a table of integers	 
void printTableOfInts(int table[MAXROWS][MAXCOLS], int nRows, int nCols)
{
    int i,j;
    for (i=0; i<nRows; i++) 
    {
        for (j=0; j<nCols; j++)
        {
            printf("%3d", table[i][j]); 
        }
	        printf("\n"); 
	    }
	}
	

//Prints the game of life board
void printGameOfLife(int table[MAXROWS][MAXCOLS], int nRow, int nCols)
{
	int i,j;
	
	for (i=0; i < nRow; i++)
	{
		for (j=0; j < nCols; j++)
		{
			if (table[i][j] == 1) {
			printf(" * ");
			} else {
			printf("   ");
			}
		}
		printf("\n");	
	}

}	

void countNeighbors(int sourceGrid[MAXROWS][MAXCOLS], int countGrid[MAXROWS][MAXCOLS], int nRows, int nCols) 
{
	int i,j,deltaRow,deltaCol;	

	for(i = 0;i < nRows;i++) { 
		for(j = 0;j < nCols;j++) { 

			countGrid[i][j] = 0;
			for(deltaRow = -1;deltaRow <= 1;deltaRow++) {
				for(deltaCol = -1;deltaCol <= 1;deltaCol++) { 
					
				  	if( i+deltaRow >= 0 && j+deltaCol >= 0 && 	
				  		i+deltaRow < nRows && j+deltaCol < nCols)
				  	{	
						if(deltaRow != 0 || deltaCol != 0){	
							countGrid[i][j] = countGrid[i][j] + sourceGrid[i+deltaRow][j+deltaCol];
					
						}
					}
				}
			}		
		}
	}		
}		

	

void updateGameOfLife(int golGrid[MAXROWS][MAXCOLS], int nRows, int nCols )
{
	int countGrid[MAXROWS][MAXCOLS];
	countNeighbors(golGrid,countGrid,nRows,nCols); 
	
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			if(golGrid[i][j] == 1){ 	
				if(countGrid[i][j] < 2 || countGrid[i][j] > 3){
					golGrid[i][j] = 0;
				}	
			
			} else {		 
				if(countGrid[i][j] == 3){ 
					golGrid[i][j] = 1;	
				}	
			}
		}
	}
}


mtgCardType * loadCardList(){
	
	int power, toughness, manaCost;
	char title[50];
	char type[20];
	char uCards[100];
	
	mtgCardType * newCardPtr = NULL;
	mtgCardType * lastCardInList = NULL;
	mtgCardType * firstCardInList = NULL;
	
    int count = 0;
	while (count!=1){	

		// read card in
		fgets(uCards, 100, stdin);
		if (uCards[0] == '\n'){
			break;
		}	 
		
		//get user input
		sscanf(uCards, "%[^,],%[^,] %d %d %d", title, type, &manaCost, &power, &toughness);
		
		//create card
		newCardPtr = (mtgCardType *) malloc(sizeof(mtgCardType)); 
		
		//copy values into structure
		strcpy(newCardPtr->title, title);
		strcpy(newCardPtr->spellType, type); 
		newCardPtr->manaCost = manaCost;
		newCardPtr->power = power;
		newCardPtr->toughness = toughness;
		
		// set to end of list
		newCardPtr->nextCard = NULL;
		
		// insert card into list
		if (firstCardInList != NULL){
			(*lastCardInList).nextCard = newCardPtr;	
		} else {
			firstCardInList = newCardPtr;
		}
		
		// point to new last card
		lastCardInList = newCardPtr;
	}
	// return to beginning of list 
	return firstCardInList;
}


void printMtgCardList(mtgCardType *cardListTop){

	mtgCardType * currentCard = cardListTop;
	
	if (cardListTop == NULL){
		printf("** CARD LIST IS EMPTY! **\n");
		exit;
	} else {	
	
		//print card headers
		printf("%20s %20s %12s %12s %12s\n", "Card Title", "Spell Type", "Mana Cost", "Power", "Toughness");

		// print cards
		while(currentCard != NULL){
			
			printf("%20s %20s %12d %12d %12d\n", currentCard->title, currentCard->spellType, currentCard->manaCost, currentCard->power, currentCard->toughness);
			currentCard = currentCard->nextCard; 
		}
	}
}

mtgCardType * sortCardsByTitle(mtgCardType * topOfList){

	int counter = 1;	
	
	mtgCardType * sortedListTop = topOfList;
	
	// check if cards are loaded
	if(topOfList == NULL){
		return 0;
	}	
	
	// loop till no more swaps
	while(counter != 0){
		
	
		mtgCardType * before = NULL;
		mtgCardType * current = sortedListTop;
		mtgCardType * after = current->nextCard;

		counter = 0;
	
		while(after != NULL){
			if(strcmp(current->title, after->title) > 0){
				// test whether to continue sorting
				counter++;
				
				// 
				if(before == NULL){
					sortedListTop = after;
				} else { 
					before->nextCard = after;
				}		
				// sort cards
				current->nextCard = after->nextCard;
				after->nextCard = current;
				

				before = after;
				after = after->nextCard->nextCard;
			} else {

				before = current;
				current = after;
				after = after->nextCard;	
			}	
		}
	}
	
	// return to beginning of list
	return sortedListTop;	
}
