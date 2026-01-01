#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "shell.h"

/**
* execute_program - Forks a new process to execute a given program.
* @command: The path of the program to execute.
* @environ: It's the global variable
*
* Return: 0 on successful execution.
*/
int execute_program(char *command, char **environ)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, environ) == -1)
		{
			write(STDERR_FILENO, command, strlen(command));
			write(STDERR_FILENO, ": not found\n", 12);
			exit(EXIT_FAILURE);
		}
	}

	else
		wait(NULL);

	return (0);
}
