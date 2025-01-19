#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef __ROBOT_H
#define __ROBOT_H

bool startRobot();
void stopRobot();

void rotateCube();
void flipCube();
void readColor();

#endif