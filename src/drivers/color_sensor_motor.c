#include "color_sensor_motor.h"

void color_sensor_motor_init() {
    motor_init(&color_sensor_motor, "outC");
    color_sensor_motor.speed = 100;
}

void hover_center_tile() {
    run_command(&color_sensor_motor, "reset");
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, CENTER_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
}

void hover_corner_tile() {
    run_command(&color_sensor_motor, "reset");
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, CORNER_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");

}

void hover_edge_tile() {
    run_command(&color_sensor_motor, "reset");
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, EDGE_TILE_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
}

void pull_back_sensor() {
    run_command(&color_sensor_motor, "reset");
    set_speed(&color_sensor_motor, color_sensor_motor.speed);
    set_run_to_position(&color_sensor_motor, SENSOR_STARTING_POS);
    run_command(&color_sensor_motor, "run-to-rel-pos");
}