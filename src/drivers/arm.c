#include "arm.h"

void arm_motor_init() {
    motor_init(&arm_motor, "outB");
    arm_motor.speed = 250;
}

void reset_arm() {
    run_command(&arm_motor, "reset");
}

void cover() {
    run_command(&arm_motor, "reset");
    set_speed(&arm_motor, arm_motor.speed);
    set_run_to_position(&arm_motor, COVER_POS - ARM_STARTING_POS);
    run_command(&arm_motor, "run-to-rel-pos");
}

void flip() {
    set_run_to_position(&arm_motor, FLIP_POS - COVER_POS);
    set_speed(&arm_motor, arm_motor.speed);
    run_command(&arm_motor, "run-to-rel-pos");
}

void open_arm() {
    set_run_to_position(&arm_motor, ARM_STARTING_POS - FLIP_POS);
    set_speed(&arm_motor, arm_motor.speed);
    run_command(&arm_motor, "run-to-rel-pos");
    reset_arm();
}