#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int handle_line(char *line, int line_count, char *argv0);
static int shell_loop(int interactive, char *argv0);

/**
* handle_line - process one command line
* @line: input line
* @line_count: command number
* @argv0: shell program name
*
* Return: status
*/
static int handle_line(char *line, int line_count, char *argv0)
{
	char **args, *cmd_path;
	int status = 0;

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

	if (builtin_exit(args))
	{
		free_args(args);
		return (-2);
	}

	if (builtin_env(args))
	{
		print_env(environ);
		free_args(args);
		return (0);
	}

	cmd_path = find_command(args[0], environ);
	status = execute_program(cmd_path, args, environ, argv0, line_count);

	free(cmd_path);
	free_args(args);

	return (status);
}

/**
* shell_loop - main shell loop
* @interactive: interactive mode flag
* @argv0: shell program name
*
* Return: status
*/
static int shell_loop(int interactive, char *argv0)
{
	char *line;
	int line_count = 1, status = 0, tmp;

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

		tmp = handle_line(line, line_count++, argv0);

		if (tmp == -2)
			break;

		status = tmp;
	}

	free(line);
	return (status);
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
	int interactive, status;

	(void)argc;
	interactive = isatty(STDIN_FILENO);
	status = shell_loop(interactive, argv[0]);

	return (status);
}
