#include "shell.h"

/**
 * main - entry point
 *
 * @ac: number of argument variables
 * @av: array of argument variables
 * @env: array of environment variables
 *
 * Return: alway (0)
 */
int main(int ac, char **av, char **env)
{
	char *line, **tokens, *command, **arguments, *program, *PATH;
	int i, t, quit;

	PATH = findenv(env, "PATH");
	quit = 0;
	(void)ac;
	for (i = 1; 1; i++)
	{
		printf("($) ");
		line = getLine();
		if (!line)
		{
			printf("\n");
			break;
		}
		tokens = tokenizeLine(line);
		if (!tokens)
			continue;
		command = tokens[0];
		arguments = &tokens[1];
		if (!strcmp(command, "exit"))
			quit = 1;
		else
		{
			program = findcmd(command, PATH);
			if (!program)
				printf("%s: %d: %s: not found\n", av[0], i, command);
			else
				execute(program, arguments);
		}
		for (t = 0; tokens[t]; t++)
			free(tokens[t]);
		free(tokens);
		free(line);
		free(program);
		if (quit)
			break;
	}
	free(PATH);
	return (0);
}
