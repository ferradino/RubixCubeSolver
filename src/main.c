#include "../include/cube.h"
#include "../include/robot.h"
// #include "../include/solve.h"
#include <stdio.h>

void demo(robot_t robot) {
  robot.basket_motor.speed = 100;

  hover_center_tile(&robot.color_sensor_motor);
  open_color_sensor(&robot.color_sensor_motor);

  for (int i = 0; i < 4; i++) {
    hover_edge_tile(&robot.color_sensor_motor);
    rotate_basket(&robot.basket_motor, C_EIGTH_TURN);

    hover_corner_tile(&robot.color_sensor_motor);
    rotate_basket(&robot.basket_motor, C_EIGTH_TURN);
  }

  open_color_sensor(&robot.color_sensor_motor);
  robot.basket_motor.speed = 250;

  printf("**** Solving Cube! ****\n");

  unsigned char move_count = 3;
  moves_t solution[256] = { L, U2, Fp };
  solve_cube(&robot, solution, move_count);
}

int main(int argc, char* argv[]) {
  // Initialize the robot
  printf("**** Starting Robot! ****\n");
  robot_t robot = robot_init();

  printf("**** Robot Initialization Complete! ****\n");

  demo(robot);

  /*
  // Initialize Rubix Cube
  rubix_cube_t rubix_cube = rubix_cube_init(&robot);


  // Read the Rubix Cube
  printf("**** Reading In Cube! ****\n");
  read_rubix_cube_tile_colors(&robot, &rubix_cube);

  // Solve
  printf("**** Solving Cube! ****\n");
  moves_t solution[256];
  unsigned char move_count = solve(&rubix_cube, solution);
  */
  

  // Done
  printf("**** Rubix Cube Has Been Solved! ****\n");

  return 0;
}
