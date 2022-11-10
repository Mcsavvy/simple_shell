#ifndef BUILTIN_H
#define BUILTIN_H
#include "./list.h"

typedef int exit_status;
typedef struct state state;
typedef struct builtin builtin;
typedef exit_status(*builtincmd)(state *, char **);

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
 * @arguments: command line argument array
 * @pid: the process ID of the shell
 */
struct state
{
	pid_t pid;
	char *prog;
	node *env;
	node *aliases;
	char *line;
	char **arguments;
	int lineno;
	int _errno;
};


/**
 * struct builtin - a shell builtin
 *
 * @name: the name of the builtin
 * @handler: a function that handles the builtin command
 */
struct builtin
{
	char *name;
	builtincmd handler;
};

exit_status shellexit(state *self, char **arguments);
exit_status shellenv(state *self, char **arguments);
exit_status shellsetenv(state *self, char **arguments);
exit_status shellunsetenv(state *self, char **arguments);
exit_status shellcd(state *self, char **arguments);
exit_status shellalias(state *self, char **arguments);

#endif
