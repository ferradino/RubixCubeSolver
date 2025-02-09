#include "robot.h"

#ifndef __CUBE_H
#define __CUBE_H

typedef struct {
    int x;
} RubixCube;

void read_rubix_cube(RubixCube *rubix_cube);


/* 
Rubix Cube Turns
- All turn are based on a clockwise rotation
- "Prime" turn indicates a counterclockwise rotation
- "Double" turn is a double rotation
*/
void left_turn();
void left_prime_turn();
void left_double_turn();
void right_turn();
void right_prime_turn();
void right_double_turn();
void down_turn();
void down_prime_turn();
void down_double_turn();
void up_turn();
void up_prime_top();
void up_double_rotation();
void front_rotation();
void front_prime_rotation();
void front_double_rotation();
void back_rotation();
void back_prime_rotation();
void back_double_rotation();

#endif