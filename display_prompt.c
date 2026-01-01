#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
* display_prompt - Prints the shell prompt "$ " to the standard output
*                  if the shell is running interactively.
*/
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
