#include <stdlib.h>
#include <string.h>

/**
* free_partial_args - frees partially allocated args
* @args: argument array
* @count: number of allocated elements
*/
static void free_partial_args(char **args, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(args[i]);
	}
	free(args);
}

/**
* add_token - adds a token to the arguments array safely
* @args: pointer to the array of argument strings
* @size: pointer to the current allocated size of the array
* @count: current number of arguments in the array
* @token: token string to add
*
* Return: 0 on success, 1 if allocation fails
*/
static int add_token(char ***args, int *size, int count, char *token)
{
	char **tmp;

	if (count >= *size)
	{
		*size *= 2;
		tmp = realloc(*args, sizeof(char *) * (*size));

		if (tmp == NULL)
			return (1);
		*args = tmp;
	}

	(*args)[count] = strdup(token);

	if ((*args)[count] == NULL)
		return (1);

	return (0);
}

/**
* split_line - split a command line into arguments
* @line: input string
*
* Return: array of pointers to arguments, terminated by NULL
*/
char **split_line(char *line)
{
	char **args = NULL;
	char *copy, *token;
	int size = 8, count = 0;

	if (line == NULL)
		return (NULL);

	copy = strdup(line);

	if (copy == NULL)
		return (NULL);

	args = malloc(sizeof(char *) * size);

	if (args == NULL)
	{
		free(copy);
		return (NULL);
	}

	token = strtok(copy, " \t\n");

	while (token != NULL)
	{
		if (add_token(&args, &size, count, token) != 0)
		{
			free_partial_args(args, count);
			free(copy);
			return (NULL);
		}
		count++;
		token = strtok(NULL, " \t\n");
	}

	args[count] = NULL;
	free(copy);
	return (args);
}

/**
* free_args - frees the argument array created by split_line
* @args: array returned by split_line
*/
void free_args(char **args)
{
	int pos;

	if (args == NULL)
		return;

	for (pos = 0; args[pos] != NULL; pos++)
		free(args[pos]);

	free(args);
}
