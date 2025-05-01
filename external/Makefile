CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

OBJ_DIR = build/obj
BIN_DIR = build/bin

EXECUTABLES = $(BIN_DIR)/gen_s1 $(BIN_DIR)/gen_s2 $(BIN_DIR)/gen_s3 $(BIN_DIR)/gen_s4

# Object files needed for each executable
COMMON_OBJS = $(OBJ_DIR)/gen_cube.o $(OBJ_DIR)/queue.o

GEN_S1_OBJS = $(OBJ_DIR)/gen_s1.o $(COMMON_OBJS)
GEN_S2_OBJS = $(OBJ_DIR)/gen_s2.o $(COMMON_OBJS)
GEN_S3_OBJS = $(OBJ_DIR)/gen_s3.o $(COMMON_OBJS)
GEN_S4_OBJS = $(OBJ_DIR)/gen_s4.o $(COMMON_OBJS)

all: $(EXECUTABLES)

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile queue.c to object file in the OBJ_DIR
$(OBJ_DIR)/queue.o: queue.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile gen_cube.c to object file in the OBJ_DIR
$(OBJ_DIR)/gen_cube.o: gen_cube.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile gen_s*.c files to object files in the OBJ_DIR
$(OBJ_DIR)/gen_s1.o: gen_s1.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gen_s2.o: gen_s2.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gen_s3.o: gen_s3.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gen_s4.o: gen_s4.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/gen_s1: $(OBJ_DIR)/gen_s1.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/gen_s1.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s2: $(OBJ_DIR)/gen_s2.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/gen_s2.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s3: $(OBJ_DIR)/gen_s3.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/gen_s3.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s4: $(OBJ_DIR)/gen_s4.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/gen_s4.o $(COMMON_OBJS)

clean:
	rm -f $(EXECUTABLES) $(OBJ_DIR)/*.o

.PHONY: all clean
