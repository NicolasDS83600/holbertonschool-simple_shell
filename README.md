## _SIMPLE_SHELL !
'''

## Description
'''
Simple Shell is a C programming project that involves creating a simple command interpreter, similar to the Unix shell (/bin/sh).
This shell allows the user to execute commands in interactive or non-interactive mode.

This project is part of the Holberton School curriculum and helps to strengthen understanding of:

	- Unix system calls
	- Process management
	- String manipulation
	- Memory management
'''

Features
'''
	- Custom shell prompt waiting for user commands
	- Support for built-in commands:
		- exit : exits the shell
		- env : displays environment variables
	- Execution of external commands using the PATH
	- Error handling with custom error messages
	- Line-by-line input handling (both interactive and non-interactive mode)
	- Graceful exit on Ctrl+D (EOF)
'''

## Technical requirements and constraints
'''
	
- Allowed editors: vi, vim, emacs
- All the files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All the files should end with a new line
- A README.md
- The code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- The shell should not have any memory leaks
- No more than 5 functions per file
- All the header files should be include guarded
- Use system calls only when it need to
'''

## List of allowed functions and system calls+
'''
	
- getline (man 3 getline)
- printf (man 3 printf)
- execve (man 2 execve)
- fork (man 2 fork)
- malloc (man 3 malloc)
'''

## Compilation
'''

To compile simple shell use:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
'''

## Man page :
'''





'''

## Flowchart :
'''







'''

## Files :
'''
	- shell.h : Header file with prototypes and includes
	- simple_shell.c : Core shell functionality including command processing and execution
	- split_line.c : Command line parsing functions
	- trim_line.c : Removes empty spaces and tabs at the beginning and end of lines
	- read_line.c : Reads a line of input from standard input
	- display_prompt.c : Prints the shell prompt in the standard output
	- execute_program.c : Forks a new process to execute a given program


## Authors :
'''
- Nicolas Da Silva
- Bengin Uzun