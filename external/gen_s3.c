#include "gen.h"

const corner_t 
        c_orbit[4] = { UFL, UBR, DFR, DBL },
        c_orbit_two[4] = { UFR, UBL, DFL, DBR };

const edge_t e_slice_x[4] = { UL, UR, DL, DR },
       e_slice_y[4] = { UF, UB, DF, DB },
       e_slice_z[4] = { FL, BL, BR, FR };

void write_table_to_file(const moves_t *lookup, const char file[PATH_LENGTH], const int32_t n) {
  FILE *fp = fopen(file, "w"); 
  assert(fp != NULL);
  for (int i = 0; i < n; i++) {
      fprintf(fp, "%d\n", lookup[i]);
  }
  fclose(fp);
}

int32_t combination(int32_t n, int32_t k) {
  if (n < k)
    return 0;

  return (f_table[n] / f_table[k]) * f_table[n - k];
}

int32_t get_index_s3(unsigned char *orbit, unsigned char *slice) {
    const int32_t C8 = 8, C7 = 7, C6 = 6, C5 = 5, C4 = 4, C3 = 3, C2 = 2, C1 = 1; 
  
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
    return (e * (int32_t) 4900) + c;
  }
  
  void get_state_s3(unsigned char *orbit, unsigned char *slice, int32_t idx) {
    int32_t c = idx % 4900;
    int32_t e = idx / 4900;
  }
  
  // Corner in correct position (corner piece must be in its orbit...whic position inside orbit does not matter here) and edges are in correct orbit (or slice)
  // This is permutations!!!
  // Also in book!!!
  void generate_stage_three_table(const rubix_cube_t cube) {
      const moves_t moves[NUM_MOVES_S3] = { L, L2, Lp, R, R2, Rp, F2, B2, U2, D2 };
      const moves_t i_moves[NUM_MOVES_S3] = { Lp, L2, L, Rp, R2, R, F2, B2, U2, D2 };
      moves_t lookup[STAGE3_NUM_PERMUTATIONS];
      int8_t permutations[STAGE3_NUM_PERMUTATIONS];
      unsigned char orbit[NUM_CORNERS] = { 1, 1, 1, 1, 1, 1, 1, 1 };
      unsigned char slice[NUM_EDGES] = { 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1};
  
      for (int i = 0; i < STAGE3_NUM_PERMUTATIONS; i++) {
        permutations[i] = UNVISITED;
      }
  
      queue_t queue;
      initQueue(&queue);
  
      permutations[STAGE3_GOAL_STATE] = VISITED;
      enqueue(&queue, STAGE3_GOAL_STATE);
  
      rubix_cube_t tmp = cube;
  
      while (!isEmpty(&queue)) {
          int32_t idx = dequeue(&queue);
  
          // reset the orbit arrray
          for (int i = 0; i < NUM_CORNERS; i++) {
            orbit[i] = 0;
          }
  
          // reset the slice array
          for (int i = 0; i < NUM_EDGES; i++) {
            slice[i] = 0;
          }
  
          get_state_s3(orbit, slice, idx);
  
          for (int i = 0; i < NUM_MOVES_S3; i++) {
              rubix_cube_t tmp2 = tmp;
  
              make_move(&tmp2, moves[i]);
  
              // Set UD slice to 0 sine we aren't concerned with this slice anymore
              slice[UF] = 0;
              slice[UB] = 0;
              slice[DF] = 0;
              slice[DB] = 0;
  
              /* Check if any of the corners are in their correct orbit (positions doesn't matter) */
              for (int i = 0; i < NUM_CORNERS / 2; i++) {
                orbit[c_orbit[i]] = 0;
                corner_t corner = tmp2.corner_positions[c_orbit[i]];
                if (corner == UFL || corner == UBR || corner == DFR || corner == DBL) {
                  orbit[c_orbit[i]] = 1;
                }
  
                orbit[c_orbit_two[i]] = 0;
                corner = tmp2.corner_positions[c_orbit_two[i]];
                if (corner == UFR || corner == UBL || corner == DFL || corner == DBR) {
                  orbit[c_orbit_two[i]] = 1;
                }
              }
              
              /* Check if any of the edges are in their correct slices 
               * (LR and FB slices...just not UD since this one done previously) */
              for (int i = 0; i < NUM_EDGES / 3; i++) {
                slice[e_slice_x[i]] = 0; 
                edge_t edge = tmp2.edge_positions[e_slice_x[i]];
                if (edge == UL || edge == UR || edge == DL || edge == DR) {
                  slice[e_slice_x[i]] = 1;
                }
  
                slice[e_slice_z[i]] = 0;
                edge = tmp2.edge_positions[e_slice_z[i]];
                if (edge == FL || edge == BL || edge == BR || edge == FR) {
                  slice[e_slice_z[i]] = 1;
                }
              }
  
              idx = get_index_s3(orbit, slice);
  
              if (permutations[idx] == UNVISITED) {
                  permutations[idx] = 1;
                  lookup[idx] = i_moves[i];
                  enqueue(&queue, idx);
              }
          }
      }
  
      write_table_to_file(lookup, STAGE3_TABLE_FILE, STAGE3_NUM_PERMUTATIONS);
  }

int main(void) {
  rubix_cube_t cube = {
      .corner_orientation = { 0, 0, 0, 0, 0, 0, 0, 0 },
      .corner_positions = { UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR },
      .edge_orientation = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      .edge_positions = { UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR },
  };

  generate_stage_three_table(cube);

  return 0;
}
