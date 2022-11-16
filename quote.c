#include "shell.h"

/**
 * findquote - finds an unescaped quote in a string
 * @str: the string to search
 * @quote: the quote to search for (could be " or ')
 * Return: the index where the unescaped quote was found, or -1
 *		if the quote wasn't found.
 */
int findquote(char *str, char quote)
{
	char next, curr, c;
	int i;

	if (str == NULL || *str == '\0')
		return (-1);

	if (quote == '"')
		c = '"';
	else
		c = '\'';

	for (i = 0; str[i] != '\0'; i++)
	{
		curr = str[i];
		next = str[i + 1];

		if (curr == c)
			return (i);
		if (next == c && curr != '\\')
			return (i + 1);
		else if (next)
			i++;
	}
	return (-1);
}

/**
 * remove_quotes - remove quotes surrounding a string
 *
 * @string: target string
 *
 * Return: nothing
 */
char *remove_quotes(char *string)
{
	char c;
	int i;

	if (!string || !string[0])
		return (NULL);
	c = string[0];
	if (c != '"' && c != '\'')
		return (string);
	i = findquote(string + 1, c);
	if (c == -1)
		return (string);
	string[i + 1] = '\0';
	string[0] = '\0';
	return (&string[1]);
}

/**
 * should_quote - logically determine if a string
 * should be put in quotes
 *
 * @string: the target string
 *
 * Return: true(1) or false(0)
 */
bool should_quote(const char *string)
{
	char **arr;
	char *str;

	str = _strdup(string);
	arr = split(str, "\t ", 1, false);
	if (!arr)
	{
		free(str);
		return (true);
	}
	if (!arr[1])
	{
		free(arr), free(str);
		return (false);
	}
	free(arr), free(str);
	return (true);
}

/**
 * comment - Identifies a comment in command line
 *
 * @av: the command line arguments
 * Return: Nothing. It is void
 */
void comment(char *av[])
{
	int j;

	if (av == NULL)
		return;
	for (j = 0; av[j]; j++)
	{
		if (_strcmp(av[j], "#") == 0)
		{
			av[j] = NULL;
			break;
		}
	}
}
