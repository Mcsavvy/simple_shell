#include "shell.h"

/**
 * appendStr - append a string to an array of strings
 *
 * @arr: a pointer to a malloced array of strings
 * @size: a pointer to an integer holding the size of the array
 * @str: the new string to append to the array
 * @index: the index at which to insert the string
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool appendStr(char ***arr, size_t *size, char *str, int index)
{
	size_t s;
	char **a;

	s = *size;
	a = *arr;

	if (!(arr && *arr))
		return (false);
	while (s <= (unsigned int)index)
	{
		s *= 2;
		a = realloc(a, s * sizeof(char *));
		if (!a)
			return (false);
	}
	(a)[index] = str;
	*arr = a;
	*size = s;
	return (true);
}

/**
 * appendChar - appends a character to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @chr: the character to add to the string
 * @index: the index at which to insert the character
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool appendChar(char **string, size_t *size, char chr, int index)
{
	size_t s;
	char *buf;

	if (!(string && *string))
		return (false);

	if (size == NULL)
		for (s = 0; (*string)[s]; s++)
			continue;
	else
		s = *size;
	buf = *string;

	while (s <= (unsigned int)index)
	{
		s *= 2;
		buf = realloc(buf, s);
		if (!buf)
			return (false);
	}
	buf[index] = chr;
	*string = buf;
	if (size != NULL)
		*size = s;
	return (true);
}

/**
 * appendInt - appends an integer to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @num: the integer to insert
 * @index: the index at which to insert the character
 *
 * Return: number of digits appended.
 *		-1 is return if appendChar failed.
 */
int appendInt(char **string, size_t *size, int num, int index)
{
	int len = 0, temp;

	if (num < 0)
	{
		if (!appendChar(string, size, '-', index + len))
			return (-1);
		num *= -1;
		len++;
	}
	if (num == 0)
		return (0);
	temp = appendInt(string, size, num / 10, index + len);
	if (temp == -1)
		return (-1);
	len += temp;
	if (!appendChar(string, size, (num % 10) + '0', index + len))
		return (-1);
	return (++len);
}
