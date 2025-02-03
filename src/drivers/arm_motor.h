#include "motor.h"

#ifndef __ARM_MOTOR_H
#define __ARM_MOTOR_H

#define COVER_POS 400
#define FLIP_POS 200
#define ARM_STARTING_POS 0

Motor arm_motor;

void arm_motor_init();
void cover();
void pull_back_arm();

#endif