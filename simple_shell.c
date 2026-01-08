#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int handle_line(char *line, int line_count, char *argv0);
static void shell_loop(int interactive, char *argv0);

/**
* handle_line - process one command line
* @line: input line
* @line_count: command number
* @argv0: shell program name
*
* Return: 0 if the line was empty or command not found,
*         otherwise the exit status of the executed command.
*/
static int handle_line(char *line, int line_count, char *argv0)
{
	char **args, *cmd_path;

	if (line == NULL)
		return (0);

	line = trim_line(line);

	if (line[0] == '\0')
		return (0);

	args = split_line(line);

	if (args == NULL || args[0] == NULL)
	{
		free_args(args);
		return (0);
	}

	cmd_path = find_command(args[0], environ);

	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_count, args[0]);
		free_args(args);

		return (1);
	}

	execute_program(cmd_path, args, environ, argv0, line_count);

	free(cmd_path);
	free_args(args);

	return (1);
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
	interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	shell_loop(interactive, argv[0]);

	return (0);
}
