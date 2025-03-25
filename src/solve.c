#include "../include/solve.h"

char* solve(RubixCube *rubix_cube);
void stage1(RubixCube *rubix_cube);
void stage2(RubixCube *rubix_cube);
void stage3(RubixCube *rubix_cube);
void stage4(RubixCube *rubix_cube);

void set_edge_orientation(RubixCube *rubix_cube);
void set_corner_orientation(RubixCube *rubix_cube);
