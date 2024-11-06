
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

void init_figure(Figure_t *figure_t) {
  figure_t->x = COLS_GAME / 2 - 2;
  figure_t->y = 0;

  srand(time(NULL));
  int rnd_figure = rand() % 7;

  figure_t->type = rnd_figure;
  figure_t->figure_size = 4;
  figure_t->next_figure_size = 4;

  // for (int i = 0; i < figure_t->figure_size; i++) {
  //   for (int j = 0; j < figure_t->figure_size; j++) {
  //     figure_t->figure[0][i][j] = 0;
  //   }
  // }

  // for (int i = 0; i < figure_t->figure_size; i++) {
  //   for (int j = 0; j < figure_t->figure_size; j++) {
  //     figure_t->next_figure[0][i][j] = 0;
  //   }
  // }
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
void init_game_state(Game_state_t *game_state, Game_field_t *field) {
  game_state = get_game_state();

  init_field(field);
  game_state->field = field;

  init_figure(&game_state->figure);

  init_game_status(&game_state->status);

  init_game_stats(&game_state->stats);
}

// ______________

void free_game(Game_state_t *game, Game_field_t *field) {
  free_field(field);
  free_field(game->field);

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

// адаптировать, удалить фри
void finish_game(Game_state_t *g_state) {
  if (g_state->status.status != GAMEOVER && !g_state->status.win) {
    g_state->status.is_playing = false;
    free_game(g_state, g_state->field);
    // free_field_gi(g_info);
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

int count_figure_height(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_size;

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

int count_figure_width(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = g_state->figure.figure_size;

  if (g_state->figure.type == J_SHAPE || g_state->figure.type == L_SHAPE) {
    figure_width = figure_width - 1;
  } else if (g_state->figure.type == O_SHAPE) {
    figure_width = 2;
  } else if (g_state->figure.type == I_SHAPE) {
    figure_width = 1;
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

  if (x + count_figure_width(g_state) - 1 >= 9) {
    collision = COLLISION_RIGHT;
  }

  if (y + count_figure_height(g_state) > 19) {
    collision = COLLISION_DOWN;
  }

  if ((y + count_figure_height(g_state) > 19) && (x < 1)) {
    collision = COLLISION_DL;
  }

  if ((y + count_figure_height(g_state) > 19) &&
      (x + count_figure_width(g_state) - 1 >= 9)) {
    collision = COLLISION_DR;
  }

  return collision;
}

int check_figure_collision(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = count_figure_width(g_state);
  int figure_height = count_figure_height(g_state);
  int type = g_state->figure.type;

  int collision = 0;

  int b_collision = border_collision(g_state);

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int y = i + g_state->figure.y;
      int x = j + g_state->figure.x;

      if (g_state->field && (y + 1 <= 19) && figures[type][i][j] == 1) {
        if (g_state->field->field[y + 1][x] != 1) {
          // g_state->field->field[y + 1][x] = 3;
          collision = 0;
        } else if (b_collision != COLLISION_DOWN &&
                   b_collision != COLLISION_DR && b_collision != COLLISION_DL) {
          collision = COLLISION_FIGURE;
        }
      }
      // if (g_state->field && (y + figure_height + 1 < 19) &&
      //     (figures[type][i][j] == 1) &&
      //     (g_state->field->field[i + 1][j] == 1)) {
      //   collision = COLLISION_FIGURE;
      // break;
      // }
    }
    // collision = 0;
  }

  return collision;
}

int check_collision(Game_state_t *g_state) {
  g_state = get_game_state();

  // int figure_width = count_figure_width(g_state);
  // int figure_height = count_figure_height(g_state);
  // int type = g_state->figure.type;

  int collision = 0;
  // int border_collision = 1;

  collision = border_collision(g_state);

  return collision;
}

void figure_to_field(Game_state_t *g_state, int figures[NUM_SHAPES][4][4]) {
  g_state = get_game_state();

  int figure_width = count_figure_width(g_state);
  int figure_height = count_figure_height(g_state);

  // g_state->figure.type == J_SHAPE || g_state->figure.type == L_SHAPE ||

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && (figures[g_state->figure.type][i][j] == 1)) {
        g_state->field->field[field_y][field_x] = 1;
      }
      //  else {
      //   g_state->field->field[field_y][field_x] = 0;
      // }

      // // показать поля вокруг фигуры
      // if (figures[g_state->figure.type][i][j] == 0 && g_state->field) {
      //   g_state->field->field[field_y][field_x] = 3;
      // }
    }
  }
}

void clear_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = count_figure_width(g_state);
  int figure_height = count_figure_height(g_state);

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

void create_figure_2(Game_state_t *g_state, int type) {
  g_state = get_game_state();

  g_state->figure.type = type;
  // центрируем фигуру по Х: g_state->figure.x - figure_t->figure_size / 2;
  g_state->figure.x = COLS_GAME / 2 - count_figure_width(g_state) / 2;
  g_state->figure.y = 0;

  switch (type) {
    case I_SHAPE:
      g_state->figure.figure_size = 4;
      break;
    case J_SHAPE:
      g_state->figure.figure_size = 3;
      break;
    case L_SHAPE:
      g_state->figure.figure_size = 3;
      break;
    case O_SHAPE:
      g_state->figure.figure_size = 2;
      break;
    case S_SHAPE:
      g_state->figure.figure_size = 3;
      break;
    case T_SHAPE:
      g_state->figure.figure_size = 3;
      break;
    case Z_SHAPE:
      g_state->figure.figure_size = 3;
      break;
    default:
      break;
  }

  // явное задание типа фигуры
  // g_state->figure.type = I_SHAPE;
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

GameInfo_t copy_game_to_gi(Game_state_t *g_state) {
  g_state = get_game_state();
  GameInfo_t g_info = updateCurrentState();

  g_info.score = g_state->stats.score;
  g_info.high_score = g_state->stats.high_score;
  g_info.level = g_state->stats.level;
  g_info.speed = g_state->stats.speed;
  g_info.pause = g_state->status.pause;

  int error_on_field_init = init_field_gi(&g_info);
  if (!error_on_field_init && g_state->field) {
    copy_field(FIELD_N, FIELD_M, g_state->field->field, g_info.field);
  }

  return g_info;
}

GameInfo_t updateCurrentState() {
  static GameInfo_t g_info = {0};
  return g_info;
}

void on_init_state(Game_state_t *g_state, UserAction_t action) {
  switch (action) {
    case Start:
      g_state->status.is_playing = true;
      g_state->status.status = START;
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

void on_start_state(Game_state_t *g_state, UserAction_t action) {
  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      if (g_state->status.is_playing) {
        g_state->status.status = SPAWN;
      }
      break;
  }
}

void on_spawn_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  srand(time(NULL));
  int rnd_figure = rand() % 7;

  create_figure_2(g_state, rnd_figure);

  // if ((g_state->figure.type > -1) && (g_state->figure.type < 7)) {
  figure_to_field(g_state, figures);
  // }

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

  g_state->figure.x--;
  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING : MOVING;
}

void move_right(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.x++;
  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING : MOVING;
}

void move_down(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y++;
  // g_state->status.status = figure_is_attaching(g_state) ? ATTACHING : MOVING;
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

  for (int i = 0; i < g_state->figure.figure_size && !is_attaching; i++) {
    for (int j = 0; j < g_state->figure.figure_size && !is_attaching; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      if ((g_state->figure.figure[g_state->figure.type][i][j] == 1) &&
          (y > FIELD_N - 1 || (y > -1 && (g_state->field->field[y][x] == 1))))
        is_attaching = true;
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

void on_move_state(Game_state_t *g_state, UserAction_t action, int collision) {
  // if (check_collision(g_state)) {
  //   g_state->status.status = ATTACHING;
  // }

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Left:
      collision = check_collision(g_state);
      // collision = border_collision(g_state);

      clear_figure(g_state);
      if (collision != COLLISION_LEFT && collision != COLLISION_DL) {
        move_left(g_state);
      }
      // figure_to_field(g_state, figures);
      break;
    case Right:
      collision = check_collision(g_state);
      // collision = border_collision(g_state);

      clear_figure(g_state);
      if (collision != COLLISION_RIGHT && collision != COLLISION_DR) {
        move_right(g_state);
      }
      // figure_to_field(g_state, figures);
      break;
    case Down:
      collision = check_collision(g_state);
      // collision = border_collision(g_state);

      clear_figure(g_state);
      if (collision != COLLISION_DOWN && collision != COLLISION_DL &&
          collision != COLLISION_DR &&
          check_figure_collision(g_state) != COLLISION_FIGURE) {
        move_down(g_state);
      } else {
        g_state->status.status = SPAWN;
      }
      // figure_to_field(g_state, figures);
      break;
    case Up:
      // collision = check_collision(g_state);
      // collision = border_collision(g_state);

      clear_figure(g_state);
      // if (collision != COLLISION_FIGURE) {
      move_up(g_state);
      // }
      // figure_to_field(g_state, figures);
      break;
    case Action:
      // move_in_array(g_state);
      clear_figure(g_state);
      // figure_to_field(g_state, figures);
      // move_in_array(g_state);
      figure_to_field(g_state, figures);
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
      g_state->status.status = MOVING;
      // }
      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  Game_state_t *g_state = get_game_state();
  int current_fsm_state = g_state->status.status;
  // GameInfo_t g_info = update_current_state(g_state);

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
      break;
    case MOVING:
      // printf("moving\n");
      on_move_state(g_state, action, 0);
      figure_to_field(g_state, figures);
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
