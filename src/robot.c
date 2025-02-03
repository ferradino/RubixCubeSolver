#include "robot.h"

void robotInit() {
  basket_motor_init();
  arm_motor_init();
  color_sensor_motor_init();
  color_sensor_init();
}

void rotateBasket() { 
  rotate(HALF_TURN);
}

void rotateCube() {
  cover();
  rotate(QUARTER_TURN);
  pull_back_arm();
}

void flipCube() {
  cover();
  rotate(QUARTER_TURN);
  pull_back_arm();
}