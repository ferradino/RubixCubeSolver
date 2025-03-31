#include "../include/cube.h"
#include <stdio.h>

corner_t get_corner_position(color_t c1,  color_t c2,  color_t c3) {
  corner_t pos = -1;

  if ((c1 == WHITE && c2 == BLUE && c3 == ORANGE) || (c1 == WHITE && c2 == ORANGE && c3 == BLUE) || (c1 == BLUE && c2 == ORANGE && c3 == WHITE) || (c1 == BLUE && c2 == WHITE && c3 == ORANGE) || (c1 == ORANGE && c2 == BLUE && c3 == WHITE) || (c1 == ORANGE && c2 == WHITE && c3 == BLUE)) {
    pos = UFR;
  } else if ((c1 == WHITE && c2 == BLUE && c3 == RED) || (c1 == WHITE && c2 == RED && c3 == BLUE) || (c1 == BLUE && c2 == RED && c3 == WHITE) || (c1 == BLUE && c2 == WHITE && c3 == RED) || (c1 == RED && c2 == BLUE && c3 == WHITE) || (c1 == RED && c2 == WHITE && c3 == BLUE)) {
    pos = UFL;
  } else if ((c1 == WHITE && c2 == GREEN && c3 == RED) || (c1 == WHITE && c2 == RED && c3 == GREEN) || (c1 == GREEN && c2 == RED && c3 == WHITE) || (c1 == GREEN && c2 == WHITE && c3 == RED) || (c1 == RED && c2 == GREEN && c3 == WHITE) || (c1 == RED && c2 == WHITE && c3 == GREEN)) {
    pos = UBL;
  } else if ((c1 == WHITE && c2 == GREEN && c3 == ORANGE) || (c1 == WHITE && c2 == ORANGE && c3 == GREEN) || (c1 == GREEN && c2 == ORANGE && c3 == WHITE) || (c1 == GREEN && c2 == WHITE && c3 == ORANGE) || (c1 == ORANGE && c2 == GREEN && c3 == WHITE) || (c1 == ORANGE && c2 == WHITE && c3 == GREEN)) {
    pos = UBR;
  } else if ((c1 == YELLOW && c2 == BLUE && c3 == ORANGE) || (c1 == YELLOW && c2 == ORANGE && c3 == BLUE) || (c1 == BLUE && c2 == ORANGE && c3 == YELLOW) || (c1 == BLUE && c2 == YELLOW && c3 == ORANGE) || (c1 == ORANGE && c2 == BLUE && c3 == YELLOW) || (c1 == ORANGE && c2 == YELLOW && c3 == BLUE)) {
    pos = DFR;
  } else if ((c1 == YELLOW && c2 == BLUE && c3 == RED) || (c1 == YELLOW && c2 == RED && c3 == BLUE) || (c1 == BLUE && c2 == RED && c3 == YELLOW) || (c1 == BLUE && c2 == YELLOW && c3 == RED) || (c1 == RED && c2 == BLUE && c3 == YELLOW) || (c1 == RED && c2 == YELLOW && c3 == BLUE)) {
    pos = DFL;
  } else if ((c1 == YELLOW && c2 == GREEN && c3 == RED) || (c1 == YELLOW && c2 == RED && c3 == GREEN) || (c1 == GREEN && c2 == RED && c3 == YELLOW) || (c1 == GREEN && c2 == YELLOW && c3 == RED) || (c1 == RED && c2 == GREEN && c3 == YELLOW) || (c1 == RED && c2 == YELLOW && c3 == GREEN)) {
    pos = DBL;
  } else if ((c1 == YELLOW && c2 == GREEN && c3 == ORANGE) || (c1 == YELLOW && c2 == ORANGE && c3 == GREEN) || (c1 == GREEN && c2 == ORANGE && c3 == YELLOW) || (c1 == GREEN && c2 == YELLOW && c3 == ORANGE) || (c1 == ORANGE && c2 == GREEN && c3 == YELLOW) || (c1 == ORANGE && c2 == YELLOW && c3 == GREEN)) {
    pos = DBR;
  }

  return pos;
}

