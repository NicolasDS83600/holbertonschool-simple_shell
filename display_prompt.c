#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
* display_prompt - Prints the shell prompt in the standard output
*                  if the shell is running interactively.
*/
void display_prompt(void)
{
	printf("($) ");
	fflush(stdout);
}
