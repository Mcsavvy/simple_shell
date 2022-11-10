#include "shell.h"

/**
 * runbuiltin - execute a builtin command
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: true(1) if a command was found else false(0)
 */
bool runbuiltin(state *self, char **arguments)
{
	int i, status;
	char *command, **args;
	builtin builtins[] = {
		{"exit", shellexit},
		{"env", shellenv},
		{"setenv", shellsetenv},
		{"unsetenv", shellunsetenv},
		{"cd", shellcd},
		{ NULL, NULL }
	};

	command = arguments[0];
	args = arguments + 1;

	for (i = 0; builtins[i].name; i++)
	{
		if (!_strcmp(builtins[i].name, command))
		{
			status = builtins[i].handler(self, args);
			self->_errno = status;
			return (true);
		}
	}
	return (false);
}

/**
 * runprogram - execute a program
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: true(1) if the program was found else false(0)
 */
bool runprogram(state *self, char **arguments)
{
	char *path, *error, **env;
	bool free_path = false;
	int status, i;

	path = arguments[0];

	if (!ispath(path))
	{
		path = findcmd(path,
			set_default(&(self->env), "PATH", "")->val);
		if (!path)
			return (false);
		free_path = true;
	}
	else if (access(path, F_OK) == -1)
		return (false);
	if (access(path, X_OK) == -1)
	{
		error = format(
			"%s: %d: %s: Permission denied\n",
			self->prog, self->lineno, arguments[0]);
		printerr(error);
		free(error);
		self->_errno = 126;
	}
	else
	{
		env = to_strarr(self->env);
		status = execute(path, arguments, env);
		for (i = 0; env[i]; i++)
			free(env[i]);
		free(env);
		self->_errno = status;
	}
	if (free_path)
		free(path);
	return (true);
}

/**
 * interactive - runs the shell in interactive mode
 *
 * @self: the shell's state
 *
 * Return: always 0
 */
int interactive(state *self)
{
	char *error;
	bool found;

	for (; true; self->lineno++)
	{
		found = false;
		printout("($) ");
		self->line = getLine();
		if (!self->line)
		{
			printout("\n");
			break;
		}
		self->arguments = tokenizeLine(self->line);
		if (!self->arguments)
		{
			cleanup(self);
			continue;
		}
		found = runbuiltin(self, self->arguments);
		if (!found)
			found = runprogram(self, self->arguments);
		if (!found)
		{
			error = format(
				"%s: %d: %s: not found\n",
				self->prog, self->lineno, self->arguments[0]
			);
			printerr(error);
			free(error);
			self->_errno = EKEYEXPIRED;
		}
		cleanup(self);
	}
	return (0);
}

/**
 * execute - execute a program in a child process
 * @program: path of the program to execute
 * @args: command line arguments to pass to the program
 * @env: the environme
 * Return: the exit status of the child process
 */
int execute(const char *program, char *args[], char *env[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (pid == 0)
	{
		execve(program, args, env);
		exit(errno);
	}
	else
	{
		wait(&status);
		if (status != 0)
			return (2);
	}
	return (status);
}
