/**************************************************************************** 
                            				Jose Jimenez
                            				February 8, 2018 

File Name:   mitnick.c
 
Description: Crack the ciphers on every chapter in the book, 
	     Ghost in the Wires by Kevin Mitnick. 
****************************************************************************/ 
// get user input. stop after one cipher finishes and ask for user input.
// create a .h file to contain all ciphers. ciphers.h?
// create a shift function. to shift all chars by some constant.
// look for single letters to deduce the number for shift
// if that doesnt work get user input to get notified.
// look for a letter or letters that occured the most frequent
// and do the same thing with the letters that are used the most
// in the english language. 
// "e t a o i n s r h l d c u m f p g w y b v k x j q z" given by 
// http://letterfrequency.org/. This way we can optimize
// the number of trials needed in a possible brute force attack.
#include <stdio.h>
#include "Ciphers.h"
#include "UserInput.c"

/*is_[...] 3 states of a character */
#define IS_SYMBOL 0
#define IS_ALPHABET  1
#define IS_NUMBER 2
#define BUFF_SIZE 1024

/*colorful output*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*function prototype declarations*/
void setUp();
void refresh();
long askUser(const char *);
long isSpace(char);
void charsFrequency();
void analyzeChars(const char*, long*, long*);
void categorizeChar(char, long*);
long proposeCeasar(long, const char * );
long shiftCipher( long, const char * );

unsigned long frequency[MAXCHARS] = { 0 }; /*Record frequency of chars*/
long charsFound[MAXCHARS + OFFSET];/*list of chars found in cipher*/

const int one_letter = 1;

void setUp() {
  /*refresh charsFound array*/
  refresh();

  line();
  fprintf(stdout, "Ghost in The Wires - By: Kevin Mitnick\n");
  fprintf(stdout, "\nThe following ciphers are given by Mitnick at every");
  fprintf(stdout, "\nchapter of his book.\n");
  line();


}

int main() {
  long numOfChars = 0; /*number of character in cipher*/
  long numOfWords = 0; /*number of words in cipher*/
  long chapter; /*chapter currently on in loop*/
  long size; /*elements in array (size)*/
  long numOfSpaces = 0;
  const char * cont = "Press Enter to Continue: ";
  const char * begin = "Press Enter to Begin: ";

  setUp();

  /*ask user to begin execution*/
  if( askUser(begin) == EOF ) {
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
    refresh();

    /*continue to scroll with the command of the user*/
    if ( askUser(cont) == EOF ) {
      break;
    }


  }

  fprintf(stdout, "\nDone.\n");
   
}

/**
 * Function Name: analyzeChars
 * 
 * Purpose: analyze the number of characters in a char array
 * 
 * Parameters: cipher: pointer to the char array of interest
 * 
 * Return: 	number of characters
 */
void analyzeChars(const char * cipher, long * numOfChars, long * numOfWords) {
  long index = 0; /*index of character array passed*/
  long currentChar = cipher[index]; /*current character of evaluation*/ 
  long type = IS_SYMBOL; /*by default the char is a symbol*/
  long open_spot; /*index of next open spot in charsFound*/
  long numOfSpaces = 0; /*number of spaces will be used to calc numOfWords*/
  long shift = 0; /*possibly a shift is possible to crack cipher*/

  while( currentChar != (char)NULL ) {
    /*categorize the character as symbol, number or alphabet*/
    categorizeChar( currentChar, &type );

    if( isSpace(currentChar) ) {
      numOfSpaces++;
    }


    /*take note of a new character. (0 frequenct of char)*/
    if( !frequency[currentChar] ) {
      open_spot = charsFound[OPEN_SPOT];
      charsFound[open_spot] = currentChar;
      /*update open spot in chars found*/
      charsFound[OPEN_SPOT]++;
    }

    shift = proposeCeasar(index, cipher);

    if( shift ) {
      /*possible crack*/
     
      /*"I" shift*/ 
      shift = ((long)'I') - shift;
      shiftCipher(shift, cipher);
      shift = shift + ((long)'I');
      shift = ((long)'a') - shift;
      shiftCipher(shift, cipher);
    }

    /*update the characters frequency*/
    frequency[currentChar]++;
    
    /*move to next character in cipher*/
    index++; 
    currentChar = cipher[index];


  }

  *numOfChars = index;
  *numOfWords = (numOfSpaces + 1);/*last word does not have a proceeding space*/

}

