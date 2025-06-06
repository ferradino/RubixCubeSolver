#ifndef __ROBOT_H
#define __ROBOT_H

#include "drivers/basket.h"
#include "drivers/arm.h"
#include "drivers/color_sensor_arm.h"
#include "drivers/color_sensor.h"

#define C_EIGTH_TURN 130
#define C_QUARTER_TURN 255
#define CC_QUARTER_TURN -290
#define HALF_TURN 510

#define BASKET_MOTOR_PORT "outA"
#define ARM_MOTOR_PORT "outB"
#define COLOR_SENSOR_MOTOR_PORT "outC"
#define COLOR_SENSOR_PORT "in4"

typedef enum MOVES { U, U2, Up, D, D2, Dp, R, R2, Rp, L, L2, Lp, F, F2, Fp, B, B2, Bp } moves_t;

typedef struct Robot {
  color_sensor_t color_sensor;
  motor_t color_sensor_motor;
  motor_t basket_motor;
  motor_t arm_motor;
} robot_t;

robot_t robot_init();
void rotate_basket(motor_t *motor, int degrees);
void flip_cube(motor_t *motor);
void rotate_cube(robot_t *robot, int degrees);

color_t read_center_tile_color(robot_t *robot);
color_t read_edge_tile_color(robot_t *robot);
color_t read_corner_tile_color(robot_t *robot);

/* 
 * Rubix Cube Turns
 *  - All turns are based on a clockwise rotation
 *  - "Turn" indicates a clockwise rotation (90 degrees)
 *  - "Prime Turn" indicates a counterclockwise rotation (90 degress)
 *  - "Double Turn" is a double rotation (180 degrees)
*/
void solve_cube(robot_t *robot, moves_t moves[256], unsigned char move_count);
void r_make_move(robot_t *robot, moves_t move);
void r_left_turn(robot_t *robot);
void r_left_prime_turn(robot_t *robot);
void r_left_double_turn(robot_t *robot);
void r_right_turn(robot_t *robot);
void r_right_prime_turn(robot_t *robot);
void r_right_double_turn(robot_t *robot);
void r_down_turn(robot_t *robot);
void r_down_prime_turn(robot_t *robot);
void r_down_double_turn(robot_t *robot);
void r_up_turn(robot_t *robot);
void r_up_prime_turn(robot_t *robot);
void r_up_double_turn(robot_t *robot);
void r_front_turn(robot_t *robot);
void r_front_prime_turn(robot_t *robot);
void r_front_double_turn(robot_t *robot);
void r_back_turn(robot_t *robot);
void r_back_prime_turn(robot_t *robot);
void r_back_double_turn(robot_t *robot);

#endif
