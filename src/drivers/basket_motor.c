#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "basket_motor.h"

void basket_motor_init() {
    motor_init(&basket_motor, "outA");
}

void rotate(int degrees) { 
    run_command(&basket_motor, "reset");
    set_speed(&basket_motor);
    set_run_to_position(&basket_motor, degrees);
    run_command(&basket_motor, "run-to-rel-pos");
}