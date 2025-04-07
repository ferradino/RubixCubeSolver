#include <stdio.h>
#include <assert.h>
#include "gen.h"

void write_table_to_file(const int32_t *lookup, const char *file, const int32_t n) {
    FILE *fp = fopen(file, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", lookup[i]);
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

void get_state_s1(unsigned char *edge_orientation, const int32_t idx) {
    unsigned char count = 0;
    for (int i = NUM_EDGES  - 2; i >= 0; i--) {
      edge_orientation[i] = (idx & (1 << i)) >> i;
      if (edge_orientation[i] == 1) {
        count++;
      }
    }

    if ((count % 2) == 1) {
      edge_orientation[NUM_EDGES - 1] = 1;
    } else {
      edge_orientation[NUM_EDGES - 1] = 0;
    }
}

void generate_stage_one_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES_S1] = { L, L2, Lp, R, R2, Rp, F, F2, Fp, B, B2, Bp, U, U2, Up, D, D2, Dp }; 
    moves_t i_moves[NUM_MOVES_S1] = { Lp, L2, L, Rp, R2, R, Fp, F2, F, Bp, B2, B, Up, U2, U, Dp, D2, D };
    int32_t lookup[STAGE1_NUM_PERMUTATIONS];
    int32_t permutations[STAGE1_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE1_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[0] = 1; 
    enqueue(&queue, (int32_t) 0); // store an integer instead

    int32_t idx;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        idx = dequeue(&queue);

        //convert int to cube state
        // if odd number of 1 bits, the 12 edge is bad
        get_state_s1(tmp.edge_orientation, idx);
        
        for (int i = 0; i < NUM_MOVES_S1; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index_s1(tmp2.edge_orientation);
            if (permutations[idx] == UNVISITED) {
                permutations[idx] = VISITED;
                lookup[idx] = i_moves[i];
                enqueue(&queue, idx);
            }
        }
    }

    write_table_to_file(lookup, STAGE1_TABLE_FILE, STAGE1_NUM_PERMUTATIONS);
}


void swap(edge_t *edges, unsigned char j) {
  edge_t tmp = edges[j];
  edges[j] = edges[j+1];
  edges[j+1] = tmp;
}

void sort(edge_t *edges, unsigned char n) {
   for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - 1 - i; j++) {
          if (edges[j] > edges[j+1]) {
              swap(edges, j);
         }
      }
  }
}

int32_t factorial(int32_t n) {
  if (n == 0) return 1;
  return n * factorial(n-1);
}

int32_t combination(int32_t n, int32_t k) {
  return factorial(n) / (factorial(k) * factorial(n - k));
}

int32_t get_index_s2(const unsigned char *corner_orientations, const edge_t *edge_positions, int32_t *pos) {
  const int32_t C4 = 4, C3 = 3, C2 = 2, C1 = 1; 
  int32_t idx, factor = 1;

  for (int i = 0; i < NUM_CORNERS - 1; i++) {
    idx += (factor * corner_orientations[i]);
    factor *= 3;
  }

  const unsigned char n = 4;
  edge_t tmp[] = { edge_positions[UF], edge_positions[DF], edge_positions[DB], edge_positions[UB] };
  sort(tmp, n);

  edge_t tmp_pos[4];
  factor = 1;
  for (int i = 0; i < 4; i++) {
    if (tmp[i] == edge_positions[UF]) {
      tmp_pos[i] = UF;
    } else if (tmp[i] == edge_positions[DF]) {
      tmp_pos[i] = DF;
    } else if (tmp[i] == edge_positions[DB]) {
      tmp_pos[i] = DB;
    } else {
      tmp_pos[i] = UB;
    }

    (*pos) += (factor * tmp_pos[i]);
    factor *= 12;
  }

  int32_t c =  (combination(tmp[3], C1) + combination(tmp[2], C4) + combination(tmp[1], C3) + combination(tmp[0], C2));

  return (c * (int32_t) 2187) + idx;
}

