#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

// названия из задания:
void userInput(UserAction_t action, bool hold);
// GameInfo_t updateCurrentState();

// void user_input(Game_state_t *g_state, UserAction_t action);
// GameInfo_t update_current_state(Game_state_t *g_state);
GameInfo_t updateCurrentState();

// ___________custom functions_________

Game_state_t *get_game_state();
GameInfo_t copy_game_to_gi(Game_state_t *g_state);

// ________inits________
int init_field(Game_field_t *field_t);
int init_field_gi(GameInfo_t *field_t);
void init_figure(Game_state_t *g_state);
void init_game_status(Game_status_t *game_status);
void init_game_stats(Game_stats_t *game_stats);
void init_game_state(Game_state_t *game_state, Game_field_t *field);

// ________frees________
void free_field(Game_field_t *field_t);
void free_field_gi(GameInfo_t *field_t);
void free_next_figure_gi(GameInfo_t *g_info);

// void free_field_gs(Game_state_t *game_state);
void free_game(Game_state_t *g_state);

// _______fsm________

void on_init_state(Game_state_t *g_state, UserAction_t action);
void on_start_state(Game_state_t *g_state, UserAction_t action);
void on_spawn_state(Game_state_t *g_state, UserAction_t action);
void on_move_state(Game_state_t *g_state, UserAction_t action);
void on_attach_state(Game_state_t *g_state, UserAction_t action);

// ________draws________

// void fill_field(Game_state_t *game_state);
// void create_figure(ShapeType type, int figure[4][4],
//                    int *figures[type][FIGURE_M][FIGURE_N]);
// void figure_to_field_1(GameInfo_t *game);

void figure_to_field(Game_state_t *g_state);
void create_next_fig_size(Game_state_t *g_state, int type);
int trim_figure_width(Game_state_t *g_state);
int trim_figure_height(Game_state_t *g_state);
// void create_next_figure(Figure_t *figure_t, int type, int y, int x);
int init_next_figure(Game_state_t *g_state);
void next_figure_to_current(Game_state_t *g_state);

// ________collisions________
int border_collision(Game_state_t *g_state);
bool bottom_figure_collision(Game_state_t *g_state);
// bool right_figure_collision(Game_state_t *g_state);
int check_collision(Game_state_t *g_state);

void finish_game(Game_state_t *g_state);

void copy_field(int rows, int cols, int **src_matrix, int **dest_matrix);

// void update_field(Game_state_t *game_state, int figure_type);
void clear_figure(Game_state_t *g_state);

// UserAction_t get_user_action(int ch);

// void move_figure(Game_state_t *g_state, UserAction_t action);
// void move_figure2(Game_state_t *g_state, int dx);
void move_left(Game_state_t *g_state);
// void move_left2(Game_state_t *g_state);
void move_right(Game_state_t *g_state);
void move_down(Game_state_t *g_state);

void move_up(Game_state_t *g_state);

bool figure_is_attaching(Game_state_t *g_state);

// int move_in_array(Game_state_t *g_state);

// void free_field(GameInfo_t *game);
// void free_next(GameInfo_t *game);
// void free_objects(GameInfo_t *game);
// void print_test();

// void draw_field(GameInfo_t *game);
// void draw_next(GameInfo_t *game);
// void draw_objects(GameInfo_t *game);
// void draw_game(GameInfo_t *game);
// void draw_stats(GameInfo_t *game);
// void draw_game_over(GameInfo_t *game);
// void draw_help(GameInfo_t *game);
// void draw_pause(GameInfo_t *game);

#endif