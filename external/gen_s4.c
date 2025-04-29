#include "gen.h"

const corner_t 
        c_orbit[4] = { UFL, UBR, DFR, DBL },
        c_orbit_two[4] = { UFR, UBL, DFL, DBR };

const edge_t 
        e_slice_x[4] = { UL, UR, DL, DR },
        e_slice_y[4] = { UF, UB, DF, DB },
        e_slice_z[4] = { FL, BL, BR, FR };

void write_table_to_file(const int32_t *lookup, const char file[PATH_LENGTH], const int32_t n) {
    FILE *fp = fopen(file, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", lookup[i]);
    }
    fclose(fp);
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
 
 void get_state_s4(corner_t *corner_positions, edge_t *edge_positions, int32_t idx) {
   uint32_t tmp_orbit_edge = (idx % 6912);
   uint32_t tmp_orbit_corner  = idx / 6912;
 
   // Get the two corner orbit permutations
   corner_t c_orbit[4] = { UFL, UBR, DFR, DBL },
            c_orbit_two[4] = { UFR, UBL, DFL, DBR };
   
 
   // Get the three edge orbit permutations
   // follow similar process for edge permutations
   int32_t e_slice_x_perm = tmp_orbit_edge / 288;
   tmp_orbit_edge %= 288; 
 
   int32_t e_slice_y_perm = tmp_orbit_edge / 12;
   int32_t e_slice_z_perm = tmp_orbit_edge % 12;
 
   edge_t e_slice_x[4] = { UL, UR, DL, DR },
          e_slice_y[4] = { UF, UB, DF, DB },
          e_slice_z[4] = { FL, BL, BR, FR };
 
   // Reversal of factoradic representation
   for (int i = 1; i < 5; i++) {
     edge_positions[e_slice_x[4-i]] = e_slice_x_perm % i;
     e_slice_x_perm /= i;
 
     edge_positions[e_slice_y[4-i]] = e_slice_y_perm % i;
     e_slice_y_perm /= i;
 
     edge_positions[e_slice_z[4-i]] = e_slice_z_perm % i;
     e_slice_z_perm /= i;
   }
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

    generate_stage_four_table(cube);

    return 0;
}