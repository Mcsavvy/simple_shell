#include "shell.h"
#include "strings.h"
/**
 * _putchar - prints a char
 *
 * @c: the char to be printed
 * Return: 1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _strlen - it swaps the values of two integers
 * Description:'A function'
 * @s: the string to be checked
 * Return: The lenght of the string
 */
int _strlen(char *s)
{
	int i, lenght;

	lenght = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		lenght++;
	}
	return (lenght);
}
/**
 * _puts - it prints out a string and a new line
 * Description:'A function'
 * @str: the string to be checked
 * Return: Nothing
 */
void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
	_putchar('\n');
}
/**
 * _strcmp - compares two strings
 * @s1: the string to be compared
 * @s2: the second string to be compared
 * Description:'A function'
 * Return: j if successful
 */
int _strcmp(char *s1, char *s2)
{
	int i, j;

	i = 0;
	j = 0;

	while (j == 0)
	{
		if ((*(s1 + i) == '\0') && (*(s2 + i) == '\0'))
			break;
		j = *(s1 + i) - *(s2 + i);
		i++;
	}
	return (j);
}
/**
 * *_strcat - it concatenates one string onto another
 * Description:'A function that replicates strncat'
 * @src: the string to be appended
 * @dest: the destination
 * Return: 'dest' if successful
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;

	while (dest[i] != '\0')
		i++;
	j = 0;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
