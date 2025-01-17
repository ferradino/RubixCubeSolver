#include "robot.h"

int main(void) {
  printf("*** Starting Robot! ***\n");
  startRobot();

  printf("*** Spinning Cube! ***\n");
  rotateCube();
  
  printf("*** Stopping Robot! ***\n");
  stopRobot();
  printf("*** Goodbye! ***\n");

  return 0;
}