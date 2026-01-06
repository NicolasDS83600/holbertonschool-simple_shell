#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"

/**
* execute_program - Forks a new process to execute a given program.
* @args: argument array
* @environ: It's the global variable
* @argv0: Name of the shell program
* @line_count: Line number of the command
*
* Return: 0 on successful execution.
*/
int execute_program(char **args, char **environ, char *argv0, int line_count)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid < 0)
	{
		perror(argv0);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_count, args[0]);
			exit(127);
		}
	}

	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
