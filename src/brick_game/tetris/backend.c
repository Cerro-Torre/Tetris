
// #include <ncurses.h>

#include <time.h>

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

int init_array(int rows, int cols, int **array) {
  int error = 0;
  array = (int **)calloc(rows, sizeof(int *));

  if (array != NULL) {
    for (int i = 0; i < rows; i++) {
      array[i] = (int *)calloc(cols, sizeof(int));
    }
  } else {
    free(array);
    array = NULL;
    error = 1;
    // printf("init_field_gi error\n");
  }

  return error;
}

void free_array(int **array) {
  if (array != NULL) {
    for (int i = 0; i < 4; i++) {
      free(array[i]);
    }
    free(array);

    array = NULL;
  }
}

void init_game_info(GameInfo_t *g_info) {
  g_info->field = NULL;
  init_field_gi(g_info);

  g_info->next = NULL;
  init_array(4, 4, g_info->next);

  g_info->score = 0;
  g_info->high_score = 0;
  g_info->level = 0;
  g_info->speed = 0;
  g_info->pause = 0;
}

void free_field(Game_field_t *field_t) {
  if (field_t && field_t->field != NULL) {
    for (int i = 0; i < ROWS_GAME; i++) {
      free(field_t->field[i]);
    }
    free(field_t->field);

    field_t->field = NULL;

    field_t->x = 0;
    field_t->y = 0;
  }
}

void free_next_figure(int **figure_t) {
  if (figure_t != NULL) {
    for (int i = 0; i < 4; i++) {
      free(figure_t[i]);
    }
    free(figure_t);

    figure_t = NULL;
  }
}

