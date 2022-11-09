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

extern char **environ;

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

/*atoi*/
int checkatoi(char *s);
int _atoi(char *s);

/*exit*/
int shellexit(char *s, char *arg);
#endif
