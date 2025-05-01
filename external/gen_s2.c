#include "gen.h"

void write_table_to_file(const int8_t *lookup, const char file[PATH_LENGTH],
                         const int32_t n) {
  FILE *fp = fopen(file, "w");
  assert(fp != NULL);
  for (int i = 0; i < n; i++) {
    fprintf(fp, "%d\n", lookup[i]);
  }
  fclose(fp);
}

int32_t combination(int32_t n, int32_t k) {
  if (n < k)
    return 0;

  return (f_table[n] / f_table[k]) * f_table[n - k];
}

int32_t get_index_s2(const unsigned char *corner_orientations,
                     unsigned char *slice) {
  
  // find which edge holds the edges we want and make sure they are sorted
  int32_t n = 4, idx = 0;
  for (int i = NUM_EDGES - 1; i >= 0; i--) {
    if (slice[i] == 1)
      idx += combination(i, n--);
  }
  // get index of corners (Horner's Method)
  for (int i = NUM_CORNERS - 2; i >= 0; i--) {
    idx = (idx * 3) + corner_orientations[i];
  }
  
  return idx;
}

void get_state_s2(unsigned char *corner_orientations, unsigned char *slice,
                  int32_t idx) {
  int32_t r = idx % 2187;
  int32_t sum = 0;

  // Get corner orientations from cube state
  for (int i = 0; i < NUM_CORNERS - 1; i++) {
    corner_orientations[i] = r % 3;
    r /= 3;
    sum += corner_orientations[i];
  }

  // Determine orientation of final corner
  corner_orientations[NUM_CORNERS - 1] = (3 - (sum % 3)) % 3;

  // Get the edges where the UD slice edges are located
  int32_t c;
  int i, j;

  for (int i = 0; i < NUM_EDGES; i++) {
    slice[i] = 0;
  }


  idx /= 2187;
  for (i = 4; i > 0; i--) {
    for (j = NUM_EDGES - 1; j >= 0; j--) {
      if (combination(j, i)  <= idx)
        break;
    }
    slice[j] = 1;
    idx -= combination(j, i);
  }
}

int encode_edges(edge_t *edges) {
  bool used[12] = {false};
  int idx = 0;

  for (int i = 0; i < 12; i++) {
    int count = 0;

    for (int j = 0; j < edges[i]; j++) {
      if (!used[j])
        count++;
    }

    idx += count * f_table[12 - 1 - i];
    used[edges[i]] = true;
  }

  return idx;
}

void decode_edges(int idx, edge_t *edges) {
    bool used[12] = { false };

    for (int i = 0; i < 12; i++) {
        int f = f_table[12 - 1 - i];
        int index = idx / f;
        idx = idx % f;

        // Find the index-th unused number
        int count = -1;
        for (int j = 0; j < 12; j++) {
            if (!used[j])
                count++;
            if (count == index) {
                edges[i] = j;
                used[j] = true;
                break;
            }
        }
    }
}

// Blue and Green sticker must be on either blue/green face for the corner
void generate_stage_two_table(const rubix_cube_t cube) {
  const moves_t moves[NUM_MOVES_S2] = {L,  L2, Lp, R,  R2, Rp, F,
                                       F2, Fp, B,  B2, Bp, U2, D2};
  const moves_t i_moves[NUM_MOVES_S2] = {Lp, L2, L,  Rp, R2, R,  Fp,
                                         F2, F,  Bp, B2, B,  U2, D2};
  int8_t permutations[STAGE2_NUM_PERMUTATIONS];
  int8_t lookup[STAGE2_NUM_PERMUTATIONS];
  unsigned char slice[NUM_EDGES] = {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

  for (int i = 0; i < STAGE2_NUM_PERMUTATIONS; i++) {
    permutations[i] = UNVISITED;
  }

  queue_t queue;
  initQueue(&queue);

  permutations[STAGE2_GOAL_STATE] = VISITED;
  lookup[STAGE2_GOAL_STATE] = 0;
  enqueue(&queue, STAGE2_GOAL_STATE);

  rubix_cube_t tmp = cube;
  enqueue(&queue, encode_edges(tmp.edge_positions));

  while (!isEmpty(&queue)) {
    unsigned short idx = dequeue(&queue);
    int32_t e_idx = dequeue(&queue);

    // reset the slice array
    for (int i = 0; i < NUM_EDGES; i++) {
      slice[i] = 0;
    }

    get_state_s2(tmp.corner_orientation, slice, idx);
    decode_edges(e_idx, tmp.edge_positions);

    for (int i = 0; i < NUM_MOVES_S2; i++) {
      rubix_cube_t tmp2 = tmp;

      make_move(&tmp2, moves[i]);

      // find which edges old the UD slice edges
      for (int i = 0; i < NUM_EDGES; i++) {
        slice[i] = 0;
        if (tmp2.edge_positions[i] == UF || tmp2.edge_positions[i] == DF ||
            tmp2.edge_positions[i] == DB || tmp2.edge_positions[i] == UB) {
          slice[i] = 1;
        }
      }

      idx = get_index_s2(tmp2.corner_orientation, slice);

      if (permutations[idx] == UNVISITED) {
        permutations[idx] = VISITED;
        lookup[idx] = i_moves[i];
        enqueue(&queue, idx);
        enqueue(&queue, encode_edges(tmp2.edge_positions));
      }
    }
  }

  write_table_to_file(lookup, STAGE2_TABLE_FILE, STAGE2_NUM_PERMUTATIONS);
}

int main(void) {
  rubix_cube_t cube = {
      .corner_orientation = {0, 0, 0, 0, 0, 0, 0, 0},
      .corner_positions = {UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR},
      .edge_orientation = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      .edge_positions = {UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR},
  };

  generate_stage_two_table(cube);

  return 0;
}
