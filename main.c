#include "main.h"

/**
 * main - code entry point
 *
 * @ac: number of arguments
 * @argv: array of arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
	char *prompt = "cisfun $ ", *cmdptr, *token, *cmd_cpy, **args;
	size_t cmdlen = 0;
	ssize_t getline_result;
	int tkn_num = 0, i = 0;

	while (1)
	{
		printf("%s", prompt);
		getline_result = getline(&cmdptr, &cmdlen, stdin);
		if (getline_result == -1)
		{
			printf("Exit..\n");
			return (-1);
		}
		cmd_cpy = strdup(cmdptr);
		if (cmd_cpy == NULL)
		{
			perror("Error:");
			continue;
		}
		args = malloc((tkn_num + 1) * sizeof(char *));
		if (args == NULL)
		{
			perror("Error:");
			free(cmd_cpy);
			continue;
		}
		token = strtok(cmd_cpy, delim);
		while (token != NULL)
		{
			args[i] = strdup(token);
			if (args[i] == NULL)
			{
				perror("Error:");
				free(args);
				free(cmd_cpy);
				continue;
			}
			i++;
			token = strtok(NULL, delim);
		}
		args[i] = NULL;
		execmd(args);
		for (i = 0; i < tkn_num; i++)
		{
			free(args[i]);
		}
		free(args);
		free(cmd_cpy);
	}
	return (0);
>>>>>>> 5a577287079fb10d44a5a8afb5831df22c053fb3
}
