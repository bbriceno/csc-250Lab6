
//3
void sortNumbers(double sortArray[], int n);
void sortVisualize(double list[], int size);

//4
#define MAXROWS 200
#define MAXCOLS 200
void init_board(void);
void draw_board(void);
void printTableOfInts(int table[MAXROWS][MAXCOLS], int nRows, int nCols);
void printGameOfLife(int table[MAXROWS][MAXCOLS], int nRows, int nCols);
void countNeighbors(int sourceGrid[MAXROWS][MAXCOLS], int countGrid[MAXROWS][MAXCOLS], int nRows, int nCols);
void updateGameOfLife(int golGrid[MAXROWS][MAXCOLS], int nRows, int nCols);

//6

//define card structure
typedef struct mtgCardType
{
	char title[51]; 
	int manaCost;	
	char spellType[15];	
	int power;
	int toughness;
	
	struct mtgCardType * nextCard;	// define pointer to structure in  list
	 
} mtgCardType;

mtgCardType * loadCardList();
void printMtgCardList(mtgCardType *cardListTop);
mtgCardType * sortCardsByTitle(mtgCardType * topOfList);
