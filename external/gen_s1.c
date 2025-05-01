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
    for (int i = 0; i < NUM_EDGES; i++) {
      edge_orientation[i] = (idx >> i) & 1;
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

    generate_stage_one_table(cube);

    return 0;
}
