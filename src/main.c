#include <stdio.h>
#include "cube.h"
#include "robot.h"

int main(void) {
  // Initialize the robot
  printf("**** Starting Robot! ****\n");
  robot_init();

  // Read the Rubix Cube
  printf("**** Reading In Cube! ****\n");

  // Solve
  printf("**** Solving Cube! ****\n");

  // Done
  printf("**** Rubix Cube Has Been Solved! ****\n");

  return 0;
}
