#include "../../include/drivers/basket.h"

void rotate(motor_t *motor, int degrees) { 
    set_speed(motor, motor->speed);
    set_run_to_position(motor, degrees);
    run_command(motor, "run-to-rel-pos");
    run_command(motor, "reset");
}
