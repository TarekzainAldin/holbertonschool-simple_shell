#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define PATH_MAX 4096

void check_command(char *command) {
    char *argv[2] = {command, NULL};
    if (execvp(command, argv) == -1) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            char path[PATH_MAX + 1];
            snprintf(path, sizeof(path), "%s/%s", cwd, command);
            if (execvp(path, argv) == -1) {
                printf("%s: FILE DOESN'T EXIST\n", command);
            }
        } else {
            printf("getcwd() error\n");
        }
    } else {
        printf("%s: FOUND THE FILE\n", command);
    }
}

void signal_handler(int signal) {
    printf("\n");
    exit(EXIT_SUCCESS);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *token;


    signal(SIGINT, signal_handler);

    while (1) {
        write(STDOUT_FILENO, "File Checker\n", 14);
        if (getline(&buffer, &buffer_size, stdin) == -1) {
            printf("\n");
            break;
        }
        token = strtok(buffer, " \t\n");
        if (strcmp(token, "EOD") == 0) {
            break;
			        } else if (strcmp(token, "which") == 0) {
            token = strtok(NULL, "\t\n");
            while (token) {
                check_command(token);
                token = strtok(NULL," \t\n");
            }
        } else {
            write(STDOUT_FILENO, "COMMAND DOESN'T EXIST\n", 23);
        }
    }

    free(buffer);
    return 0;
}