GameInfo_t updateCurrentState() {
  static GameInfo_t g_info = {0};
  return g_info;
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

int figures[NUM_SHAPES][4][4] = {
    // I-образная фигура
    {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},
    // J -образная фигура
    {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
    // L-образная фигура
    {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
    // O-образная фигура
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // S-образная фигура
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // T-образная фигура
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // Z-образная фигура
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

int init_next_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.next_type = J_SHAPE;
  g_state->figure.next_x = 0;
  g_state->figure.next_y = 0;

  int figure_height = 4;
  int figure_width = 4;
  g_state->figure.next_figure_height = figure_height;
  g_state->figure.next_figure_width = figure_width;

  int error = 0;
  g_state->figure.next_figure = (int **)calloc(figure_height, sizeof(int *));

  if (g_state->figure.next_figure != NULL) {
    for (int i = 0; i < g_state->figure.next_figure_height; i++) {
      g_state->figure.next_figure[i] = (int *)calloc(figure_width, sizeof(int));
    }
  } else {
    free(g_state->figure.next_figure);
    g_state->figure.next_figure = NULL;
    error = 1;
    // printf("init_field_gi error\n");
  }

  return error;
}

void init_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  // srand(time(NULL));
  // int rnd_figure = rand() % 7;

  g_state->figure.x = 0;
  g_state->figure.y = 0;
  g_state->figure.type = g_state->figure.next_type + 1;
  g_state->figure.figure_height = 4;
  g_state->figure.figure_width = 4;

  for (int i = 0; i < g_state->figure.figure_height; i++) {
    for (int j = 0; j < g_state->figure.figure_width; j++) {
      g_state->figure.figure[g_state->figure.type][i][j] =
          figures[g_state->figure.type][i][j];
    }
  }
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
  static Game_state_t game_state = {0};
  return &game_state;
}

// ________инициализация одной функцией________
void init_game_state(Game_state_t *g_state, Game_field_t *field) {
  g_state = get_game_state();

  init_field(field);
  g_state->field = field;

  int error_on_init_next = init_next_figure(g_state);

  if (!error_on_init_next) {
    init_figure(g_state);
  }

  init_game_status(&g_state->status);

  init_game_stats(&g_state->stats);
}

// ______________

void free_game(Game_state_t *g_state) {
  g_state = get_game_state();
  GameInfo_t g_info = updateCurrentState();
  // free_field(field);
  free_field(g_state->field);
  g_state->field = NULL;

  free_next_figure(g_state->figure.next_figure);
  free_next_figure(g_info.next);

  g_state->field = NULL;
  g_info.next = NULL;

  // free_next_figure(&g_state->figure);

  g_state->figure.figure_height = 0;
  g_state->figure.figure_width = 0;
  g_state->figure.type = 0;

  g_state->figure.next_figure_height = 0;
  g_state->figure.next_figure_width = 0;
  g_state->figure.next_type = 0;

  // g_state->status.status = GAMEOVER;
  g_state->status.pause = 0;
  g_state->status.win = 0;
  g_state->status.is_playing = 0;

  g_state->stats.score = 0;
  g_state->stats.high_score = 0;
  g_state->stats.level = 0;
  g_state->stats.speed = 0;

  // game = NULL;
}

// адаптировать, удалить фри
void finish_game(Game_state_t *g_state) {
  if (g_state->status.status != GAMEOVER && !g_state->status.win) {
    g_state->status.is_playing = false;
    free_game(g_state);
    // free_field_gi(g_info);
  }
}

int trim_figure_height(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;

  if (g_state->figure.type == T_SHAPE || g_state->figure.type == S_SHAPE ||
      g_state->figure.type == Z_SHAPE || g_state->figure.type == O_SHAPE) {
    figure_height = 2;
  } else if (g_state->figure.type == J_SHAPE ||
             g_state->figure.type == L_SHAPE) {
    figure_height = 3;
  } else if (g_state->figure.type == I_SHAPE) {
    figure_height = 4;
  }

  return figure_height;
}

int trim_figure_width(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = g_state->figure.figure_width;

  if (g_state->figure.type == J_SHAPE || g_state->figure.type == L_SHAPE ||
      g_state->figure.type == O_SHAPE) {
    figure_width = 2;
  } else if (g_state->figure.type == I_SHAPE) {
    figure_width = 1;
  } else if (g_state->figure.type == T_SHAPE ||
             g_state->figure.type == S_SHAPE ||
             g_state->figure.type == Z_SHAPE) {
    figure_width = 3;
  }

  return figure_width;
}

int border_collision(Game_state_t *g_state) {
  g_state = get_game_state();

  int x = g_state->figure.x;
  int y = g_state->figure.y;
  int collision = 0;

  if ((x < 1)) {
    collision = COLLISION_LEFT;
  }

  if (x + trim_figure_width(g_state) - 1 >= 9) {
    collision = COLLISION_RIGHT;
  }

  if (y + trim_figure_height(g_state) >= ROWS_GAME) {
    collision = COLLISION_DOWN;
  }

  if ((y + trim_figure_height(g_state) >= ROWS_GAME) && (x < 1)) {
    collision = COLLISION_DL;
  }

  if ((y + trim_figure_height(g_state) >= ROWS_GAME) &&
      (x + trim_figure_width(g_state) - 1 >= 9)) {
    collision = COLLISION_DR;
  }

  return collision;
}

bool bottom_figure_collision(Game_state_t *g_state) {
  g_state = get_game_state();
  // GameInfo_t g_info = updateCurrentState(g_state);

  int figure_height = trim_figure_height(g_state);
  int figure_width = trim_figure_width(g_state);
  // int type = g_state->figure.type;

  bool f_collision = false;

  for (int i = 0; i < figure_height && !f_collision; i++) {
    for (int j = 0; j < figure_width && !f_collision; j++) {
      int y = i + g_state->figure.y;
      int x = j + g_state->figure.x;

      if ((g_state->field) && (y < ROWS_GAME - 1) &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1 &&
          (g_state->figure.figure[g_state->figure.type][i + 1][j] != 1) &&
          (g_state->field->field[y + 1][x] == 1))

      {
        f_collision = true;
      }
    }
  }

  return f_collision;
}

// int check_collision(Game_state_t *g_state) {
//   g_state = get_game_state();

//   // int figure_width = trim_figure_width(g_state);
//   // int figure_height = trim_figure_height(g_state);
//   // int type = g_state->figure.type;

//   int collision = 0;
//   // int border_collision = 1;

//   collision = border_collision(g_state);

//   return collision;
// }

void figure_to_field(Game_state_t *g_state) {
  g_state = get_game_state();

  // int figure_height = g_state->figure.figure_width;
  // int figure_width = g_state->figure.figure_height;

  int type = g_state->figure.type;
  int figure_height = trim_figure_height(g_state);
  int figure_width = trim_figure_width(g_state);

  // if (type != 6) {
  //   type = g_state->figure.type + 1;
  // } else {
  //   type = 1;
  // }

  // g_state->figure.type == J_SHAPE || g_state->figure.type == L_SHAPE ||

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && (g_state->figure.figure[type][i][j] == 1)) {
        g_state->field->field[field_y][field_x] =
            g_state->figure.figure[type][i][j];
      }
      // отображение 9 (?)
      // else if (g_state->field && (g_state->figure.figure[type][i][j] ==
      // 9)) {
      //   g_state->field->field[field_y][field_x] = 9;
      // }

      //  else {
      //   g_state->field->field[field_y][field_x] = 0;
      // }

      // // // показать ауру вокруг фигуры
      // if (figures[g_state->figure.type][i][j] == 0 && g_state->field) {
      //   g_state->field->field[field_y][field_x] = 3;
      // }
    }
  }
}

