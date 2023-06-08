#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "utils.h"

#define HISTORY_SIZE 10
#define MAX_ARGS 50

// global variables
char* history[HISTORY_SIZE];
int historyCount = 0;

void addCommandToHistory(const char* command) {
    if (historyCount == HISTORY_SIZE) {
        free(history[0]);
        for (int i = 1; i < HISTORY_SIZE; i++) {
            history[i - 1] = history[i];
        }
        historyCount--;
    }
    history[historyCount] = strdup(command);
    historyCount++;
}

void printCommandHistory() {
    for (int i = historyCount - 1; i >= 0; i--) {
        printf("%d %s\n", i + 1, history[i]);
    }
}

void executeRecentCommand() {
    if (historyCount > 0) {
        executeCommandFromHistory(historyCount);
    } else {
        printError("No commands in history");
    }
}

void executeCommandFromHistory(int commandNumber) {
    int index = historyCount - commandNumber;
    if (index >= 0 && index < historyCount) {
        char* command = strdup(history[index]);
        char* args[MAX_ARGS];
        int argCount = splitString(command, " ", args, MAX_ARGS);
        args[argCount] = NULL;
        executeCommand(args, 0);
        free(command);
    } else {
        printError("Command not in history");
    }
}