edge_t get_edge_position(color_t c1,  color_t c2) {
  edge_t pos = -1;

  if ((c1 == WHITE && c2 == BLUE) || (c1 == BLUE && c2 == WHITE)) {
    pos = UF;
  } else if ((c1 == WHITE && c2 == RED) || (c1 == RED && c2 == WHITE)) {
    pos = UL;
  } else if ((c1 == WHITE && c2 == GREEN) || (c1 == GREEN && c2 == WHITE)) {
    pos = UB;
  } else if ((c1 == WHITE && c2 == ORANGE) || (c1 == ORANGE && c2 == WHITE)) {
    pos = UR;
  } else if ((c1 == YELLOW && c2 == BLUE) || (c1 == BLUE && c2 == YELLOW)) {
    pos = DF;
  } else if ((c1 == YELLOW && c2 == RED) || (c1 == RED && c2 == YELLOW)) {
    pos = DL;
  } else if ((c1 == YELLOW && c2 == GREEN) || (c1 == GREEN && c2 == YELLOW)) {
    pos = DB;
  } else if ((c1 == YELLOW && c2 == ORANGE) || (c1 == ORANGE && c2 == YELLOW)) {
    pos = DR;
  } else if ((c1 == BLUE && c2 == RED) || (c1 == RED && c2 == BLUE)) {
    pos = FL;
  } else if ((c1 == RED && c2 == GREEN) || (c1 == GREEN && c2 == RED)) {
    pos = BL;
  } else if ((c1 == GREEN && c2 == ORANGE) || (c1 == ORANGE && c2 == GREEN)) {
    pos = BR;
  } else if ((c1 == BLUE && c2 == ORANGE) || (c1 == ORANGE && c2 == BLUE)) {
    pos = FR;
  }

  return pos;
}

void get_initial_positions(rubix_cube_t *rubix_cube) {
  /* Edge Positions */
  rubix_cube->edge_positions[UF] = get_edge_position(rubix_cube->tile_colors[wB], rubix_cube->tile_colors[bT]);
  rubix_cube->edge_positions[UL] = get_edge_position(rubix_cube->tile_colors[wL], rubix_cube->tile_colors[rT]);
  rubix_cube->edge_positions[UB] = get_edge_position(rubix_cube->tile_colors[wT], rubix_cube->tile_colors[gT]);
  rubix_cube->edge_positions[UR] = get_edge_position(rubix_cube->tile_colors[wR], rubix_cube->tile_colors[oT]);

  rubix_cube->edge_positions[DF] = get_edge_position(rubix_cube->tile_colors[yT], rubix_cube->tile_colors[bB]);
  rubix_cube->edge_positions[DL] = get_edge_position(rubix_cube->tile_colors[yL], rubix_cube->tile_colors[rB]);
  rubix_cube->edge_positions[DB] = get_edge_position(rubix_cube->tile_colors[yB], rubix_cube->tile_colors[gB]);
  rubix_cube->edge_positions[DR] = get_edge_position(rubix_cube->tile_colors[yR], rubix_cube->tile_colors[oB]);

  rubix_cube->edge_positions[FL] = get_edge_position(rubix_cube->tile_colors[bL], rubix_cube->tile_colors[rR]);
  rubix_cube->edge_positions[BL] = get_edge_position(rubix_cube->tile_colors[gR], rubix_cube->tile_colors[rL]);
  rubix_cube->edge_positions[BR] = get_edge_position(rubix_cube->tile_colors[gL], rubix_cube->tile_colors[oR]);
  rubix_cube->edge_positions[FR] = get_edge_position(rubix_cube->tile_colors[bR], rubix_cube->tile_colors[oL]);

  /* Corner Positions */
  rubix_cube->corner_positions[UFR] = get_corner_position(rubix_cube->tile_colors[wBR], rubix_cube->tile_colors[bTR], rubix_cube->tile_colors[oTL]);
  rubix_cube->corner_positions[UFL] = get_corner_position(rubix_cube->tile_colors[wBL], rubix_cube->tile_colors[bTL], rubix_cube->tile_colors[rTR]);
  rubix_cube->corner_positions[UBL] = get_corner_position(rubix_cube->tile_colors[wTL], rubix_cube->tile_colors[gTR], rubix_cube->tile_colors[rTL]);
  rubix_cube->corner_positions[UBR] = get_corner_position(rubix_cube->tile_colors[wTR], rubix_cube->tile_colors[gTL], rubix_cube->tile_colors[oTR]);

  rubix_cube->corner_positions[DFR] = get_corner_position(rubix_cube->tile_colors[yTR], rubix_cube->tile_colors[bBR], rubix_cube->tile_colors[oBL]);
  rubix_cube->corner_positions[DFL] = get_corner_position(rubix_cube->tile_colors[yTL], rubix_cube->tile_colors[bBL], rubix_cube->tile_colors[rBR]);
  rubix_cube->corner_positions[DBL] = get_corner_position(rubix_cube->tile_colors[yBL], rubix_cube->tile_colors[gBR], rubix_cube->tile_colors[rBL]);
  rubix_cube->corner_positions[DBR] = get_corner_position(rubix_cube->tile_colors[yBR], rubix_cube->tile_colors[gBL], rubix_cube->tile_colors[oBR]);
}

