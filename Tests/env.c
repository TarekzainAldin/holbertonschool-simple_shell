#include <stdio.h>
#include <stdlib.h>

extern char **environ; // Declare the global variable

int main(void) {
    char **env_ptr = environ; // Pointer to the environment variables

    // Loop through each environment variable and print it
    while (*env_ptr != NULL) {
        printf("%s\n", *env_ptr);
        env_ptr++;
    }

    return 0;
}
