#include "arm_motor.h"

void arm_motor_init() {
    motor_init(&arm_motor, "outB");
    arm_motor.speed = 250;
}

void reset_arm() {
    run_command(&arm_motor, "reset");
    set_speed(&arm_motor, arm_motor.speed);
    run_command(&arm_motor, "run-forever");
    run_command(&arm_motor, "stop");
}

void cover() {
    run_command(&arm_motor, "reset");
    set_speed(&arm_motor, 200);
    set_run_to_position(&arm_motor, COVER_POS);
    run_command(&arm_motor, "run-to-rel-pos");
}

void pull_back_arm() {
    set_run_to_position(&arm_motor, FLIP_POS);
    run_command(&arm_motor, "run-to-rel-pos");
    reset_arm();
}