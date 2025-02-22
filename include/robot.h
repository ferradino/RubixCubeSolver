#include "drivers/basket.h"
#include "drivers/arm.h"
#include "drivers/color_sensor_arm.h"
#include "drivers/color_sensor.h"

#ifndef __ROBOT_H
#define __ROBOT_H

#define C_EIGTH_TURN 130
#define C_QUARTER_TURN 265
#define CC_QUARTER_TURN -265
#define HALF_TURN 535

void robot_init();
void rotate_basket(int degrees);
void rotate_cube(int degrees);
void flip_cube();

enum Color read_center_tile_color();
enum Color read_edge_tile_color();
enum Color read_corner_tile_color();

/* 
 * Rubix Cube Turns
 *  - All turns are based on a clockwise rotation
 *  - "Turn" indicates a clockwise rotation (90 degrees)
 *  - "Prime Turn" indicates a counterclockwise rotation (90 degress)
 *  - "Double Turn" is a double rotation (180 degrees)
*/
void r_left_turn();
void r_left_prime_turn();
void r_left_double_turn();
void r_right_turn();
void r_right_prime_turn();
void r_right_double_turn();
void r_down_turn();
void r_down_prime_turn();
void r_down_double_turn();
void r_up_turn();
void r_up_prime_turn();
void r_up_double_turn();
void r_front_turn();
void r_front_prime_turn();
void r_front_double_turn();
void r_back_turn();
void r_back_prime_turn();
void r_back_double_turn();

#endif
