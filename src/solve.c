#include <stdio.h>
#include <assert.h>
#include "../include/solve.h"
#include "../external/gen.h"

const corner_t 
        c_orbit[4] = { UFL, UBR, DFR, DBL },
        c_orbit_two[4] = { UFR, UBL, DFL, DBR };

const edge_t 
        e_slice_x[4] = { UL, UR, DL, DR },
        e_slice_y[4] = { UF, UB, DF, DB },
        e_slice_z[4] = { FL, BL, BR, FR };

int32_t factorial(int32_t n) {
    if (n == 0) return 1;
    return n * factorial(n-1);
}
  
int32_t combination(int32_t n, int32_t k) {
  return factorial(n) / (factorial(k) * factorial(n - k));
}

void read_file(int32_t *lookup, const char file[PATH_LENGTH], const int32_t n) {
  FILE *fp = fopen(file, "r");
  assert(fp != NULL);
  for (int i = 0; i < n; i++) {
    assert(fscanf(fp, "%d", &lookup[i]) == 1);
  }
  fclose(fp);
}

int32_t get_index_s1(const unsigned char *edge_orientation) {
  int32_t idx = 0;
  for (int i = 0; i < NUM_EDGES - 1; i++) {
      idx |= (edge_orientation[i] << i);
  }
  return idx;
}

void stage1(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE1_NUM_PERMUTATIONS];
  read_file(lookup, STAGE1_FILE, STAGE1_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != STAGE1_GOAL_STATE) {
    idx = get_index_s1(rubix_cube->edge_orientation); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

int32_t get_index_s2(const unsigned char *corner_orientations, unsigned char *slice) {
  const int32_t C4 = 4, C3 = 3, C2 = 2, C1 = 1; 
  int32_t idx, x = 3;

  // get index of corners (Horner's Method)
  idx = corner_orientations[0];
  for (int i = 1; i < NUM_CORNERS - 1; i++) {
    idx = (idx * x) + corner_orientations[i];
  }

  // find which edge holds the edges we want and make sure they are sorted
  unsigned char n = 4;
  edge_t tmp[n];
  for (int i = 0; i < NUM_EDGES; i++) {
    if (slice[i] == 1) {
      tmp[n-1] = i;
      n--;
    }
  }
}

void stage2(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  uint8_t slice[NUM_EDGES];
  int32_t lookup[STAGE2_NUM_PERMUTATIONS];
  read_file(lookup, STAGE2_FILE, STAGE2_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != STAGE2_GOAL_STATE) { 
    // find which edges old the UD slice edges
    for (int i = 0; i < NUM_EDGES; i++) {
      slice[i] = 0;
      if (rubix_cube->edge_positions[i] == UF || rubix_cube->edge_positions[i] == DF || rubix_cube->edge_positions[i] == DB || rubix_cube->edge_positions[i] == UB) {
        slice[i] = 1;
      }
    }
    idx = get_index_s2(rubix_cube->edge_orientation, slice); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

int32_t get_index_s3(unsigned char *orbit, unsigned char *slice) {
  const int32_t C8 = 8, C7 = 7, C6 = 6, C5 = 5, C4 = 4, C3 = 3, C2 = 2, C1 = 1; 
  int32_t idx;

  // find which edge holds the edges we want and make sure they are sorted
  unsigned char n = 8;
  corner_t c_tmp[n];
  for (int i = 0; i < NUM_CORNERS; i++) {
    if (orbit[i] == 1) {
      c_tmp[n-1] = i;
      n--;
    }
  }

  // index of edges (combinatorial indexing)
  int32_t c = (combination(c_tmp[7], C1) + combination(c_tmp[6], C2) + combination(c_tmp[5], C3) + combination(c_tmp[4], C4) + 
                combination(c_tmp[3], C5) + combination(c_tmp[2], C6) + combination(c_tmp[1], C7) + combination(c_tmp[0], C8));

  // find which edge holds the edges we want and make sure they are sorted
  n = 8;
  edge_t e_tmp[n];
  for (int i = 0; i < NUM_EDGES; i++) {
    if (slice[i] == 1) {
      e_tmp[n-1] = i;
      n--;
    }
  }

  // index of edges (combinatorial indexing)
  int32_t e = (combination(e_tmp[7], C1) + combination(e_tmp[6], C2) + combination(e_tmp[5], C3) + combination(e_tmp[4], C4) + 
                combination(e_tmp[3], C5) + combination(e_tmp[2], C6) + combination(e_tmp[1], C7) + combination(e_tmp[0], C8));

  // return index of cube state
  return (e * (int32_t) 2187) + c; // Need to figure what to replace 2187 with
}

void stage3(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE3_NUM_PERMUTATIONS];
  read_file(lookup, STAGE3_FILE, STAGE3_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != STAGE3_GOAL_STATE) {
    idx = get_index_s3(rubix_cube->corner_positions, rubix_cube->edge_positions); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

int32_t get_index_s4(const corner_t *corner_positions, const edge_t *edge_positions) {
  /* example, 3:4:1:0:1:0! stands for
 = 3×5! + 4×4! + 1×3! + 0×2! + 1×1! + 0×0! 
 = ((((3×5 + 4)×4 + 1)×3 + 0)×2 + 1)×1 + 0
 =  46310 */
 int32_t c_orbit_perm = ((corner_positions[c_orbit[0]] * 3 + corner_positions[c_orbit[1]]) * 2 + corner_positions[c_orbit[2]]) * 1 + corner_positions[c_orbit[3]]; 
 int32_t c_orbit_two_perm = ((corner_positions[c_orbit_two[0]] * 3 + corner_positions[c_orbit_two[1]]) * 2 + corner_positions[c_orbit_two[2]]) * 1 + corner_positions[c_orbit_two[3]]; 

 // make list of all the possible orbits
 int32_t c_idx = (c_orbit_perm * c_orbit_two_perm) / 6; // Ask about the 6


 int32_t e_slice_x_perm = ((edge_positions[e_slice_x[0]] * 3 + edge_positions[e_slice_x[1]]) * 2 + edge_positions[e_slice_x[2]]) * 1 + edge_positions[e_slice_x[3]]; 
 int32_t e_slice_y_perm = ((edge_positions[e_slice_y[0]] * 3 + edge_positions[e_slice_y[1]]) * 2 + edge_positions[e_slice_y[2]]) * 1 + edge_positions[e_slice_y[3]]; 
 int32_t e_slice_z_perm = ((edge_positions[e_slice_z[0]] * 3 + edge_positions[e_slice_z[1]]) * 2 + edge_positions[e_slice_z[2]]) * 1 + edge_positions[e_slice_z[3]]; 

 return ((c_idx * 6912) + (e_slice_x_perm * 288 + e_slice_y_perm * 12 + e_slice_z_perm));
}

void stage4(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE4_NUM_PERMUTATIONS];
  read_file(lookup, STAGE4_FILE, STAGE4_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != STAGE4_GOAL_STATE) {
    idx = get_index_s4(rubix_cube->corner_positions, rubix_cube->edge_positions); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

unsigned char solve(rubix_cube_t *rubix_cube, moves_t *solution) {
  unsigned char count = 0;
  stage1(rubix_cube, solution, &count);
  // stage2(rubix_cube, solution, &count);
  // stage3(rubix_cube, solution, &count);
  // stage4(rubix_cube, solution, &count);
  return count;
}

