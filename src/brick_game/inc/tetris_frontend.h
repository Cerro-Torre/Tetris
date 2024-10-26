#ifndef FROGGER_FRONTEND_H
#define FROGGER_FRONTEND_H

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "defines.h"
#include "objects.h"

void print_field(GameInfo_t *game);

// _______________
void print_overlay(void);
WINDOW *print_menu();
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
WINDOW *print_tetris_overlay();
WINDOW *print_status_gi(GameInfo_t *g_info);
WINDOW *print_states(Game_state_t *g_state, int key);

void clear_menu();
void print_figure();

void render_game_gi(WINDOW *tetris_window, GameInfo_t g_info);
void render_game_gs(WINDOW *tetris_window, Game_state_t *g_state);

// void print_stats(game_stats_t *stats);
// void print_board(board_t *game, player_pos *frog);
// void print_cars(board_t *game);
// void print_finished(board_t *game);
// void print_banner(game_stats_t *stats);
// int read_banner(game_stats_t *stats, banner_t *banner);

#endif