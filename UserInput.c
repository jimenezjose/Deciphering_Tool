#include <stdio.h>
#define BUFF_SIZE 1024

long askUser(const char *, unsigned long);
long * getaline(long *, unsigned long);
void clrbuff(long);

/**
 * Purpose: Ask for user input.
 */
long askUser(const char * prompt, unsigned long input_size) {
  long answer; /*user input answer*/
  long buffer[BUFF_SIZE]; /*input buffer*/
  /*get user input to begin program*/

  do {

    fprintf(stdout, "%s", prompt);
    getaline( buffer, input_size ); /*only record one letter from input*/
    answer = *buffer; /*character from first element in buffer*/

  } while( answer != '\0' && answer != EOF );

  return answer;
}

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

