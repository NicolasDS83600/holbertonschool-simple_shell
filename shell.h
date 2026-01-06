#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
int execute_program(char **args, char **environ, char *argv0, int line_count);
char *trim_line(char *line);
char **split_line(char *line);
void free_args(char **args);

#endif
