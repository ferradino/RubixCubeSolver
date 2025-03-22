#include "../include/cube.h"
#include <stdio.h>

// void get_initial_orientation(RubixCube *rubix_cube);

void rubix_cube_init(RubixCube *rubix_cube) {
  for (int i = 0; i < NUM_EDGES; i++) {
    rubix_cube->edge_positions[i] = i;
  }

  for (int i = 0; i < NUM_CORNERS; i++) {
    rubix_cube->corner_positions[i] = i;
  }

  read_rubix_cube_tile_colors(rubix_cube);
  // get_initial_orientation(rubix_cube);
}

void read_rubix_cube_tile_colors(RubixCube *rubix_cube) {
  enum Color color; 

  for (int i = 0; i < NUM_FACES; i++) {
    color = read_center_tile_color();
    printf("%d", color);
    rubix_cube->tile_colors[i * 9] = color;

    for (int j = i * 9 + 1; i < i * 9 + 5; i++) {
      color = read_edge_tile_color();
      printf("%d", color);
      rubix_cube->tile_colors[j] = color;
      rotate_basket(C_QUARTER_TURN);
    }

    rotate_basket(C_EIGTH_TURN);

    for (int k = i * 9 + 5; i < i * 9 + 9; i++) {
      color = read_corner_tile_color();
      printf("%d", color);
      rubix_cube->tile_colors[k] = color;
      rotate_basket(C_QUARTER_TURN);
    }

    rotate_basket(C_EIGTH_TURN);

    if (i == 0) {
      flip_cube();
      flip_cube();
    } else if (i == 1) {
      rotate_basket(HALF_TURN);
      flip_cube();
      rotate_basket(HALF_TURN);
    } else {
      rotate_basket(CC_QUARTER_TURN);
      flip_cube();
      rotate_basket(C_QUARTER_TURN);
    }
  }

  rotate_basket(HALF_TURN);
  flip_cube();
  rotate_basket(HALF_TURN);
}

void left_turn(RubixCube *rubix_cube) {
  unsigned char corner_temp;  
  enum Color color_temp;
  
  corner_temp = rubix_cube->corner_orientation[UFL];

  /* Update corner orientation */
  rubix_cube->corner_orientation[UFL] = (rubix_cube->corner_orientation[UBL] + 1) % 3;
  rubix_cube->corner_orientation[UBL] = (rubix_cube->corner_orientation[DBL] + 2) % 3;
  rubix_cube->corner_orientation[DBL] = (rubix_cube->corner_orientation[DFL] + 2) % 3;
  rubix_cube->corner_orientation[DFL] = (corner_temp + 1) % 3;

  /* Update tile color */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void left_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void left_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}


void right_turn(RubixCube *rubix_cube) {
  unsigned char corner_temp;  
  enum Color color_temp;
  
  corner_temp = rubix_cube->corner_orientation[UFR];

  /* Update corner orientation */
  rubix_cube->corner_orientation[UFR] = (rubix_cube->corner_orientation[DFR] + 2) % 3;
  rubix_cube->corner_orientation[DFR] = (rubix_cube->corner_orientation[DBR] + 2) % 3;
  rubix_cube->corner_orientation[DBR] = (rubix_cube->corner_orientation[UBR] + 1) % 3;
  rubix_cube->corner_orientation[UBR] = (corner_temp + 1) % 3;

  /* Update tile color */
  /* !!!! Needs indexes updated */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void right_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    right_turn(rubix_cube);
  }
}

void right_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    right_turn(rubix_cube);
  }
}

void down_turn(RubixCube *rubix_cube) {
  unsigned char edge_temp;  
  enum Color color_temp;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[DF];
  rubix_cube->edge_orientation[DF] = (rubix_cube->edge_orientation[DL] + 1) % 2;
  rubix_cube->edge_orientation[DL] = (rubix_cube->edge_orientation[DB] + 1) % 2;
  rubix_cube->edge_orientation[DB] = (rubix_cube->edge_orientation[DR] + 1) % 2;
  rubix_cube->edge_orientation[DR] = (edge_temp + 1) % 2;

  /* Update tile color */
  /* !!!! Needs indexes updated */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void down_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    down_turn(rubix_cube);
  }
}

void down_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    down_turn(rubix_cube);
  }
}

void up_turn(RubixCube *rubix_cube) { 
  unsigned char edge_temp;  
  enum Color color_temp;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[UF];
  rubix_cube->edge_orientation[UF] = (rubix_cube->edge_orientation[UR] + 1) % 2;
  rubix_cube->edge_orientation[UR] = (rubix_cube->edge_orientation[UB] + 1) % 2;
  rubix_cube->edge_orientation[UB] = (rubix_cube->edge_orientation[UL] + 1) % 2;
  rubix_cube->edge_orientation[UL] = (edge_temp + 1) % 2;

  /* Update tile color */
  /* !!!! Needs indexes updated */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void up_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    up_turn(rubix_cube);
  }
}

