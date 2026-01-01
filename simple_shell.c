#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
* main - Entry point for the simple shell program.
*
* Return: 0 on normal exit.
*/
int main(void)
{
	char *command;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			display_prompt();

	command = read_line();

	if (command == NULL)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "\n", 1);
		}

		break;
	}

	size_t len = strlen(command);

	if (len > 0 && command[len - 1] == '\n')
		command[len - 1] = '\0';

	char *clean_up = clean_blank_line(command);

	if (clean_up[0] != '\0')
		execute_program(clean_up);

	free(command);
	}

	return (0);
}
