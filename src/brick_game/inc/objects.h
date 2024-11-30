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

typedef enum {
  INIT = 8,
  START,
  SPAWN,
  MOVING,
  ATTACHING,
  SHIFTING,
  GAMEOVER
} Fsm_states;

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

// typedef enum {
//   I_SHAPE_90 = 8,
//   J_SHAPE_90,
//   J_SHAPE_180,
//   J_SHAPE_270,
//   L_SHAPE_90,
//   L_SHAPE_180,
//   L_SHAPE_270,
//   S_SHAPE_90,
//   T_SHAPE_90,
//   T_SHAPE_180,
//   T_SHAPE_270,
//   Z_SHAPE_90,
//   ROTATED_SHAPES
// } RotatedShapeType;

typedef enum {
  COLLISION_LEFT = 1,
  COLLISION_RIGHT,
  COLLISION_DOWN,
  COLLISION_FIGURE,
  COLLISION_DL,
  COLLISION_DR
} CollisionType;

typedef struct {
  int x;
  int y;
  int **field;
} Game_field_t;

typedef struct {
  int x;
  int y;
  int figure[NUM_SHAPES][FIGURE_M][FIGURE_N];
  int figure_height;
  int figure_width;
  int type;
  bool rotated;
  int next_x;
  int next_y;
  int **next_figure;
  int next_figure_height;
  int next_figure_width;
  int next_type;
} Figure_t;

typedef struct {
  Fsm_states status;
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

#endif