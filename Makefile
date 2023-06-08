# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Source files
SRCS = src/main.c src/shell.c src/history.c src/utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
EXEC = shell

# Default target
all: $(EXEC)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f $(EXEC) $(OBJS)
