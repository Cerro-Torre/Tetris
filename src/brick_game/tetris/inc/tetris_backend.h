/**
 * @file tetris_backend.h
 * @author whatarml
 * @brief The backend of the tetris game
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defines.h"
#include "objects.h"

//              ___________spec functions_________

/**
 * @brief Process user input actions and update game state accordingly.
 *
 * @param action The user action to be processed.
 * @param hold Whether the action is a hold action.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Update and retrieve the current state of the game.
 *
 * @return GameInfo_t The updated game information.
 */
GameInfo_t updateCurrentState();

//              ___________custom functions_________
/**
 * @brief Returns the current game state.
 *
 * @return Game_state_t* The current game state.
 */
Game_state_t *get_game_state();

/**
 * @brief Copies the game state to GameInfo_t struct.
 *
 * @param scr The source game state to be copied.
 * @param dest The destination GameInfo_t struct to store the copied
 * information.
 */
void copy_game_to_gi(Game_state_t *scr, GameInfo_t *dest);

//                      ________inits________
/**
 * @brief Initialize the game state to a default state.
 *
 * @return GameInfo_t The initial game state.
 */
GameInfo_t init_game_info();

/**
 * @brief Initialize the figure for the game state.
 *
 * @param g_state The game state to initialize a figure for.
 */
void init_figure(Game_state_t *g_state);

/**
 * @brief Initialize the game status to a default state.
 *
 * @param game_status The game status to be initialized.
 */
void init_game_status(Game_status_t *game_status);

/**
 * @brief Initialize the game statistics to a default state.
 *
 * @param game_stats The game statistics to be initialized.
 */
void init_game_stats(Game_stats_t *game_stats);

/**
 * @brief Initialize the game state with a default state.
 *
 * The game state's game status, game statistics, figure, and field are
 * initialized to a default state.
 *
 * @param g_state The game state to be initialized.
 */
void init_game_state(Game_state_t *g_state);

/**
 * @brief Initialize the next figure to be spawned.
 *
 * The next figure is initialized with a random type and its height and width
 * are set to 4.
 *
 * @param g_state The game state to initialize the next figure for.
 */
void init_next_figure(Game_state_t *g_state);

/**
 * @brief Create a 2D array of integers.
 *
 * The array is created with the specified number of rows and columns.
 *
 * @param rows The number of rows in the array.
 * @param cols The number of columns in the array.
 *
 * @return A pointer to a 2D array of integers.
 */
int **init_array(int rows, int cols);

//                      ________frees________
/**
 * @brief Frees a 2D array of integers.
 *
 * The array is deallocated, and the pointer to the array is set to NULL.
 *
 * @param rows The number of rows in the array.
 * @param array The 2D array to be deallocated.
 */
void free_array(int rows, int **array);

/**
 * @brief Frees the game state.
 *
 * The game state's game status, game statistics, figure, and field are
 * deallocated, and the pointers are set to NULL.
 *
 * @param g_state The game state to be deallocated.
 */
void free_game(Game_state_t *g_state);

/**
 * @brief Frees the game info.
 *
 * The game info's field and next figure are deallocated, and the pointers
 * are set to NULL.
 *
 * @param g_info The game info to be deallocated.
 */
void free_game_gi(GameInfo_t *g_info);

//                      ________draws________
/**
 * @brief Copy the figure to the field.
 *
 * The figure is copied to the field based on its position and type.
 *
 * @param g_state The game state to copy the figure to.
 */
void figure_to_field(Game_state_t *g_state);

/**
 * @brief Clear the figure from the field.
 *
 * The figure is cleared from the field based on its position and type.
 *
 * @param g_state The game state to clear the figure from.
 */
void clear_figure(Game_state_t *g_state);
/**
 * @brief Fill the next figure in the game state.
 *
 * This function populates the next figure in the game state using the
 * predefined figure shapes and the next type specified in the game state.
 *
 * @param g_state The game state containing the next figure information.
 */
void fill_next_figure(Game_state_t *g_state);

/**
 * @brief Calculate the minimum width of the current figure.
 *
 * This function determines the minimum width of the current figure based on its
 * type.
 *
 * @param g_state The game state containing the current figure information.
 * @return int The minimum width of the current figure.
 */
