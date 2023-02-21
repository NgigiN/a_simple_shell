#include "main.h"

/*
 * execmd - executes a command found by location
 * @argv: passed command argument
 * Return: NULL
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
		return (0);
	}
	actual_cmd = location(cmd);

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
	}
	else if (pid == 0)
	{
		if (execve(actual_cmd, argv, NULL) == -1)
		{
			perror("Error:");
			return (1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: ");
			return (1);
		}
	}
	return (0);
}

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
            dir_len = strlen(path_tkn);
            file_path = malloc(cmd_len + dir_len + 2);
            if (file_path == NULL)
            {
                perror("Error:");
                return (NULL);
            }
            strcpy(file_path, path_tkn);
            strcat(file_path, "/");
            strcat(file_path, command);
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
        free(cpy_path);
    }
    return (NULL);
}