long shiftCipher( long shift, const char * cipher ) {
  long currentChar; /*current character in cipher*/
  long index; /*current index of cipher array*/
  long shiftedChar; /*new mapped character*/
  long isUpperCase;
  long isLowerCase;

  printf("Possible Ceasar Cipher.\n"); 
  printf("Shifting Cipher by %ld\n", shift);

  index = 0;
  currentChar = cipher[index];

  while( currentChar != '\0' ){

    if( currentChar == ' ' ) {
      /*skip shifts to spaces if any*/
      index++;
      currentChar = cipher[index];
      fprintf(stdout, " ");
      continue;
    }

    isLowerCase = currentChar >= 'a' && currentChar <= 'z';
    isUpperCase = currentChar >= 'A' && currentChar <= 'Z';

    /*shifted cipher will be in green*/
    printf( ANSI_COLOR_GREEN );


    if( isLowerCase ) {
	shiftedChar = ( (currentChar - 'a') + shift ) % 26 + 'a';
        fprintf(stdout, "%c", (char) shiftedChar);	
    }
    else if( isUpperCase ) {	
	shiftedChar = ( (currentChar - 'A') + shift ) % 26 + 'A';
        fprintf(stdout, "%c", (char) shiftedChar);	
    }


    /*move to the next character in cipher*/
    index++;
    currentChar = cipher[index]; 
  }

  /*newline*/
  fprintf(stdout, ANSI_COLOR_RESET "\n\n" );

  return shift;

}

/**
 * Function Name: proposeCeasar
 * Pupose: Find isolated characters, or use most frequent char
 *  	   to shift the cipher appropriately.
 * Return: the possible character in cipher that is an a or I.
 *  	   otherwise return 0.
 */
long proposeCeasar( long cipher_index, const char * cipher ) {
  const long CHARS_NEEDED = 3; /*3 characters needed for triplet sequence*/
  const long MIN_INDEX = 1; /*sequnce of 3 characters*/
  const long FIRST = 0; /*first character index in triplet*/
  const long MIDDLE = 1; /*second character index in triplet*/
  const long LAST = 2; /*last character index of triplet sequence*/
  long triplet[CHARS_NEEDED]; /*hold triplet*/
  long firstIndex; /* first index in charsFound pertains to triplet sequence*/
  long count; /*loop index*/

  if( cipher_index < MIN_INDEX ) {
    /*not enough characters to propose a shift*/
    return 0;
  }

  if( !cipher[cipher_index] || !cipher[cipher_index + 1]) {
    /*end of cipher*/
    return 0;
  }

  firstIndex = cipher_index - 1;
  /*retrieve triplet sequence*/
  for( count = 0; count < CHARS_NEEDED; count++ ) {
    triplet[count] = cipher[firstIndex + count];
  }

  if( triplet[MIDDLE] ==  ' ' ) {
    /*middle character must be non-space*/
    return 0;
  }

  /*possibly search for punctuations??TODO*/
  if( triplet[FIRST] == ' ' && triplet[LAST] == ' ' ) {
    /*middle character is surrounded by spaces!*/
    /*middle character is possible an I or a*/
    
 //   fprintf(stderr, "shifted B to I: %c, %c", (char) triplet[MIDDLE], 
 //(char)((triplet[MIDDLE] + ('I' - triplet[MIDDLE] )) ) ); 

    return triplet[MIDDLE];
  }

  return 0;
}

/**
 * Purpose: function that categorizes the char passed as a number, alphabet char
 *          or a symbol
 *
 * Return:  if character is a number of
 */
void categorizeChar( char character, long * type ) {
  long isAlphabet = (character >= 'a' && character <= 'z') || 
                                        (character >= 'A' && character <= 'Z') ;

  long isNumber = (character >= '0' && character <= '9');

  /*define the type*/
  if( isAlphabet ) {
    *type = IS_ALPHABET;
  }
  else if( isNumber ) {
    *type = IS_NUMBER;
  }
  else {
    *type = IS_SYMBOL;
  }

}

/**
 * Purpose: print a frequency chart for characters used in current cipher
 */
void charsFrequency() {
  const long SPACE = ' '; /*space character*/
  long character; /*refers to current character of analysis*/
  long index = 0; /*iterating variable*/

  character = charsFound[index];

  while( character != -1 ) {

    if( character != SPACE ) {
      fprintf(stdout, "%c\t%lu\n", (char) character, frequency[character] );
    }

    character = charsFound[++index];
  }

}

/**
 * Purpose: reassign the content of charsFound to 0.
 */
void refresh() {
  long index; /*coincides with index of an array*/
  unsigned long size; /*size of charsFound array*/
  size = sizeof(charsFound) / sizeof(charsFound[0]);
 
  /*default values of charsFound will be -1. no ascii is negative*/
  for( index = 0; index < size; index++ ) {
    charsFound[index] = -1;
  }

  /*reset arrays open spot*/
  charsFound[OPEN_SPOT] = 0; 
 
}

/**
 * Purpose: Ask for user input.
 */
long askUser(const char * when) {
  long answer; /*user input answer*/
  long buffer[BUFF_SIZE]; /*input buffer*/
  /*get user input to begin program*/

  do {

    fprintf(stdout, "%s", when);
    getaline( buffer, one_letter ); /*only record one letter from input*/
    answer = *buffer; /*character from first element in buffer*/    

  } while( answer != '\0' && answer != EOF );

  return answer;
}

/**
 * Puspose: boolean function that checks of character is a space
 */
long isSpace( char character ) {
  if( character == ' ' ) {
    return 1;
  }

  return 0;
}


