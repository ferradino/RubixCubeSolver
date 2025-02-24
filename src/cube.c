#include "../include/cube.h"
#include <stdio.h>

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

  set_edge_position_colors(rubix_cube);
  set_corner_position_colors(rubix_cube);
}

void set_edge_position_colors(RubixCube *rubix_cube) {
  rubix_cube->edge_positions[UF].colors[0] = rubix_cube->tile_colors[1]; 
  rubix_cube->edge_positions[UF].colors[1] = rubix_cube->tile_colors[21]; 

  rubix_cube->edge_positions[UR].colors[0] = rubix_cube->tile_colors[2];
  rubix_cube->edge_positions[UR].colors[1] = rubix_cube->tile_colors[48];

  rubix_cube->edge_positions[UB].colors[0] = rubix_cube->tile_colors[3];
  rubix_cube->edge_positions[UB].colors[1] = rubix_cube->tile_colors[39];

  rubix_cube->edge_positions[UL].colors[0] = rubix_cube->tile_colors[4];
  rubix_cube->edge_positions[UL].colors[1] = rubix_cube->tile_colors[30];

  rubix_cube->edge_positions[DF].colors[0] = rubix_cube->tile_colors[12];
  rubix_cube->edge_positions[DF].colors[1] = rubix_cube->tile_colors[19];

  rubix_cube->edge_positions[DR].colors[0] = rubix_cube->tile_colors[11];
  rubix_cube->edge_positions[DR].colors[1] = rubix_cube->tile_colors[46];

  rubix_cube->edge_positions[DB].colors[0] = rubix_cube->tile_colors[10];
  rubix_cube->edge_positions[DB].colors[1] = rubix_cube->tile_colors[37];

  rubix_cube->edge_positions[DL].colors[0] = rubix_cube->tile_colors[13];
  rubix_cube->edge_positions[DL].colors[1] = rubix_cube->tile_colors[28];

  rubix_cube->edge_positions[FL].colors[0] = rubix_cube->tile_colors[22];
  rubix_cube->edge_positions[FL].colors[1] = rubix_cube->tile_colors[29];

  rubix_cube->edge_positions[BL].colors[0] = rubix_cube->tile_colors[38];
  rubix_cube->edge_positions[BL].colors[1] = rubix_cube->tile_colors[31];

  rubix_cube->edge_positions[BR].colors[0] = rubix_cube->tile_colors[40];
  rubix_cube->edge_positions[BR].colors[1] = rubix_cube->tile_colors[47];

  rubix_cube->edge_positions[FR].colors[0] = rubix_cube->tile_colors[20];
  rubix_cube->edge_positions[FR].colors[1] = rubix_cube->tile_colors[49];
}

void set_corner_position_colors(RubixCube *rubix_cube) {
  rubix_cube->corner_positions[UFR].colors[0] = rubix_cube->tile_colors[5];
  rubix_cube->corner_positions[UFR].colors[1] = rubix_cube->tile_colors[24];
  rubix_cube->corner_positions[UFR].colors[2] = rubix_cube->tile_colors[52];

  rubix_cube->corner_positions[UFL].colors[0] = rubix_cube->tile_colors[8];
  rubix_cube->corner_positions[UFL].colors[1] = rubix_cube->tile_colors[25];
  rubix_cube->corner_positions[UFL].colors[2] = rubix_cube->tile_colors[33];

  rubix_cube->corner_positions[UBL].colors[0] = rubix_cube->tile_colors[7];
  rubix_cube->corner_positions[UBL].colors[1] = rubix_cube->tile_colors[42];
  rubix_cube->corner_positions[UBL].colors[2] = rubix_cube->tile_colors[34];

  rubix_cube->corner_positions[UBR].colors[0] = rubix_cube->tile_colors[6];
  rubix_cube->corner_positions[UBR].colors[1] = rubix_cube->tile_colors[43];
  rubix_cube->corner_positions[UBR].colors[2] = rubix_cube->tile_colors[31];

  rubix_cube->corner_positions[DFR].colors[0] = rubix_cube->tile_colors[15];
  rubix_cube->corner_positions[DFR].colors[1] = rubix_cube->tile_colors[23];
  rubix_cube->corner_positions[DFR].colors[2] = rubix_cube->tile_colors[53];

  rubix_cube->corner_positions[DFL].colors[0] = rubix_cube->tile_colors[16];
  rubix_cube->corner_positions[DFL].colors[1] = rubix_cube->tile_colors[26];
  rubix_cube->corner_positions[DFL].colors[2] = rubix_cube->tile_colors[22];

  rubix_cube->corner_positions[DBL].colors[0] = rubix_cube->tile_colors[17];
  rubix_cube->corner_positions[DBL].colors[1] = rubix_cube->tile_colors[41];
  rubix_cube->corner_positions[DBL].colors[2] = rubix_cube->tile_colors[35];

  rubix_cube->corner_positions[DBR].colors[0] = rubix_cube->tile_colors[12];
  rubix_cube->corner_positions[DBR].colors[1] = rubix_cube->tile_colors[44];
  rubix_cube->corner_positions[DBR].colors[2] = rubix_cube->tile_colors[50];
}