int figure_min_width(Game_state_t *g_state);

/**
 * @brief Calculate the minimum height of the current figure.
 *
 * This function determines the minimum height of the current figure based on
 * its type.
 *
 * @param g_state The game state containing the current figure information.
 * @return int The minimum height of the current figure.
 */
int figure_min_height(Game_state_t *g_state);

//                      ________collisions________
/**
 * @brief Checks for collisions with the border.
 *
 * This function checks for collisions between the figure and the border of the
 * game field. The collision is determined by the position and type of the
 * figure.
 *
 * @param g_state The game state containing the figure information.
 * @return int The type of collision. 0 if no collision, otherwise it is one of
 * enums: COLLISION_LEFT, COLLISION_RIGHT, COLLISION_DOWN, COLLISION_DL, or
 * COLLISION_DR.
 */
int border_collision(Game_state_t *g_state);

/**
 * @brief Checks for collisions with the bottom of the game field.
 *
 * This function checks for collisions between the figure and the bottom of the
 * game field. The collision is determined by the position and type of the
 * figure.
 *
 * @param g_state The game state containing the figure information.
 * @return bool Whether a collision was detected.
 */
bool bottom_figure_collision(Game_state_t *g_state);

//                      ________moves________
/**
 * @brief Moves the current figure to the left.
 *
 * This function moves the current figure one square to the left. If the figure
 * is already at the leftmost position, it does nothing.
 *
 * @param g_state The game state containing the current figure information.
 */
void move_left(Game_state_t *g_state);

/**
 * @brief Moves the current figure to the right.
 *
 * This function moves the current figure one square to the right. If the figure
 * is already at the rightmost position, it does nothing.
 *
 * @param g_state The game state containing the current figure information.
 */
void move_right(Game_state_t *g_state);

/**
 * @brief Moves the current figure downwards.
 *
 * This function moves the current figure one square down. If the figure
 * is at the bottommost position, it does nothing.
 *
 * @param g_state The game state containing the current figure information.
 */
void move_down(Game_state_t *g_state);

//                       ________other________
/**
 * @brief Copies the contents of the source matrix to the destination matrix.
 *
 * This function copies the contents of the source matrix to the destination
 * matrix. The source matrix is not modified.
 *
 * @param rows The number of rows in the source matrix.
 * @param cols The number of columns in the source matrix.
 * @param src_matrix The source matrix to be copied.
 * @param dest_matrix The destination matrix to store the copied information.
 */
void copy_field(int rows, int cols, int **src_matrix, int **dest_matrix);

/**
 * @brief Checks if the current figure is attached to the bottom of the game
 * field.
 *
 * This function checks if the current figure is attached to the bottom of the
 * game field. The figure is considered attached if its bottommost square is
 * at the bottommost row of the game field.
 *
 * @param g_state The game state containing the current figure information.
 * @return bool Whether the figure is attached to the bottom of the game field.
 */
bool figure_is_attaching(Game_state_t *g_state);

/**
 * @brief Checks if a row in the game field is full.
 *
 * This function checks if all squares in a given row of the game field are
 * occupied. If a row is full, it is removed and the squares above it are
 * shifted down.
 *
 * @param g_state The game state containing the current game field information.
 */
void collapse_full_lines(Game_state_t *g_state);

/**
 * @brief Shifts the squares in the game field above the given row down.
 *
 * This function shifts the squares in the game field above the given row down
 * by one row.
 *
 * @param g_state The game state containing the current game field information.
 * @param i The row to be shifted.
 */
void shift_lines(Game_state_t *g_state, int i);

/**
 * @brief Updates the game score based on the number of full lines.
 *
 * This function updates the game score based on the number of full lines
 * removed from the game field. The score is updated based on the number of
 * full lines removed according to the score table.
 *
 * @param g_state The game state containing the current score information.
 * @param num_full_lines The number of full lines removed from the game field.
 */
void update_score(Game_state_t *g_state, int num_full_lines);

/**
 * @brief Updates the game level based on the score.
 *
 * This function updates the game level based on the current score. The level
 * is updated if the score exceeds the next level's score requirement.
 *
 * @param g_state The game state containing the current score information.
 */
void update_level(Game_state_t *g_state);

#endif