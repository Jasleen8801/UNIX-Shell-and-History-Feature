#ifndef HISTORY_H
#define HISTORY_H

void addCommandToHistory(const char* command);
void printCommandHistory();
void executeRecentCommand();
void executeCommandFromHistory(int commandNumber);

#endif // HISTORY_H
