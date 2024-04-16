#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ; // Externally declared environment variable array

int _unsetenv(const char *name) {
    // Check if name is NULL
    if (name == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to _unsetenv.\n");
        return -1;
    }

    // Find the environment variable to remove
    int found = 0;
    int num_env = 0;
    for (char **env = environ; *env != NULL; env++) {
        if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=') {
            // Shift subsequent environment variables to remove the found one
            found = 1;
        } else if (found) {
            // Shift subsequent environment variables to fill the gap
            environ[num_env] = *env;
            num_env++;
        } else {
            num_env++;
        }
    }

    // If the variable was found, remove it from the environment array
    if (found) {
        // Free the memory occupied by the last environment variable
        free(environ[num_env]);
        environ[num_env] = NULL;
    } else {
        fprintf(stderr, "Error: Environment variable %s not found.\n", name);
        return -1;
    }

    return 0;
}
