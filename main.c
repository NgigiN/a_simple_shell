#include "main.h"



int main(int ac, char **argv)
{
	char *prompt = "cisfun $ ";
	char *cmdptr;
	char *cmd_cpy; /*copies the line*/
	size_t cmdlen = 0;
	ssize_t getline_result;
	const char *delim = " \n";//tokenizing delimiter
	int tkn_num = 0;
	char *token;
	int i;

	while (1)
	{
		//memset (cmdptr, '\0', 1024);
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

	/*memory allocation to hold the strings*/
	argv = malloc(sizeof(char *) * tkn_num);
	
	/*store each token in the argv array*/
	token = strtok(cmd_cpy, delim);

	for(i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	execmd(argv);
	for (i = 0; i < tkn_num - 1; i++)
{
    free(argv[i]);
}
free(argv);

	printf("%s", cmdptr);

	//free(cmdptr);
	free(cmd_cpy);
	}
	
	return (0);
}
