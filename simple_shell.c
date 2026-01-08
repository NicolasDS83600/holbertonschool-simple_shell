#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void handle_line(char *line, int line_count, char *argv0);
static void shell_loop(int interactive, char *argv0);

/**
* handle_line - process one command line
* @line: input line
* @line_count: command number
* @argv0: shell program name
*/
static void handle_line(char *line, int line_count, char *argv0)
{
	char *clean_line, **args, *cmd_path;

	clean_line = trim_line(line);

	if (clean_line == NULL || clean_line[0] == '\0')
		return;

	args = split_line(clean_line);

	if (args == NULL)
		return;

	cmd_path = find_command(args[0], environ);

	execute_program(cmd_path, args, environ, argv0, line_count);

	if (cmd_path)
		free(cmd_path);

	free_args(args);
}

/**
* shell_loop - main shell loop
* @interactive: interactive mode flag
* @argv0: shell program name
*/
static void shell_loop(int interactive, char *argv0)
{
	char *line;
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

		handle_line(line, line_count++, argv0);
		free(line);
	}
}

/**
* main - Entry point for the simple shell program.
* @argc: number of arguments (unused)
* @argv: array of argument strings
*
* Return: 0 on normal exit.
*/
int main(int argc, char **argv)
{
	int interactive;

	(void)argc;
	interactive = isatty(STDIN_FILENO);
	shell_loop(interactive, argv[0]);

	return (0);
}