void left_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[UL];

  rubix_cube->edge_positions[UL] = rubix_cube->edge_positions[BL];
  rubix_cube->edge_positions[BL] = rubix_cube->edge_positions[DL];
  rubix_cube->edge_positions[DL] = rubix_cube->edge_positions[FL];
  rubix_cube->edge_positions[FL] = edge_temp;

  corner_temp = rubix_cube->corner_positions[UFL];

  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[UBL];
  /* Fix colors for UFL corner */
  color_temp = rubix_cube->corner_positions[UFL].colors[0];
  rubix_cube->corner_positions[UFL].colors[0] = rubix_cube->corner_positions[UFL].colors[1];
  rubix_cube->corner_positions[UFL].colors[1] = color_temp;

  rubix_cube->corner_positions[UBL] = rubix_cube->corner_positions[DBL];
  /* Fix colors for UBL corner */
  color_temp = rubix_cube->corner_positions[UBL].colors[0];
  rubix_cube->corner_positions[UBL].colors[0] = rubix_cube->corner_positions[UFL].colors[1];
  rubix_cube->corner_positions[UBL].colors[1] = color_temp;

  rubix_cube->corner_positions[DBL] = rubix_cube->corner_positions[DFL];
  /* Fix colors for DBL corner */
  color_temp = rubix_cube->corner_positions[DBL].colors[0];
  rubix_cube->corner_positions[DBL].colors[0] = rubix_cube->corner_positions[DFL].colors[1];
  rubix_cube->corner_positions[DBL].colors[1] = color_temp;

  rubix_cube->corner_positions[DFL] = corner_temp;
  /* Fix colors for DFL corner */
  color_temp = rubix_cube->corner_positions[DFL].colors[0];
  rubix_cube->corner_positions[DFL].colors[0] = rubix_cube->corner_positions[DFL].colors[1];
  rubix_cube->corner_positions[DFL].colors[1] = color_temp;
}

void left_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void left_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}


void right_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[UR];

  rubix_cube->edge_positions[UR] = rubix_cube->edge_positions[FR];
  rubix_cube->edge_positions[FR] = rubix_cube->edge_positions[DR];
  rubix_cube->edge_positions[DR] = rubix_cube->edge_positions[BR];
  rubix_cube->edge_positions[BR] = edge_temp;

  corner_temp = rubix_cube->corner_positions[UFR];

  rubix_cube->corner_positions[UFR] = rubix_cube->corner_positions[DFR];
  /* Fix colors for UFR corner */
  color_temp = rubix_cube->corner_positions[UFR].colors[0];
  rubix_cube->corner_positions[UFR].colors[0] = rubix_cube->corner_positions[UFR].colors[1];
  rubix_cube->corner_positions[UFR].colors[0] = color_temp;

  rubix_cube->corner_positions[DFR] = rubix_cube->corner_positions[DBR];
  /* Fix colors for DFR corner */
  color_temp = rubix_cube->corner_positions[DFR].colors[0];
  rubix_cube->corner_positions[DFR].colors[0] = rubix_cube->corner_positions[DFR].colors[1];
  rubix_cube->corner_positions[DFR].colors[0] = color_temp;

  rubix_cube->corner_positions[DBR] = rubix_cube->corner_positions[UBR];
  /* Fix colors for DBR corner */
  color_temp = rubix_cube->corner_positions[DBR].colors[0];
  rubix_cube->corner_positions[DBR].colors[0] = rubix_cube->corner_positions[DBR].colors[1];
  rubix_cube->corner_positions[DBL].colors[0] = color_temp;

  rubix_cube->corner_positions[UBR] = corner_temp;
  /* Fix colors for UBR corner */
  color_temp = rubix_cube->corner_positions[UBR].colors[0];
  rubix_cube->corner_positions[UBR].colors[0] = rubix_cube->corner_positions[DFL].colors[1];
  rubix_cube->corner_positions[UBR].colors[0] = color_temp;
}

