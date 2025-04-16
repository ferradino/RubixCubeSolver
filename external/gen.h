#ifndef __GEN_H
#define __GEN_H

#include "queue.h"
#include "../include/cube.h"

#define NUM_MOVES_S1 18
#define NUM_MOVES_S2 14
#define NUM_MOVES_S3 10
#define NUM_MOVES_S4 6
#define NUM_MOVES 18
#define STAGE1_NUM_PERMUTATIONS 2048
#define STAGE1_TABLE_FILE "./external/tables/stage1.txt"
#define STAGE2_NUM_PERMUTATIONS 1082565
#define STAGE2_TABLE_FILE "./external/tables/stage2.txt"
#define STAGE3_NUM_PERMUTATIONS 29400 
#define STAGE3_TABLE_FILE "./external/tables/stage3.txt"
#define STAGE4_NUM_PERMUTATIONS 663552
#define STAGE4_TABLE_FILE "./external/tables/stage4.txt"

enum STATUS { UNVISITED, VISITED };

void gen_tables(void);
void generate_stage_one_table(rubix_cube_t cube);
void generate_stage_two_table(rubix_cube_t cube);
void generate_stage_three_table(rubix_cube_t cube);
void generate_stage_four_table(rubix_cube_t cube);

int32_t get_index_s1(const unsigned char *array);
int32_t get_index_s2(const unsigned char *corner_orientations, const edge_t *edge_positions, unsigned char *slice, int32_t *pos);
int32_t get_index_s3(const corner_t *corner_positions, const edge_t *edge_positions, int32_t *pos);
int32_t get_index_s4(const edge_t *edge_positions);
void get_state_s1(unsigned char *array, const int32_t idx);
void get_state_s2(unsigned char *corner_orientations, edge_t *edge_positions, unsigned char *slice, int32_t idx, int32_t pos);
void get_state_s3(corner_t *corner_positions, edge_t *edge_positions, int32_t idx, int32_t pos);
void get_state_s4(edge_t *edge_positions, int32_t idx);

void write_table_to_file(const int32_t *lookup, const char file[28], const int32_t n);

#endif
