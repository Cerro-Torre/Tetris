#ifndef TETRIS_H
#define TETRIS_H

#define _GNU_SOURCE

#include "tetris_backend.h"
#include "tetris_frontend.h"
#include "tetris_fsm.h"

UserAction_t get_user_action(int ch);
void brick_game_menu(Game_state_t *g_state);
void game_loop(Game_state_t *g_state, GameInfo_t g_info, WINDOW *tetris,
               WINDOW *status, WINDOW *next, int user_inp_key);
void process_delay(GameInfo_t g_info);
void moving_loop(Game_state_t *g_state, GameInfo_t g_info, WINDOW *tetris);
void refresh_windows(WINDOW *tetris, WINDOW *status, WINDOW *next);
void delete_windows(WINDOW *tetris, WINDOW *status, WINDOW *next);

#endif