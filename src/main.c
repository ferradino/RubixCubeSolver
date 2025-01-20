#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "robot.h"

int main(void) {
  printf("*** Connecting to EV3 robot! ****\n");
  startRobot();

  printf("*** Starting Motor! ****\n");
  rotateCube();
  
  printf("*** Attempting to Flip Cube ! ****\n");
  flipCube();

  printf("*** Stopping EV3 robot! ****\n");
  stopRobot();

  return 0;
}