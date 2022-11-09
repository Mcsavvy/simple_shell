#ifndef SHELL_H
#define SHELL_H
#define bool int
#define true 1
#define false 0

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "list.h"

extern char **environ;

/**
 * struct state - useful variables that would be passed
 * around from the main function.
 *
 * @env: shell environment variables
 * @aliases: shell aliases
 * @line: the current line of command being parsed
 * @_errno: a number indicating the error of the last command ran
 * @lineno: the current line number
 * @prog: the program name used to start the shell
 * @pid: the process ID of the shell
 */
struct state
{
	pid_t pid;
	char *prog;
	node *env;
	node *aliases;
	char *line;
	int lineno;
	int _errno;
};

typedef struct state state;

/* quote */
int findquote(char *str, char quote);

/* line */
char *getLine(void);
char **tokenizeLine(char *line);

/* find */
char *findcmd(const char *command, const char *PATH);
char *findenv(char *env[], const char *name);
struct dirent *findfile(DIR *dir, const char *filename);
char *joinpath(const char *base, const char *child);

/* run */
int execute(const char *program, char *args[]);

/* append */
int appendStr(char ***arr, size_t *size, char *str, int index);
int appendChar(char **string, size_t *size, char chr, int index);

#endif
