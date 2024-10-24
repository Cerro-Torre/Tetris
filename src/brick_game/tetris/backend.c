
#include "../inc/tetris_backend.h"

int init_field(Game_field_t *field_t) {
  int error = 0;
  field_t->field = (int **)calloc(ROWS_GAME, sizeof(int *));

  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_GAME; i++) {
      field_t->field[i] = (int *)calloc(COLS_GAME, sizeof(int));
    }
  } else {
    free(field_t->field);
    field_t->field = NULL;
    error = 1;
  }

  field_t->x = 0;
  field_t->y = 0;
  return error;
}

int init_field_gi(GameInfo_t *field_t) {
  int error = 0;
  field_t->field = (int **)calloc(ROWS_GAME, sizeof(int *));

  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_GAME; i++) {
      field_t->field[i] = (int *)calloc(COLS_GAME, sizeof(int));
    }
  } else {
    free(field_t->field);
    field_t->field = NULL;
    error = 1;
    // printf("init_field_gi error\n");
  }

  return error;
}

void free_field(Game_field_t *field_t) {
  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_GAME; i++) {
      free(field_t->field[i]);
    }
    free(field_t->field);

    field_t->field = NULL;

    field_t->x = 0;
    field_t->y = 0;
  }
}

void free_field_gi(GameInfo_t *field_t) {
  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_GAME; i++) {
      free(field_t->field[i]);
    }
    free(field_t->field);

    field_t->field = NULL;
  }
}

// void free_field_gs(Game_state_t *game_state) {
//   // Game_field_t *field_t = &game_state->field;
//   if (game_state->field->field != NULL) {
//     for (int i = 0; i < ROWS_GAME; i++) {
//       free(game_state->field->field[i]);
//     }
//     free(game_state->field->field);
//   }
// }

void init_figure(Figure_t *figure_t) {
  figure_t->x = 0;
  figure_t->y = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure_t->figure[NUM_SHAPES][i][j] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure_t->next_figure[NUM_SHAPES][i][j] = 0;
    }
  }

  figure_t->x = COLS_GAME / 2 - 2;
  figure_t->y = 0;
  figure_t->type = -1;
  figure_t->figure_size = 4;
  figure_t->next_figure_size = 4;
}

void init_game_status(Game_status_t *game_status) {
  game_status->status = INIT;
  game_status->pause = 0;
  game_status->win = 0;
  game_status->is_playing = 0;
}

void init_game_stats(Game_stats_t *game_stats) {
  game_stats->level = 1;
  game_stats->score = 0;
  game_stats->high_score = 1;
  game_stats->speed = 1;
}

Game_state_t *get_game_state() {
  static Game_state_t game_state;
  return &game_state;
}

// ________инициализация одной функцией________
void init_game_state(Game_state_t *game_state, Game_field_t *field) {
  game_state = get_game_state();

  init_field(field);
  game_state->field = field;

  // init_field(game_state->field);

  // Figure_t figure;
  init_figure(&game_state->figure);

  // Game_status_t status;
  init_game_status(&game_state->status);

  // Game_stats_t stats;
  init_game_stats(&game_state->stats);
}

// ______________

void free_game(Game_state_t *game, Game_field_t *field) {
  // free_field_gs(game);
  // if (game->field != NULL) {
  free_field(field);
  free_field(game->field);
  // }

  // free_field_gs(game);

  // game->figure.figure[FIGURE_N][FIGURE_M] = 0;
  // game->figure.next_figure[FIGURE_N][FIGURE_M] = 0;
  game->figure.figure_size = 0;
  game->figure.next_figure_size = 0;
  game->figure.type = 0;

  game->status.status = 0;
  game->status.pause = 0;
  game->status.win = 0;
  game->status.is_playing = 0;

  game->stats.score = 0;
  game->stats.high_score = 0;
  game->stats.level = 0;
  game->stats.speed = 0;

  // game = NULL;
}

