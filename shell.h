#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
int execute_program(char *cmd_path, char **args, char **env,
			char *argv0, int line_count);
char *trim_line(char *line);
char **split_line(char *line);
void free_args(char **args);
char *find_command(char *cmd, char **env);
int builtin_exit(char **args);

#endif
