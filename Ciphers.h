/**************************************************************************** 
Jose Jimenez
                                                        February 8, 2018 

File Name:   Ciphers.h
 
Description: Ciphers from Ghost in The Wires and necessary variable/function 
	     definitions for Mitnick.c  
****************************************************************************/
#ifndef _CIPHERS_H
#define _CIPHERS_H

#define MAXCHARS 256
#define OPEN_SPOT 257 /*index that will store next available spot in array*/
#define OFFSET 2 /*for arrays. +2: for termination, and next open spot*/

/*colorful output*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*Titles and Ciphers*/
static const char TITLE_CH1[] =
	"[Part One: The Making of a Hacker]\nONE: Rough Start\n";
static const char CHAPTER_1[] =
	"Max vhlm hy max unl wkboxk ingva B nlxw mh ingva fr hpg mktglyxkl";
static const char TITLE_CH2[] =
	"\nTWO: Just Visiting\n";
static const char CHAPTER_2[] =
"Estd mzzu esle elfrse xp szh ez ncplep yph topyetetpd hspy T hld l acp-eppy";

/*Chapters titles and Ciphers in book. */
static const char * TITLE[] = { TITLE_CH1, TITLE_CH2 };
static const char * CIPHER[] = { CHAPTER_1, CHAPTER_2 };


/**
 * Purpose: Create a line in the output for formatting sections
 */
static void line() {
  fprintf(stdout, "------------------------------------------------------\n");
}

#endif /*_CIPHERS_H*/
