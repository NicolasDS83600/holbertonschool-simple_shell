#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* builtin_exit - handles the "exit" builtin command
* @args: array of command arguments
*
* Return: 1 if exit, 0 otherwise
*/
int builtin_exit(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
		return (1);

	return (0);
}

/**
* builtin_env - handles the env builtin command
* @args: array of arguments
*
* Return: 1 if is "env", 0 otherwise
*/
int builtin_env(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "env") == 0)
		return (1);

	return (0);
}

/**
* print_env - prints the environnement variable
* @env: environnement variables
*/
void print_env(char **env)
{
	int element = 0;

	if (env == NULL)
		return;

	while (env[element] != NULL)
	{
		printf("%s\n", env[element]);
		element++;
	}
}
