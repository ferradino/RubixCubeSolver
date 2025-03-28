#ifndef __SOLVE_H
#define __SOLVE_H
    
#include "cube.h"

/*
 * Solve Function
 *  - solve is the first function called. It will call each stage function as
 *    it attempts to solve that stage. It returns a char array of the moves needed
 *    to solve the cube
 */
char** solve(rubix_cube_t *rubix_cube);

#endif