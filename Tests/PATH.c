#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_PATH_directories() {
    char *path = getenv("PATH"); // Get the PATH environment variable
    if (path != NULL) {
        char *token = strtok(path, ":"); // Tokenize the PATH using ":" as delimiter
        while (token != NULL) {
            printf("%s\n", token); // Print each directory
            token = strtok(NULL, ":"); // Move to the next token
        }
    }
}
