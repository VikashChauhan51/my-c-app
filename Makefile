# Define the C compiler
CC = gcc

# Compiler flags:
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Linker flags: (none needed for this simple project)
LDFLAGS =

# Define directories for build artifacts
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Define source files for your modules (excluding main.c)
LIB_SRCS = src/vector.c

# Define source file for the main application
APP_SRCS = main.c

# Generate object file paths using the OBJ_DIR
# e.g., src/vector.c -> build/obj/vector.o
# e.g., main.c       -> build/obj/main.o
LIB_OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))
APP_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(APP_SRCS))
ALL_OBJS = $(LIB_OBJS) $(APP_OBJS)

# Define the final executable path and name
TARGET = $(BIN_DIR)/app_demo.exe

.PHONY: all clean run dirs

# Default target: builds the executable
all: dirs $(TARGET)

# Create the build directories if they don't exist
# Use native Windows 'mkdir' command. The '-p' equivalent is handled by checking first.
dirs:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
    # Note: 'mkdir -p' (recursive, no error if exists) is more robust in Unix.
    # On Windows, you typically check existence first or just let 'mkdir' fail
    # if the directory already exists (which is fine if you're not doing 'clean' often).
    # For make, '@mkdir -p' is expected to work in a shell with 'mkdir -p' capability.
    # The 'if not exist' syntax is for cmd.exe. Make can handle multiple lines if needed.

# Rule to link object files into the executable
$(TARGET): $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile module source files into object files
# Output to OBJ_DIR
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile main.c into an object file
# Output to OBJ_DIR
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: removes all generated directories and their contents
# Use native Windows 'rmdir /s /q' command for recursive forceful deletion
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
    # The '@if exist' check prevents an error if the directory isn't there.

# Run target: builds and then runs the executable
run: all
	./$(TARGET)