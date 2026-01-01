#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
* execute_program - Forks a new process to execute a given program.
* @command: The path of the program to execute.
*
* Return: 0 on successful execution.
*/
int execute_program(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *args[] = {command, NULL};

		execve(command, args, NULL);
		perror("command not found");
		exit(EXIT_FAILURE);
	}

	else
		wait(NULL);

	return (0);
}
