#include "shell.h"

bool runbuiltin(state **global, char **arguments)
{
	int i, status;
	state *self;
	char *command, **args;
	builtin builtins[] = {
		{ "exit", shellexit },
		{ NULL, NULL }
	};

	self = *global;
	command = arguments[0];
	args = arguments + 1;

	for (i = 0; builtins[i].name; i++)
	{
		if (!_strcmp(builtins[i].name, command))
		{
			status = builtins[i].handler(global, args);
			self->_errno = status;
			return (true);
		}
	}
	return (false);
}


int interactive(state **global)
{
	char *error;
	bool found;
	state *self = *global;


	for (; true; self->lineno++)
	{
		found = false;
		write(STDOUT_FILENO, "($) ", 4);
		self->line = getLine();
		if (!self->line)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		self->arguments = tokenizeLine(self->line);
		if (!self->arguments)
		{
			cleanup(self);
			continue;
		}
		found = runbuiltin(global, self->arguments);
		if (!found)
		{
			error = format(
				"%s: %d: %s: not found",
				self->prog, self->lineno, self->arguments[0]
			);
			write(STDERR_FILENO, error, _strlen(error));
			free(error);
			write(STDOUT_FILENO, "\n", 1);
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
 * Return: an integer
 */
int execute(const char *program, char *args[])
{
	pid_t pid;
	int status;

	(void)args;
	printf("process[%u]: creating child process\n", getpid());
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (pid == 0)
	{
		printf("process[%u]: executing %s\n", getpid(), program);
		exit(0);
	}
	else
	{
		wait(&status);
		printf(
			"process[%u]: child process exited with status %d\n",
			getpid(), status);
	}
	return (status);
}
