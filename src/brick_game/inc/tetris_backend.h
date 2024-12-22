#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defines.h"
#include "objects.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

// ___________custom functions_________

Game_state_t *get_game_state();
// GameInfo_t copy_game_to_gi();
void copy_game_to_gi(Game_state_t *g_state, GameInfo_t *current_state);

// ________inits________
// int init_field(Game_state_t *g_state);
// int init_field_gi(GameInfo_t *field_t);
GameInfo_t init_game_info();
void init_figure(Game_state_t *g_state);
void init_game_status(Game_status_t *game_status);
void init_game_stats(Game_stats_t *game_stats);
void init_game_state(Game_state_t *g_state);
void init_next_figure(Game_state_t *g_state);
int **init_array(int rows, int cols);

// ________frees________
void free_field(Game_state_t *g_state);
void free_field_gi(GameInfo_t *field_t);
void free_next_figure(int **figure_t);
void free_array(int rows, int **array);

// void free_field_gs(Game_state_t *game_state);
void free_game(Game_state_t *g_state);
void free_game_gi(GameInfo_t *g_info);
// void finish_game(Game_state_t *g_state);

// ________draws________

void figure_to_field(Game_state_t *g_state);
void fill_next_figure(Game_state_t *g_state);
int figure_min_width(Game_state_t *g_state);
int figure_min_height(Game_state_t *g_state);

// ________collisions________
int border_collision(Game_state_t *g_state);
bool bottom_figure_collision(Game_state_t *g_state);

void copy_field(int rows, int cols, int **src_matrix, int **dest_matrix);

void clear_figure(Game_state_t *g_state);

void move_left(Game_state_t *g_state);
void move_right(Game_state_t *g_state);
void move_down(Game_state_t *g_state);
// void move_up(Game_state_t *g_state);

bool figure_is_attaching(Game_state_t *g_state);

void collapse_full_lines(Game_state_t *g_state);

void shift_lines(Game_state_t *g_state, int i);

// void rotate_figure(Game_state_t *g_state);

void update_score(Game_state_t *g_state, int num_full_lines);

#endif