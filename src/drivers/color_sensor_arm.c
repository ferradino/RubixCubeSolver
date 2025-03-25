#include "../../include/drivers/color_sensor_arm.h"

void hover_center_tile(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, CENTER_TILE_POS);
    run_command(motor, "run-to-abs-pos");
}

void hover_corner_tile(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, CORNER_TILE_POS);
    run_command(motor, "run-to-abs-pos");

}

void hover_edge_tile(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, EDGE_TILE_POS);
    run_command(motor, "run-to-abs-pos");
}

void open_color_sensor(motor_t *motor) {
    set_speed(motor, motor->speed);
    set_run_to_position(motor, SENSOR_STARTING_POS);
    run_command(motor, "run-to-abs-pos");
    run_command(motor, "reset");
}
