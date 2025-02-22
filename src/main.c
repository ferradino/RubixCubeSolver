#include <stdio.h>
#include "../include/cube.h"
#include "../include/robot.h"

int main(void) {
  // Initialize the robot
  printf("**** Starting Robot! ****\n");
  robot_init();

  // Initialize Rubix Cube
  RubixCube rubix_cube;
  rubix_cube_init(&rubix_cube);

  // Read the Rubix Cube
  printf("**** Reading In Cube! ****\n");
  read_rubix_cube_tile_colors(&rubix_cube);

  // Solve
  printf("**** Solving Cube! ****\n");

  // Done
  printf("**** Rubix Cube Has Been Solved! ****\n");

  return 0;
}
