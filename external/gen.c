#include <stdio.h>
#include <assert.h>
#include "gen.h"

void write_table_to_file(const unsigned char lookup[PART1_NUM_PERMUTATIONS]) {
    FILE *fp = fopen(PART1_TABLE_FILE, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < PART1_NUM_PERMUTATIONS; i++) {
        fprintf(fp, "%c", lookup[i]);
    }
    fclose(fp);
}

unsigned short get_index(const unsigned char perm[NUM_EDGES]) {
    unsigned short idx = 0;
    for (int i = 0; i < NUM_EDGES; i++) {
        idx |= (perm[i] << i);
    }
    return idx;
}

void generate_stage_one_table(rubix_cube_t cube) {
    moves_t moves[PART1_MOVES] = { L, R, F, B, U, D }; 
    unsigned char lookup[PART1_NUM_PERMUTATIONS];
    unsigned char permutations[PART1_NUM_PERMUTATIONS];

    for (int i = 0; i < PART1_NUM_PERMUTATIONS; i++) {
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

        for (int i = 0; i < PART1_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup);
}

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

    printf("calling gen 1 tables");

    generate_stage_one_table(cube);
}
