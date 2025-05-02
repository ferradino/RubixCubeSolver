#include "../../include/drivers/arm.h"

void cover(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, COVER_POS);
    run_command(motor, "run-to-abs-pos");
}

void tap(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, TAP_POS);
    run_command(motor, "run-to-abs-pos");
}

void flip(motor_t *motor) {
    set_run_to_position(motor, FLIP_POS);
    set_speed(motor, motor->speed);
    run_command(motor, "run-to-abs-pos");
}

void open_arm(motor_t *motor) {
    set_run_to_position(motor, ARM_STARTING_POS);
    set_speed(motor, motor->speed);
    run_command(motor, "run-to-abs-pos");
    run_command(motor, "reset");
}