void up_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    up_turn(rubix_cube);
  }
}

void front_turn(RubixCube *rubix_cube) {
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  enum Color color_temp;

  /* Update corner orientation */
  corner_temp = rubix_cube->corner_orientation[UFL];
  rubix_cube->corner_orientation[UFL] = (rubix_cube->corner_orientation[DFL] + 2) % 3;
  rubix_cube->corner_orientation[DFL] = (rubix_cube->corner_orientation[DFR] + 2) % 3;
  rubix_cube->corner_orientation[DFR] = (rubix_cube->corner_orientation[UFR] + 1) % 3;
  rubix_cube->corner_orientation[UFR] = (corner_temp + 1) % 3;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[UF];
  rubix_cube->edge_orientation[UF] = (rubix_cube->edge_orientation[FL] + 1) % 2;
  rubix_cube->edge_orientation[FL] = (rubix_cube->edge_orientation[DF] + 1) % 2;
  rubix_cube->edge_orientation[DF] = (rubix_cube->edge_orientation[FR] + 1) % 2;
  rubix_cube->edge_orientation[FR] = (edge_temp + 1) % 2;

  /* Update tile color */
  /* !!!! Needs indexes updated */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void front_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    front_turn(rubix_cube);
  }
}

void front_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    front_turn(rubix_cube);
  }
}

void back_turn(RubixCube *rubix_cube) {
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  enum Color color_temp;
  
  corner_temp = rubix_cube->corner_orientation[UBL];

  /* Update corner orientation */
  rubix_cube->corner_orientation[UBL] = (rubix_cube->corner_orientation[UBR] + 1) % 3;
  rubix_cube->corner_orientation[UBR] = (rubix_cube->corner_orientation[DBR] + 2) % 3;
  rubix_cube->corner_orientation[DBR] = (rubix_cube->corner_orientation[DBL] + 2) % 3;
  rubix_cube->corner_orientation[DBL] = (corner_temp + 1) % 3;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[UB];
  rubix_cube->edge_orientation[UB] = (rubix_cube->edge_orientation[BR] + 1) % 2;
  rubix_cube->edge_orientation[BR] = (rubix_cube->edge_orientation[DB] + 1) % 2;
  rubix_cube->edge_orientation[DB] = (rubix_cube->edge_orientation[BL] + 1) % 2;
  rubix_cube->edge_orientation[BL] = (edge_temp + 1) % 2;

  /* Update tile color */
  /* !!!! Needs indexes updated */
  color_temp = rubix_cube->tile_colors[5];
  rubix_cube->tile_colors[5] = rubix_cube->tile_colors[43];
  rubix_cube->tile_colors[43] = rubix_cube->tile_colors[17];
  rubix_cube->tile_colors[17] = rubix_cube->tile_colors[23];
  rubix_cube->tile_colors[23] = color_temp;

  color_temp = rubix_cube->tile_colors[8];
  rubix_cube->tile_colors[8] = rubix_cube->tile_colors[42];
  rubix_cube->tile_colors[42] = rubix_cube->tile_colors[16];
  rubix_cube->tile_colors[16] = rubix_cube->tile_colors[26];
  rubix_cube->tile_colors[26] = color_temp;

  color_temp = rubix_cube->tile_colors[4];
  rubix_cube->tile_colors[4] = rubix_cube->tile_colors[38];
  rubix_cube->tile_colors[38] = rubix_cube->tile_colors[13];
  rubix_cube->tile_colors[13] = rubix_cube->tile_colors[22];
  rubix_cube->tile_colors[22] = color_temp;

  color_temp = rubix_cube->tile_colors[30];
  rubix_cube->tile_colors[30] = rubix_cube->tile_colors[31];
  rubix_cube->tile_colors[31] = rubix_cube->tile_colors[47];
  rubix_cube->tile_colors[47] = rubix_cube->tile_colors[29];
  rubix_cube->tile_colors[29] = color_temp;

  color_temp = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[35] = rubix_cube->tile_colors[35];
  rubix_cube->tile_colors[32] = rubix_cube->tile_colors[33];
  rubix_cube->tile_colors[33] = rubix_cube->tile_colors[34];
  rubix_cube->tile_colors[33] = color_temp;
}

void back_prime_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    back_turn(rubix_cube);
  }
}

void back_double_turn(RubixCube *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    back_turn(rubix_cube);
  }
}
