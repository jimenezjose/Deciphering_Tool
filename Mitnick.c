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

#include "Mitnick.h"

unsigned long frequency[MAXCHARS] = { 0 }; /*Record frequency of chars*/
long charsFound[MAXCHARS + OFFSET];/*list of chars found in cipher*/

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

  refresh(); /*0 out charsFound global array*/

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

  if( triplet[FIRST] == ' ' && triplet[LAST] == ' ' ) {
    /*middle character is surrounded by spaces!*/
    /*middle character is possible an I or a*/

    //fprintf(stderr, "shifted B to I: %c, %c", (char) triplet[MIDDLE], 
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
  long isNumber = (character >= '0' && character <= '9');
  long isAlphabet = (character >= 'a' && character <= 'z') || 
                                        (character >= 'A' && character <= 'Z') ;
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
 * Puspose: boolean function that checks of character is a space
 */
long isSpace( char character ) {
  if( character == ' ' ) {
    return 1;
  }

  return 0;
}


