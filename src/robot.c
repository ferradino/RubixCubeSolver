#include "robot.h"

void robot_init() {
  basket_motor_init();
  arm_motor_init();
  color_sensor_motor_init();
  color_sensor_init();
}

void rotate_basket() { 
  rotate(HALF_TURN);
}

void rotate_cube() {
  cover();
  rotate(QUARTER_TURN);
  open_arm();
}

void flip_Cube() {
  cover();
  flip();
  open_arm();
}

enum Color read_center_tile_color() {
  enum Color color;

  hover_center_tile();
  color = read_color();
  open_color_sensor();

  return color;
}

enum Color read_edge_tile_color() {
  enum Color color;

  hover_edge_tile();
  color = read_color();
  open_color_sensor();

  return color;
}

enum Color read_corner_tile_color() {
  enum Color color;

  hover_corner_tile();
  color = read_color();
  open_color_sensor();

  return color;
}