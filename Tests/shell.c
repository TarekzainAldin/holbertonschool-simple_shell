#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100

void signal_handler(int signal) {
    // Ignorer le signal
    printf("\n");
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    // Gestion du signal d'interruption (Ctrl+C)
    signal(SIGINT, signal_handler);

    while (1) {
        // Affiche le prompt
        printf("$ ");

        // Lit la commande entrée par l'utilisateur
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // Si la lecture échoue (EOF), quitte le shell
            break;
        }

        // Supprime le saut de ligne ajouté par fgets
        command[strcspn(command, "\n")] = '\0';

        // Quitte le shell si la commande est "exit"
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Exécute la commande
        system(command);
    }

    return 0;
}
