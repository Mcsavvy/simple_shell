#include "shell.h"
/**
 * _env - prints out all env variables
 *
 * @env: the environment
 * Return: 0 if success
 */
int _env(char *env[])
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		_puts(env[i]);
	return (0);

}
/**
 * token - crate an array of strings
 *
 * @c: the string
 * Return: the string
 */
char *token(char *c)
{
	char *token;

	int i;

	for (i = 0; c[i] != '='; i++)
		token[i] = c[i];
	return (token);
}
/**
 * _setenv - sets a new environmental variable
 *
 * @name: the name of the variable
 * @value: its value
 * @env: the environment
 * Return: 0
 */
int _setenv(char *name, char *value, char *env[])
{
	char *buffer;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		buffer = token(env[i]);
		if (_strcmp(buffer, name) == 0)
		{
			env[i] = _strcat(name, "=");
			env[i] = _strcat(env[i], "value");
			return (0);
		}
	}
	env[i] = _strcat(name, "=");
	env[i] = _strcat(env[i], "value");
	i++;
	env[i] = NULL;
	return (0);

}
/**
 * _unsetenv - deletes a variable
 *
 * @name: the name of the variable
 * @env: the environment
 * Return: 0 if successful
 */
int _unsetenv(char *name, char *env[])
{
	char *buffer;
	char *temp;
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		buffer = token(env[i]);
		if (_strcmp(buffer, name) == 0)
			break;
	}
	while (env[i] != NULL)
	{
		temp = env[i + 1];
		env[i] = temp;
	}
	return (0);

}
