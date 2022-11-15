#include "shell.h"

/**
 * get_equal_sign - find the '=' character in a string
 *
 * @s: the string to search
 *
 * Return: the index where the character was found.
 * 0 is returned if the character was not found
 */
int get_equal_sign(const char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] == '=')
			return (i);
	return (0);
}

char *find_alias(node *alias, char *aliasname)
{
	node *temp;

	temp = alias;
	while (temp != NULL)
	{
		if (_strcmp(temp->var, aliasname) == 0)
			return (temp->val);
		temp = temp->next;
	}
	return (NULL);
}
/**
 * shellexit - exits the shell
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: the exit value
 */
exit_status shellalias(state *self, char **arguments)
{
	int eq, i, status;
	char *token;
	node *alias;

	status = 0;

	if (!arguments[0])
	{
		print_list(self->aliases);
		return (0);
	}
	for (i = 0; arguments[i]; i++)
	{
		token = arguments[i];
		eq = get_equal_sign(token);
		if (!eq)
		{
			alias = get_node(self->aliases, token);
			if (!alias)
			{
				fprinterr(format("alias: %s not found\n", token));
				status = 1;
			}
			else
			{
				fprintout(format("%s=%s\n",
					alias->var, (!alias->val[0]) ? "''" : alias->val));
			}
		}
		else
		{
			token[eq] = '\0';
			set_node(&(self->aliases), token, &token[eq + 1]);
		}
	}
	return (status);
}
/**
 * count_str - count the number of strings in a string array
 *
 * @stri: the string to e counted
 * Return: the number of counted strings
 */
int count_str(char **stri)
{
	int i;

	i = 0;
	if (stri == NULL)
		return(i);
	for (i = 0; stri[i] != NULL; i++)
		;
	return (i);
}
/**
 * runalias - runs an alias
 *
 * @state: the shell's state
 * @line: the line to run
 * Return: true if it works or false if it fails
 */
bool runalias(state *self, char *line)
{

	int i, j, count;
	char **arguments, **tokens, *aliasi;
	bool status;
	size_t size, index;

	tokens = split(line, "\t ", 0);
	size = count_str(tokens);

	aliasi = find_alias(self->aliases, *tokens);
	if (!aliasi)
		return (false);
/*
	arguments = split(aliasi, "\t ", 0);
	for (i = 0;  arguments[i] != NULL; i++)
	{
		;
	}
	for (j = 1; tokens[j] != NULL; j++)
	{
		index = count_str(arguments);
		size = index + 1;
		appendStr(&arguments, &size, tokens[j], index);
		i++;
	}
	appendStr(&arguments, &size, NULL, index);
	self->tokens = arguments;
	for (count = 0; arguments[count]; count++)
	{
		arguments[count] = replace(self, arguments[count]);
	}
	comment(arguments);
	status = runbuiltin(self, arguments);
	if (status == false)
		status = runprogram(self, arguments);
	if (status == false)
	{
		 fprinterr(format("%s: %d: %s: not found\n",
			self->prog, self->lineno, arguments[0]));
		self->_errno = EKEYEXPIRED;
	}
	free(self->tokens);
	self->tokens = NULL;
*/	return (true);
}

