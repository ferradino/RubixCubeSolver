#include "drivers/basket.h"
#include "drivers/arm.h"
#include "drivers/color_sensor_arm.h"
#include "drivers/color_sensor.h"

#ifndef __ROBOT_H
#define __ROBOT_H

#define QUARTER_TURN 270
#define HALF_TURN 540

void robot_init();
void rotate_basket();
void rotate_cube();
void flip_cube();

enum Color read_center_tile_color();
enum Color read_edge_tile_color();
enum Color read_corner_tile_color();

#endif