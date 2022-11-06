#include "shell.h"

/**
 * execute - execute a program in a child process
 * @program: path of the program to execute
 * @args: command line arguments to pass to the program
 * Return: an integer
 */
int execute(const char *program, char *args[])
{
	pid_t pid;
	int status;

	(void)args;
	printf("process[%u]: creating child process\n", getpid());
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (pid == 0)
	{
		printf("process[%u]: executing %s\n", getpid(), program);
		exit(0);
	}
	else
	{
		wait(&status);
		printf(
			"process[%u]: child process exited with status %d\n",
			getpid(), status);
	}
	return (status);
}
