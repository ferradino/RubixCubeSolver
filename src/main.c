#include <stdio.h>
#include "../include/cube.h"
#include "../include/robot.h"
#include "../include/solve.h"

int main(void) {
  // Initialize the robot
  printf("**** Starting Robot! ****\n");
  robot_t robot = robot_init();

  // Initialize Rubix Cube
  rubix_cube_t rubix_cube = rubix_cube_init(&robot);

  // Read the Rubix Cube
  printf("**** Reading In Cube! ****\n");
  read_rubix_cube_tile_colors(&robot, &rubix_cube);

  // Solve
  printf("**** Solving Cube! ****\n");

  // Done
  printf("**** Rubix Cube Has Been Solved! ****\n");

  return 0;
}
