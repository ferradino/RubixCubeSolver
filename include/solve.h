#ifndef __SOLVE_H
#define __SOLVE_H
    
#include <stdint.h>
#include "cube.h"

#define STAGE1_FILE "./tables/stage1.txt"
#define STAGE2_FILE "./tables/stage2.txt"
#define STAGE3_FILE "./tables/stage3.txt"
#define STAGE4_FILE "./tables/stage4.txt"

/*
 * Solve Function
 *  - Driver function that calls 4 functions to solve each stage of the cube. Updates the solution
 *    array with moves needed to solve cube
 *  - Returns the number of moves made
 */
void stage1(rubix_cube_t *rubix_cube_t, moves_t *solution, unsigned char *count);
void stage2(rubix_cube_t *rubix_cube_t, moves_t *solution, unsigned char *count);
void stage3(rubix_cube_t *rubix_cube_t, moves_t *solution, unsigned char *count);
void stage4(rubix_cube_t *rubix_cube_t, moves_t *solution, unsigned char *count);
unsigned char solve(rubix_cube_t *rubix_cube_t, moves_t *solution);

#endif
