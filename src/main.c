#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "robot.h"

int main(void) {
  printf("*** Starting Motor! ****\n");
  rotateCube();
  
  printf("*** Attempting to Flip Cube ! ****\n");
  flipCube();

  return 0;
}