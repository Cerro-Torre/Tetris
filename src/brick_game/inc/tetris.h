#ifndef TETRIS_H
#define TETRIS_H

#define _GNU_SOURCE

#include "tetris_backend.h"
#include "tetris_frontend.h"
#include "tetris_fsm.h"

UserAction_t get_user_action(int ch);
void game_loop();

#endif