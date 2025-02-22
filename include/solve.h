#include "cube.h"

#ifndef __SOLVE_H
#define __SOLVE_H

/*
 * Solve Functions
 *  - solve is the first function called. It will call each stage function as
 *    it attempts to solve that stage. It returns a char array of the moves needed
 *    to solve the cube
 */
char* solve(RubixCube *rubix_cube);
void stage1(RubixCube *rubix_cube);
void stage2(RubixCube *rubix_cube);
void stage3(RubixCube *rubix_cube);
void stage4(RubixCube *rubix_cube);

void set_edge_orientation(RubixCube *rubix_cube);
void set_corner_orientation(RubixCube *rubix_cube);

#endif
