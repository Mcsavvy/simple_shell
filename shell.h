#ifndef SHELL_H
#define SHELL_H
#define bool int
#define true 1
#define false 0

#include "headers/include.h"
#include "headers/list.h"
#include "headers/string.h"
#include "headers/builtin.h"
#include "headers/path.h"

extern char **environ;

/* io */
void printerr(const char *message);
void printout(const char *message);

/* quote */
int findquote(char *str, char quote);
void comment(char *av[]);

/* line */
char *getLine(void);
char **tokenizeLine(char *line);

/* find */
char *findcmd(const char *command, const char *PATH);
char *findenv(char *env[], const char *name);
struct dirent *findfile(DIR *dir, const char *filename);
char *joinpath(const char *base, const char *child);

/* run */
int interactive(state *self);
int execute(const char *program, char **args, char **env);

/* append */
bool appendStr(char ***arr, size_t *size, char *str, int index);
bool appendChar(char **string, size_t *size, char chr, int index);
bool appendInt(char **string, size_t *size, int num, int index);

/*atoi*/
int checkatoi(char *s);
int _atoi(char *s);


/* format */
char *format(const char *fmt, ...);


/* main */
state *init(char *prog, char **env);
void deinit(state *self);
void cleanup(state *self);

char *replace(state *self, char *var);

#endif
