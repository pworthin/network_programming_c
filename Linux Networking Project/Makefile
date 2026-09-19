# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC_FILES = fileio.c modules.c udp-server.c udp_modules.c terminator.c server.c sniffer.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Build all object files
all: $(OBJ_FILES)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove generated object files
clean:
	rm -f $(OBJ_FILES)

.PHONY: all clean