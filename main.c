#include "main.h"
/**
 * main - entry point of our shell
 * @ac: number of arguments
 * @argv: the arguments
 * Return: integer value
 */
int main(int ac, char **argv)
{
	char *prompt = "BabyBoo $ ", *token, *cmdptr, *cmd_cpy;
	size_t cmdlen = 0;
	ssize_t getline_result;
	const char *delim = " \n";/*tokenizing delimiter*/
	int tkn_num = 0, i;

	while (1)
	{
	printf("%s", prompt);
	getline_result = getline(&cmdptr, &cmdlen, stdin);
	if (getline_result == -1)
	{
		printf("Exit..\n");
		return (-1);
	}
	cmd_cpy = malloc(sizeof(char) * getline_result);
	if (cmd_cpy == NULL)
	{
		perror("malloc error");
		return (-1);
	}
	strcpy(cmd_cpy, cmdptr);
	token = strtok(cmd_cpy, delim);
	while (token != NULL)
	{
		tkn_num++;
		token = strtok(NULL, delim);
	}
	tkn_num++;
	argv = malloc(sizeof(char *) * tkn_num);
	token = strtok(cmd_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	execmd(argv);
	free(cmd_cpy);
	}
	return (0);
}
