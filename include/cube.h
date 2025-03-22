#include "robot.h"

#ifndef __CUBE_H
#define __CUBE_H

#define NUM_FACES 6
#define NUM_EDGES 12
#define NUM_CORNERS 8
#define NUM_TILES 54

/*
 * Cube Face Notation
 *   - F : front
 *   - B : back
 *   - U : up
 *   - D : down
 *   - L : left
 *   - R : right
 */
enum FACE { U, D, F, L, B, R };
enum CORNER_POS { UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR };
enum EDGE_POS { UF, UL, UB, UR, DF, DL, DB, DR, FL, BL, BR, FR};

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
 *  Corner orientation is a 0 if the corner's white or yellow sticker is on the white or yello face, 1
 *  if the white/yellow sticker is clockwise from the white/yellow face, and 2 if counterclockwise from 
 *  the white/yellow face
 *
 *  Tile colors just holds the color of tile
 *    - 0-8 will be top tiles
 *    - 9-17 will be bottom tiles
 *    - 18-26 will be front tiles
 *    - 27-35 will be left tiles
 *    - 36-45 will be back tiles
 *    - 46-53 will be right tiles
 */
typedef struct {
  enum EDGE_POS edge_positions[NUM_EDGES];
  enum CORNER_POS corner_positions[NUM_CORNERS];
  unsigned char edge_orientation[NUM_EDGES];
  unsigned char corner_orientation[NUM_CORNERS];
  enum Color tile_colors[NUM_TILES];
} RubixCube;


/* Initialize Rubix Cube */
void rubix_cube_init(RubixCube *rubix_cube);

/* Read in all the faces and their colors */
void read_rubix_cube_tile_colors(RubixCube *rubix_cube);

/* 
 * Rubix Cube Turns
 *  - All turns are based on a clockwise rotation
 *  - "Turn" indicates a clockwise rotation (90 degrees)
 *  - "Prime Turn" indicates a counterclockwise rotation (90 degress)
 *  - "Double Turn" is a double rotation (180 degrees)
 */
void left_turn(RubixCube *rubix_cube);
void left_prime_turn(RubixCube *rubix_cube);
void left_double_turn(RubixCube *rubix_cube);
void right_turn(RubixCube *rubix_cube);
void right_prime_turn(RubixCube *rubix_cube);
void right_double_turn(RubixCube *rubix_cube);
void down_turn(RubixCube *rubix_cube);
void down_prime_turn(RubixCube *rubix_cube);
void down_double_turn(RubixCube *rubix_cube);
void up_turn(RubixCube *rubix_cube);
void up_prime_turn(RubixCube *rubix_cube);
void up_double_turn(RubixCube *rubix_cube);
void front_turn(RubixCube *rubix_cube);
void front_prime_turn(RubixCube *rubix_cube);
void front_double_turn(RubixCube *rubix_cube);
void back_turn(RubixCube *rubix_cube);
void back_prime_turn(RubixCube *rubix_cube);
void back_double_turn(RubixCube *rubix_cube);

#endif
