#include "../include/cube.h"
#include "../include/robot.h"
#include "../include/solve.h"
#include <stdio.h>
#include <string.h>

#include "../external/gen.h"

int main(int argc, char* argv[]) {

  // Flag to track if -g was provided
  bool g_flag = false;
  
  // Loop through all command-line arguments
  for (int i = 1; i < argc; i++) {
      // Check if the current argument is "-g"
      if (strcmp(argv[i], "-g") == 0) {
          g_flag = true;
      }
  }
  
  // Example of using the flag
  if (g_flag) {
    gen_tables();
  } else {
      printf("The -g flag was not provided\n");
      // Do something when -g flag is not present
  }

  // Initialize the robot
  printf("**** Starting Robot! ****\n");
  robot_t robot = robot_init();

  // Initialize Rubix Cube
  rubix_cube_t rubix_cube = rubix_cube_init(&robot);

  /*
  // Read the Rubix Cube
  printf("**** Reading In Cube! ****\n");
  read_rubix_cube_tile_colors(&robot, &rubix_cube);

  // Solve
  printf("**** Solving Cube! ****\n");
  moves_t solution[256];
  unsigned char move_count = solve(&rubix_cube, solution);
  solve_cube(&robot, solution, move_count);

  // Done
  printf("**** Rubix Cube Has Been Solved! ****\n");
  */

  gen_tables();

  return 0;
}