unsigned char get_edge_orientation(const edge_t edge, const color_t tile_colors[NUM_TILES]) {
  unsigned char ori = -1;
  
  switch (edge) {
    case UF:
      ori = 0;
      break;
    case UL:
      ori = 0;
      break;
    case UB:
      ori = 0;
      break;
    case UR:
      ori = 0;
      break;
    case DF:
      ori = 0;
      break;
    case DL:
      ori = 0;
      break;
    case DB:
      ori = 0;
      break;
    case DR:
      ori = 0;
      break;
    case FL:
      if (tile_colors[bL] == RED || tile_colors[bL] == ORANGE || tile_colors[rR] == BLUE || tile_colors[rR] == GREEN) {
        ori = 1;
      } else {
        ori = 0;
      }
      break;
    case BL:
      if (tile_colors[gR] == RED || tile_colors[gR] == ORANGE || tile_colors[rL] == BLUE || tile_colors[rL] == GREEN) {
        ori = 1;
      } else {
        ori = 0;
      }
      break;
    case BR:
      if (tile_colors[gL] == RED || tile_colors[gL] == ORANGE || tile_colors[oR] == BLUE || tile_colors[oR] == GREEN) {
        ori = 1;
      } else {
        ori = 0;
      }
      break;
    case FR:
      if (tile_colors[bR] == RED || tile_colors[bR] == ORANGE || tile_colors[oL] == BLUE || tile_colors[oL] == GREEN) {
        ori = 1;
      } else {
        ori = 0;
      }
      break;
  }

  return ori;
}

