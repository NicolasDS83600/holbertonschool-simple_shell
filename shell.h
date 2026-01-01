#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void display_prompt(void);
char *read_line(void);
int execute_program(char *command);
char *clean_blank_line(char *str);

#endif