// UserAction_t get_user_action(int ch) {
//   UserAction_t action = {0};

//   if (ch == KEY_R) {
//     action = Start;
//   } else if (ch == KEY_P)
//     action = Pause;
//   else if (ch == KEY_Q)
//     action = Terminate;
//   else if (ch == KEY_LEFT) {
//     action = Left;
//     // printw("KEY_LEFT\n");
//   } else if (ch == KEY_RIGHT)
//     action = Right;
//   else if (ch == KEY_UP)
//     action = Up;
//   else if (ch == KEY_DOWN)
//     action = Down;
//   else if (ch == KEY_Z)
//     action = Action;

//   return action;
// }

void move_left(Game_state_t *g_state) {
  bool can_move = true;

  for (int i = 0; i < g_state->figure.figure_size; i++) {
    for (int j = 0; j < g_state->figure.figure_size; j++) {
      int x = g_state->field->x + j - 1;
      int y = g_state->field->y + i;

      if (g_state->figure.figure[g_state->figure.type][i][j] == '1' &&
          (x >= FIELD_M || x < 0 || g_state->field->field[y][x] == '1')) {
        can_move = false;
      }
    }
  }

  if (can_move) {
    g_state->figure.x--;
  }
  // g_state->status = figure_is_attaching(g_state) ? Attaching : Moving;
}

void move_right(Game_state_t *g_state) {
  bool can_move = true;

  for (int i = 0; i < g_state->figure.figure_size; i++) {
    for (int j = 0; j < g_state->figure.figure_size; j++) {
      int x = g_state->field->x + j - 1;
      int y = g_state->field->y + i;

      if (g_state->figure.figure[g_state->figure.type][i][j] == '1' &&
          (x >= FIELD_M || x < 0 || g_state->field->field[y][x] == '1')) {
        can_move = false;
      }
    }
  }

  if (can_move) {
    g_state->field->x++;
  }
  // g_state->status = figure_is_attaching(g_state) ? Attaching : Moving;
}

void move_figure(Game_state_t *g_state, UserAction_t action) {
  if (action == Left && !g_state->status.pause) {
    move_left(g_state);
  } else if (action == Right && !g_state->status.pause)
    move_right(g_state);
  // else if (action == Down && !g_state->status.pause)
  //   move_down(g_state);
  // else if ((action == Action || action == Up) && !g_state->status.pause)
  //   rotate(g_state);
  else if (action == Pause)
    g_state->status.pause = !g_state->status.pause;
  else if (action == Terminate)
    free_game(g_state, g_state->field);

  // if (timer(g_state, g_state->speed) && !g_state->status.pause)
  //   g_state->status = Shifting;
}

void finish_game(Game_state_t *g_state) {
  if (g_state->status.status != GAMEOVER && !g_state->status.win) {
    g_state->status.is_playing = false;
    free_game(g_state, g_state->field);
    // free_field_gi(g_info);
  }
}

void user_input(Game_state_t *g_state, UserAction_t action) {
  if (g_state->status.status == INIT) {
    if (action == Terminate) {
      // finish_game(g_state);
      // free_game(g_state, g_state->field);
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
    }
    // } else if (action == Start) {
    //   g_state->status.status = SPAWN;
    // }
    // } else if (g_state->status.status == SPAWN) {
    //   if (action == Terminate || g_state->win)
    //     finish_game(g_state);
    //   else
    //     spawn_figure(g_state);

  } else if (g_state->status.status == MOVING) {
    // printf("action = %d\n", action);
    move_figure(g_state, action);
  }
  // } else if (g_state->status.status == SHIFTING) {
  //   move_down(g_state);
  // } else if (g_state->status.status == ATTACHING) {
  //   attach_figure(g_state);
  // } else if (g_state->status.status == GAMEOVER) {
  //   finish_game(g_state);
  // }
}

// void create_figure(ShapeType type, int figure[4][4], int
// *figures[type][4][4]) {
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       figure[i][j] = *figures[type][i][j];
//     }
//   }
// }

