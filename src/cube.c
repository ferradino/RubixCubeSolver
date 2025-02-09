#include "cube.h"

void read_rubix_cube_face(RubixCube *rubix_cube) {
    enum Color color; 
    color = read_center_tile_color();

    for (int i = 0; i < 4; i++) {
        color = read_edge_tile_color();
        rotate_basket(C_QUARTER_TURN);
    }

    rotate_basket(C_EIGTH_TURN);

    for (int i = 0; i < 4; i++) {
        color = read_corner_tile_color();
        rotate_basket(C_QUARTER_TURN);
    }

    rotate_basket(C_EIGTH_TURN);
}

void read_rubix_cube(RubixCube *rubix_cube) {
    read_rubix_cube_face(rubix_cube);

    flip_cube();
    flip_cube();

    read_rubix_cube_face(rubix_cube);

    flip_cube();
    rotate_basket(HALF_TURN);

    for (int i = 0; i < 4; i++) {
        read_rubix_cube_face(rubix_cube);
        flip_cube();
    }

    rotate_basket(CC_QUARTER_TURN);
    flip_cube();
}

void left_turn() {
    rotate_basket(CC_QUARTER_TURN);
    flip_cube();

    rotate_cube(C_QUARTER_TURN);
    rotate_basket(CC_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_basket(CC_QUARTER_TURN);
}

void left_prime_turn() {
    rotate_basket(CC_QUARTER_TURN);
    flip_cube();

    rotate_cube(CC_QUARTER_TURN);
    rotate_basket(C_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_basket(CC_QUARTER_TURN);
}

void left_double_turn() {
    rotate_basket(CC_QUARTER_TURN);
    flip_cube();

    rotate_cube(HALF_TURN);

    flip_cube();
    rotate_basket(-1 * HALF_TURN);
}

void right_turn() {
    rotate_basket(C_QUARTER_TURN);
    flip_cube();

    rotate_cube(CC_QUARTER_TURN);
    rotate_basket(C_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_basket(C_QUARTER_TURN);
}

void right_prime_turn() {
    rotate_basket(C_QUARTER_TURN);
    flip_cube();

    rotate_cube(C_QUARTER_TURN);
    rotate_basket(CC_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_basket(C_QUARTER_TURN);
}

void right_double_turn() {
    rotate_basket(C_QUARTER_TURN);
    flip_cube();

    rotate_cube(HALF_TURN);

    flip_cube();
    rotate_basket(C_QUARTER_TURN);
}

void down_turn() {
    flip_cube();
    flip_cube();

    rotate_cube(C_QUARTER_TURN); 
    rotate_basket(CC_QUARTER_TURN);

    flip_cube();
    flip_cube();
}

void down_prime_turn() {
    flip_cube();
    flip_cube();

    rotate_cube(CC_QUARTER_TURN);
    rotate_basket(C_QUARTER_TURN); 

    flip_cube();
    flip_cube();
}

void down_double_turn() {
    flip_cube();
    flip_cube();

    rotate_cube(HALF_TURN); 
    rotate_basket(HALF_TURN);

    flip_cube();
    flip_cube();
}

void up_turn() { 
   rotate_cube(C_QUARTER_TURN);
   rotate_basket(CC_QUARTER_TURN);
}

void up_prime_turn() {
   rotate_cube(CC_QUARTER_TURN);
   rotate_basket(C_QUARTER_TURN);
}

void up_double_turn() {
    rotate_cube(HALF_TURN);
    rotate_basket(HALF_TURN);
}

void front_turn() {
    flip_cube();

    rotate_cube(C_QUARTER_TURN);
    rotate_basket(CC_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();
}

void front_prime_turn() {
    flip_cube();

    rotate_cube(CC_QUARTER_TURN);
    rotate_basket(C_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();
}

void front_double_turn() {
    flip_cube();

    rotate_cube(HALF_TURN);
    rotate_basket(HALF_TURN);

    flip_cube();
}

void back_turn() {
    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_cube(C_QUARTER_TURN);
    rotate_basket(CC_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();
}

void back_prime_turn() {
    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_cube(CC_QUARTER_TURN);
    rotate_basket(C_QUARTER_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();
}

void back_double_turn() {
    rotate_basket(HALF_TURN);
    flip_cube();

    rotate_cube(HALF_TURN);

    rotate_basket(HALF_TURN);
    flip_cube();
}