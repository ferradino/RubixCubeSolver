#include "gen_cube.h"

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
  unsigned char corner_temp, edge_temp;  

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

  /* Update Corner Orientation */
  corner_temp = rubix_cube->corner_orientation[UFL];
  rubix_cube->corner_orientation[UFL] = (rubix_cube->corner_orientation[UBL] + 1) % 3;
  rubix_cube->corner_orientation[UBL] = (rubix_cube->corner_orientation[DBL] + 2) % 3;
  rubix_cube->corner_orientation[DBL] = (rubix_cube->corner_orientation[DFL] + 2) % 3;
  rubix_cube->corner_orientation[DFL] = (corner_temp + 1) % 3;

  /* Update Edge Orientation */
  edge_temp = rubix_cube->edge_orientation[UL];
  rubix_cube->edge_orientation[UL] = rubix_cube->edge_orientation[BL];
  rubix_cube->edge_orientation[BL] = rubix_cube->edge_orientation[DL];
  rubix_cube->edge_orientation[DL] = rubix_cube->edge_orientation[FL];
  rubix_cube->edge_orientation[FL] = edge_temp ;
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
  unsigned char corner_temp, edge_temp;  

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

  /* Update Edge Orientation */
  edge_temp = rubix_cube->edge_orientation[UR];
  rubix_cube->edge_orientation[UR] = rubix_cube->edge_orientation[BR];
  rubix_cube->edge_orientation[BR] = rubix_cube->edge_orientation[DR];
  rubix_cube->edge_orientation[DR] = rubix_cube->edge_orientation[FR];
  rubix_cube->edge_orientation[FR] = edge_temp ;
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
  unsigned char corner_temp, edge_temp;  

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

  /* Update Corner Orientation */
  corner_temp = rubix_cube->corner_orientation[DFL];
  rubix_cube->corner_orientation[DFL] = rubix_cube->corner_orientation[DBL];
  rubix_cube->corner_orientation[DBL] = rubix_cube->corner_orientation[DBR];
  rubix_cube->corner_orientation[DBR] = rubix_cube->corner_orientation[DFR];
  rubix_cube->corner_orientation[DFR] = corner_pos_temp;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[DF];
  rubix_cube->edge_orientation[DF] = 1 - rubix_cube->edge_orientation[DL];
  rubix_cube->edge_orientation[DL] = 1 - rubix_cube->edge_orientation[DB];
  rubix_cube->edge_orientation[DB] = 1 - rubix_cube->edge_orientation[DR];
  rubix_cube->edge_orientation[DR] = 1 - edge_temp;
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
  unsigned char corner_temp, edge_temp;  

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

  /* Update Corner Orientation */
  corner_temp = rubix_cube->corner_orientation[UFL];
  rubix_cube->corner_orientation[UFL] = rubix_cube->corner_orientation[UFR];
  rubix_cube->corner_orientation[UFR] = rubix_cube->corner_orientation[UBR];
  rubix_cube->corner_orientation[UBR] = rubix_cube->corner_orientation[UBL];
  rubix_cube->corner_orientation[UBL] = corner_pos_temp;

  /* Update edge orientation */
  edge_temp = rubix_cube->edge_orientation[UF];
  rubix_cube->edge_orientation[UF] = 1 - rubix_cube->edge_orientation[UR];
  rubix_cube->edge_orientation[UR] = 1 - rubix_cube->edge_orientation[UB];
  rubix_cube->edge_orientation[UB] = 1 - rubix_cube->edge_orientation[UL];
  rubix_cube->edge_orientation[UL] = 1 - edge_temp;
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
  rubix_cube->edge_orientation[UF] = rubix_cube->edge_orientation[FL];
  rubix_cube->edge_orientation[FL] = rubix_cube->edge_orientation[DF];
  rubix_cube->edge_orientation[DF] = rubix_cube->edge_orientation[FR];
  rubix_cube->edge_orientation[FR] = edge_temp;
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
  rubix_cube->edge_orientation[UB] = rubix_cube->edge_orientation[BR];
  rubix_cube->edge_orientation[BR] = rubix_cube->edge_orientation[DB];
  rubix_cube->edge_orientation[DB] = rubix_cube->edge_orientation[BL];
  rubix_cube->edge_orientation[BL] = edge_temp;
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
