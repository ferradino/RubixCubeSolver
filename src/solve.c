#include "../include/solve.h"

char *moves[200];
unsigned char count;

/* Use BFS to solve each stage */
void solve_stage(RubixCube *rubix_cube, char** group, unsigned char *correct_orientation, unsigned char group_num) {

}

void stage_one(RubixCube *rubix_cube ) {
  unsigned char group_num = 0;
  char *group_zero[12] = { "L", "R", "F", "B", "U", "D", "L'", "R'", "F'", "B'", "U'", "D'"};
  unsigned char correct_edge_orientation[12] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };
  solve_stage(rubix_cube, group_zero, correct_edge_orientation, group_num);
}

void stage_two(RubixCube *rubix_cube) {
  unsigned char group_num = 1;
  char *group_one[10] = { "L", "R", "F", "B", "U2", "D2", "L'", "R'", "F'", "B'"};
  unsigned char correct_corner_orientation[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
  solve_stage(rubix_cube, group_one, correct_corner_orientation, group_num);
}

void stage_three(RubixCube *rubix_cube) {
  char *group_two[8] = { "L", "R", "F2", "B2", "U2", "D2", "L'", "R'" };
  unsigned char correct_corner_orientation[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
  unsigned char group_num = 2;
  solve_stage(rubix_cube, group_two, correct_corner_orientation, group_num);
}

void stage_four(RubixCube *rubix_cube) {
  unsigned char group_num = 3;
  char *group_three[6] = { "L2", "R2", "F2", "B2", "U2", "D2" };
  unsigned char correct_corner_orientation[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
  solve_stage(rubix_cube, group_three, correct_corner_orientation, group_num);
}

char** solve(RubixCube *rubix_cube) {
  stage_one(rubix_cube);
  stage_two(rubix_cube);
  stage_three(rubix_cube);
  stage_four(rubix_cube);
  
  return moves;
}
