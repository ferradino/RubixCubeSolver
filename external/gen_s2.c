#include "gen.h"
#include "../include/cube.h"

int32_t factorial(int32_t n) {
    if (n == 0) return 1;
    return n * factorial(n-1);
  }
  
  int32_t combination(int32_t n, int32_t k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
  }

  void write_table_to_file(const int32_t *lookup, const char file[PATH_LENGTH], const int32_t n) {
    FILE *fp = fopen(file, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", lookup[i]);
    }
    fclose(fp);
}
  
  int32_t get_index_s2(const unsigned char *corner_orientations, unsigned char *slice) {
    // get index of corners (Horner's Method)
    int32_t idx = corner_orientations[0];
    for (int i = 1; i < NUM_CORNERS - 1; i++) {
      idx = (idx * 3) + corner_orientations[i];
    }
  
    // find which edge holds the edges we want and make sure they are sorted
    int32_t n = 4, c = 0;
    for (int i = NUM_EDGES - 1; i >= 0; i--) {
      if (slice[i] == 1) {
        c += combination(i, n--);
      }
    }
  
    // return index of cube state
    return (c * (int32_t) 2187) + idx;
  }
  
  void get_state_s2(unsigned char *corner_orientations, unsigned char *slice, int32_t idx) { 
    int32_t r = idx % 2187;
    int32_t sum = 0, base = 3;
  
    // Get corner orientations from cube state
    for (int i = 0; i < NUM_CORNERS - 1; i++) {
      corner_orientations[i] = (unsigned char) (r % base);
      sum += corner_orientations[i];
      r /= base;
    }
  
    // Determine orientation of final corner
    corner_orientations[NUM_CORNERS - 1] = (base - (sum % base)) % base;
    
    // Get the edges where the UD slice edges are located
    // Mark with a 1
    int32_t c;
    idx /= 2187;
    for (int i = 4; i > 0; i--) {
      for (int j = NUM_EDGES; j >= 0; j--) {
        c = combination(j, i); 
        if (c <= idx) {
          slice[j] = 1;
          break;
        }
      }
      idx -= c;
    }
  }
  
  // Blue and Green sticker must be on either blue/green face for the corner
  void generate_stage_two_table(const rubix_cube_t cube) {
      const moves_t moves[NUM_MOVES_S2] = { L, L2, Lp, R, R2, Rp, F, F2, Fp, B, B2, Bp, U2, D2 };
      const moves_t i_moves[NUM_MOVES_S2] = { Lp, L2, L, Rp, R2, R, Fp, F2, F, Bp, B2, B, U2, D2 };
      int32_t lookup[STAGE2_NUM_PERMUTATIONS];
      int32_t permutations[STAGE2_NUM_PERMUTATIONS];
      unsigned char slice[NUM_EDGES] = { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};
  
      for (int i = 0; i < STAGE2_NUM_PERMUTATIONS; i++) {
        permutations[i] = UNVISITED;
      }
  
      queue_t queue;
      initQueue(&queue);
  
      lookup[STAGE2_GOAL_STATE] = VISITED;
      enqueue(&queue, STAGE2_GOAL_STATE);
  
      rubix_cube_t tmp = cube;
  
      while (!isEmpty(&queue)) {
          unsigned short idx = dequeue(&queue);
  
          // reset the slice array
          for (int i = 0; i < NUM_EDGES; i++) {
            slice[i] = 0;
          }
  
          get_state_s2(tmp.corner_orientation, slice, idx);
  
          for (int i = 0; i < NUM_MOVES_S2; i++) {
              rubix_cube_t tmp2 = tmp;
  
              make_move(&tmp2, moves[i]);
  
              // find which edges old the UD slice edges
              for (int i = 0; i < NUM_EDGES; i++) {
                slice[i] = 0;
                if (tmp2.edge_positions[i] == UF || tmp2.edge_positions[i] == DF || tmp2.edge_positions[i] == DB || tmp2.edge_positions[i] == UB) {
                  slice[i] = 1;
                }
              }
  
              idx = get_index_s2(tmp2.corner_orientation, slice);
  
              if (permutations[idx] == UNVISITED) {
                  permutations[idx] = VISITED;
                  lookup[idx] = i_moves[i];
                  enqueue(&queue, idx);
              }
          }
      }
  
      write_table_to_file(lookup, STAGE2_TABLE_FILE, STAGE2_NUM_PERMUTATIONS);
  }

int main(void) {
  rubix_cube_t cube = {
      .corner_orientation = { 0, 0, 0, 0, 0, 0, 0, 0 },
      .corner_positions = { UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR },
      .edge_orientation = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      .edge_positions = { UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR },
  };

  for (int i = 0; i < NUM_FACES; i++) {
      for (int j = 0; j < (NUM_TILES / NUM_FACES); j++) {
          cube.tile_colors[(NUM_FACES * i) + j] = i;
      }
  }

  generate_stage_two_table(cube);

  return 0;
}
