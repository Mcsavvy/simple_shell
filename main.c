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
	global->line = NULL;
	global->arguments = NULL;

	return (global);
}

/**
 * deinit - destroy the shell's state
 * 
 * @state: the shell's state
 * 
 * Return: nothing
 */
void deinit(state **global)
{
	if (!global || !global[0])
		return;
	free_list((*global)->env);
	free_list((*global)->aliases);
	free((*global)->line);
	free((*global)->arguments);
	free(*global);
	*global = NULL;
}

/**
 * cleanup - routine clean up that frees up memory in the state
 * @state: the state
 * Return: nothing
 */
void cleanup(state *self)
{

	if (!self)
		return;
	if (self->arguments)
	{
		free(self->arguments);
		self->arguments = NULL;
	}
	if (self->line)
	{
		free(self->line);
		self->line = NULL;
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
	self = init(av[0], env);
	interactive(&self);
	status = self->_errno;
	deinit(&self);
	return (status);
}
