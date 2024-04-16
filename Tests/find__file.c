#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 4096
#define MAX_FILENAME_LENGTH 256

void search_in_path(const char *filename) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        exit(EXIT_FAILURE);
    }

    char path[MAX_PATH_LENGTH];
    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, filename);
        if (access(path, F_OK) == 0) {
            printf("%s\n", path);
            free(path_copy);
            return;
        }
        dir = strtok(NULL, ":");
    }

    printf("File '%s' not found in PATH.\n", filename);
    free(path_copy);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        search_in_path(argv[i]);
    }

    return EXIT_SUCCESS;
}
