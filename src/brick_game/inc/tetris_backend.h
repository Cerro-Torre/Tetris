#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdlib.h>

#include "defines.h"
#include "objects.h"
#include "string.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

// ___________custom functions_________

Game_state_t get_game_state();

void draw_figure_1(GameInfo_t *game);
void init_game(GameInfo_t *game);
// void free_field(GameInfo_t *game);
// void free_next(GameInfo_t *game);
// void free_objects(GameInfo_t *game);
void free_game(GameInfo_t *game);
void print_test();

// void draw_field(GameInfo_t *game);
// void draw_next(GameInfo_t *game);
// void draw_objects(GameInfo_t *game);
// void draw_game(GameInfo_t *game);
// void draw_stats(GameInfo_t *game);
// void draw_game_over(GameInfo_t *game);
// void draw_help(GameInfo_t *game);
// void draw_pause(GameInfo_t *game);

#endif