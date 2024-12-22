/**
 * @file tetris.h
 * @author whatarml
 * @brief The main header file for the tetris game
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS_H
#define TETRIS_H

#define _GNU_SOURCE

#include "tetris_backend.h"
#include "tetris_frontend.h"
#include "tetris_fsm.h"

/**
 * @brief Gets the user action from the input character.
 *
 * @param ch The input character.
 * @return The user action.
 */
UserAction_t get_user_action(int ch);

/**
 * @brief Starts the menu loop.
 *
 * @param g_state The game state.
 */
void brick_game_menu(Game_state_t *g_state);

/**
 * @brief Starts the game loop.
 *
 * @param g_state The game state.
 * @param g_info The game information.
 * @param tetris The tetris window.
 * @param status The status window.
 * @param next The next window.
 * @param user_inp_key The user input key.
 */
void game_loop(Game_state_t *g_state, GameInfo_t g_info, WINDOW *tetris,
               WINDOW *status, WINDOW *next, int user_inp_key);

/**
 * @brief Processes the delay.
 *
 * @param g_info The game information.
 */
void process_delay(GameInfo_t g_info);

/**
 * @brief Starts the moving loop.
 *
 * @param g_state The game state.
 * @param g_info The game information.
 * @param tetris The tetris window.
 */
void moving_loop(Game_state_t *g_state, GameInfo_t g_info, WINDOW *tetris);

/**
 * @brief Refreshes the windows.
 *
 * @param tetris The tetris window.
 * @param status The status window.
 * @param next The next window.
 */
void refresh_windows(WINDOW *tetris, WINDOW *status, WINDOW *next);

/**
 * @brief Deletes the windows.
 *
 * @param tetris The tetris window.
 * @param status The status window.
 * @param next The next window.
 */
void delete_windows(WINDOW *tetris, WINDOW *status, WINDOW *next);

#endif
