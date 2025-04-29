#ifndef __GEN_H
#define __GEN_H

#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "../include/cube.h"

#define NUM_MOVES_S1 18
#define NUM_MOVES_S2 14
#define NUM_MOVES_S3 10
#define NUM_MOVES_S4 6

#define STAGE1_GOAL_STATE 0
#define STAGE2_GOAL_STATE 43740
#define STAGE3_GOAL_STATE -1
#define STAGE4_GOAL_STATE -1

#define STAGE1_NUM_PERMUTATIONS 2048
#define STAGE2_NUM_PERMUTATIONS 1082565
#define STAGE3_NUM_PERMUTATIONS 29400 
#define STAGE4_NUM_PERMUTATIONS 663552

#define STAGE1_TABLE_FILE "./tables/stage1.txt"
#define STAGE2_TABLE_FILE "./tables/stage2.txt"
#define STAGE3_TABLE_FILE "./tables/stage3.txt"
#define STAGE4_TABLE_FILE "./tables/stage4.txt"
#define PATH_LENGTH 20

enum STATUS { UNVISITED, VISITED };

#endif