void clear_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = trim_figure_width(g_state);
  int figure_height = trim_figure_height(g_state);

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      // очистить текущую фигуру
      if (g_state->field && (figures[g_state->figure.type][i][j] == 1 ||
                             g_state->field->field[field_y][field_x] == 3)) {
        g_state->field->field[field_y][field_x] = 0;
      }
    }
  }
}

// void create_next_figure(Game_state_t *g_state, int type) {
//   g_state = get_game_state();

//   // srand(time(NULL));
//   // int type = rand() % 7;

//   // g_state->figure.type = type;
//   // центрируем фигуру по Х: g_state->figure.x - figure_t->figure_size /
//   // 2;

//   // int type = Z_SHAPE;

//   switch (type) {
//     case I_SHAPE:
//       g_state->figure.next_figure_height = 4;
//       g_state->figure.next_figure_width = 4;

//       break;
//     case J_SHAPE:
//       g_state->figure.next_figure_height = 3;
//       g_state->figure.next_figure_width = 3;
//       break;
//     case L_SHAPE:
//       g_state->figure.next_figure_height = 3;
//       g_state->figure.next_figure_width = 3;
//       break;
//     case O_SHAPE:
//       g_state->figure.next_figure_height = 2;
//       g_state->figure.next_figure_width = 2;
//       break;
//     case S_SHAPE:
//       g_state->figure.next_figure_height = 3;
//       g_state->figure.next_figure_width = 3;
//       break;
//     case T_SHAPE:
//       g_state->figure.next_figure_height = 3;
//       g_state->figure.next_figure_width = 3;
//       break;
//     case Z_SHAPE:
//       g_state->figure.next_figure_height = 3;
//       g_state->figure.next_figure_width = 3;
//       break;
//     default:
//       break;
//   }

//   g_state->figure.next_x =
//       COLS_GAME / 2 - g_state->figure.next_figure_width / 2;
//   g_state->figure.next_y = 0;

//   for (int i = 0; i < g_state->figure.next_figure_height; i++) {
//     for (int j = 0; j < g_state->figure.next_figure_width; j++) {
//       if (g_state->figure.next_figure) {
//         g_state->figure.next_figure[i][j] = figures[type][i][j];
//       }
//     }
//   }

