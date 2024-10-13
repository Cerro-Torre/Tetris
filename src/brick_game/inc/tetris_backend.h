#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

// ___________custom functions_________

Game_state_t *get_game_state();

// ________inits________
int init_field(Game_field_t *field_t);
void init_figure(Figure_t *figure_t);
void init_game_status(Game_status_t *game_status);
void init_game_stats(Game_stats_t *game_stats);
void init_game_state(Game_state_t *game_state, Game_field_t *field);

// ________frees________
void free_field(Game_field_t *field_t);
void free_field_gs(Game_state_t *game_state);
void free_game(Game_state_t *game, Game_field_t *field);

// ________draws________
void fill_field(Game_state_t *game_state);
void create_figure(ShapeType type, int figure[4][4],
                   int *figures[type][FIGURE_M][FIGURE_N]);
void draw_figure_1(GameInfo_t *game);
void update_field(Game_state_t *game_state);

UserAction_t get_user_action(int ch);

// void free_field(GameInfo_t *game);
// void free_next(GameInfo_t *game);
// void free_objects(GameInfo_t *game);
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