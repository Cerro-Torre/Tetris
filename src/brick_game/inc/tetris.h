#ifndef TETRIS_H
#define TETRIS_H

#include <unistd.h>

#include "fsm.h"
#include "tetris_backend.h"
#include "tetris_frontend.h"

UserAction_t get_user_action(int ch);
void game_loop();

#endif