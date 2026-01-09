#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
* get_path - retrieve the PATH environment variable
* @env: environment variables
*
* Return: pointer to PATH string or NULL if not found
*/
char *get_path(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

/**
* build_full_path - create full path string "dir/cmd"
* @dir: directory
* @cmd: command
*
* Return: allocated string, or NULL on failure
*/
static char *build_full_path(char *dir, char *cmd)
{
	char *full_path;
	size_t len;

	len = strlen(dir) + strlen(cmd) + 2;
	full_path = malloc(len);

	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, cmd);

	return (full_path);
}

/**
* check_absolute_or_relative - check if command contains '/' and exists
* @cmd: command string
*
* Return: allocated path if exists, NULL otherwise
*/
static char *check_absolute_or_relative(char *cmd)
{
	if (cmd == NULL)
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);

		return (strdup(cmd));

	}

	return (NULL);
}

/**
* search_in_path - search for command in PATH directories
* @cmd: command string
* @env: environment variables
*
* Return: allocated path if found, NULL otherwise
*/
static char *search_in_path(char *cmd, char **env)
{
	char *path_env, *path_copy, *dir, *full_path;

	path_env = get_path(env);

	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);

	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = build_full_path(dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
* find_command - resolve a command to its full path
* @cmd: command string
* @env: environment variables
*
* Return: allocated path if found, NULL otherwise
*/
char *find_command(char *cmd, char **env)
{
	char *result;

	result = check_absolute_or_relative(cmd);

	if (result)
		return (result);

	return (search_in_path(cmd, env));
}