//   // явное задание типа фигуры
//   // g_state->figure.type = S_SHAPE;
// }

// void create_next_figure(Figure_t *figure_t, int type, int y, int x) {
//   figure_t->next_type = type;
//   figure_t->next_y = y;
//   figure_t->next_x = x;
// }

// void next_figure_to_current(Game_state_t *g_state) {
//   g_state = get_game_state();
//   g_state->figure.type = g_state->figure.next_type;
//   g_state->figure.x = trim_figure_width(g_state) / 2;
//   g_state->figure.y = 0;

//   if (g_state->figure.next_figure && g_state->figure.figure) {
//     for (int i = 0; i < g_state->figure.figure_height; i++) {
//       for (int j = 0; j < g_state->figure.figure_width; j++) {
//         g_state->figure.figure[g_state->figure.type][i][j] =
//             g_state->figure.next_figure[i][j];
//       }
//     }
//   }
// }

void copy_field(int rows, int cols, int **src_matrix, int **dest_matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      dest_matrix[i][j] = src_matrix[i][j];
    }
  }
}

// void copy_next(int rows, int cols, int **src_matrix, int **dest_matrix)
// {
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       dest_matrix[i][j] = src_matrix[i][j];
//     }
//   }
// }

GameInfo_t copy_game_to_gi(Game_state_t *g_state) {
  g_state = get_game_state();
  GameInfo_t g_info = updateCurrentState();

  g_info.score = g_state->stats.score;
  g_info.high_score = g_state->stats.high_score;
  g_info.level = g_state->stats.level;
  g_info.speed = g_state->stats.speed;
  g_info.pause = g_state->status.pause;
  // segfault
  // g_info.next = g_state->figure.next_figure;

  int error_on_field_init = init_field_gi(&g_info);
  if (!error_on_field_init && g_state->field) {
    copy_field(FIELD_N, FIELD_M, g_state->field->field, g_info.field);
  }

  // int error_on_next_init = init_field_gi(&g_info);
  // if (!error_on_next_init && g_state->figure.next_figure) {
  //   copy_field(g_state->figure.next_figure_height,
  //              g_state->figure.next_figure_width,
  //              &g_state->figure.next_figure[g_state->figure.type],
  //              g_info.next);
  // }

  return g_info;
}

void on_init_state(Game_state_t *g_state, UserAction_t action) {
  switch (action) {
    case Start:
      g_state->status.is_playing = true;
      g_state->status.status = START;
      // create_next_figure(g_state, S_SHAPE);
      break;
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      g_state->status.status = INIT;
      break;
  }
}

void fill_next_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  for (int i = 0; i < g_state->figure.next_figure_height; i++) {
    for (int j = 0; j < g_state->figure.next_figure_width; j++) {
      g_state->figure.next_figure[i][j] =
          figures[g_state->figure.next_type][i][j];
    }
  }
}

void on_start_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      if (g_state->status.is_playing) {
        //   srand(time(NULL));
        //   int rnd_figure = rand() % 7;
        // figure_to_field(g_state);
        //   g_state->figure.next_type = rnd_figure;
        //   create_next_figure(g_state, g_state->figure.next_type);

        fill_next_figure(g_state);

        g_state->status.status = SPAWN;
      }
      break;
  }
}

void on_spawn_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  g_state->figure.type = g_state->figure.next_type;

  // next figure to current
  for (int i = 0; i < g_state->figure.figure_height; i++) {
    for (int j = 0; j < g_state->figure.figure_width; j++) {
      g_state->figure.figure[g_state->figure.type][i][j] =
          g_state->figure.next_figure[i][j];
    }
  }

  // create rnd next figure
  srand(time(NULL));
  int rnd_figure = rand() % 7;
  g_state->figure.next_type = rnd_figure;

  fill_next_figure(g_state);

  // установка начальной позиции figure
  g_state->figure.x = COLS_GAME / 2 - g_state->figure.figure_width / 2 + 1;
  g_state->figure.y = 0;

  // figure_to_field(g_state);

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      if (g_state->status.is_playing) {
        g_state->status.status = MOVING;
      }
      break;
  }
}

