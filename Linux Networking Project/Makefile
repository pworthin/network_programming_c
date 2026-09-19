# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Directory for object files
BIN_DIR = bin

# Source files
SRC_FILES = fileio.c modules.c udp-server.c udp_modules.c terminator.c server.c sniffer.c

# Convert source filenames into bin/*.o filenames
OBJ_FILES = $(SRC_FILES:%.c=$(BIN_DIR)/%.o)

# Build all object files
all: $(OBJ_FILES)

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile each .c file into bin/*.o
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove generated object files
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean