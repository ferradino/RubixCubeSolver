#include "../include/robot.h"

void robot_init() {
  basket_motor_init();
  arm_motor_init();
  color_sensor_motor_init();
  color_sensor_init();
}

void rotate_basket(int degrees) { rotate(degrees); }

void rotate_cube(int degrees) {
  cover();
  rotate(degrees);
  open_arm();
}

void flip_cube() {
  cover();
  flip();
  open_arm();
}

color_t read_center_tile_color() {
  color_t color;

  hover_center_tile();
  color = read_color();
  open_color_sensor();

  return color;
}

color_t read_edge_tile_color() {
  color_t color;

  hover_edge_tile();
  color = read_color();
  open_color_sensor();

  return color;
}

color_t read_corner_tile_color() {
  color_t color;

  hover_corner_tile();
  color = read_color();
  open_color_sensor();

  return color;
}

void r_left_turn() {
  rotate_basket(CC_QUARTER_TURN);
  flip_cube();

  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_basket(CC_QUARTER_TURN);
}

void r_left_prime_turn() {
  rotate_basket(CC_QUARTER_TURN);
  flip_cube();

  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_basket(CC_QUARTER_TURN);
}

void r_left_double_turn() {
  rotate_basket(CC_QUARTER_TURN);
  flip_cube();

  rotate_cube(HALF_TURN);

  flip_cube();
  rotate_basket(-1 * HALF_TURN);
}

void r_right_turn() {
  rotate_basket(C_QUARTER_TURN);
  flip_cube();

  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_basket(C_QUARTER_TURN);
}

void r_right_prime_turn() {
  rotate_basket(C_QUARTER_TURN);
  flip_cube();

  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_basket(C_QUARTER_TURN);
}

void r_right_double_turn() {
  rotate_basket(C_QUARTER_TURN);
  flip_cube();

  rotate_cube(HALF_TURN);

  flip_cube();
  rotate_basket(C_QUARTER_TURN);
}

void r_down_turn() {
  flip_cube();
  flip_cube();

  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);

  flip_cube();
  flip_cube();
}

void r_down_prime_turn() {
  flip_cube();
  flip_cube();

  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);

  flip_cube();
  flip_cube();
}

void r_down_double_turn() {
  flip_cube();
  flip_cube();

  rotate_cube(HALF_TURN);
  rotate_basket(HALF_TURN);

  flip_cube();
  flip_cube();
}

void r_up_turn() {
  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);
}

void r_up_prime_turn() {
  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);
}

void r_up_double_turn() {
  rotate_cube(HALF_TURN);
  rotate_basket(HALF_TURN);
}

void r_front_turn() {
  flip_cube();

  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();
}

void r_front_prime_turn() {
  flip_cube();

  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();
}

void r_front_double_turn() {
  flip_cube();

  rotate_cube(HALF_TURN);
  rotate_basket(HALF_TURN);

  flip_cube();
}

void r_back_turn() {
  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_cube(C_QUARTER_TURN);
  rotate_basket(CC_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();
}

void r_back_prime_turn() {
  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_cube(CC_QUARTER_TURN);
  rotate_basket(C_QUARTER_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();
}

void r_back_double_turn() {
  rotate_basket(HALF_TURN);
  flip_cube();

  rotate_cube(HALF_TURN);

  rotate_basket(HALF_TURN);
  flip_cube();
}
