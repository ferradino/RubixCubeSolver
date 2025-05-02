#ifndef __ARM_MOTOR_H
#define __ARM_MOTOR_H

#include "motor.h"

#define COVER_POS 80 
#define TAP_POS 200
#define FLIP_POS 270
#define ARM_STARTING_POS 0

void cover(motor_t *motor);
void tap(motor_t *motor);
void flip(motor_t *motor);
void open_arm(motor_t *motor);

#endif
