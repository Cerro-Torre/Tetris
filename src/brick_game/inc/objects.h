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

typedef struct {
  int x;
  int y;
  int figure[NUM_SHAPES][FIGURE_M][FIGURE_N];
  int figure_size;
  int next_figure[NUM_SHAPES][FIGURE_M][FIGURE_N];
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
  Game_field_t *field;
  Figure_t figure;
  Game_status_t status;
  Game_stats_t stats;
} Game_state_t;

typedef enum {
  INIT = 0,
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER
} Game_enum_t;

#endif