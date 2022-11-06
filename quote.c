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
 * parsequote - group characters within quotes as one token
 * during tokenization.
 *
 * @string: the string that is being parse
 * @index: a pointer to the index position of the string
 * @buffer: a pointer to a buffer where characters would be put
 * @buf_size: a pointer to a variable holding the size of the buffer
 * @buf_index: a pointer to the index position of the buffer
 *
 * Return: 1 if group was found and parsed, else 0
 */
int parsequote(
	char *string,
	int *index,
	char **buffer,
	size_t *buf_size,
	int *buf_index)
{
	int i, found, bi;
	char c, p;

	i = *index;
	bi = *buf_index;
	c = string[i];
	p = '\0';

	if (i > 0)
		p = string[i - 1];
	if ((c == '\'' || c == '"') && p != '\\')
	{
		found = findquote(&string[i + 1], c);
		if (found == -1)
		{
			return (0);
		}
		found += i + 1;
		while (found >= i)
		{
			appendChar(buffer, buf_size, string[i++], bi++);
		}
		*index = i;
		*buf_index = bi;
		printf("next char %c\n", string[i]);
		return (1);
	}
	return (0);
}
