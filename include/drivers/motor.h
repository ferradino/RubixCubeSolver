#ifndef __MOTOR_H
#define __MOTOR_H

#define BUFFER_SIZE 256

typedef struct {
    int number;
    int speed;
    char command_file_path[BUFFER_SIZE];
    char position_file_path[BUFFER_SIZE];
    char speed_file_path[BUFFER_SIZE];
    char state_file_path[BUFFER_SIZE];
} Motor;

void motor_init(Motor *motor, const char *port);
void set_speed(Motor *motor, int speed);
void set_run_to_position(Motor *motor, const int position);
void run_command(Motor *motor, const char *command);
void wait_for_motor_to_stop(Motor *motor);

#endif