void update_field(Game_state_t *game_state, int figure_type) {
  for (int i = 0; i < FIGURE_M; i++) {
    for (int j = 0; j < FIGURE_N; j++) {
      int x = game_state->figure.x + i;
      int y = game_state->figure.y + j;

      if (game_state->figure.figure[figure_type][i][j] == 1 &&
          game_state->figure.y > -1 && game_state->field->y < COLS_GAME &&
          game_state->figure.x > -1 && game_state->field->x < ROWS_GAME) {
        game_state->field->field[i][j] =
            game_state->figure.figure[figure_type][i + x][j + y];

        // game_state->field->field[x][y] = '#';
      }
    }
  }
}

// void fill_field(Game_state_t *game_state) {
//   for (int i = 0; i < ROWS_GAME; i++) {
//     for (int j = 0; j < COLS_GAME; j++) {
//       // if ((i == 0 && (j > 0 && j < COLS_GAME - 1)) ||
//       //     (i == ROWS_GAME - 1 && (j > 0 && j < COLS_GAME - 1)) ||
//       //     (j == 0 && (i >= 0 && i < ROWS_GAME)) ||
//       //     (j == COLS_GAME - 1 && (i >= 0 && i < ROWS_GAME))) {
//       // game_state->field->field[i][j] = '#';
//       // } else {
//       //   game_state->field->field[i][j] = ' ';
//       // }
//       game_state->field->field[i][j] = '.';
//     }
//   }
// }

// bool check_collision(Game_field_t * field_t, Figure_t * figure_t) {
//   ;
//   ;
// }

void figure_to_field(Game_state_t *game_state, int figures[NUM_SHAPES][4][4]) {
  Figure_t *figure_t = &game_state->figure;
  Game_field_t field_t = *game_state->field;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figures[figure_t->type][i][j] == 1) {
        // int field_x = figure_t->x + j;
        // int field_y = figure_t->y + i;
        // if (field_x > -1 && field_x < ROWS_GAME && field_y > -1 &&
        //     field_y < COLS_GAME) {
        //   field_t.field[field_y][field_x] = '1';
        // printf("x = %d, y = %d\n", figure_t->x + i, figure_t->y + j);

        field_t.field[figure_t->y + i][figure_t->x + j] = 1;
      }
    }
  }
}
// }

void create_figure_2(Figure_t *figure_t, int type, int y, int x) {
  figure_t->type = type;
  figure_t->x = x;
  figure_t->y = y;
}

void create_next_figure(Figure_t *figure_t, int type, int y, int x) {
  figure_t->next_type = type;
  figure_t->next_y = y;
  figure_t->next_x = x;
}

void next_figure_to_current(Figure_t *figure_t) {
  figure_t->type = figure_t->next_type;
  figure_t->x = figure_t->next_x;
  figure_t->y = figure_t->next_y;
}

void copy_field(int rows, int cols, int **src_matrix, int **dest_matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      dest_matrix[i][j] = src_matrix[i][j];
    }
  }
}

GameInfo_t update_current_state(Game_state_t *g_state) {
  GameInfo_t g_info = {0};

  g_info.score = g_state->stats.score;
  g_info.high_score = g_state->stats.high_score;
  g_info.level = g_state->stats.level;
  g_info.speed = g_state->stats.speed;
  g_info.pause = g_state->status.pause;

  int error_on_field_init = init_field_gi(&g_info);
  if (!error_on_field_init) {
    copy_field(FIELD_N, FIELD_M, g_state->field->field, g_info.field);
  }

  if (g_info.field != NULL) {
    update_field(g_state, Z_SHAPE);
  }

  // int size = g_state->next_figure_size;
  // g_info.next = create_matrix(size, size);
  // copy_matrix(size, size, g_state->next_figure, g_info.next);
  // g_info.next_size = size;

  return g_info;
}
