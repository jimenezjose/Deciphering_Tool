/**************************************************************************** 
Jose Jimenez
                                                        February 8, 2018 

File Name:   Ciphers.h
 
Description: Ciphers from Ghost in The Wires and neccessary variable/function 
	     definitions for Mitnick.c  
****************************************************************************/
#define MAXCHARS 256
#define OPEN_SPOT 257 /*index that will store next available spot in array*/
#define OFFSET 2 /*for arrays. +2: for termination, and next open spot*/

/*Titles and Ciphers*/
const char TITLE_CH1[] =
        "[Part One: The Making of a Hacker]\nONE: Rough Start\n";
const char CHAPTER_1[] =
        "Max vhlm hy max unl wkboxk ingva B nlxw mh ingva fr hpg mktglyxkl";
const char TITLE_CH2[] =
        "\nTWO: Just Visiting\n";
const char CHAPTER_2[] =
"Estd mzzu esle elfrse xp szh ez ncplep yph topyetetpd hspy T hld l acp-eppy";

/*Chapters titles and Ciphers in book. */
const char * TITLE[] = { TITLE_CH1, TITLE_CH2 };
const char * CIPHER[] = { CHAPTER_1, CHAPTER_2 };

/**
 * Purpose: Create a line in the output
 */
void line() {
  fprintf(stdout, "------------------------------------------------------\n");
}
