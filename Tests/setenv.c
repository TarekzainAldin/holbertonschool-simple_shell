#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ; // Externally declared environment variable array

int _setenv(const char *name, const char *value, int overwrite) {
    // Check if name or value is NULL
    if (name == NULL || value == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to _setenv.\n");
        return -1;
    }

    // Check if the environment variable already exists
    char *env_var = getenv(name);
    if (env_var != NULL && !overwrite) {
        fprintf(stderr, "Error: Environment variable %s already exists.\n", name);
        return -1;
    }

    // Construct the new environment variable string
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t env_len = name_len + value_len + 2; // +2 for '=' and '\0'
    char *new_env = (char *)malloc(env_len);
    if (new_env == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return -1;
    }
    snprintf(new_env, env_len, "%s=%s", name, value);

    // Check if the environment variable already exists and overwrite is enabled
    if (env_var != NULL && overwrite) {
        // Find the existing environment variable and update its value
        for (char **env = environ; *env != NULL; env++) {
            if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=') {
                strcpy(*env, new_env);
                free(new_env);
                return 0;
            }
        }
    }

    // Append the new environment variable to the environment array
    int num_env = 0;
    for (char **env = environ; *env != NULL; env++) {
        num_env++;
    }
    char **new_environ = (char **)realloc(environ, (num_env + 2) * sizeof(char *));
    if (new_environ == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(new_env);
        return -1;
    }
    new_environ[num_env] = new_env;
    new_environ[num_env + 1] = NULL;
    environ = new_environ;

    return 0;
}
