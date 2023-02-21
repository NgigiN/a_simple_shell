#include "main.h"

int main(int ac, char **av)
{
    char *prompt = "cisfun$ ";
    char *cmdptr;
    char *cmd_cpy;
    size_t cmdlen = 0;
    ssize_t getline_result;
    const char *delim = " \n";
    int tkn_num = 0;
    char *token;
    int i;

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

        char **cmd_args = malloc(sizeof(char *) * tkn_num);

        token = strtok(cmd_cpy, delim);

        for (i = 0; token != NULL; i++)
        {
            cmd_args[i] = malloc(sizeof(char) * strlen(token));
            strcpy(cmd_args[i], token);

            token = strtok(NULL, delim);
        }

        cmd_args[i] = NULL;

        execmd(cmd_args);

        for (i = 0; i < tkn_num - 1; i++)
        {
            free(cmd_args[i]);
        }

        free(cmd_args);
        free(cmd_cpy);
        free(cmdptr);
    }
    
    return (0);
}
