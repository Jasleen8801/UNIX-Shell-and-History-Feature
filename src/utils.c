#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// trim leading and trailing whitespace from a string
char* trimWhitespace(char* str) {
    if (str == NULL) return NULL;

    // trim leadiing whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n') str++;

    // trim trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) end--;
    *(end + 1) = '\0';

    return str;
}

// Split a string into an array of strings based on a delimiter and return the number of tokens
int splitString(char* str, const char* delimiter, char** token, int maxToken) {
    int count = 0;
    char* token = strtok(str, delimiter);
    // strtok returns no of tokens
    while (token != NULL && count < maxToken) {
        token[count] = trimWhitespace(token);
        count++;
        token = strtok(NULL, delimiter);
    }
    return count;
}

// validate if a string is a valid integer
int validateInteger(const char* str) {
    if (str == NULL) return 0;
    while (*str != '\0') {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }
    return 1;
}

// print an error message and exit the program
void printError(const char* errorMessage) {
    fprintf(stderr, "Error: %s\n", errorMessage);
}
