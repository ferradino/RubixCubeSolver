#include "ev3dev-c/source/ev3/brick.h"
#include <stdio.h>

#ifndef __ROBOT_H
#define __ROBOT_H

bool startRobot();
void stopRobot();

void rotateCube();
void flipCube();
void readColor();

#endif
