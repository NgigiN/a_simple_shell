#include "main.h"

/**
 * execmd - Executes commnands
 *
 * @argv: array of arguments
 *
 * Return: 0 for success
 */

int execmd(char **argv)
{
	char *cmd, *actual_cmd;
	pid_t pid;
	int status;

	cmd = argv[0];
	if (strcmp(cmd, "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(cmd, "pwd") == 0)
	{
		printf("%s\n", getcwd(currentDirectory, 1024));
	}
	else
	{
		actual_cmd = location(cmd);

		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
		}
		else if (pid == 0)
		{
			if (execv(actual_cmd, argv) == -1)
			{
				perror("Error:");
				return (1);
			}
		}

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: ");
			return (1);
		}

		free(actual_cmd);
	}
	return (0);
}
