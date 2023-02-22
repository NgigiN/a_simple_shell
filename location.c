#include "main.h"

char *location(char *command)
{
    char *path_env, *path,*path_cmd,  *dir;
    size_t len;

    path_env = getenv("PATH");
    
    if (path_env == NULL) {
        // PATH environment variable not set
        return (NULL);
    }

    // Copy the PATH environment variable to a new string
    path = strdup(path_env);
    if (path == NULL) {
        // Failed to allocate memory for path string
        return (NULL);
    }

    dir = strtok(path, ":");
    while (dir != NULL) {
        // Construct the full path of the command in this directory
        len = strlen(dir) + 1 + strlen(command) + 1;
        path_cmd = malloc(len);
        if (path_cmd == NULL) {
            // Failed to allocate memory for path_cmd string
            free(path);
            return (NULL);
        }
        snprintf(path_cmd, len, "%s/%s", dir, command);

        // Check if the file exists and is executable
        if (access(path_cmd, X_OK) == 0) {
            // Found the command, return its absolute path
            free(path);
            return (path_cmd);
        }

        // The file was not found or is not executable, free path_cmd
        free(path_cmd);

        dir = strtok(NULL, ":");
    }

    // Command not found in any directory, free path and return NULL
    free(path);
    return (NULL);
}


