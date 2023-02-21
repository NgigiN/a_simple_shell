#include "main.h"

char *location(char *command)
{
    char *path, *cpy_path, *path_tkn, *file_path;
    int cmd_len, dir_len;

    path = getenv("PATH");
    if (path)
    {
        cpy_path = strdup(path);
        cmd_len = strlen(command);
        path_tkn = strtok(cpy_path, ":");
        while (path_tkn != NULL)
        {
            
            file_path = malloc(cmd_len + dir_len + 2);
            strcpy(file_path, path_tkn);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");
            if (access(file_path, X_OK) == 0)
            {
                free(cpy_path);
                return (file_path);
            }
            else
            {
                free(file_path);
                path_tkn = strtok(NULL, ":");
            }
        }
        free(file_path);
    }
    return (NULL);
}


