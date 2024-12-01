#ifndef TETRIS_H
#define TETRIS_H

#include "tetris_backend.h"
#include "tetris_frontend.h"

void game_loop();
UserAction_t get_user_action(int ch);

#endif