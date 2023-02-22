#include "main.h"

/**
 * location - finds the location from path
 *
 * @command: command that has been input
 * Return: NULL or the path
 */

char *location(char *command)
{
	char *path_env, *path, *path_cmd, *dir;
	size_t len;

	path_env = getenv("PATH");

	if (path_env == NULL)
	{
		return (NULL);
	}
	path = strdup(path_env);
	if (path == NULL)
	{
		return (NULL);
	}

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + 1 + strlen(command) + 1;
		path_cmd = malloc(len);
		if (path_cmd == NULL)
		{
			free(path);
			return (NULL);
		}
		snprintf(path_cmd, len, "%s/%s", dir, command);
		if (access(path_cmd, X_OK) == 0)
		{
			free(path);
			return (path_cmd);
		}
		free(path_cmd);

		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
