#include "../include/robot.h"

robot_t robot_init() {
  robot_t robot = {
    .color_sensor = color_sensor_init(COLOR_SENSOR_PORT),
    .color_sensor_motor = motor_init(COLOR_SENSOR_MOTOR_PORT),
    .basket_motor = motor_init(BASKET_MOTOR_PORT),
    .arm_motor = motor_init(ARM_MOTOR_PORT),
  };

  robot.color_sensor_motor.speed = 200;
  robot.basket_motor.speed = 300;
  robot.arm_motor.speed = 200;

  return robot;
}

void r_make_move(robot_t *robot, moves_t move) {
  switch (move) {
    case U: r_up_turn(robot); break;
    case U2: r_up_double_turn(robot); break;
    case Up: r_up_prime_turn(robot); break;
    case D: r_down_turn(robot); break;
    case D2: r_down_double_turn(robot); break;
    case Dp: r_down_prime_turn(robot); break;
    case R: r_right_turn(robot); break;
    case R2: r_right_double_turn(robot); break;
    case Rp: r_right_prime_turn(robot); break;
    case L: r_left_turn(robot); break;
    case L2: r_left_double_turn(robot); break;
    case Lp: r_left_prime_turn(robot); break;
    case F: r_front_turn(robot); break;
    case F2: r_front_double_turn(robot); break;
    case Fp: r_front_prime_turn(robot); break;
    case B: r_back_turn(robot); break;
    case B2: r_back_double_turn(robot); break;
    case Bp: r_back_prime_turn(robot); break;
  }
}

void solve_cube(robot_t *robot, moves_t moves[256], unsigned char move_count) {
  for (int i = 0; i < move_count; i++) {
    r_make_move(robot, moves[i]);
  }
}

void rotate_basket(motor_t *motor, int degrees) { 
  rotate(motor, degrees); 
}

void rotate_cube(robot_t *robot, int degrees) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  cover(arm);
  rotate(basket, degrees);
  open_arm(arm);
}

void flip_cube(motor_t *motor) {
  cover(motor);
  flip(motor);
  open_arm(motor);
}

color_t read_center_tile_color(robot_t *robot) {
  motor_t *arm = &(robot->color_sensor_motor);
  color_sensor_t *reader = &(robot->color_sensor);
  color_t color;

  hover_center_tile(arm);
  color = read_color(reader);
  open_color_sensor(arm);

  return color;
}

color_t read_edge_tile_color(robot_t *robot) {
  motor_t *arm = &(robot->color_sensor_motor);
  color_sensor_t *reader = &(robot->color_sensor);
  color_t color;

  hover_edge_tile(arm);
  color = read_color(reader);
  open_color_sensor(arm);

  return color;
}

color_t read_corner_tile_color(robot_t *robot) {
  motor_t *arm = &(robot->color_sensor_motor);
  color_sensor_t *reader = &(robot->color_sensor);
  color_t color;

  hover_corner_tile(arm);
  color = read_color(reader);
  open_color_sensor(arm);

  return color;
}

void r_left_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, CC_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_basket(basket, CC_QUARTER_TURN);
}

void r_left_prime_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, CC_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_basket(basket, CC_QUARTER_TURN);
}

void r_left_double_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, CC_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, HALF_TURN);

  flip_cube(arm);
  rotate_basket(basket, HALF_TURN);
}

void r_right_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, C_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_basket(basket, C_QUARTER_TURN);
}

void r_right_prime_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, C_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_basket(basket, C_QUARTER_TURN);
}

void r_right_double_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, C_QUARTER_TURN);
  flip_cube(arm);

  rotate_cube(robot, HALF_TURN);

  flip_cube(arm);
  rotate_basket(basket, C_QUARTER_TURN);
}

void r_down_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);
  flip_cube(arm);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);

  flip_cube(arm);
  flip_cube(arm);
}

void r_down_prime_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);
  flip_cube(arm);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);

  flip_cube(arm);
  flip_cube(arm);
}

void r_down_double_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);
  flip_cube(arm);

  rotate_cube(robot, HALF_TURN);
  rotate_basket(basket, HALF_TURN);

  flip_cube(arm);
  flip_cube(arm);
}

void r_up_turn(robot_t *robot) {
  motor_t *basket = &(robot->basket_motor);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);
}

void r_up_prime_turn(robot_t *robot) {
  motor_t *basket = &(robot->basket_motor);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);
}

void r_up_double_turn(robot_t *robot) {
  motor_t *basket = &(robot->basket_motor);

  rotate_cube(robot, HALF_TURN);
  rotate_basket(basket, HALF_TURN);
}

void r_front_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
}

void r_front_prime_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
}

void r_front_double_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  flip_cube(arm);

  rotate_cube(robot, HALF_TURN);
  rotate_basket(basket, HALF_TURN);

  flip_cube(arm);
}

void r_back_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);
  
  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_cube(robot, C_QUARTER_TURN);
  rotate_basket(basket, CC_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
}

void r_back_prime_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_cube(robot, CC_QUARTER_TURN);
  rotate_basket(basket, C_QUARTER_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
}

void r_back_double_turn(robot_t *robot) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);

  rotate_cube(robot, HALF_TURN);

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
}
