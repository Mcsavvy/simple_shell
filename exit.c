#include "shell.h"
/**
 * shellexit - exits the shell
 *
 * @s: the argument to be compared
 * @arg: the exit value
 * Return: the exit value
 */
int shellexit(char *s, char *arg)
{
	int value;

	value = 0;

	if ((strcmp(s, "exit") != 0))
		return (-1);
	if (arg == NULL)
		return (value);
	if (checkatoi(s) == -1)
	{
		printf("Error: exit takes a numeric argument\n");
		return (0);
	}
	else
	{
		value = atoi(arg);
	}
	return (value);
}

