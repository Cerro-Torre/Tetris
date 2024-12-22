/**
 * @file tetris_fsm.h
 * @author whatarml
 * @brief The state machine of the tetris game
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FSM_H
#define FSM_H

#include "../inc/defines.h"
#include "../inc/tetris_backend.h"

/**
 * @brief State machine functions.
 *
 * Functions that handle the state machine logic.
 */

/**
 * @brief Initialize game state.
 *
 * Function that handles the initialization of the game state.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_init_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Start game state.
 *
 * Function that handles the start of the game.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_start_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Spawn new figure state.
 *
 * Function that handles the spawning of a new figure.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_spawn_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Move figure state.
 *
 * Function that handles the movement of a figure.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_moving(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Move state.
 *
 * Function that handles the movement of a figure.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_move_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Attach figure state.
 *
 * Function that handles the attachment of a figure to the game field.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_attach_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Pause game state.
 *
 * Function that handles the pause of the game.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_pause_state(Game_state_t *g_state, UserAction_t action);

/**
 * @brief Shift game state.
 *
 * Function that handles the shifting of the game state.
 *
 * @param g_state Pointer to the game state.
 * @param action User action.
 */
void on_shift_state(Game_state_t *g_state, UserAction_t action);

#endif