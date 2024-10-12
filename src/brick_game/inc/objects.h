#ifndef __OBJECTS_H
#define __OBJECTS_H

#include "./defines.h"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// _________custom objects_________

typedef struct {
  int x;
  int y;
  int **field;
} Game_field_t;

typedef struct {
  int x;
  int y;
  int figure[FIGURE_M][FIGURE_N];
  int figure_size;
  int next_figure[FIGURE_M][FIGURE_N];
  int next_figure_size;
  int type;
} Figure_t;

typedef struct {
  int status;
  int pause;
  int win;
  int is_playing;
} Game_status_t;

typedef struct {
  int score;
  int high_score;
  int level;
  int speed;
} Game_stats_t;

typedef struct {
  Game_field_t field;
  Figure_t figure;
  Game_status_t status;
  Game_stats_t stats;
} Game_state_t;

typedef enum {
  INIT = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER
} Game_enum_t;

typedef enum {
  I_SHAPE = 0,
  J_SHAPE,
  L_SHAPE,
  O_SHAPE,
  S_SHAPE,
  T_SHAPE,
  Z_SHAPE,
  NUM_SHAPES
} ShapeType;

// // Определение трехмерного массива для хранения фигур
// static int figures[NUM_SHAPES][4][4] = {
//     // I-образная фигура
//     {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // J-образная фигура
//     {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // L-образная фигура
//     {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // O-образная фигура
//     {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // S-образная фигура
//     {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // T-образная фигура
//     {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//     // Z-образная фигура
//     {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

#endif