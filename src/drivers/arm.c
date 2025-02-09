#include "arm.h"

void arm_motor_init() {
    motor_init(&arm_motor, "outB");
    reset_arm();
    arm_motor.speed = 200;
}

void reset_arm() {
    run_command(&arm_motor, "reset");
}

void cover() {
    set_speed(&arm_motor, arm_motor.speed);
    set_run_to_position(&arm_motor, COVER_POS);
    run_command(&arm_motor, "run-to-abs-pos");
}

void flip() {
    set_run_to_position(&arm_motor, FLIP_POS);
    set_speed(&arm_motor, arm_motor.speed);
    run_command(&arm_motor, "run-to-abs-pos");
}

void open_arm() {
    set_run_to_position(&arm_motor, ARM_STARTING_POS);
    set_speed(&arm_motor, arm_motor.speed);
    run_command(&arm_motor, "run-to-abs-pos");
    reset_arm();
}