void get_state_s2(unsigned char *corner_orientations, edge_t *edge_positions, int32_t idx, int32_t pos) { 
  int32_t base3 = (idx % 2187);
  int32_t sum;

  for (int i = 0; i < NUM_CORNERS - 1; i++) {
    corner_orientations[i] = (unsigned char) (base3 % 3);
    sum += corner_orientations[i];
    base3 /= 3;
  }

  corner_orientations[NUM_CORNERS - 1] = (3 - sum % 3) % 3;
   

  edge_t edges[4];
  for (int i = 0; i < 4; i++) {
    edges[i] = (pos % NUM_EDGES);
    pos /= NUM_EDGES;
  }
  
  uint32_t c;
  idx /= 2187;
  for (int i = 4; i > 0; i--) {
    for (int j = NUM_EDGES - 1; j >= 0; j--) {
      c = combination(j, i); 
      if (c <= idx) {
        edge_positions[edges[i - 1]] = j;
        break;
      }
    }
    idx -= c;
  }

}

// Blue and Green sticker must be on either blue/green face for the corner
void generate_stage_two_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES_S2] = { L, L2, Lp, R, R2, Rp, F, F2, Fp, B, B2, Bp, U2, D2 };
    moves_t i_moves[NUM_MOVES_S2] = { Lp, L2, L, Rp, R2, R, Fp, F2, F, Bp, B2, B, U2, D2 };
    int32_t lookup[STAGE2_NUM_PERMUTATIONS];
    int32_t permutations[STAGE2_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE2_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[0] = 1; 
    enqueue(&queue, (int32_t) 0); // fix the starting point
    enqueue(&queue, (int32_t) (combination(12, 4) - 1)); // fix the starting point

    unsigned short idx;
    int32_t pos;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        idx = dequeue(&queue);
        pos = dequeue(&queue);

        get_state_s2(tmp.corner_orientation, tmp.edge_positions, idx, pos);

        for (int i = 0; i < NUM_MOVES_S2; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index_s2(tmp2.corner_orientation, tmp2.edge_positions, &pos);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = i_moves[i];
                enqueue(&queue, idx);
                enqueue(&queue, pos);
            }
        }
    }

    write_table_to_file(lookup, STAGE2_TABLE_FILE, STAGE2_NUM_PERMUTATIONS);
}

/*
// Corner in correct position and edges are in correct orbit (or slice)
void generate_stage_three_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, R, F2, B2, U2, D2 }; 
    unsigned char lookup[STAGE3_NUM_PERMUTATIONS];
    unsigned char permutations[STAGE3_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE3_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[0] = 1; 
    enqueue(&queue, cube);

    unsigned short idx;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        tmp = dequeue(&queue);

        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, STAGE3_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, STAGE3_TABLE_FILE, STAGE3_NUM_PERMUTATIONS);
}

void generate_stage_four_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L2, R2, F2, B2, U2, D2 }; 
    unsigned char lookup[STAGE4_NUM_PERMUTATIONS];
    unsigned char permutations[STAGE4_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE1_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[0] = 1; 
    enqueue(&queue, cube);

    unsigned short idx;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        tmp = dequeue(&queue);

        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, STAGE4_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, STAGE4_TABLE_FILE, STAGE4_NUM_PERMUTATIONS);
}
*/

void gen_tables(void) {
    rubix_cube_t cube = {
        .corner_orientation = { 0, 0, 0, 0, 0, 0, 0, 0 },
        .corner_positions = { UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR },
        .edge_orientation = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        .edge_positions = { UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR },
    };

    unsigned char idx = 0;  
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            cube.tile_colors[idx] = i;
            idx++;
        }
    }

    generate_stage_one_table(cube);
    generate_stage_two_table(cube);
    // generate_stage_three_table(cube);
    // generate_stage_four_table(cube);
}
