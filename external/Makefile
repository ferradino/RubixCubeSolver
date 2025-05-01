CC = gcc
CFLAGS = -Wall -Wextra -O2 -I../include

OBJ_DIR = ../build/obj
SRC_OBJ_DIR = $(OBJ_DIR)/src
DRIVERS_OBJ_DIR = $(OBJ_DIR)/src/drivers
EXTERNAL_OBJ_DIR = build/obj
BIN_DIR = build/bin

EXECUTABLES = $(BIN_DIR)/gen_s1 $(BIN_DIR)/gen_s2 $(BIN_DIR)/gen_s3 $(BIN_DIR)/gen_s4

# Object files needed for each executable
COMMON_OBJS = $(SRC_OBJ_DIR)/cube.o $(SRC_OBJ_DIR)/robot.o \
              $(DRIVERS_OBJ_DIR)/arm.o $(DRIVERS_OBJ_DIR)/basket.o \
              $(DRIVERS_OBJ_DIR)/color_sensor.o $(DRIVERS_OBJ_DIR)/motor.o \
              $(DRIVERS_OBJ_DIR)/color_sensor_arm.o $(EXTERNAL_OBJ_DIR)/queue.o

GEN_S1_OBJS = $(EXTERNAL_OBJ_DIR)/gen_s1.o $(COMMON_OBJS)
GEN_S2_OBJS = $(EXTERNAL_OBJ_DIR)/gen_s2.o $(COMMON_OBJS)
GEN_S3_OBJS = $(EXTERNAL_OBJ_DIR)/gen_s3.o $(COMMON_OBJS)
GEN_S4_OBJS = $(EXTERNAL_OBJ_DIR)/gen_s4.o $(COMMON_OBJS)

all: $(EXECUTABLES)

# Create the object directory if it doesn't exist
$(EXTERNAL_OBJ_DIR):
	mkdir -p $(EXTERNAL_OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile queue.c to object file in the EXTERNAL_OBJ_DIR
$(EXTERNAL_OBJ_DIR)/queue.o: queue.c | $(EXTERNAL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile gen_s*.c files to object files in the EXTERNAL_OBJ_DIR
$(EXTERNAL_OBJ_DIR)/gen_s1.o: gen_s1.c | $(EXTERNAL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXTERNAL_OBJ_DIR)/gen_s2.o: gen_s2.c | $(EXTERNAL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXTERNAL_OBJ_DIR)/gen_s3.o: gen_s3.c | $(EXTERNAL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXTERNAL_OBJ_DIR)/gen_s4.o: gen_s4.c | $(EXTERNAL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/gen_s1: $(EXTERNAL_OBJ_DIR)/gen_s1.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXTERNAL_OBJ_DIR)/gen_s1.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s2: $(EXTERNAL_OBJ_DIR)/gen_s2.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXTERNAL_OBJ_DIR)/gen_s2.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s3: $(EXTERNAL_OBJ_DIR)/gen_s3.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXTERNAL_OBJ_DIR)/gen_s3.o $(COMMON_OBJS)

$(BIN_DIR)/gen_s4: $(EXTERNAL_OBJ_DIR)/gen_s4.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXTERNAL_OBJ_DIR)/gen_s4.o $(COMMON_OBJS)

clean:
	rm -f $(EXECUTABLES) $(EXTERNAL_OBJ_DIR)/*.o

.PHONY: all clean