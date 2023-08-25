# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
#SRC_FILES = fileio.c helper.h modules.c socket_mods.h test-server-0818.c
SRC_FILES = fileio.c helper.h modules.c socket_mods.h udp-server.c udp_header.h udp_modules.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output executable name
#TARGET = test-serverAug18
TARGET = udp-server
# Rule to build the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f *.o
