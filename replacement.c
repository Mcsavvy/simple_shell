#include "shell.h"

char *replace(state *self, char *var)
{
	int len;
	node *n;

	if (var[0] != '$')
		return (var);

	if (!_strcmp(var, "$$"))
	{
		len = appendInt(&(self->buf), &(self->bufsize), self->pid, 0);
		appendChar(&(self->buf), &(self->bufsize), '\0', len);
		return (self->buf);
	}
	else if (!_strcmp(var, "$?"))
	{
		len = appendInt(&(self->buf), &(self->bufsize), self->_errno, 0);
		appendChar(&(self->buf), &(self->bufsize), '\0', len);
		return (self->buf);
	}
	n = get_node(self->env, var + 1);
	if (!n)
		return ("");
	return (n->val);
}