#ifndef __GEN_H
#define __GEN_H

#include "queue.h"
#include "../include/cube.h"

#define NUM_MOVES 6
#define PART1_NUM_PERMUTATIONS 2048
#define PART1_TABLE_FILE "./external/tables/stage1.txt"
#define PART2_NUM_PERMUTATIONS 1082565
#define PART2_TABLE_FILE "./external/tables/stage2.txt"
#define PART3_NUM_PERMUTATIONS 29400 
#define PART3_TABLE_FILE "./external/tables/stage3.txt"
#define PART4_NUM_PERMUTATIONS 663552
#define PART4_TABLE_FILE "./external/tables/stage4.txt"

enum STATUS { UNVISITED, VISITED };

void gen_tables(void);
void generate_stage_one_table(rubix_cube_t cube);
void generate_stage_two_table(rubix_cube_t cube);
void generate_stage_three_table(rubix_cube_t cube);
void generate_stage_four_table(rubix_cube_t cube);

unsigned short get_index(const unsigned char *array, const int n);
void write_table_to_file(const unsigned char *lookup, const char file[28], const int n);

#endif
