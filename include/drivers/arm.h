#include "motor.h"

#ifndef __ARM_MOTOR_H
#define __ARM_MOTOR_H

#define COVER_POS -220
#define FLIP_POS -80
#define ARM_STARTING_POS 0

void cover(motor_t *motor);
void flip(motor_t *motor);
void open_arm(motor_t *motor);

#endif
