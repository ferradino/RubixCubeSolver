#ifndef __CUBE_H
#define __CUBE_H

#define NUM_FACES 6
#define NUM_EDGES 12
#define NUM_CORNERS 8
#define NUM_TILES 54

typedef enum MOVES { U, U2, Up, D, D2, Dp, R, R2, Rp, L, L2, Lp, F, F2, Fp, B, B2, Bp } moves_t;

/*
 * Cube Edge and Corner Notation
 *  - This follows from the Cube Face Notation from above
 *  - Corners are represented by 3 chars (3 faces)
 *  - Edges are respresented by 2 chars (2 faces)
 */
typedef enum corner_t { UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR } corner_t;
typedef enum edge_t { UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR } edge_t;

/*
 * Cube Structure:
 * 5 Arrays
 *  - edge_position
 *  - edge_orientation
 *  - corner_position
 *  - corner_orientation
 *  - tile_colors
 *
 *  Position just gives the position on the cube that the edge/corner is at
 *
 *  Edge orientation is a 1 if a quarter turn on all three axes is required
 *  to put the edge in the proper position and orientation
 *
 *  Corner orientation is a 0 if the corner's white or yellow sticker is on the
 * white or yello face, 1 if the white/yellow sticker is clockwise from the
 * white/yellow face, and 2 if counterclockwise from the white/yellow face
 *
 */
typedef struct RubixCube {
  edge_t edge_positions[NUM_EDGES];
  corner_t corner_positions[NUM_CORNERS];
  unsigned char edge_orientation[NUM_EDGES];
  unsigned char corner_orientation[NUM_CORNERS];
} rubix_cube_t;

/* Takes in a move and performs move on cube */
void make_move(rubix_cube_t *rubix_cube, moves_t moves);

/*
 * Rubix Cube Turns
 *  - All turns are based on a clockwise rotation
 *  - "Turn" indicates a clockwise rotation (90 degrees)
 *  - "Prime Turn" indicates a counterclockwise rotation (90 degress)
 *  - "Double Turn" is a double rotation (180 degrees)
 */
void c_left_turn(rubix_cube_t *rubix_cube);
void c_left_prime_turn(rubix_cube_t *rubix_cube);
void c_left_double_turn(rubix_cube_t *rubix_cube);
void c_right_turn(rubix_cube_t *rubix_cube);
void c_right_prime_turn(rubix_cube_t *rubix_cube);
void c_right_double_turn(rubix_cube_t *rubix_cube);
void c_down_turn(rubix_cube_t *rubix_cube);
void c_down_prime_turn(rubix_cube_t *rubix_cube);
void c_down_double_turn(rubix_cube_t *rubix_cube);
void c_up_turn(rubix_cube_t *rubix_cube);
void c_up_prime_turn(rubix_cube_t *rubix_cube);
void c_up_double_turn(rubix_cube_t *rubix_cube);
void c_front_turn(rubix_cube_t *rubix_cube);
void c_front_prime_turn(rubix_cube_t *rubix_cube);
void c_front_double_turn(rubix_cube_t *rubix_cube);
void c_back_turn(rubix_cube_t *rubix_cube);
void c_back_prime_turn(rubix_cube_t *rubix_cube);
void c_back_double_turn(rubix_cube_t *rubix_cube);

#endif
