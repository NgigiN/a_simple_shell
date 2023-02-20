#include "main.h"

/*
 * execmd - executes command found by location
 * @argv: passed command argument
 * Return: integer value
 */

int execmd(char **argv)
{
	char *cmd, *actual_cmd;
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		return (1);
	}
	else if (pid == 0)
	{
		cmd = argv[0];

		actual_cmd = location(cmd);

		if (execve(actual_cmd, argv, NULL) == -1)
		{
			perror("Error:");
			return (1);
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("Error: ");
				return (1);
			}
		}
	}
	return (0);
}
