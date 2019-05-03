#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//set max number of words, max length and max line length
#define MAXWORDS 10000
#define MAXWORDLENGTH 50
#define MAXLINELENGTH 1000

int main(int argc, char *argv[])
{
	char word[MAXWORDLENGTH+1];
	char line[MAXLINELENGTH];
	
	char *wordListData; //define pointer to store list of strings
	int *wordListOffsets; //define pointer to an array
	
	int wordListLength = 8;

	int wordIndex = 0, byteCount = 0, dataSize = 32;

	wordListData = malloc(dataSize); //assign 32 bytes to word list 
    wordListOffsets = malloc(wordListLength * sizeof(int)); 
		
	char *junkToGetInTheWay = malloc(dataSize);
									
	printf("Please enter a list of words: \nPress the enter key without entering a word to complete\n");
	
	while (wordIndex < MAXWORDS)
	{
        //get user input, break if new line entered
		fgets(line, MAXLINELENGTH, stdin);
		
		if(line[0] == '\n') 
            break;
		
        //read line into array
		sscanf(line, "%50s", word);
		
        //get a word from the line
		if(wordIndex >= wordListLength)
		{
			wordListLength = wordListLength * 2;
			wordListOffsets = realloc(wordListOffsets, wordListLength * sizeof(int));
		}
		wordListOffsets[wordIndex] = byteCount;

        //calculate the number of bytes
		byteCount = byteCount + strlen(word) + 1;

        //increase allocated memore if size is less than curent memory
		if(byteCount > dataSize)
		{ 
			dataSize = dataSize * 2;

			wordListData = realloc(wordListData, dataSize);

			char *junkToGetInTheWay = malloc(dataSize);
		}
        
        //copy word into the array
		strcpy(wordListData + wordListOffsets[wordIndex], word); 
	
		wordIndex++;
	}
		
		int numWords = wordIndex;
		
		for(wordIndex = numWords - 1; wordIndex >= 0; wordIndex--)
		{
			printf("%s\n", (char *)(wordListData + wordListOffsets[wordIndex])); 
		}
}