void right_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void right_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}

void down_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[DF];

  rubix_cube->edge_positions[DF] = rubix_cube->edge_positions[DL];
  rubix_cube->edge_positions[DL] = rubix_cube->edge_positions[DB];
  rubix_cube->edge_positions[DB] = rubix_cube->edge_positions[DR];
  rubix_cube->edge_positions[DF] = edge_temp;

  corner_temp = rubix_cube->corner_positions[DFR];

  rubix_cube->corner_positions[DFR] = rubix_cube->corner_positions[DFL];
  /* Fix colors for DFR corner */
  color_temp = rubix_cube->corner_positions[DFR].colors[1];
  rubix_cube->corner_positions[DFR].colors[1] = rubix_cube->corner_positions[DFL].colors[2];
  rubix_cube->corner_positions[UFL].colors[2] = color_temp;

  rubix_cube->corner_positions[DFL] = rubix_cube->corner_positions[DBL];
  /* Fix colors for DFL corner */
  color_temp = rubix_cube->corner_positions[DFL].colors[1];
  rubix_cube->corner_positions[DFL].colors[1] = rubix_cube->corner_positions[DFL].colors[2];
  rubix_cube->corner_positions[DFL].colors[2] = color_temp;

  rubix_cube->corner_positions[DBL] = rubix_cube->corner_positions[DBR];
  /* Fix colors for DBL corner */
  color_temp = rubix_cube->corner_positions[DBL].colors[1];
  rubix_cube->corner_positions[DBL].colors[1] = rubix_cube->corner_positions[DBL].colors[2];
  rubix_cube->corner_positions[DBL].colors[2] = color_temp;

  rubix_cube->corner_positions[DBR] = corner_temp;
  /* Fix colors for DBR corner */
  color_temp = rubix_cube->corner_positions[DBR].colors[1];
  rubix_cube->corner_positions[DBR].colors[1] = rubix_cube->corner_positions[DBR].colors[2];
  rubix_cube->corner_positions[DBR].colors[2] = color_temp;
}

void down_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void down_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}

void up_turn(RubixCube *rubix_cube) { 
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[UL];

  rubix_cube->edge_positions[UL] = rubix_cube->edge_positions[UF];
  rubix_cube->edge_positions[UF] = rubix_cube->edge_positions[UR];
  rubix_cube->edge_positions[UR] = rubix_cube->edge_positions[UB];
  rubix_cube->edge_positions[UB] = edge_temp;

  corner_temp = rubix_cube->corner_positions[UFL];

  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[UFR];
  /* Fix colors for UFL corner */
  color_temp = rubix_cube->corner_positions[UFL].colors[1];
  rubix_cube->corner_positions[UFL].colors[1] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UFL].colors[2] = color_temp;

  rubix_cube->corner_positions[UFR] = rubix_cube->corner_positions[UBR];
  /* Fix colors for UBL corner */
  color_temp = rubix_cube->corner_positions[UBL].colors[1];
  rubix_cube->corner_positions[UBL].colors[1] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UBL].colors[2] = color_temp;

  rubix_cube->corner_positions[UBR] = rubix_cube->corner_positions[UBL];
  /* Fix colors for UBR corner */
  color_temp = rubix_cube->corner_positions[UBL].colors[1];
  rubix_cube->corner_positions[UBL].colors[1] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UBL].colors[2] = color_temp;

  rubix_cube->corner_positions[DBL] = corner_temp;
  /* Fix colors for UFR corner */
  color_temp = rubix_cube->corner_positions[UFL].colors[1];
  rubix_cube->corner_positions[UFL].colors[1] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UFL].colors[2] = color_temp;
}

