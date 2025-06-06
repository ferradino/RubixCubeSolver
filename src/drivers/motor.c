#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "../../include/drivers/motor.h"

short get_motor_number(const char *port) {
    char motor_address_path[BUFFER_SIZE];
    char address[BUFFER_SIZE];
    int motor_number = -1;

    for (int i = 0; i < 3; i++) {
        sprintf(motor_address_path, "/sys/class/tacho-motor/motor%d/address", i);
        int fd = open(motor_address_path, O_RDONLY);
    
        if (fd == -1) {
            fprintf(stderr, "Failed to open motor address: %s\n", motor_address_path);
            perror("Error");
            exit(EXIT_FAILURE);
        }

        ssize_t num_bytes = read(fd, address, 256);
        assert(num_bytes != -1); // Ensure read was successful
        close(fd);

        address[num_bytes] = '\0';

        char *curr_port = strstr(address, ":");
        curr_port++;
        curr_port[strcspn(curr_port, "\n")] = 0;

        if (strcmp(curr_port, port) == 0) {
            motor_number = i;
            printf("Found motor connected to port: %s\n", port);
            break;
        }
    }

    if (motor_number == -1) {
        fprintf(stderr, "Failed to find motor connected to port: %s\n", port);
        exit(EXIT_FAILURE);
    }
    
    return motor_number;
}

motor_t motor_init(const char *port) {
  motor_t motor = {
    .number = get_motor_number(port),
  };

  snprintf(motor.command_file_path, sizeof(motor.command_file_path), "/sys/class/tacho-motor/motor%d/command", motor.number);
  snprintf(motor.speed_file_path, sizeof(motor.speed_file_path), "/sys/class/tacho-motor/motor%d/speed_sp", motor.number);
  snprintf(motor.position_file_path, sizeof(motor.position_file_path), "/sys/class/tacho-motor/motor%d/position_sp", motor.number);
  snprintf(motor.state_file_path, sizeof(motor.state_file_path), "/sys/class/tacho-motor/motor%d/state", motor.number);
  
  run_command(&motor, "reset");  

  return motor;
}

void set_speed(motor_t *motor, int speed) {
    int fd = open(motor->speed_file_path, O_WRONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed to open speed file: %s\n", motor->speed_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%d", speed); 
    assert(write(fd, buffer, BUFFER_SIZE) != -1);
    close(fd);
}

void set_run_to_position(motor_t *motor, const int degrees) {
    int fd = open(motor->position_file_path, O_WRONLY);
    
    if (fd == -1) {
        fprintf(stderr, "Failed to open position file: %s\n", motor->position_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%d", degrees); 

    assert(write(fd, buffer, BUFFER_SIZE) != -1);
    close(fd);
}

void run_command(motor_t *motor, const char *command) {
    int fd = open(motor->command_file_path, O_WRONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed to open command file: %s\n", motor->command_file_path);
        perror("Error");
        exit(EXIT_FAILURE);
    }

    assert(write(fd, command, strlen(command)) != -1);
    close(fd);

    wait_for_motor_to_stop(motor);
    usleep(500 * 1000);
}

void wait_for_motor_to_stop(motor_t *motor) {
    char running[BUFFER_SIZE] = "running";
    char stalled[BUFFER_SIZE] = "stalled";
    char state[BUFFER_SIZE];

    do { 
        int fd = open(motor->state_file_path, O_RDONLY);

        if (fd == -1) {
            fprintf(stderr, "Failed to open command file: %s\n", motor->command_file_path);
            perror("Error");
            exit(EXIT_FAILURE);
        }

        assert(read(fd, state, BUFFER_SIZE) != -1);
        state[strcspn(state, "\n")] = '\0';

        close(fd);
    } while (strcmp(state, running) == 0);
}
