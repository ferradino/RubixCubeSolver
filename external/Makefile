CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -I../include

# Source files
SRCS = gen_s1.c gen_s2.c gen_s3.c gen_s4.c queue.c

# Object files (placed in ./obj/)
BUILD_DIR = obj
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

# Default target
all: $(BUILD_DIR) $(OBJS)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files to object files in build dir
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean