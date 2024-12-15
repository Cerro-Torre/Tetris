#ifndef TETRIS_H
#define TETRIS_H

#define _POSIX_C_SOURCE 199309L

#include <unistd.h>

#include "tetris_backend.h"
#include "tetris_frontend.h"
#include "time.h"

void game_loop();
UserAction_t get_user_action(int ch);

#endif