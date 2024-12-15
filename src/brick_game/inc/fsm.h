#ifndef __FSM_H__
#define __FSM_H__

#include "../inc/defines.h"
#include "../inc/tetris_backend.h"

void on_init_state(Game_state_t *g_state, UserAction_t action);
void on_start_state(Game_state_t *g_state, UserAction_t action);
void on_spawn_state(Game_state_t *g_state, UserAction_t action);
void on_move_state(Game_state_t *g_state, UserAction_t action);
void on_attach_state(Game_state_t *g_state, UserAction_t action);
void on_pause_state(Game_state_t *g_state, UserAction_t action);
void on_shift_state(Game_state_t *g_state, UserAction_t action);

#endif