void up_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void up_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}

void front_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[UF];

  rubix_cube->edge_positions[UF] = rubix_cube->edge_positions[FL];
  rubix_cube->edge_positions[FL] = rubix_cube->edge_positions[DF];
  rubix_cube->edge_positions[DF] = rubix_cube->edge_positions[FR];
  rubix_cube->edge_positions[FR] = edge_temp;

  corner_temp = rubix_cube->corner_positions[UFL];

  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[DFL];
  /* Fix colors for UFL corner */
  color_temp = rubix_cube->corner_positions[UFL].colors[0];
  rubix_cube->corner_positions[UFL].colors[0] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UFL].colors[2] = color_temp;

  rubix_cube->corner_positions[DFL] = rubix_cube->corner_positions[DFR];
  /* Fix colors for DFL corner */
  color_temp = rubix_cube->corner_positions[DFL].colors[0];
  rubix_cube->corner_positions[DFL].colors[0] = rubix_cube->corner_positions[DFL].colors[2];
  rubix_cube->corner_positions[DFL].colors[2] = color_temp;

  rubix_cube->corner_positions[DFR] = rubix_cube->corner_positions[UFR];
  /* Fix colors for DFR corner */
  color_temp = rubix_cube->corner_positions[DFR].colors[0];
  rubix_cube->corner_positions[DFR].colors[0] = rubix_cube->corner_positions[DFR].colors[2];
  rubix_cube->corner_positions[DFR].colors[2] = color_temp;

  rubix_cube->corner_positions[UFR] = corner_temp;
  /* Fix colors for UFR corner */
  color_temp = rubix_cube->corner_positions[UFR].colors[0];
  rubix_cube->corner_positions[UFR].colors[0] = rubix_cube->corner_positions[UFL].colors[2];
  rubix_cube->corner_positions[UFR].colors[2] = color_temp;
}

void front_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void front_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}

void back_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  edge_temp = rubix_cube->edge_positions[UB];

  rubix_cube->edge_positions[UB] = rubix_cube->edge_positions[BR];
  rubix_cube->edge_positions[BR] = rubix_cube->edge_positions[DB];
  rubix_cube->edge_positions[DB] = rubix_cube->edge_positions[BL];
  rubix_cube->edge_positions[BL] = edge_temp;

  corner_temp = rubix_cube->corner_positions[UBL];

  rubix_cube->corner_positions[UBL] = rubix_cube->corner_positions[UBR];
  /* Fix colors for UBL corner */
  color_temp = rubix_cube->corner_positions[UBL].colors[0];
  rubix_cube->corner_positions[UBL].colors[0] = rubix_cube->corner_positions[UBL].colors[2];
  rubix_cube->corner_positions[UBL].colors[2] = color_temp;

  rubix_cube->corner_positions[UBR] = rubix_cube->corner_positions[DBR];
  /* Fix colors for UBR corner */
  color_temp = rubix_cube->corner_positions[UBR].colors[0];
  rubix_cube->corner_positions[UBR].colors[0] = rubix_cube->corner_positions[UBR].colors[2];
  rubix_cube->corner_positions[UBR].colors[2] = color_temp;

  rubix_cube->corner_positions[DBR] = rubix_cube->corner_positions[DBL];
  /* Fix colors for DBR corner */
  color_temp = rubix_cube->corner_positions[DBR].colors[0];
  rubix_cube->corner_positions[DBR].colors[0] = rubix_cube->corner_positions[DBR].colors[2];
  rubix_cube->corner_positions[DBR].colors[2] = color_temp;

  rubix_cube->corner_positions[DBL] = corner_temp;
  /* Fix colors for DBL corner */
  color_temp = rubix_cube->corner_positions[DBL].colors[0];
  rubix_cube->corner_positions[DBL].colors[0] = rubix_cube->corner_positions[DBL].colors[2];
  rubix_cube->corner_positions[DBL].colors[2] = color_temp;
}

void back_prime_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 3; i++) {
    left_turn(rubix_cube);
  }
}

void back_double_turn(RubixCube *rubix_cube) {
  Edge edge_temp;  
  Corner corner_temp;  
  enum Color color_temp;

  for (int i = 0; i < 2; i++) {
    left_turn(rubix_cube);
  }
}
