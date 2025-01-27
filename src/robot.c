#include "robot.h"

const int HALF_TURN = 500;
const int QUARTER_TURN = 270;

void robotInit() {
  basket_motor_init();
}

void rotateCube() { 
  rotate(HALF_TURN);
}