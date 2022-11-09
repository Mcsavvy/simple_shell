#include "shell.h"
#include <stdarg.h>


char *format(const char *fmt, ...)
{
	char *buffer, chr, nxt, *s;
	size_t size;
	int buf_index, index, i;
	va_list args;

	if (!fmt || !fmt[0])
		return (NULL);

	size = 4;
	buffer = malloc(size * sizeof(char));
	index = buf_index = 0;
	chr = fmt[index++];
	nxt = fmt[index];
	va_start(args, fmt);

	for (index = 0; fmt[index]; index++)
	{
		chr = fmt[index];
		nxt = fmt[index + 1];
	
		if (chr == '%')
		{
			if (nxt == 'd')
			{
				buf_index += appendInt(&buffer, &size, va_arg(args, int), buf_index);
			}
			else if (nxt == 's')
			{
				s = va_arg(args, char *);
				for (i = 0; s[i]; i++)
					appendChar(&buffer, &size, s[i], buf_index++);
			}
			index++;
		}
		else
			appendChar(&buffer, &size, chr, buf_index++);
	}
	va_end(args);
	appendChar(&buffer, &size, '\0', buf_index);
	return (buffer);
}