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
 * skipTrailingWhiteSpace - skips whitespace during tokenization
 *
 * @string: the string being parsed
 * @index: a pointer to the index position in the string
 *
 * Return: 1 if whitespace was found and skipped, else 0
 */
int skipTrailingWhiteSpace(char *string, int *index)
{
	if (string[*index] != ' ' && string[*index] != '\t')
		return (0);
	while (string[*index] == ' ' || string[*index] == '\t')
		*index = *index + 1;
	return (1);
}

/**
 * tokenizeLine - split a line into separate words
 * @line: a malloced string to tokenize
 * Return: a null-terminated array of strings
 */
char **tokenizeLine(char *line)
{
	char **array, *buffer, c;
	size_t arr_size, buf_size;
	int arr_index, buf_index, index;

	if (!(line && *line))
		return (NULL);

	index = arr_index = 0; /* line index */
	arr_size = 4;
	array = malloc(arr_size * sizeof(char *));

	while (line && line[index])
	{
		buf_size = 16;
		buf_index = 0;
		buffer = malloc(buf_size * sizeof(char));

		for (; line[index]; index++)
		{
			c = line[index];
			if (skipTrailingWhiteSpace(line, &index))
				break;
			if (parsequote(line, &index, &buffer, &buf_size, &buf_index))
				break;
			appendChar(&buffer, &buf_size, c, buf_index++);
		}
		if (buf_index == 0)
		{
			free(buffer);
			continue;
		}
		appendChar(&buffer, &buf_size, '\0', buf_index++);
		appendStr(&array, &arr_size, buffer, arr_index++);
	}
	appendStr(&array, &arr_size, NULL, arr_index);
	return (array);
}
