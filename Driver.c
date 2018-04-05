#include <stdio.h>
#include "Ciphers.h"
#include "UserInput.c"
#include "Mitnick.c"

#define ENTER 1

const char * CONTINUE = "Press Enter to Continue: ";
const char * BEGIN = "Press Enter to Begin: ";


int main() {
  long numOfChars = 0; /*number of character in cipher*/
  long numOfWords = 0; /*number of words in cipher*/
  long chapter; /*chapter currently on in loop*/
  long size; /*elements in array (size)*/
  long numOfSpaces = 0; /*number of space characters*/

  /*Program Description*/ 
  line();
  fprintf(stdout, "Ghost in The Wires - By: Kevin Mitnick\n");
  fprintf(stdout, "\nThe following ciphers are given by Mitnick at every");
  fprintf(stdout, "\nchapter of his book.\n");
  line();


  /*ask user to begin execution*/
  if( askUser(BEGIN, ENTER) == EOF ) {
    fprintf(stdout, "\nDone.\n");
    return 0;
  }

  size = sizeof(CIPHER) / sizeof(CIPHER[0]);
  /*print data for ciphers*/
  for( chapter = 0; chapter < size; chapter++ ) {

    printf("%s\n", TITLE[chapter]);
    printf(ANSI_COLOR_RED "\"%s\"" ANSI_COLOR_RESET "\n\n", CIPHER[chapter] );

    analyzeChars( CIPHER[chapter], &numOfChars, &numOfWords );
    numOfSpaces = numOfWords + 1; /*last word has no proceeding space*/

    printf("number of Characters: %ld\n", (numOfChars - numOfSpaces) );
    printf("number of Words: %ld\n", numOfWords);
    printf(ANSI_COLOR_BLUE "\nCharacter Frequency Chart:\n" ANSI_COLOR_RESET);
    charsFrequency();

    /*continue to scroll with the command of the user*/
    if ( askUser(CONTINUE, ENTER) == EOF ) {
      break;
    }


  }

  printf("\nDone.\n");

}
