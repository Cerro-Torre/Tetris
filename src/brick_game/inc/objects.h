/**
 * @file objects.h
 * @author whatarml
 * @brief structs and enums
 * @version 1
 * @date 2024-22-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __OBJECTS_H
#define __OBJECTS_H

#include "./defines.h"

/**
 * @brief Enum representing possible user actions.
 */
typedef enum {
  Start,     /**< Start action */
  Pause,     /**< Pause action */
  Terminate, /**< Terminate action */
  Left,      /**< Move left action */
  Right,     /**< Move right action */
  Up,        /**< Move up action */
  Down,      /**< Move down action */
  Action     /**< General action */
} UserAction_t;

/**
 * @brief Structure containing game information.
 */
typedef struct {
  int **field;    /**< Game field matrix */
  int **next;     /**< Next piece matrix */
  int score;      /**< Current score */
  int high_score; /**< High score */
  int level;      /**< Current level */
  int speed;      /**< Current speed */
  int pause;      /**< Pause status */
} GameInfo_t;

/**
 * @brief Enum representing finite state machine states.
 */
typedef enum {
  INIT = 8,  /**< Initial state */
  START,     /**< Start state */
  SPAWN,     /**< Spawn state */
  MOVING,    /**< Moving state */
  ATTACHING, /**< Attaching state */
  SHIFTING,  /**< Shifting state */
  PAUSE,     /**< Pause state */
  GAMEOVER   /**< Game over state */
} Fsm_states;

/**
 * @brief Enum representing types of shapes.
 */
typedef enum {
  I_SHAPE = 0, /**< I shape */
  J_SHAPE,     /**< J shape */
  L_SHAPE,     /**< L shape */
  O_SHAPE,     /**< O shape */
  S_SHAPE,     /**< S shape */
  T_SHAPE,     /**< T shape */
  Z_SHAPE,     /**< Z shape */
  NUM_SHAPES   /**< Number of shapes */
} ShapeType;

/**
 * @brief Enum representing collision types.
 */
typedef enum {
  COLLISION_LEFT = 1, /**< Collision on the left */
  COLLISION_RIGHT,    /**< Collision on the right */
  COLLISION_DOWN,     /**< Collision at the bottom */
  COLLISION_FIGURE,   /**< Collision with another figure */
  COLLISION_DL,       /**< Collision at the bottom-left */
  COLLISION_DR        /**< Collision at the bottom-right */
} CollisionType;

/**
 * @brief Structure representing the game field.
 */
typedef struct {
  int **field; /**< Game field matrix */
} Game_field_t;

/**
 * @brief Structure representing a figure in the game.
 */
typedef struct {
  int x;                                      /**< X position */
  int y;                                      /**< Y position */
  int figure[NUM_SHAPES][FIGURE_M][FIGURE_N]; /**< Figure matrix */
  int figure_height;                          /**< Height of the figure */
  int figure_width;                           /**< Width of the figure */
  int type;                                   /**< Type of the figure */
  int rotation;                               /**< Rotation state */
  int next_x;                                 /**< Next X position */
  int next_y;                                 /**< Next Y position */
  int **next_figure;                          /**< Matrix of the next figure */
  int next_figure_height;                     /**< Height of the next figure */
  int next_figure_width;                      /**< Width of the next figure */
  int next_type;                              /**< Type of the next figure */
} Figure_t;

/**
 * @brief Structure representing the game status.
 */
typedef struct {
  Fsm_states status; /**< Current FSM state */
  int pause;         /**< Pause status */
  int win;           /**< Win status */
  int is_playing;    /**< Is playing status */
} Game_status_t;

/**
 * @brief Structure representing game statistics.
 */
typedef struct {
  int score;      /**< Current score */
  int high_score; /**< High score */
  int level;      /**< Current level */
  int speed;      /**< Current speed */
} Game_stats_t;

/**
 * @brief Structure representing the overall game state.
 */
typedef struct {
  Game_field_t field;   /**< Game field */
  Figure_t figure;      /**< Current figure */
  Game_status_t status; /**< Current game status */
  Game_stats_t stats;   /**< Game statistics */
} Game_state_t;
#endif
