#include <stdio.h>
#include <assert.h>
#include "gen.h"

void write_table_to_file(const unsigned char *lookup, const char *file, const int n) {
    FILE *fp = fopen(PART1_TABLE_FILE, "w"); 
    assert(fp != NULL);
    for (int i = 0; i < PART1_NUM_PERMUTATIONS; i++) {
        fprintf(fp, "%c", lookup[i]);
    }
    fclose(fp);
}

unsigned short get_index(const unsigned char *array, const int n) {
    unsigned short idx = 0;
    for (int i = 0; i < n; i++) {
        idx |= (array[i] << i);
    }
    return idx;
}

void generate_stage_one_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, R, F, B, U, D }; // make inverse move
    unsigned char lookup[PART1_NUM_PERMUTATIONS];
    unsigned char permutations[PART1_NUM_PERMUTATIONS];

    for (int i = 0; i < PART1_NUM_PERMUTATIONS; i++) {
      permutations[i] = UNVISITED;
    }

    queue_t queue;
    initQueue(&queue);

    permutations[0] = 1; 
    enqueue(&queue, cube); // store an integer instead

    unsigned short idx;
    rubix_cube_t tmp, tmp2;

    while (!isEmpty(&queue)) {
        tmp = dequeue(&queue);
        
        //convert int to cube state
        // if odd number of 1 bits, the 12 edge is bad
        
        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, PART1_NUM_PERMUTATIONS);
            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2); // enqueue index
            }
        }
    }

    write_table_to_file(lookup, PART1_TABLE_FILE, PART1_NUM_PERMUTATIONS);
}


// Blue and Green sticker must be on either blue/green face for the corner
void generate_stage_two_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, R, F, B, U2, D2 }; // fix these moves
    unsigned char lookup[PART2_NUM_PERMUTATIONS];
    unsigned char permutations[PART2_NUM_PERMUTATIONS];

    for (int i = 0; i < PART2_NUM_PERMUTATIONS; i++) {
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

            idx = get_index(tmp2.edge_orientation, PART2_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, PART2_TABLE_FILE, PART2_NUM_PERMUTATIONS);
}

// Corner in correct position and edges are in correct orbit (or slice)
void generate_stage_three_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L, R, F2, B2, U2, D2 }; 
    unsigned char lookup[PART3_NUM_PERMUTATIONS];
    unsigned char permutations[PART3_NUM_PERMUTATIONS];

    for (int i = 0; i < PART3_NUM_PERMUTATIONS; i++) {
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

            idx = get_index(tmp2.edge_orientation, PART3_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, PART3_TABLE_FILE, PART3_NUM_PERMUTATIONS);
}

void generate_stage_four_table(rubix_cube_t cube) {
    moves_t moves[NUM_MOVES] = { L2, R2, F2, B2, U2, D2 }; 
    unsigned char lookup[PART4_NUM_PERMUTATIONS];
    unsigned char permutations[PART4_NUM_PERMUTATIONS];

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

        for (int i = 0; i < NUM_MOVES; i++) {
            tmp2 = tmp;

            make_move(&tmp2, moves[i]);

            idx = get_index(tmp2.edge_orientation, PART4_NUM_PERMUTATIONS);

            if (permutations[idx] == UNVISITED) {
                permutations[idx] = 1;
                lookup[idx] = (moves[i] + (unsigned char) 2);
                enqueue(&queue, tmp2);
            }
        }
    }

    write_table_to_file(lookup, PART4_TABLE_FILE, PART4_NUM_PERMUTATIONS);
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

    generate_stage_one_table(cube);
    generate_stage_two_table(cube);
    generate_stage_three_table(cube);
    generate_stage_four_table(cube);
}
