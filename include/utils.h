#ifndef UTILS_H
#define UTILS_H

// function prototypes
char* trimWhitespace(char* str);
int splitString(char* str, const char* delimiters, char** tokens, int maxTokens);
int validateInteger(const char* str);
void printError(const char* errorMessage);

#endif // UTILS_H
