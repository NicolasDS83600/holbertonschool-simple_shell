#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* builtin_exit - handles the "exit" builtin command
* @args: array of command arguments
*
* Return: -1 to signal shell_loop to exit, 0 otherwise
*/
int builtin_exit(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
		return (1);

	return (0);
}
