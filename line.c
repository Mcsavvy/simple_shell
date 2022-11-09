#include "shell.h"


/**
 * getLine - read a line from the stdin
 * Return: the line read from stdin, or NULL if EOF was encountered
 *
 * NOTE: the newline would not be include in the returned string
 */
char *getLine(void)
{
	int index;
	size_t bufsize;
	char *buffer;
	int c;

	bufsize = 2;
	buffer = malloc(bufsize);
	index = 0;

	if (buffer == NULL)
	{
		perror("Error");
		exit(errno);
	}
	c = fgetc(stdin);

	while (c != EOF)
	{
		if (c == '\n')
		{
			appendChar(&buffer, &bufsize, '\0', index);
			break;
		}
		appendChar(&buffer, &bufsize, c, index);
		index++;
		c = fgetc(stdin);
	}
	if (c == EOF)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}


/**
 * tokenizeLine - split a line into separate words
 * @line: a malloced string to tokenize
 * Return: a null-terminated array of strings
 */
char **tokenizeLine(char *line)
{
	char **array, c, temp;
	size_t arr_size;
	int arr_index, line_index, next_quote_index;

	if (!(line && *line))
		return (NULL);

	line_index = arr_index = 0; /* line index */
	arr_size = 4;
	array = malloc(arr_size * sizeof(char *));
	temp = '\0';

	for (line_index = 0; line && line[line_index]; line_index++)
	{
		c = line[line_index];

		if ((c == '\'' || c == '"') && temp != '\\')
		{
			if (temp == '\0')
				appendStr(&array, &arr_size, &line[line_index], arr_index++);
			next_quote_index = findquote(&line[line_index + 1], c);
			printf("next quote index: %d\n", next_quote_index);
			if (next_quote_index == -1)
			{}
			else
				line_index += next_quote_index;
		}
		else if (c == ' ' || c == '\t')
			line[line_index] = '\0';
		else
			if (temp == '\0')
				appendStr(&array, &arr_size, &line[line_index], arr_index++);
		temp = line[line_index];
	}
	appendStr(&array, &arr_size, NULL, arr_index);
	return (array);
}
