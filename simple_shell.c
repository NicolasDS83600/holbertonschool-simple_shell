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
	char *line, *clean_line;
	size_t len;
	int interactive = isatty(STDIN_FILENO);
	int line_count = 1;

	while (1)
	{
		if (interactive)
			display_prompt();

		line = read_line();

		if (line == NULL)
		{
			if (interactive)
			{
				write(STDOUT_FILENO, "\n", 1);
			}

			break;
		}

		len = strlen(line);

		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		clean_line = trim_line(line);

		if (clean_line && clean_line[0] != '\0')
			execute_program(clean_line, environ, "./hsh", line_count);

		free(line);
		line_count++;
	}

	return (0);
}
