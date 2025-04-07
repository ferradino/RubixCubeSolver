#include <stdio.h>
#include <assert.h>
#include "../include/solve.h"
#include "../external/gen.h"

void read_file(int32_t *lookup, const char file[18], const int32_t n) {
  FILE *fp = fopen(file, "r");
  assert(fp != NULL);
  for (int i = 0; i < n; i++) {
    assert(fscanf(fp, "%d", &lookup[i]) == 1);
  }
  fclose(fp);
}

void stage1(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE1_NUM_PERMUTATIONS];
  read_file(lookup, STAGE1_FILE, STAGE1_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != 0) {
    idx = get_index_s1(rubix_cube->edge_orientation); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

void stage2(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE2_NUM_PERMUTATIONS];
  read_file(lookup, STAGE2_FILE, STAGE2_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != 0) { // Change this
    // idx = get_index_s1(rubix_cube->edge_orientation); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

void stage3(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE3_NUM_PERMUTATIONS];
  read_file(lookup, STAGE3_FILE, STAGE3_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != 0) { // Change this
    // idx = get_index_s1(rubix_cube->edge_orientation); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

void stage4(rubix_cube_t *rubix_cube, moves_t *solution, unsigned char *count) {
  int32_t lookup[STAGE4_NUM_PERMUTATIONS];
  read_file(lookup, STAGE4_FILE, STAGE4_NUM_PERMUTATIONS);

  int32_t idx = -1; 
  while (idx != 0) { // Change this
    // idx = get_index_s1(rubix_cube->edge_orientation); 
    moves_t move = lookup[idx];
    make_move(rubix_cube, move);
    (*count)++;
  }
}

unsigned char solve(rubix_cube_t *rubix_cube, moves_t *solution) {
  unsigned char count = 0;
  stage1(rubix_cube, solution, &count);
  stage2(rubix_cube, solution, &count);
  stage3(rubix_cube, solution, &count);
  stage4(rubix_cube, solution, &count);
  return count;
}

