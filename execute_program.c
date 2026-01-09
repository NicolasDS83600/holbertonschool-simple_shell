#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include "shell.h"

/**
* check_err - check if command exists and is executable
* @cmd_path: full path of the command
* @args: argument array
* @argv0: shell program name
* @line_count: command line number
*
* Return: 0 if ok, 126 if permission denied, 127 if not found
*/
static int check_err(char *cmd_path, char **args, char *argv0, int line_count)
{
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_count, args[0]);
		return (127);
	}

	if (access(cmd_path, F_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
		argv0, line_count, args[0]);
		return (127);
	}

	if (access(cmd_path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
		argv0, line_count, args[0]);
		return (126);
	}

	return (0);
}

/**
* execute_program - fork and execute a program
* @cmd_path: full path of the command
* @args: argument array
* @env: environment variables
* @argv0: shell program name
* @line_count: command line number
*
* Return: exit status of the command
*/
int execute_program(char *cmd_path, char **args, char **env,
		char *argv0, int line_count)
{
	pid_t pid;
	int status, err;

	err = check_err(cmd_path, args, argv0, line_count);

	if (err != 0)
		return (err);

	pid = fork();

	if (pid < 0)
		return (1);

	if (pid == 0)
	{
		execve(cmd_path, args, env);

		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				argv0, line_count, args[0]);
			exit(126);
		}

		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_count, args[0]);
		exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
		return (1);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
