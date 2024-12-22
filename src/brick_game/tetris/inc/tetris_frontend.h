/**
 * @file tetris_frontend.h
 * @author whatarml
 * @brief The frontend of the tetris game
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FROGGER_FRONTEND_H
#define FROGGER_FRONTEND_H

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "defines.h"
#include "objects.h"

/**
 * @brief Prints the initial overlay.
 */
void print_overlay(void);

/**
 * @brief Prints the level error.
 */
void print_levelerror(void);

/**
 * @brief Renders the game.
 *
 * @param tetris_window The window to render the game in.
 * @param g_info The game information.
 */
void render_game_gi(WINDOW *tetris_window, GameInfo_t g_info);

/**
 * @brief Prints the menu.
 *
 * @return The menu window.
 */
WINDOW *print_menu();

/**
 * @brief Prints the tetris overlay.
 *
 * @return The tetris overlay window.
 */
WINDOW *print_tetris_overlay();

/**
 * @brief Prints the status.
 *
 * @param g_info The game information.
 *
 * @return The status window.
 */
WINDOW *print_status_gi(GameInfo_t *g_info);

/**
 * @brief Prints the states.
 *
 * @param g_state The game state.
 * @param key The key.
 *
 * @return The states window.
 */
WINDOW *print_states(Game_state_t *g_state, int key);

/**
 * @brief Prints the next display.
 *
 * @param g_info The game information.
 *
 * @return The next display window.
 */
WINDOW *next_display(GameInfo_t *g_info);

#endif