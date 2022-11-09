#include "shell.h"
/**
 * shellexit - exits the shell
 *
 * @s: the argument to be compared
 * @arg: the exit value
 * Return: the exit value
 */
exit_status shellexit(state **self, char **arguments)
{
	exit_status status = 0;
	char *arg = arguments[0];
	char *error = NULL;

	if (arg == NULL)
	{
		deinit(self);
		exit(0);
	}
	if (checkatoi(arg) == false)
	{
		error = format(
			"%s: %d: exit: Illegal number: %s\n",
			(*self)->prog, (*self)->lineno, arg
		);
		write(STDERR_FILENO, error, strlen(error));
		free(error);
		return (2);
	}
	else
		status = atoi(arg);
	deinit(self);
	exit(status);
}