unsigned char get_corner_orientation(const corner_t corner, const color_t tile_colors[NUM_TILES]) {
  unsigned char ori = -1;

  switch (corner) {
    case UFR:
      if (tile_colors[wBR] == WHITE || tile_colors[wBR] == YELLOW) {
        ori = 0;
      } else if (tile_colors[oTL] == WHITE || tile_colors[oTL] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case UFL:
      if (tile_colors[wBL] == WHITE || tile_colors[wBL] == YELLOW) {
        ori = 0;
      } else if (tile_colors[rTR] == WHITE || tile_colors[rTR] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case UBL:
      if (tile_colors[wTL] == WHITE || tile_colors[wTL] == YELLOW) {
        ori = 0;
      } else if (tile_colors[rTL] == WHITE || tile_colors[oTL] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case UBR:
      if (tile_colors[wTR] == WHITE || tile_colors[wTR] == YELLOW) {
        ori = 0;
      } else if (tile_colors[oTR] == WHITE || tile_colors[oTR] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case DFR:
      if (tile_colors[yTR] == WHITE || tile_colors[yTR] == YELLOW) {
        ori = 0;
      } else if (tile_colors[oBL] == WHITE || tile_colors[oBL] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case DFL:
      if (tile_colors[yTL] == WHITE || tile_colors[yTL] == YELLOW) {
        ori = 0;
      } else if (tile_colors[rBR] == WHITE || tile_colors[rBR] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case DBL:
      if (tile_colors[yBL] == WHITE || tile_colors[yBL] == YELLOW) {
        ori = 0;
      } else if (tile_colors[rBL] == WHITE || tile_colors[rBL] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
    case DBR:
      if (tile_colors[yBR] == WHITE || tile_colors[yBR] == YELLOW) {
        ori = 0;
      } else if (tile_colors[oBR] == WHITE || tile_colors[oBR] == YELLOW) {
        ori = 1;
      } else {
        ori = 2;
      }
      break;
  }

  return ori;
}

void get_initial_orientations(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < NUM_EDGES; i++) {
    rubix_cube->edge_orientation[i] = get_edge_orientation(i, rubix_cube->tile_colors);
  }

  for (int i = 0; i < NUM_CORNERS; i++) {
    rubix_cube->corner_orientation[i] = get_corner_orientation(i, rubix_cube->tile_colors);
  }
}

void read_rubix_cube_tile_colors(robot_t *robot, rubix_cube_t *rubix_cube) {
  motor_t *arm = &(robot->arm_motor);
  motor_t *basket = &(robot->basket_motor);
  color_t color; 

  for (int i = 0; i < NUM_FACES; i++) {
    color = read_center_tile_color(robot);
    printf("%d", color);
    rubix_cube->tile_colors[i * 9] = color;

    for (int j = i * 9 + 1; j < i * 9 + 5; j++) {
      color = read_edge_tile_color(robot);
      printf("%d", color);
      rubix_cube->tile_colors[j] = color;
      rotate_basket(basket, C_QUARTER_TURN);
    }

    rotate_basket(basket, C_EIGTH_TURN);

    for (int k = i * 9 + 5; k < i * 9 + 9; k++) {
      color = read_corner_tile_color(robot);
      printf("%d", color);
      rubix_cube->tile_colors[k] = color;
      rotate_basket(basket, C_QUARTER_TURN);
    }

    rotate_basket(basket, C_EIGTH_TURN);

    if (i == 0) {
      flip_cube(arm);
      flip_cube(arm);
    } else if (i == 1) {
      rotate_basket(basket, HALF_TURN);
      flip_cube(arm);
      rotate_basket(basket, HALF_TURN);
    } else {
      rotate_basket(basket, C_QUARTER_TURN);
      flip_cube(arm);
      rotate_basket(basket, CC_QUARTER_TURN);
    }
  }

  rotate_basket(basket, HALF_TURN);
  flip_cube(arm);
  rotate_basket(basket, CC_QUARTER_TURN);
}

rubix_cube_t rubix_cube_init(robot_t *robot) {
  rubix_cube_t rubix_cube = {0};

  get_initial_positions(&rubix_cube);
  get_initial_orientations(&rubix_cube);
  read_rubix_cube_tile_colors(robot, &rubix_cube);

  return rubix_cube;
}

void make_move(rubix_cube_t *rubix_cube, moves_t move) {
  switch (move) {
    case U: c_up_turn(rubix_cube); break;
    case U2: c_up_double_turn(rubix_cube); break;
    case Up: c_up_prime_turn(rubix_cube); break;
    case D: c_down_turn(rubix_cube); break;
    case D2: c_down_double_turn(rubix_cube); break;
    case Dp: c_down_prime_turn(rubix_cube); break;
    case R: c_right_turn(rubix_cube); break;
    case R2: c_right_double_turn(rubix_cube); break;
    case Rp: c_right_prime_turn(rubix_cube); break;
    case L: c_left_turn(rubix_cube); break;
    case L2: c_left_double_turn(rubix_cube); break;
    case Lp: c_left_prime_turn(rubix_cube); break;
    case F: c_front_turn(rubix_cube); break;
    case F2: c_front_double_turn(rubix_cube); break;
    case Fp: c_front_prime_turn(rubix_cube); break;
    case B: c_back_turn(rubix_cube); break;
    case B2: c_back_double_turn(rubix_cube); break;
    case Bp: c_back_prime_turn(rubix_cube); break;
  }
}

void c_left_turn(rubix_cube_t *rubix_cube) {
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char corner_temp;  
  color_t color_temp;

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

void c_left_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_left_turn(rubix_cube);
  }
}

void c_left_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_left_turn(rubix_cube);
  }
}


void c_right_turn(rubix_cube_t *rubix_cube) {
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char corner_temp;  
  color_t color_temp;

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
  rubix_cube->edge_positions[DR] = rubix_cube->edge_positions[FR];
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

void c_right_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_right_turn(rubix_cube);
  }
}

void c_right_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_right_turn(rubix_cube);
  }
}

void c_down_turn(rubix_cube_t *rubix_cube) {
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char edge_temp;  
  color_t color_temp;

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

void c_down_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_down_turn(rubix_cube);
  }
}

void c_down_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_down_turn(rubix_cube);
  }
}

void c_up_turn(rubix_cube_t *rubix_cube) { 
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char edge_temp;  
  color_t color_temp;

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

void c_up_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_up_turn(rubix_cube);
  }
}

void c_up_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_up_turn(rubix_cube);
  }
}

void c_front_turn(rubix_cube_t *rubix_cube) {
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  color_t color_temp;

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

void c_front_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_front_turn(rubix_cube);
  }
}

void c_front_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_front_turn(rubix_cube);
  }
}

void c_back_turn(rubix_cube_t *rubix_cube) {
  edge_t edge_pos_temp;
  corner_t corner_pos_temp;
  unsigned char edge_temp;  
  unsigned char corner_temp;  
  color_t color_temp;

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

void c_back_prime_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 3; i++) {
    c_back_turn(rubix_cube);
  }
}

void c_back_double_turn(rubix_cube_t *rubix_cube) {
  for (int i = 0; i < 2; i++) {
    c_back_turn(rubix_cube);
  }
}
