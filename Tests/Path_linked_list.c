#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the linked list
typedef struct PathNode {
    char directory[256];
    struct PathNode *next;
} PathNode;

// Function to insert a new node at the end of the linked list
void insertNode(PathNode **head, const char *directory) {
    PathNode *newNode = (PathNode *)malloc(sizeof(PathNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->directory, directory);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        PathNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the linked list
void printList(PathNode *head) {
    PathNode *current = head;
    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }
}

// Function to free memory allocated for the linked list
void freeList(PathNode *head) {
    PathNode *current = head;
    while (current != NULL) {
        PathNode *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to build the linked list of PATH directories
PathNode *buildPathList() {
    PathNode *head = NULL;
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        exit(EXIT_FAILURE);
    }

    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        insertNode(&head, dir);
        dir = strtok(NULL, ":");
    }
    free(path_copy);

    return head;
}
