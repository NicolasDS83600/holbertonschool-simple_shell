#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
* main - Entry point for the simple shell program.
*
* Return: 0 on normal exit.
*/
int main(void)
{
	char *line = read_line();
	int interactive = isatty(STDIN_FILENO);
	size_t len = strlen(line);
	char *clean_up = clean_blank_line(line);

	while (1)
	{
		if (interactive)
			display_prompt();

	if (line == NULL)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "\n", 1);
		}

		break;
	}

	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';

	if (clean_up && clean_up[0] != '\0')
		execute_program(clean_up, environ);

	free(line);
	}

	return (0);
}
