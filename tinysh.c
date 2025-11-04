#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        // Print prompt
        printf("tinysh> ");
        fflush(stdout);

        // Read input
        if (!fgets(line, sizeof(line), stdin)) {
            break; // EOF (Ctrl+D)
        }

        // Remove newline
        line[strcspn(line, "\n")] = 0;

        // Skip empty lines
        if (line[0] == 0) continue;

        // Exit command
        if (strcmp(line, "exit") == 0) break;

        // Tokenize input into args
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Fork and execute
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror("exec"); // If exec fails
            exit(1);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            perror("fork");
        }
    }

    printf("Bye!\n");
    return 0;
}
