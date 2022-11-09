#include "shell.h"

/**
 * findenv - returns the value of an environment variable
 *
 * @env: an array of all environment variables
 * @name: name of the variable to search for
 *
 * Return: the value of the environment variable if found, or
 * NULL if it couldn't be found
 */
char *findenv(char *env[], const char *name)
{
	char *key, *val, *var;
	int i;

	for (i = 0; env[i]; i++)
	{
		var = strdup(env[i]);
		key = strtok(var, "=");
		if (!strcmp(key, name))
		{
			val = strdup(strtok(NULL, ""));
			free(var);
			return (val);
		}
		free(var);
	}
	return (NULL);
}

/**
 * findfile - searches through a directory for a file
 *
 * @dir: the directory to search
 * @filename: name of the file to search for
 *
 * Return: a pointer to the file if found, else NULL
 */
struct dirent *findfile(DIR *dir, const char *filename)
{
	struct dirent *file;

	errno = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		if (strcmp(filename, file->d_name) == 0)
			break;
		file = readdir(dir);
	}
	return (file);
}

/**
 * joinpath - join two paths together using /
 *
 * @base: the base path
 * @child: the child path
 *
 * Return: A new malloced string where base and child are stringed
 * together like this: base/child
 *
 * NOTE: if one of the strings is NULL, it returns NULL
 */
char *joinpath(const char *base, const char *child)
{
	char *newpath;
	int baselen, childlen, i, index;
	bool has_sep;

	baselen = childlen = index = 0;
	has_sep = false;

	if (!(base && child))
		return (NULL);

	while (base[baselen] != '\0')
		baselen++;
	while (child[childlen] != '\0')
		childlen++;

	if (base[baselen - 1] == '/' || child[0] == '/')
		has_sep = true;

	newpath = malloc(
		/* create space for a nullbyte and space for the / */
		baselen + childlen + 1 + has_sep ? 0 : 1
	);

	for (i = 0; i < baselen; i++)
	{
		newpath[index] = base[i];
		index++;
	}
	if (!has_sep)
	{
		newpath[index] = '/';
		index++;
	}
	for (i = 0; i < childlen; i++)
	{
		newpath[index] = child[i];
		index++;
	}
	newpath[index] = '\0';
	return (newpath);
}

/**
 * findcmd - searches through $PATH to find a command
 *
 * @command: name of the command
 * @PATH: a string containing directories in which to search
 * for the command. The directories should be delimited by :
 *
 * Return: a pointer to the path of the command if found, otherwise NULL
 */
char *findcmd(const char *command, const char *PATH)
{
	char *dirname, *PATHCPY, *cmd;
	DIR *dir;
	struct dirent *node;

	cmd = NULL;
	PATHCPY = strdup(PATH);
	dirname = strtok(PATHCPY, ":");

	while (dirname)
	{
		dir = opendir(dirname);
		if (!dir)
		{
			dirname = strtok(NULL, ":");
			continue;
		}
		node = findfile(dir, command);
		closedir(dir);
		if (node)
		{
			cmd = joinpath(dirname, node->d_name);
			break;
		}
		dirname = strtok(NULL, ":");
	}
	free(PATHCPY);
	return (cmd);
}
