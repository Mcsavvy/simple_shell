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
	state *self = malloc(sizeof(state));

	self->lineno = 1;
	self->aliases = NULL;
	self->env = from_strarr(env);
	self->pid = getpid();
	self->prog = prog;
	self->_errno = 0;
	self->content = NULL;
	self->lines = NULL;
	self->tokens = NULL;
	self->bufsize = 3;
	self->buf = malloc(NCHARS(self->bufsize));
	self->parts = NULL;
	self->fd = STDIN_FILENO;

	return (self);
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
	if (self->parts)
		free(self->parts);
	if (self->fd)
		close(self->fd);
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
	if (self->parts)
	{
		free(self->parts);
		self->parts = NULL;
	}
	if (self->tokens)
	{
		free(self->tokens);
		self->tokens = NULL;
	}
}

/**
 * open_file - used by the main function to open a file
 *
 * @self: the shell's state
 * @path: the path of the file
 *
 * Return: the open file descriptor
 */
int open_file(state *self, char *path)
{
	int fd;

	if (access(path, F_OK) == -1)
	{
		fprinterr(format(
			"%s: %d: cannot open %s: No such file\n",
			self->prog, 0, path));
		deinit(self);
		exit(2);
	}
	if (access(path, R_OK) == -1)
	{
		{
			fprinterr(format(
				"%s: %d: cannot open %s: Permission denied\n",
				self->prog, 0, path));
			deinit(self);
			exit(2);
		}
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(self->prog);
		deinit(self);
		exit(EXIT_FAILURE);
	}
	self->fd = fd;
	return (fd);
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
	int fd;

	(void)ac;
	fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	self = init(av[0], env);

	if (av[1])
		fd = open_file(self, av[1]);
	if (isatty(fd))
		interactive(self);
	else
		non_interactive(self, fd);
	status = self->_errno;
	deinit(self);
	return (status);
}
