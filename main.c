#include "main.h"



int main(int ac, char **argv)
{
    char *prompt = "cisfun $ ";
    char *cmdptr, *token;
    char *cmd_cpy; /*copies the line*/
    size_t cmdlen = 0;
    ssize_t getline_result;
    const char *delim = " \n";//tokenizing delimiter
    int tkn_num = 0;
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

        cmd_cpy = strdup(cmdptr);
        if (cmd_cpy == NULL) {
            perror("Error:");
            continue;
        }

        // Tokenize the input string
        char **args = malloc((tkn_num + 1) * sizeof(char *));
        if (args == NULL) {
            perror("Error:");
            free(cmd_cpy);
            continue;
        }

        i = 0;
        token = strtok(cmd_cpy, delim);
        while (token != NULL) {
            args[i] = strdup(token);
            if (args[i] == NULL) {
                perror("Error:");
                free(args);
                free(cmd_cpy);
                continue;
            }
            i++;
            token = strtok(NULL, delim);
        }
        args[i] = NULL;

        // Execute the command
        execmd(args);

        // Free the memory allocated for the arguments
        for (i = 0; i < tkn_num; i++) {
            free(args[i]);
        }
        free(args);
        free(cmd_cpy);
    }

    return 0;
}
