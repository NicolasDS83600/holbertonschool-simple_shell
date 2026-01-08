#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"
#include <errno.h>
#include <sys/stat.h>

/**
* check_cmd_path - Check if comd exists, isn't a directory and is executable
* @cmd_path: full path of the command
* @args: argument array
* @argv0: shell program name
* @line_count: command line number
*
* Return: 0 if OK, 126 if permission denied or directory,
* 127 if command not found
*/
static int check_cmd_path(char *cmd_path, char **args,
			char *argv0, int line_count)
{
	struct stat st;

	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_count, args[0]);
		return (127);
	}

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: %d: %s: Is a directory\n", argv0, line_count, args[0]);
		return (126);
	}

	if (access(cmd_path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n", argv0,
			line_count, args[0]);
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
* Return: 0 on success, 126 or 127 on error
*/
int execute_program(char *cmd_path, char **args, char **env,
			char *argv0, int line_count)
{
	pid_t pid;
	int status, error;

	error = check_cmd_path(cmd_path, args, argv0, line_count);

	if (error != 0)
		return (error);

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
			exit(126);

		else
			exit(127);
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
