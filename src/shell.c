#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/wait.h>
#include "utils.h"
#include "shell.h"

#define MAX_LINE 80
#define MAX_ARGS 64
#define HISTORY_SIZE 10

// global variables
char* history[HISTORY_SIZE];
int historyCount = 0;

void executeCommand(char** args, int background) {
    pid_t pid = fork();

    if (pid < 0) {
        printError("Unable to fork");
        return;
    } else if (pid == 0) {
        // child process
        if (execvp(args[0], args) < 0) {
            printError("Unable to execute command");
            exit(1);
        }
    } else {
        // parent process
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

void runShell() {
    char input[MAX_LINE]; // Buffer to hold the command entered by the user
    int shouldRun = 1; // Flag to determine when to exit program

    while (shouldRun) {
        printf("osh> ");
        fflush(stdout);

        // read user input
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        char* trimmedInput = trimWhitespace(input);
        if (strlen(trimmedInput) == 0) continue;

        // add command to history
        if (historyCount == HISTORY_SIZE) {
            free(history[0]);
            for (int i = 1; i < HISTORY_SIZE; i++) {
                history[i - 1] = history[i];
            }
            historyCount--;
        }
        history[historyCount] = strdup(trimmedInput);
        historyCount++;

        // check if user wants to exit
        if (strcmp(trimmedInput, "exit") == 0) {
            shouldRun = 0;
            break;
        }

        // check if user entered history
        if (strcmp(trimmedInput, "history") == 0) {
            for (int i = 0; i < historyCount; i++) {
                printf("%d %s\n", i + 1, history[i]);
            }
            continue;
        }   

        // check if user entered a command from history
        if (trimmedInput[0] == '!') {
            int commandNumber = validateInteger(trimmedInput + 1);
            if (commandNumber) {
                int index = historyCount - commandNumber;
                if (index >= 0 && index < historyCount) {
                    executeCommand(splitString(history[index], " ", NULL, MAX_ARGS), 0);
                } else {
                    printError("Command not in history");
                }
            } else if (strcmp(trimmedInput, '!!') == 0) {
                if (historyCount > 0) {
                    executeCommand(splitString(history[historyCount - 1], " ", NULL, MAX_ARGS), 0);
                } else {
                    printError("No commands in history");
                }
            } else {
                printError("Invalid command");
            }
            continue;
        }

        // parse the input into command and arguments
        char* args[MAX_ARGS];
        int background = 0;
        int argCount = splitString(trimmedInput, " ", args, MAX_ARGS);

        // check if the command should be run in the background
        if (strcmp(args[argCount - 1], "&") == 0) {
            background = 1;
            args[argCount - 1] = NULL;
        } else {
            args[argCount] = NULL;
        }

        // execute the command
        executeCommand(args, background);
    }
}
