#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFunctionsLib.h"	

int main(int argc, char *argv[]) {

	mtgCardType *topOfCardList;
	
	
    printf("Please Enter a Title, Spell Type, Mana Cost, Power, Toughness. Values should be comma separated. \n");
	printf("Press enter key twice to end card input.\n");
	
    //load cards
	topOfCardList = loadCardList(); 
    //call print cards function
	printMtgCardList(topOfCardList);	

	return 0;
}
