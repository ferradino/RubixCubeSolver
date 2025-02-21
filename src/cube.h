#include "robot.h"

#ifndef __CUBE_H
#define __CUBE_H

typedef struct {
  unsigned char edges[12];
} RubixCube;

void read_rubix_cube(RubixCube *rubix_cube);

/* 
Rubix Cube Turns
- All turns are based on a clockwise rotation
- "Turn" indicates a clockwise rotation (90 degrees)
- "Prime Turn" indicates a counterclockwise rotation (90 degress)
- "Double Turn" is a double rotation (180 degrees)
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
void up_prime_turn();
void up_double_turn();
void front_turn();
void front_prime_turn();
void front_double_turn();
void back_turn();
void back_prime_turn();
void back_double_turn();

#endif