void move_left(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = trim_figure_height(g_state);
  int figure_width = trim_figure_width(g_state);

  bool figure_collision = false;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && g_state->field->field[field_y][field_x - 1] == 1 &&
          figures[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  // bool bottom_fig_coll = bottom_figure_collision(g_state);

  if (!figure_collision) {
    g_state->figure.x--;
  }

  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING :
  // MOVING;
}

void move_right(Game_state_t *g_state) {
  g_state = get_game_state();

  // bool fig_on_the_right = right_figure_collision(g_state);

  int figure_width = trim_figure_width(g_state);
  int figure_height = trim_figure_height(g_state);

  bool figure_collision = false;

  // int b_collision = border_collision(g_state);

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && g_state->field->field[field_y][field_x + 1] == 1 &&
          figures[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  if (!figure_collision) {
    g_state->figure.x++;
  }

  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING :
  // MOVING;
}

void move_down(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y++;
  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING :
  // MOVING;
}

void move_up(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y--;
}

// experiment for rotation
// int move_in_array(Game_state_t *g_state) {
//   g_state = get_game_state();

//   int x = g_state->figure.x;
//   int y = g_state->figure.y;
//   int size_x = g_state->figure.figure_size;
//   int size_y = g_state->figure.figure_size;
//   int type = g_state->figure.type;

//   // g_state->field->field[y][x] = 3;

//   int temp_figure[NUM_SHAPES][4][4] = {0};

//   for (int i = 0; i < size_y; i++) {
//     for (int j = 0; j < size_x; j++) {
//       temp_figure[type][i][j] = 0;

//       g_state->field->field[y + i][x + j] = temp_figure[type][i][j];
//     }
//   }

//   return temp_figure[NUM_SHAPES][4][4];
// }

bool figure_is_attaching(Game_state_t *g_state) {
  bool is_attaching = false;

  for (int i = 0; i < g_state->figure.figure_height && !is_attaching; i++) {
    for (int j = 0; j < g_state->figure.figure_width && !is_attaching; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      if ((figures[g_state->figure.type][i][j] == 1) &&
          (y > FIELD_N - 1 || (y > -1 && (g_state->field->field[y][x] == 1)))) {
        is_attaching = true;
      }
    }
  }

  return is_attaching;
}

// _________возможно пригодится чтобы сократить код
// void move_figure(Game_state_t *g_state, UserAction_t action) {
//   if (action == Left && !g_state->status.pause) {
//     move_left(g_state);
//   } else if (action == Right && !g_state->status.pause)
//     move_right(g_state);
//   // else if (action == Down && !g_state->status.pause)
//   //   move_down(g_state);
//   // else if ((action == Action || action == Up) &&
//   !g_state->status.pause)
//   //   rotate(g_state);
//   else if (action == Pause)
//     g_state->status.pause = !g_state->status.pause;
//   else if (action == Terminate)
//     free_game(g_state, g_state->field);

//   // if (timer(g_state, g_state->speed) && !g_state->status.pause)
//   //   g_state->status = Shifting;
// }

void on_move_state(Game_state_t *g_state, UserAction_t action) {
  // if (check_collision(g_state)) {
  //   g_state->status.status = ATTACHING;
  // }
  int b_collision = border_collision(g_state);
  // int f_collision = bottom_figure_collision(g_state);

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Left:
      // collision = check_collision(g_state);
      // collision = border_collision(g_state);

      if (b_collision != COLLISION_LEFT && b_collision != COLLISION_DL) {
        // clear_figure(g_state);
        move_left(g_state);
        // figure_to_field(g_state);
      }
      // figure_to_field(g_state, figures);
      break;
    case Right:
      // b_collision = border_collision(g_state);
      // collision = border_collision(g_state);

      if (b_collision != COLLISION_RIGHT && b_collision != COLLISION_DR) {
        // clear_figure(g_state);
        move_right(g_state);
        // figure_to_field(g_state);
      }
      // figure_to_field(g_state, figures);
      break;
    case Down:
      // collision = check_collision(g_state);
      // collision = border_collision(g_state);

      // clear_figure(g_state);
      // if ((b_collision != COLLISION_DOWN && b_collision != COLLISION_DL
      // &&
      //  b_collision != COLLISION_DR)) {
      // if (!f_collision) {
      move_down(g_state);
      // }
      // else {
      // g_state->status.status = ATTACHING;
      // }
      // figure_to_field(g_state);
      // } else {
      //   g_state->status.status = SPAWN;
      // }
      break;
    case Up:
      // collision = check_collision(g_state);
      // collision = border_collision(g_state);

      clear_figure(g_state);
      // if (collision != COLLISION_FIGURE) {
      move_up(g_state);
      figure_to_field(g_state);
      // }
      break;
    case Action:
      // move_in_array(g_state);
      // clear_figure(g_state);
      // figure_to_field(g_state, figures);
      // move_in_array(g_state);
      // figure_to_field(g_state);
      g_state->status.status = SPAWN;
      break;
    case Pause:
      g_state->status.pause = !g_state->status.pause;
      break;
    default:

      if (g_state->status.is_playing) {
        g_state->status.status = MOVING;
      }
      break;
  }
}

void on_attach_state(Game_state_t *g_state, UserAction_t action) {
  // int b_collision = border_collision(g_state);
  bool f_collision = bottom_figure_collision(g_state);
  int b_collision = border_collision(g_state);

  if (g_state->figure.y <= 0 && f_collision) {
    g_state->status.is_playing = false;
    g_state->status.status = GAMEOVER;
  }

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      // if (g_state->status.is_playing) {
      //   g_state->status.status = SPAWN;
      // }
      // if (g_state->status.is_playing) {
      // g_state->status.status = MOVING;
      // }

      if (!f_collision && b_collision != COLLISION_DOWN && b_collision &&
          b_collision != COLLISION_DL && b_collision != COLLISION_DR &&
          !f_collision) {
        // figure_to_field(g_state);
        g_state->status.status = MOVING;
      } else {
        // figure_to_field(g_state);
        g_state->status.status = SPAWN;
      }
      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  Game_state_t *g_state = get_game_state();
  int current_fsm_state = g_state->status.status;
  int f_collision = bottom_figure_collision(g_state);
  int b_collision = border_collision(g_state);

  (hold) ? printf("hold") : false;

  switch (current_fsm_state) {
    case INIT:
      on_init_state(g_state, action);
      break;
    case START:
      on_start_state(g_state, action);
      break;
    case SPAWN:
      on_spawn_state(g_state, action);
      figure_to_field(g_state);
      break;
    case MOVING:
      f_collision = bottom_figure_collision(g_state);

      if (b_collision != COLLISION_DOWN && b_collision != COLLISION_DL &&
          b_collision != COLLISION_DR && !f_collision) {
        // if (!f_collision) {
        // f_collision = bottom_figure_collision(g_state);
        // clear_figure(g_state);

        clear_figure(g_state);
        on_move_state(g_state, action);
        figure_to_field(g_state);
        // if (!bottom_figure_collision(g_state)) {
        // }
        // }
        // f_collision = bottom_figure_collision(g_state);
      } else {
        g_state->status.status = ATTACHING;
      }

      break;
    // case SHIFTING:
    //   move_down(g_state);
    //   break;
    case ATTACHING:
      on_attach_state(g_state, action);
      break;
    // case GAMEOVER:
    //   finish_game(g_state);
    //   break;
    default:
      break;
  }
}
