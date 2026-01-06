#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "shell.h"

/**
* execute_program - Forks a new process to execute a given program.
* @cmd: The path of the program to execute.
* @environ: It's the global variable
* @argv0: Name of the shell program
* @line_count: Line number of the command
*
* Return: 0 on successful execution.
*/
int execute_program(char *cmd, char **environ, char *argv0, int line_count)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)
	{
		perror(argv0);
		return (1);
	}

	if (pid == 0)
	{
		char *args[2];

		args[0] = cmd;
		args[1] = NULL;

		if (execve(cmd, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_count, cmd);
			exit(EXIT_FAILURE);
		}
	}

	else
		waitpid(pid, &status, 0);

	return (0);
}
