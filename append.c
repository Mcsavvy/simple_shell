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
int appendStr(char ***arr, size_t *size, char *str, int index)
{
	size_t s;
	char **a;

	s = *size;
	a = *arr;

	if (!(arr && *arr))
		return (0);
	while (s <= (unsigned int)index)
	{
		s *= 2;
		a = realloc(a, s * sizeof(char *));
		if (!a)
			return (0);
	}
	(a)[index] = str;
	*arr = a;
	*size = s;
	return (1);
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
int appendChar(char **string, size_t *size, char chr, int index)
{
	size_t s;
	char *buf;

	if (!(string && *string))
		return (0);

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
			return (0);
	}
	buf[index] = chr;
	*string = buf;
	if (size != NULL)
		*size = s;
	return (1);
}
