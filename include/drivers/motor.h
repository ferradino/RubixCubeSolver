#ifndef __MOTOR_H
#define __MOTOR_H

#define BUFFER_SIZE 256

typedef struct Motor {
    int number;
    int speed;
    char command_file_path[BUFFER_SIZE];
    char position_file_path[BUFFER_SIZE];
    char speed_file_path[BUFFER_SIZE];
    char state_file_path[BUFFER_SIZE];
} motor_t;

motor_t motor_init(const char *port);
void set_speed(motor_t *motor, int speed);
void set_run_to_position(motor_t *motor, const int position);
void run_command(motor_t *motor, const char *command);
void wait_for_motor_to_stop(motor_t *motor);

#endif
