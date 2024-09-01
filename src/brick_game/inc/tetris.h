#ifndef TETRIS_H
#define TETRIS_H

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
// #include "fsm.h"
#include "objects.h"
#include "tetris_backend.h"
#include "tetris_frontend.h"

void game_loop();

void free_field(GameInfo_t *game);
void free_next(GameInfo_t *game);

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif