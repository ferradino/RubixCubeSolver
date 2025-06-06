# Compiler and flags
CC = arm-linux-gnueabi-gcc
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -O2 -I ./src -I ./include -I ./external
CFLAGS = -O2 -g -I ./src -I ./include

# Directories
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/**/*.c)
SRCS += $(wildcard $(SRC_DIR)/*.c)

# Object files 
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Target binary
TARGET = $(BIN_DIR)/main

# Build target
all: $(TARGET)

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the target binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
