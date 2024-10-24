#ifndef TETRIS_H
#define TETRIS_H

#include "tetris_backend.h"
#include "tetris_frontend.h"

void game_loop();

// #define KEY_R 114
// #define KEY_P 112
// #define KEY_Q 113
// #define KEY_Z 122

// #define KEY_LEFT 684
// #define KEY_RIGHT 674
// #define KEY_UP 654
// #define KEY_DOWN 664

UserAction_t get_user_action(int ch);

#endif