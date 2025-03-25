#include "motor.h"

#ifndef __COLOR_SENSOR_MOTOR_H
#define __COLOR_SENSOR_MOTOR_H

#define CENTER_TILE_POS -735
#define EDGE_TILE_POS -610
#define CORNER_TILE_POS -585
#define SENSOR_STARTING_POS 0

void hover_center_tile(motor_t *motor);
void hover_corner_tile(motor_t *motor);
void hover_edge_tile(motor_t *motor);
void open_color_sensor(motor_t *motor);

#endif

