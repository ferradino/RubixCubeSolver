#include "../include/cube.h"
#include <stdio.h>

void get_initial_position(RubixCube *rubix_cube) {}
void get_initial_orientation(RubixCube *rubix_cube) {}

void rubix_cube_init(RubixCube *rubix_cube) {
  read_rubix_cube_tile_colors(rubix_cube);
  get_initial_position(rubix_cube);
  get_initial_orientation(rubix_cube);
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
      rotate_basket(C_QUARTER_TURN);
      flip_cube();
      rotate_basket(CC_QUARTER_TURN);
    }
  }

  rotate_basket(HALF_TURN);
  flip_cube();
  rotate_basket(CC_QUARTER_TURN);
}

void left_turn(RubixCube *rubix_cube) {
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char corner_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[UFL];
  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[UBL];
  rubix_cube->corner_positions[UBL] = rubix_cube->corner_positions[DBL];
  rubix_cube->corner_positions[DBL] = rubix_cube->corner_positions[DFL];
  rubix_cube->corner_positions[DFL] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[UL];
  rubix_cube->edge_positions[UL] = rubix_cube->edge_positions[BL];
  rubix_cube->edge_positions[BL] = rubix_cube->edge_positions[DL];
  rubix_cube->edge_positions[DL] = rubix_cube->edge_positions[FL];
  rubix_cube->edge_positions[FL] = edge_pos_temp ;
  
  /* Update corner orientation */
  corner_temp = rubix_cube->corner_orientation[UFL];
  rubix_cube->corner_orientation[UFL] = (rubix_cube->corner_orientation[UBL] + 1) % 3;
  rubix_cube->corner_orientation[UBL] = (rubix_cube->corner_orientation[DBL] + 2) % 3;
  rubix_cube->corner_orientation[DBL] = (rubix_cube->corner_orientation[DFL] + 2) % 3;
  rubix_cube->corner_orientation[DFL] = (corner_temp + 1) % 3;

  /* Update tile color */
  color_temp = rubix_cube->tile_colors[wBL];
  rubix_cube->tile_colors[wBL] = rubix_cube->tile_colors[gTR];
  rubix_cube->tile_colors[gTR] = rubix_cube->tile_colors[yBL];
  rubix_cube->tile_colors[yBL] = rubix_cube->tile_colors[bBL];
  rubix_cube->tile_colors[bBL] = color_temp;

  color_temp = rubix_cube->tile_colors[wTL];
  rubix_cube->tile_colors[wTL] = rubix_cube->tile_colors[gBR];
  rubix_cube->tile_colors[gBR] = rubix_cube->tile_colors[yTL];
  rubix_cube->tile_colors[yTL] = rubix_cube->tile_colors[bTL];
  rubix_cube->tile_colors[bTL] = color_temp;

  color_temp = rubix_cube->tile_colors[wL];
  rubix_cube->tile_colors[wL] = rubix_cube->tile_colors[gR];
  rubix_cube->tile_colors[gR] = rubix_cube->tile_colors[yL];
  rubix_cube->tile_colors[yL] = rubix_cube->tile_colors[bL];
  rubix_cube->tile_colors[bL] = color_temp;

  color_temp = rubix_cube->tile_colors[rT];
  rubix_cube->tile_colors[rT] = rubix_cube->tile_colors[rL];
  rubix_cube->tile_colors[rL] = rubix_cube->tile_colors[rB];
  rubix_cube->tile_colors[rB] = rubix_cube->tile_colors[rR];
  rubix_cube->tile_colors[rR] = color_temp;

  color_temp = rubix_cube->tile_colors[rTL];
  rubix_cube->tile_colors[rTL] = rubix_cube->tile_colors[rBL];
  rubix_cube->tile_colors[rBL] = rubix_cube->tile_colors[rBR];
  rubix_cube->tile_colors[rBR] = rubix_cube->tile_colors[rTR];
  rubix_cube->tile_colors[rTR] = color_temp;
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
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char corner_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[UFR];
  rubix_cube->corner_positions[UFR] = rubix_cube->corner_positions[UBR];
  rubix_cube->corner_positions[UBR] = rubix_cube->corner_positions[DBR];
  rubix_cube->corner_positions[DBR] = rubix_cube->corner_positions[DFR];
  rubix_cube->corner_positions[DFR] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[UR];
  rubix_cube->edge_positions[UR] = rubix_cube->edge_positions[BR];
  rubix_cube->edge_positions[BR] = rubix_cube->edge_positions[DR];
  rubix_cube->edge_positions[DR] = rubix_cube->edge_positions[FL];
  rubix_cube->edge_positions[FR] = edge_pos_temp ;
  
  /* Update corner orientation */
  corner_temp = rubix_cube->corner_orientation[UFR];
  rubix_cube->corner_orientation[UFR] = (rubix_cube->corner_orientation[DFR] + 2) % 3;
  rubix_cube->corner_orientation[DFR] = (rubix_cube->corner_orientation[DBR] + 2) % 3;
  rubix_cube->corner_orientation[DBR] = (rubix_cube->corner_orientation[UBR] + 1) % 3;
  rubix_cube->corner_orientation[UBR] = (corner_temp + 1) % 3;

  /* Update tile color */
  color_temp = rubix_cube->tile_colors[wTR];
  rubix_cube->tile_colors[wTR] = rubix_cube->tile_colors[bTR];
  rubix_cube->tile_colors[bTR] = rubix_cube->tile_colors[yTR];
  rubix_cube->tile_colors[yTR] = rubix_cube->tile_colors[gBL];
  rubix_cube->tile_colors[gBL] = color_temp;

  color_temp = rubix_cube->tile_colors[wBR];
  rubix_cube->tile_colors[wBR] = rubix_cube->tile_colors[bBR];
  rubix_cube->tile_colors[bBR] = rubix_cube->tile_colors[yBR];
  rubix_cube->tile_colors[yBR] = rubix_cube->tile_colors[gTL];
  rubix_cube->tile_colors[gTL] = color_temp;

  color_temp = rubix_cube->tile_colors[wR];
  rubix_cube->tile_colors[wR] = rubix_cube->tile_colors[bR];
  rubix_cube->tile_colors[bR] = rubix_cube->tile_colors[yR];
  rubix_cube->tile_colors[yR] = rubix_cube->tile_colors[gL];
  rubix_cube->tile_colors[gL] = color_temp;

  color_temp = rubix_cube->tile_colors[oTL];
  rubix_cube->tile_colors[oTL] = rubix_cube->tile_colors[oBL];
  rubix_cube->tile_colors[oBL] = rubix_cube->tile_colors[oBR];
  rubix_cube->tile_colors[oBR] = rubix_cube->tile_colors[oTR];
  rubix_cube->tile_colors[oTR] = color_temp;

  color_temp = rubix_cube->tile_colors[oT];
  rubix_cube->tile_colors[oT] = rubix_cube->tile_colors[oL];
  rubix_cube->tile_colors[oL] = rubix_cube->tile_colors[oB];
  rubix_cube->tile_colors[oB] = rubix_cube->tile_colors[oR];
  rubix_cube->tile_colors[oR] = color_temp;
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
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char edge_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[DFL];
  rubix_cube->corner_positions[DFL] = rubix_cube->corner_positions[DBL];
  rubix_cube->corner_positions[DBL] = rubix_cube->corner_positions[DBR];
  rubix_cube->corner_positions[DBR] = rubix_cube->corner_positions[DFR];
  rubix_cube->corner_positions[DFR] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[DF];
  rubix_cube->edge_positions[DF] = rubix_cube->edge_positions[DL];
  rubix_cube->edge_positions[DL] = rubix_cube->edge_positions[DB];
  rubix_cube->edge_positions[DB] = rubix_cube->edge_positions[DR];
  rubix_cube->edge_positions[DR] = edge_pos_temp ;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[DF];
  rubix_cube->edge_orientation[DF] = (rubix_cube->edge_orientation[DL] + 1) % 2;
  rubix_cube->edge_orientation[DL] = (rubix_cube->edge_orientation[DB] + 1) % 2;
  rubix_cube->edge_orientation[DB] = (rubix_cube->edge_orientation[DR] + 1) % 2;
  rubix_cube->edge_orientation[DR] = (edge_temp + 1) % 2;

  /* Update tile color */
  color_temp = rubix_cube->tile_colors[bBR];
  rubix_cube->tile_colors[bBR] = rubix_cube->tile_colors[rBR];
  rubix_cube->tile_colors[rBR] = rubix_cube->tile_colors[gBR];
  rubix_cube->tile_colors[gBR] = rubix_cube->tile_colors[oBR];
  rubix_cube->tile_colors[oBR] = color_temp;

  color_temp = rubix_cube->tile_colors[bBL];
  rubix_cube->tile_colors[bBL] = rubix_cube->tile_colors[rBL];
  rubix_cube->tile_colors[rBL] = rubix_cube->tile_colors[gBL];
  rubix_cube->tile_colors[gBL] = rubix_cube->tile_colors[oBL];
  rubix_cube->tile_colors[oBL] = color_temp;

  color_temp = rubix_cube->tile_colors[bB];
  rubix_cube->tile_colors[bB] = rubix_cube->tile_colors[rB];
  rubix_cube->tile_colors[rB] = rubix_cube->tile_colors[gB];
  rubix_cube->tile_colors[gB] = rubix_cube->tile_colors[oR];
  rubix_cube->tile_colors[oR] = color_temp;

  color_temp = rubix_cube->tile_colors[yTL];
  rubix_cube->tile_colors[yTL] = rubix_cube->tile_colors[yBL];
  rubix_cube->tile_colors[yBL] = rubix_cube->tile_colors[yBR];
  rubix_cube->tile_colors[yBR] = rubix_cube->tile_colors[yTR];
  rubix_cube->tile_colors[yTR] = color_temp;

  color_temp = rubix_cube->tile_colors[yT];
  rubix_cube->tile_colors[yT] = rubix_cube->tile_colors[yL];
  rubix_cube->tile_colors[yL] = rubix_cube->tile_colors[yB];
  rubix_cube->tile_colors[yB] = rubix_cube->tile_colors[yR];
  rubix_cube->tile_colors[yR] = color_temp;
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
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char edge_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[UFL];
  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[UFR];
  rubix_cube->corner_positions[UFR] = rubix_cube->corner_positions[UBR];
  rubix_cube->corner_positions[UBR] = rubix_cube->corner_positions[UBL];
  rubix_cube->corner_positions[UBL] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[UF];
  rubix_cube->edge_positions[UF] = rubix_cube->edge_positions[UR];
  rubix_cube->edge_positions[UR] = rubix_cube->edge_positions[UB];
  rubix_cube->edge_positions[UB] = rubix_cube->edge_positions[UL];
  rubix_cube->edge_positions[UL] = edge_pos_temp ;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[UF];
  rubix_cube->edge_orientation[UF] = (rubix_cube->edge_orientation[UR] + 1) % 2;
  rubix_cube->edge_orientation[UR] = (rubix_cube->edge_orientation[UB] + 1) % 2;
  rubix_cube->edge_orientation[UB] = (rubix_cube->edge_orientation[UL] + 1) % 2;
  rubix_cube->edge_orientation[UL] = (edge_temp + 1) % 2;

  /* Update tile color */
  color_temp = rubix_cube->tile_colors[bTL];
  rubix_cube->tile_colors[bTL] = rubix_cube->tile_colors[oTL];
  rubix_cube->tile_colors[oTL] = rubix_cube->tile_colors[gTL];
  rubix_cube->tile_colors[gTL] = rubix_cube->tile_colors[rTL];
  rubix_cube->tile_colors[rTL] = color_temp;

  color_temp = rubix_cube->tile_colors[bTR];
  rubix_cube->tile_colors[bTR] = rubix_cube->tile_colors[oTR];
  rubix_cube->tile_colors[oTR] = rubix_cube->tile_colors[gTR];
  rubix_cube->tile_colors[gTR] = rubix_cube->tile_colors[rTR];
  rubix_cube->tile_colors[rTR] = color_temp;

  color_temp = rubix_cube->tile_colors[bT];
  rubix_cube->tile_colors[bT] = rubix_cube->tile_colors[oT];
  rubix_cube->tile_colors[oT] = rubix_cube->tile_colors[gT];
  rubix_cube->tile_colors[gT] = rubix_cube->tile_colors[rT];
  rubix_cube->tile_colors[rT] = color_temp;

  color_temp = rubix_cube->tile_colors[wTL];
  rubix_cube->tile_colors[wTL] = rubix_cube->tile_colors[wBL];
  rubix_cube->tile_colors[wBL] = rubix_cube->tile_colors[wBR];
  rubix_cube->tile_colors[wBR] = rubix_cube->tile_colors[wTR];
  rubix_cube->tile_colors[wTR] = color_temp;

  color_temp = rubix_cube->tile_colors[wT];
  rubix_cube->tile_colors[wT] = rubix_cube->tile_colors[wL];
  rubix_cube->tile_colors[wL] = rubix_cube->tile_colors[wB];
  rubix_cube->tile_colors[wB] = rubix_cube->tile_colors[wR];
  rubix_cube->tile_colors[wR] = color_temp;
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
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[UFL];
  rubix_cube->corner_positions[UFL] = rubix_cube->corner_positions[DFL];
  rubix_cube->corner_positions[DFL] = rubix_cube->corner_positions[DFR];
  rubix_cube->corner_positions[DFR] = rubix_cube->corner_positions[UFR];
  rubix_cube->corner_positions[UFR] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[UF];
  rubix_cube->edge_positions[UF] = rubix_cube->edge_positions[FL];
  rubix_cube->edge_positions[FL] = rubix_cube->edge_positions[DF];
  rubix_cube->edge_positions[DF] = rubix_cube->edge_positions[FR];
  rubix_cube->edge_positions[FR] = edge_pos_temp ;

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
  color_temp = rubix_cube->tile_colors[wBL];
  rubix_cube->tile_colors[wBL] = rubix_cube->tile_colors[rBR];
  rubix_cube->tile_colors[rBR] = rubix_cube->tile_colors[yTR];
  rubix_cube->tile_colors[yTR] = rubix_cube->tile_colors[oTL];
  rubix_cube->tile_colors[oTL] = color_temp;

  color_temp = rubix_cube->tile_colors[wBR];
  rubix_cube->tile_colors[wBR] = rubix_cube->tile_colors[rTR];
  rubix_cube->tile_colors[rTR] = rubix_cube->tile_colors[yTL];
  rubix_cube->tile_colors[yTL] = rubix_cube->tile_colors[oBL];
  rubix_cube->tile_colors[oBL] = color_temp;

  color_temp = rubix_cube->tile_colors[wB];
  rubix_cube->tile_colors[wB] = rubix_cube->tile_colors[rR];
  rubix_cube->tile_colors[rR] = rubix_cube->tile_colors[yT];
  rubix_cube->tile_colors[yT] = rubix_cube->tile_colors[oL];
  rubix_cube->tile_colors[oL] = color_temp;

  color_temp = rubix_cube->tile_colors[bTL];
  rubix_cube->tile_colors[bTL] = rubix_cube->tile_colors[bBL];
  rubix_cube->tile_colors[bBL] = rubix_cube->tile_colors[bBR];
  rubix_cube->tile_colors[bBR] = rubix_cube->tile_colors[bTR];
  rubix_cube->tile_colors[bTR] = color_temp;

  color_temp = rubix_cube->tile_colors[bT];
  rubix_cube->tile_colors[bT] = rubix_cube->tile_colors[bL];
  rubix_cube->tile_colors[bL] = rubix_cube->tile_colors[bB];
  rubix_cube->tile_colors[bB] = rubix_cube->tile_colors[bR];
  rubix_cube->tile_colors[bR] = color_temp;
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
  enum EDGE_POS edge_pos_temp;
  enum CORNER_POS corner_pos_temp;
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  enum Color color_temp;

  /* Update Corner Position */
  corner_pos_temp = rubix_cube->corner_positions[UBL];
  rubix_cube->corner_positions[UBL] = rubix_cube->corner_positions[UBR];
  rubix_cube->corner_positions[UBR] = rubix_cube->corner_positions[DBR];
  rubix_cube->corner_positions[DBR] = rubix_cube->corner_positions[DBL];
  rubix_cube->corner_positions[DBL] = corner_pos_temp;

  /* Update Edge Position */
  edge_pos_temp = rubix_cube->edge_positions[UB];
  rubix_cube->edge_positions[UB] = rubix_cube->edge_positions[BR];
  rubix_cube->edge_positions[BR] = rubix_cube->edge_positions[DB];
  rubix_cube->edge_positions[DB] = rubix_cube->edge_positions[BL];
  rubix_cube->edge_positions[BL] = edge_pos_temp ;
  
  /* Update corner orientation */
  corner_temp = rubix_cube->corner_orientation[UBL];
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
  color_temp = rubix_cube->tile_colors[wTL];
  rubix_cube->tile_colors[wTL] = rubix_cube->tile_colors[oTR];
  rubix_cube->tile_colors[oTR] = rubix_cube->tile_colors[yBR];
  rubix_cube->tile_colors[yBR] = rubix_cube->tile_colors[rBL];
  rubix_cube->tile_colors[rBL] = color_temp;

  color_temp = rubix_cube->tile_colors[wTR];
  rubix_cube->tile_colors[wTR] = rubix_cube->tile_colors[oBR];
  rubix_cube->tile_colors[oBR] = rubix_cube->tile_colors[yBL];
  rubix_cube->tile_colors[yBL] = rubix_cube->tile_colors[rTL];
  rubix_cube->tile_colors[rTL] = color_temp;

  color_temp = rubix_cube->tile_colors[wT];
  rubix_cube->tile_colors[wT] = rubix_cube->tile_colors[oR];
  rubix_cube->tile_colors[oR] = rubix_cube->tile_colors[yB];
  rubix_cube->tile_colors[yB] = rubix_cube->tile_colors[rL];
  rubix_cube->tile_colors[rL] = color_temp;

  color_temp = rubix_cube->tile_colors[gTL];
  rubix_cube->tile_colors[gTL] = rubix_cube->tile_colors[gBL];
  rubix_cube->tile_colors[gBL] = rubix_cube->tile_colors[gBR];
  rubix_cube->tile_colors[gBR] = rubix_cube->tile_colors[gTR];
  rubix_cube->tile_colors[gTR] = color_temp;

  color_temp = rubix_cube->tile_colors[gT];
  rubix_cube->tile_colors[gT] = rubix_cube->tile_colors[gL];
  rubix_cube->tile_colors[gL] = rubix_cube->tile_colors[gB];
  rubix_cube->tile_colors[gB] = rubix_cube->tile_colors[gR];
  rubix_cube->tile_colors[gR] = color_temp;
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
