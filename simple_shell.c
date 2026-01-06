#include "shell.h"
#include <unistd.h>
#include <stdlib.h>

static void shell_loop(int interactive);
static void handle_line(char *line, int line_count);

/**
* handle_line - process one command line
* @line: input line
* @line_count: command number
*/
static void handle_line(char *line, int line_count)
{
	char *clean_line;
	char **args;

	clean_line = trim_line(line);

	if (clean_line == NULL || clean_line[0] == '\0')
		return;

	args = split_line(clean_line);

	if (args == NULL)
		return;

	execute_program(args, environ, "./hsh", line_count);
	free_args(args);
}

/**
* shell_loop - main shell loop
* @interactive: interactive mode flag
*/
static void shell_loop(int interactive)
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
		{
			execute_program(clean_line, environ, "./hsh", line_count);
			line_count++;
		}
		free(line);
	}

	return (0);
}
