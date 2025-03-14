#include "cube.h"

#ifndef __SOLVE_H
#define __SOLVE_H

/*
 * Solve Function
 *  - solve is the first function called. It will call each stage function as
 *    it attempts to solve that stage. It returns a char array of the moves needed
 *    to solve the cube
 */
char** solve(RubixCube *rubix_cube);

#endif
