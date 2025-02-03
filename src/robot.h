#include "drivers/basket_motor.h"
#include "drivers/arm_motor.h"
#include "drivers/color_sensor_motor.h"
#include "drivers/color_sensor.h"

#ifndef __ROBOT_H
#define __ROBOT_H

#define QUARTER_TURN 270
#define HALF_TURN 540

void robotInit();
void rotateBasket();
void rotateCube();
void flipCube();
void reset_arm();

#endif