#include "../../include/drivers/basket.h"

void rotate(motor_t *motor, int degrees) { 
    run_command(motor, "reset");
    set_speed(motor, motor->speed);
    set_run_to_position(motor, degrees);
    run_command(motor, "run-to-abs-pos");
    run_command(motor, "reset");
}
