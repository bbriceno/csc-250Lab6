#include <stdio.h>

#include <string.h>

#include <stdlib.h>

//set max number of words, max length and max line length
#define MAXWORDS 10000
#define MAXWORDLENGTH 50
#define MAXLINELENGTH 1000

int main(int argc, char * argv[]) {
    char word[MAXWORDLENGTH + 1];
    char line[MAXLINELENGTH];

    char * wordListData; //define pointer to store list of strings
    int * wordListOffsets; //define pointer to an array

    int wordListLength = 8;

    int wordIndex = 0,i=0, byteCount = 0, dataSize = 1024;

    wordListData = malloc(dataSize); //assign 32 bytes to word list 
    wordListOffsets = malloc(wordListLength * sizeof(int));

    char * junkToGetInTheWay = malloc(dataSize);
    FILE * userTxtFile;

    userTxtFile = fopen(argv[1], "r");

    if (userTxtFile == NULL) {
      printf("Sorry the file could not be open. Check to ensure it exist");
      exit(0);
    }
    printf("Input file found: %s\n\n", argv[1]);

    while (!feof(userTxtFile)) {
      //get user input, break if new line entered
      fgets(line, MAXLINELENGTH, userTxtFile);

      //read line into array
      sscanf(line, "%50s", word);

      //get a word from the line
      if (wordIndex >= wordListLength) {
        wordListLength = wordListLength * 2;
        wordListOffsets = realloc(wordListOffsets, wordListLength * sizeof(int));
      }
      wordListOffsets[wordIndex] = byteCount;

      //calculate the number of bytes
      byteCount = byteCount + strlen(word) + 1;

      //increase allocated memore if size is less than curent memory
      if (byteCount > dataSize) {
        dataSize = dataSize * 2;

        wordListData = realloc(wordListData, dataSize);

        char * junkToGetInTheWay = malloc(dataSize);
      }

      //copy word into the array
      strcpy(wordListData + wordListOffsets[wordIndex], word);

      wordIndex++;
    }
    fclose(userTxtFile);

    int count = 0;

    char firstWord[MAXWORDLENGTH + 1], secondWord[MAXWORDLENGTH + 1]="barb_test_01";

    while (count != 1) {
      //print instructions to user
      printf("Enter a command without quotes. Commands begin with ':' \n");
      printf("':quit' - end the program\n':list' - displays list of words\n':list whatever' - displays a list of words containing whatever\n");
      printf("You can also enter any word to check if word is in the given list: \n");

        //get user inout
      fgets(word, MAXWORDLENGTH + 1, stdin);
      sscanf(word, "%s %s", firstWord, secondWord);
       
        //check if user decides to quit
      if (strcmp(firstWord, ":quit")== 0) {
          printf("Thanks for playing. Goodbye\n");
          count = 1;
        } 
        //check if user entered list command
        else if (strcmp(firstWord, ":list")== 0) {
        
            //check if user did not enter a word and print full list
            if (strcmp(secondWord,"barb_test_01")==0) {
              for (i = 0; i < wordIndex-1; i++) {
                printf("%s\n", (char * )(wordListData + wordListOffsets[i]));
              }
            }
            //check if word exists 
            else {
              for (i = 0; i < wordIndex-1; i++) {
                if (strcmp(secondWord,(char * )(wordListData + wordListOffsets[i]))==0) {
              
                printf("\n~~~Word was FOUND in the word list~~~\n\n");
                    i=-1;
                    break;
                }
              }
               //if word was not found tell user
              if (i>=0){
              printf("\n~~~Word was NOT found in the word list~~~\n\n");
                }
            }
           }
        }
}
