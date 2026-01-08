#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"
#include <errno.h>

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
	int status;

	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_count, args[0]);
		return (127);
	}

	pid = fork();

	if (pid < 0)
	{
		perror(argv0);
		return (1);
	}

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

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
