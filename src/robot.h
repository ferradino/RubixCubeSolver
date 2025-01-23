#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef __ROBOT_H
#define __ROBOT_H

/* The color sensor returns integers from 0 to 7, 
where each number corresponds to a color. */
#define NO_COLOR 0
#define BLACK 1
#define BLUE 2
#define GREEN 3
#define YELLOW 4
#define RED 5
#define WHITE 6
#define BROWN 7

void startRobot();
void stopRobot();

void rotateCube();
void flipCube();
void readColor();

#endif