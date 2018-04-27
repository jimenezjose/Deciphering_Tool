/**************************************************************************** 
Jose Jimenez                                            April 27, 2018  
            
File Name:   Userinput.c
 
Description: Handles user input.
****************************************************************************/
#include <stdio.h>
#include "UserInput.h"

/***************************************************************************
% Routine Name : askUser
% File :         UserInput.c
% Parameters:    prompt:     message to inform user
%		 max_input: max number of characters expected
% Description :  prompts user with passed "prompt" message and reads in 
%	 	 "input_size" characters
% Returns :      returns response of user.
***************************************************************************/
long askUser(const char * prompt, unsigned long max_input) {
  long answer; /*user input answer*/
  long buffer[BUFF_SIZE]; /*input buffer*/
  /*get user input to begin program*/

  do {

    fprintf(stdout, "%s", prompt);
    getaline( buffer, max_input ); /*only record one letter from input*/
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
/***************************************************************************
% Routine Name : getaline
% File :         Mitnick.c
% Parameters:    buffer: array to store user input.
% 		 maxlength: expected length of input
% Description :  gets a line of input from user.
% Returns :      pointer to the buffer passed
***************************************************************************/
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
      /*flush characters in stdin buffer after maxlength*/
      clrbuff(character);  
      break;
    }
 
  }

  buffer[index] = (character == EOF) ? EOF : '\0'; /*null terminating string.*/

  return buffer;
} 

/***************************************************************************
% Routine Name : clrbuff
% File :         Mitnick.c
% Parameters:    character: last character extracted from stdin.
% Description :  Clears essentially the garbage character in the stdin buffer
% Returns :      Nothing
***************************************************************************/
void clrbuff(long character) {
  /*flush stdin buffer*/
  while( character != '\n' ) {
    character = fgetc(stdin);
  }

}

