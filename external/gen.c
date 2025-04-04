#include <stdio.h>
#include <assert.h>
#include "gen.h"

void write_table_to_file(const int32_t *lookup, const char *file, const int32_t n) {
    FILE *fp = fopen(STAGE1_TABLE_FILE, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < STAGE1_NUM_PERMUTATIONS; i++) {
        fprintf(fp, "%c", lookup[i]);
    }
    fclose(fp);
}

int32_t get_index(const unsigned char *array, const uint8_t n) {
    int32_t idx = 0;
    for (int i = 0; i < n - 1; i++) {
        idx |= (array[i] << i);
    }
    return idx;
}

void get_state(unsigned char *array, const uint8_t n, const int32_t idx) {
    unsigned char count = 0;
    for (int i = n - 2; i >= 0; i--) {
      array[i] = (idx >> i);
      if (array[i] == 1) {
        count++;
      }
    }

    if ((count % 2) == 1) {
      array[n-1] = 1;
    }
}

void generate_stage_one_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, L2, Lp, R, R2, Rp, F, F2, Fp, B, B2, Bp, U, U2, Up, D, D2, Dp }; 
    moves_t i_moves[NUM_MOVES] = { Lp, L2, L, Rp, R2, R, Fp, F2, F, Bp, B2, B, Up, U2, U, Dp, D2, D };
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
        get_state(tmp.edge_orientation, NUM_EDGES, idx);
        
        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, NUM_EDGES);
            if (permutations[idx] == UNVISITED) {
                permutations[idx] = VISITED;
                lookup[idx] = i_moves[i];
                enqueue(&queue, idx);
            }
        }
    }

    write_table_to_file(lookup, STAGE1_TABLE_FILE, STAGE1_NUM_PERMUTATIONS);
}

/*

// Blue and Green sticker must be on either blue/green face for the corner
void generate_stage_two_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, R, F, B, U2, D2 }; // fix these moves
    unsigned char lookup[STAGE2_NUM_PERMUTATIONS];
    unsigned char permutations[STAGE2_NUM_PERMUTATIONS];

    for (int i = 0; i < STAGE2_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    // Algorithms for taking combinations and making them positions (indexs)
    // corner is 7 base 3 * 495
    // kunth books have this algorithm (volume 4)
    // algorithms C
    // art of computer programming volume 4 fascile generating all partitions
    // look for gzip not necessarily pdf (also postscript)
    permutations[0] = 1; 
    enqueue(&queue, cube);

    unsigned short idx;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        tmp = dequeue(&queue);

        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, STAGE2_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, STAGE2_TABLE_FILE, STAGE2_NUM_PERMUTATIONS);
}

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
    // generate_stage_two_table(cube);
    // generate_stage_three_table(cube);
    // generate_stage_four_table(cube);
}
