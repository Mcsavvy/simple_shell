#include "shell.h"

/**
 * init - initialize the shell's state
 *
 * @prog: the program name
 * @env: the process' environment variables
 *
 * Return: the shell's state
 */
state *init(char *prog, char **env)
{
	state *global = malloc(sizeof(state));

	global->lineno = 1;
	global->aliases = NULL;
	global->env = from_strarr(env);
	global->pid = getpid();
	global->prog = prog;
	global->_errno = 0;
	global->content = NULL;
	global->lines = NULL;
	global->tokens = NULL;
	global->bufsize = 3;
	global->buf = malloc(NCHARS(global->bufsize));

	return (global);
}

/**
 * deinit - destroy the shell's state
 *
 * @self: the shell's state
 *
 * Return: nothing
 */
void deinit(state *self)
{
	if (!self)
		return;

	free_list(self->aliases);
	free_list(self->env);
	if (self->content)
		free(self->content);
	if (self->lines)
		free(self->lines);
	if (self->tokens)
		free(self->tokens);
	if (self->buf)
		free(self->buf);
	free(self);
}

/**
 * cleanup - routine clean up that frees up memory in the state
 * @self: the shell's state
 * Return: nothing
 */
void cleanup(state *self)
{

	if (!self)
		return;

	if (self->content)
	{
		free(self->content);
		self->content = NULL;
	}
	if (self->lines)
	{
		free(self->lines);
		self->lines = NULL;
	}
	if (self->tokens)
	{
		free(self->tokens);
		self->tokens = NULL;
	}
}


/**
 * main - entry point
 *
 * @ac: number of argument variables
 * @av: array of argument variables
 * @env: array of environment variables
 *
 * Return: alway (0)
 */
int main(int ac, char **av, char **env)
{
	int status;
	state *self;

	(void)ac;
	signal(SIGINT, SIG_IGN);
	self = init(av[0], env);
	interactive(self);
	status = self->_errno;
	deinit(self);
	return (status);
}
