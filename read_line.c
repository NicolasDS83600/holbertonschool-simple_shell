#include <stdio.h>
#include <stdlib.h>

/**
* read_line - Reads a line of input from standard input (stdin).
*
* Return: Pointer to the line read (char *) on success,
*         or NULL on EOF/error.
*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_len;

	read_len = getline(&line, &len, stdin);

	if (read_len == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
