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
