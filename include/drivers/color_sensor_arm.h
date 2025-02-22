#include "motor.h"

#ifndef __COLOR_SENSOR_MOTOR_H
#define __COLOR_SENSOR_MOTOR_H

#define CENTER_TILE_POS -735
#define EDGE_TILE_POS -610
#define CORNER_TILE_POS -585
#define SENSOR_STARTING_POS 0

Motor color_sensor_motor;

void color_sensor_motor_init();
void reset_color_sensor_motor();
void hover_center_tile();
void hover_corner_tile();
void hover_edge_tile();
void open_color_sensor();

#endif

