#include "color_sensor_arm.h"

void color_sensor_motor_init() {
    motor_init(&color_sensor_motor, "outC");
    color_sensor_motor.speed = 100;
}

void reset_color_sensor_motor() {
    run_command(&color_sensor_motor, "reset");
}

void hover_center_tile() {
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, CENTER_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
}

void hover_corner_tile() {
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, CORNER_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");

}

void hover_edge_tile() {
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, EDGE_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
}

void open_color_sensor() {
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, SENSOR_STARTING_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
    reset_color_sensor_motor();
}