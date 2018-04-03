#include <stdio.h>

long * getaline(long *, unsigned long);
void clrbuff(long);

/**
 * Function Name: getaline
 * Purpose: gets a line of standard input
 * Parameters: buffer: output paramter, stores the array
 *		       of ASCII values read from user input.
 * Return: altered input paramter, buffer.
 */
long * getaline( long * buffer, unsigned long maxlength ) {
  long index; /*index of buffer array*/
  long character; /*character input from stdin*/

  character = fgetc(stdin); 
  index = 0;

  while( character != '\n' && character != EOF) {

    if( index < maxlength ) {

      buffer[index] = character;
      character = fgetc(stdin);
      index++;  

    }
    else {
    
      clrbuff(character);  
      break;
    }
 
  }

  buffer[index] = (character == EOF) ? EOF : '\0'; /*null terminating string.*/

  return buffer;
} 

/**
 * Function Name: clrbuff
 * Purpose: Clear the stdin buffer
 * Parameters: character: stdin character
 */
void clrbuff(long character) {
  /*flush stdin buffer*/
  while( character != '\n' ) {
    character = fgetc(stdin);
  }

}
