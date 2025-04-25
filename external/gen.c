#include <stdio.h>
#include <assert.h>
#include "gen.h"

void write_table_to_file(const int32_t *lookup, const char file[PATH_LENGTH], const int32_t n) {
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

void generate_stage_one_table(const rubix_cube_t cube) {
    const moves_t moves[NUM_MOVES_S1] = { L, L2, Lp, R, R2, Rp, F, F2, Fp, B, B2, Bp, U, U2, Up, D, D2, Dp }; 
    const moves_t i_moves[NUM_MOVES_S1] = { Lp, L2, L, Rp, R2, R, Fp, F2, F, Bp, B2, B, Up, U2, U, Dp, D2, D };
    int32_t lookup[STAGE1_NUM_PERMUTATIONS];
    int32_t permutations[STAGE1_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE1_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[STAGE1_GOAL_STATE] = VISITED; 
    enqueue(&queue, STAGE1_GOAL_STATE);

    rubix_cube_t tmp = cube;

    while (!isEmpty(&queue)) {
        uint32_t idx = dequeue(&queue);

        //convert int to cube state
        // if odd number of 1 bits, the 12 edge is bad
        get_state_s1(tmp.edge_orientation, idx);
        
        for (int i = 0; i < NUM_MOVES_S1; i++) {
            rubix_cube_t tmp2 = tmp;

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

int32_t factorial(int32_t n) {
  if (n == 0) return 1;
  return n * factorial(n-1);
}

int32_t combination(int32_t n, int32_t k) {
  return factorial(n) / (factorial(k) * factorial(n - k));
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

  // get index of edges (combinatorial indexing)
  int32_t c = (combination(tmp[3], C1) + combination(tmp[2], C2) + combination(tmp[1], C3) + combination(tmp[0], C4));

  // return index of cube state
  return (c * (int32_t) 2187) + idx;
}

void get_state_s2(unsigned char *corner_orientations, unsigned char *slice, int32_t idx) { 
  int32_t r = idx % 2187;
  int32_t sum, base = 3;

  // Get corner orientations from cube state
  for (int i = 0; i < NUM_CORNERS - 1; i++) {
    corner_orientations[i] = (unsigned char) (r % base);
    sum += corner_orientations[i];
    r /= base;
  }

  // Determine orientation of final corner
  corner_orientations[NUM_CORNERS - 1] = (base - sum % base) % base;
  
  // Get the edges where the UD slice edges are located
  // Mark with a 1
  uint32_t c;
  idx /= 2187;
  for (int i = 4; i > 0; i--) {
    for (int j = NUM_EDGES - 1; j >= 0; j--) {
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

int32_t get_index_s3(const corner_t *corner_positions, const edge_t *edge_positions) {}
void get_state_s3(corner_t *corner_positions, edge_t *edge_positions, int32_t idx) {}

// Corner in correct position and edges are in correct orbit (or slice)
// This is permutations!!!
// Also in book!!!
void generate_stage_three_table(const rubix_cube_t cube) {
    const moves_t moves[NUM_MOVES_S3] = { L, L2, Lp, R, R2, Rp, F2, B2, U2, D2 };
    const moves_t i_moves[NUM_MOVES_S3] = { Lp, L2, L, Rp, R2, R, F2, B2, U2, D2 };
    int32_t lookup[STAGE3_NUM_PERMUTATIONS];
    int32_t permutations[STAGE3_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE3_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    lookup[STAGE3_GOAL_STATE] = VISITED;
    enqueue(&queue, STAGE3_GOAL_STATE);

    rubix_cube_t tmp;

    while (!isEmpty(&queue)) {
        int32_t idx = dequeue(&queue);

        get_state_s3(tmp.corner_positions, tmp.edge_positions, idx);

        for (int i = 0; i < NUM_MOVES_S3; i++) {
            rubix_cube_t tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index_s3(tmp2.corner_positions, tmp2.edge_positions);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = i_moves[i];
                enqueue(&queue, idx);
            }
        }
    }

    write_table_to_file(lookup, STAGE3_TABLE_FILE, STAGE3_NUM_PERMUTATIONS);
}

// Corner is 4th stage can have only 3 positions it can go to
// 4 positions - the 4 positions that are half turn on any face
// Orbit has 24 permutations

// 96 - comes from two sets of 4 corner orbit permutations. Other orbit can only have a certain set of permutations (1 of 6 possible)
// (4! * 4!) / 6 = 96
//
// get the permutation of both 4 corner orbits (value from 0 - 23 for both, multiply them, and then divide by 1 of 6 permutation of one of the orbits)


// Edges have 3 orbits (middle slice on each orbit)
// 2 of the axis is independent (3 is almost)
// (4! * 4! * 4!) / 2

// index is 4 values (corner, and the 3 edges)
// corner * 6912 + (xslice * 288 + yslice * 12 + zslice) assuming 0 slice counts only to 11

// This is permutations!!!
// Also in book!!
// Factoradic Representation
// First place is 0!, 1!, 2!, 3!, 4! ... (it is for both) Korner's method again

int32_t get_index_s4(const corner_t *corner_positions, const edge_t *edge_positions) {
  corner_t c_orbit[4] = { UFL, UBR, DFR, DBL },
           c_orbit_two[4] = { UFR, UBL, DFL, DBR };

  
  /* example, 3:4:1:0:1:0! stands for
  = 3×5! + 4×4! + 1×3! + 0×2! + 1×1! + 0×0! 
  = ((((3×5 + 4)×4 + 1)×3 + 0)×2 + 1)×1 + 0
  =  46310 */
  int32_t c_orbit_perm = ((corner_positions[c_orbit[0]] * 3 + corner_positions[c_orbit[1]]) * 2 + corner_positions[c_orbit[2]]) * 1 + corner_positions[c_orbit[3]]; 
  int32_t c_orbit_two_perm = ((corner_positions[c_orbit_two[0]] * 3 + corner_positions[c_orbit_two[1]]) * 2 + corner_positions[c_orbit_two[2]]) * 1 + corner_positions[c_orbit_two[3]]; 

  int32_t c_idx = (c_orbit_perm * c_orbit_two_perm) / 6; // Ask about the 6

  edge_t e_orbit_x[4] = { UL, UR, DL, DR },
         e_orbit_y[4] = { UF, UB, DF, DB },
         e_orbit_z[4] = { FL, BL, BR, FR };

  int32_t e_orbit_x_perm = ((edge_positions[e_orbit_x[0]] * 3 + edge_positions[e_orbit_x[1]]) * 2 + edge_positions[e_orbit_x[2]]) * 1 + edge_positions[e_orbit_x[3]]; 
  int32_t e_orbit_y_perm = ((edge_positions[e_orbit_y[0]] * 3 + edge_positions[e_orbit_y[1]]) * 2 + edge_positions[e_orbit_y[2]]) * 1 + edge_positions[e_orbit_y[3]]; 
  int32_t e_orbit_z_perm = ((edge_positions[e_orbit_z[0]] * 3 + edge_positions[e_orbit_z[1]]) * 2 + edge_positions[e_orbit_z[2]]) * 1 + edge_positions[e_orbit_z[3]]; 

  /* Ask about doing it this way as well
  int e_idx = (e_orbit_x_perm * e_orbit_y_perm * e_orbit_z_perm) / 2;
  return (c_idx * 6912) + e_idx; */

  return ((c_idx * 6912) + (e_orbit_x_perm * 288 + e_orbit_y_perm * 12 + e_orbit_z_perm));
}

void get_state_s4(corner_t *corner_positions, edge_t *edge_positions, int32_t idx) {
  uint32_t tmp_orbit = (idx % 6912);
  uint32_t tmp_corner = (idx - tmp_orbit) / 6912;

  // Get the two corner orbit permutations
  

  // Get the three edge orbit permutations
}

void generate_stage_four_table(const rubix_cube_t cube) {
    const moves_t moves[NUM_MOVES_S4] = { L2, R2, F2, B2, U2, D2 };
    const moves_t i_moves[NUM_MOVES_S4] = { L2, R2, F2, B2, U2, D2 };
    int32_t lookup[STAGE4_NUM_PERMUTATIONS];
    int32_t permutations[STAGE4_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE4_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    lookup[STAGE4_GOAL_STATE] = VISITED;
    enqueue(&queue, STAGE4_GOAL_STATE);

    rubix_cube_t tmp;

    while (!isEmpty(&queue)) {
        uint32_t idx = dequeue(&queue);

        get_state_s4(tmp.corner_positions, tmp.edge_positions, idx);

        for (int i = 0; i < NUM_MOVES_S4; i++) {
            rubix_cube_t tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index_s4(tmp2.corner_positions, tmp2.edge_positions);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = i_moves[i];
                enqueue(&queue, idx);
            }
        }
    }

    write_table_to_file(lookup, STAGE4_TABLE_FILE, STAGE4_NUM_PERMUTATIONS);
}

void gen_tables(void) {
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

    generate_stage_one_table(cube);
    generate_stage_two_table(cube);
    // generate_stage_three_table(cube);
    generate_stage_four_table(cube);
}

// PowerPoint on Project - (finals week)
// Either W, TH, F after 1pm and let Dr. Bob know by Monday (21st)
// No more then a hour (assuming people show up lol)
// What the project was about
// Tell about the issues, how did you deal with them, and how could someone modify it (or finish it)
