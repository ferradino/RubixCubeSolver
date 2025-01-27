#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "robot.h"

int main(void) {
  printf("*** Starting Motor(s)! ****\n");
  robotInit();
  
  printf("*** Attempting to Rotate Cube! ****\n");
  rotateCube();

  return 0;
}