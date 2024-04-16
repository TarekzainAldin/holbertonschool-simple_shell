#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name) {
    if (name == NULL || *name == '\0') {
        return NULL;
    }

    extern char **environ;
    char **env_ptr = environ;
    size_t name_len = strlen(name);

    while (*env_ptr != NULL) {
        if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=') {
            return *env_ptr + name_len + 1; // Return the value part of the environment variable
        }
        env_ptr++;
    }

    return NULL; // Variable not found
}
