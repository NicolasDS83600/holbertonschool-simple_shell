#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* builtin_exit - handles the "exit" builtin command
* @args: array of command arguments
* @interactive: flag indicating if the shell is running interactively
*
* Return: -1 to signal shell_loop to exit, 0 otherwise
*/
int builtin_exit(char **args, int interactive)
{
	(void)args;

	if (interactive)
		exit(0);

	return (-1);
}
