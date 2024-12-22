/**
 * @file defines.h
 * @author whatarml
 * @brief Definitions for the Tetris game.
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 * This file contains definitions for the game.
 */

#ifndef DEFINES_H
#define DEFINES_H

/** Width of the game border */
#define GAME_BORDER_WIDTH 14

/** Height of the game border */
#define GAME_BORDER_HEIGHT 22

/** Number of rows in the game field */
#define ROWS_GAME 20

/** Number of columns in the game field */
#define COLS_GAME 10

/** X position of the next piece display */
#define NEXT_FIELD_X 10

/** Y position of the next piece display */
#define NEXT_FIELD_Y 10

/** Key to start the game */
#define KEY_T 't'

/** Key to pause the game */
#define KEY_P 'p'

/** Key to quit the game */
#define KEY_Q 'q'

/** Key to rotate the piece */
#define KEY_Z 'z'

/** Number of rows in a Tetris figure */
#define FIGURE_N 4

/** Number of columns in a Tetris figure */
#define FIGURE_M 4

/** Introductory message displayed to the player */
#define INTRO_MESSAGE "Press \"t\" to start tetris!"

/** Length of the introductory message */
#define INTRO_MESSAGE_LEN 28

#endif
