#include "shell.h"
/**
 * tokenizefile - split a line into separate lines
 * @line: a malloced string to tokenize
 * Return: a null-terminated array of strings
 */
char **tokenizefile(char *line)
{
	char **array, c, temp;
	size_t arr_size;
	int arr_index, line_index;

	if (!(line && *line))
		return (NULL);

	line_index = arr_index = 0; /* line index */
	arr_size = 4;
	array = malloc(arr_size * sizeof(char *));
	temp = '\0';

	for (line_index = 0; line && line[line_index]; line_index++)
	{
		c = line[line_index];
		if (c == '\n')
			line[line_index] = '\0';
		else
			if (temp == '\0')
				appendStr(&array, &arr_size, &line[line_index], arr_index++);
		temp = line[line_index];
	}
	if (arr_index)
		appendStr(&array, &arr_size, NULL, arr_index);
	else
	{
		free(array);
		array = NULL;
	}
	return (array);
}
/**
 * tokenizefiles - Splits a file into seperate words
 * @s: the file to be split
 *
 * Return: an array of array of words pointing to each line
 */
char ***tokenizefiles(char *s)
{
	char **files;
	char ***tokenizedfiles;
	int i;

	if (s == NULL)
		return (NULL);
	i = 0;
	files = tokenizefile(s);
	while (files[i] != NULL)
	{
		tokenizedfiles[i] = tokenizeLine(files[i]);
		i++;
	}
	return (tokenizedfiles);

}
