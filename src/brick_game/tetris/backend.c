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
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

    // J -образная фигура
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },

    // L-образная фигура
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },

    // O-образная фигура
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    // S-образная фигура
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

    // T-образная фигура
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

    // Z-образная фигура
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

};

int init_next_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  srand(time(NULL));
  int rnd_figure = rand() % 6;
  g_state->figure.next_type = rnd_figure;

  fill_next_figure(g_state);
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
  }

  return error;
}

void init_figure(Game_state_t *g_state) {
  g_state = get_game_state();

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

void free_game(Game_state_t *g_state) {
  g_state = get_game_state();
  GameInfo_t g_info = updateCurrentState();
  free_field(g_state->field);
  g_state->field = NULL;

  free_next_figure(g_state->figure.next_figure);
  free_next_figure(g_info.next);

  g_state->field = NULL;
  g_info.next = NULL;

  g_state->figure.figure_height = 0;
  g_state->figure.figure_width = 0;
  g_state->figure.type = 0;

  g_state->figure.next_figure_height = 0;
  g_state->figure.next_figure_width = 0;
  g_state->figure.next_type = 0;

  g_state->status.pause = 0;
  g_state->status.win = 0;
  g_state->status.is_playing = 0;

  g_state->stats.score = 0;
  g_state->stats.high_score = 0;
  g_state->stats.level = 0;
  g_state->stats.speed = 0;
}

void finish_game(Game_state_t *g_state) {
  if (g_state->status.status != GAMEOVER && !g_state->status.win) {
    g_state->status.is_playing = false;
    free_game(g_state);
  }
}

int figure_min_height(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;

  if (g_state->figure.type == T_SHAPE || g_state->figure.type == S_SHAPE ||
      g_state->figure.type == Z_SHAPE || g_state->figure.type == O_SHAPE) {
    figure_height = 2;
  } else if (g_state->figure.type == J_SHAPE ||
             g_state->figure.type == L_SHAPE) {
    figure_height = 3;
  } else if (g_state->figure.type == I_SHAPE) {
    figure_height = 1;
  }
  return figure_height;
}

int figure_min_width(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_width = g_state->figure.figure_width;

  if (g_state->figure.type == J_SHAPE || g_state->figure.type == L_SHAPE ||
      g_state->figure.type == O_SHAPE) {
    figure_width = 2;
  } else if (g_state->figure.type == I_SHAPE) {
    figure_width = 4;
  } else if (g_state->figure.type == T_SHAPE ||
             g_state->figure.type == S_SHAPE ||
             g_state->figure.type == Z_SHAPE) {
    figure_width = 3;
  }

  return figure_width;
}

int trim_figure_height(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = figure_min_height(g_state);
  int figure_width = figure_min_width(g_state);
  int row_is_empty = 0;

  for (int i = 0; i < figure_height; i++) {
    row_is_empty = 0;
    for (int j = 0; j < figure_width; j++) {
      if (g_state->figure.figure[g_state->figure.type][i][j] == 0 && i != 0) {
        row_is_empty++;
      }
    }

    if (row_is_empty == figure_width) {
      figure_height--;
    }
  }

  return figure_height;
}

int border_collision(Game_state_t *g_state) {
  g_state = get_game_state();

  int x = g_state->figure.x;
  int y = g_state->figure.y;
  int collision = 0;

  if (x < 1) {
    collision = COLLISION_LEFT;
  }

  if (x + g_state->figure.figure_width - 1 >= 9) {
    collision = COLLISION_RIGHT;
  }

  if (y + g_state->figure.figure_height >= ROWS_GAME) {
    collision = COLLISION_DOWN;
  }

  if ((y + g_state->figure.figure_height >= ROWS_GAME) && (x < 1)) {
    collision = COLLISION_DL;
  }

  if ((y + g_state->figure.figure_height >= ROWS_GAME) &&
      (x + g_state->figure.figure_width - 1 >= 9)) {
    collision = COLLISION_DR;
  }

  return collision;
}

bool bottom_figure_collision(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

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

void figure_to_field(Game_state_t *g_state) {
  g_state = get_game_state();

  int type = g_state->figure.type;

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && (g_state->figure.figure[type][i][j] == 1)) {
        g_state->field->field[field_y][field_x] = 1;
      }
    }
  }
}

void clear_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field &&
          (g_state->figure.figure[g_state->figure.type][i][j] == 1) &&
          (g_state->field->field[field_y][field_x] == 1 ||
           g_state->field->field[field_y][field_x] == 3)) {
        g_state->field->field[field_y][field_x] = 0;
      }
    }
  }
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
  // segfault
  // g_info.next = g_state->figure.next_figure;

  int error_on_field_init = init_field_gi(&g_info);
  if (!error_on_field_init && g_state->field) {
    copy_field(FIELD_N, FIELD_M, g_state->field->field, g_info.field);
  }

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
        fill_next_figure(g_state);

        g_state->status.status = SPAWN;
      }
      break;
  }
}

void on_spawn_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  g_state->figure.type = g_state->figure.next_type;
  g_state->figure.rotated = false;

  int figure_height = figure_min_height(g_state);
  int figure_width = figure_min_width(g_state);

  g_state->figure.figure_height = figure_height;
  g_state->figure.figure_width = figure_width;

  // next figure to current
  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      if (g_state->figure.next_figure) {
        g_state->figure.figure[g_state->figure.type][i][j] =
            g_state->figure.next_figure[i][j];
      }
    }
  }

  // create rnd next figure
  srand(time(NULL));
  int rnd_figure = rand() % 7;
  g_state->figure.next_type = rnd_figure;

  fill_next_figure(g_state);

  g_state->figure.x = COLS_GAME / 2 - g_state->figure.figure_width / 2;
  g_state->figure.y = 0;

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

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  bool figure_collision = false;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && g_state->field->field[field_y][field_x - 1] == 1 &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  if (!figure_collision) {
    g_state->figure.x--;
  }
}

void move_right(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  bool figure_collision = false;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field && g_state->field->field[field_y][field_x + 1] == 1 &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  if (!figure_collision) {
    g_state->figure.x++;
  }
}

void move_down(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y++;
}

void move_up(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y--;
}

bool figure_is_attaching(Game_state_t *g_state) {
  bool is_attaching = false;

  for (int i = 0; i < g_state->figure.figure_height && !is_attaching; i++) {
    for (int j = 0; j < g_state->figure.figure_width && !is_attaching; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      if ((y > FIELD_N - 1 || (y > -1 && (g_state->field->field[y][x] == 1)))) {
        is_attaching = true;
      }
    }
  }

  return is_attaching;
}

void on_move_state(Game_state_t *g_state, UserAction_t action) {
  int b_collision = border_collision(g_state);

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Left:

      if (b_collision != COLLISION_LEFT && b_collision != COLLISION_DL) {
        move_left(g_state);
      }
      break;
    case Right:

      if (b_collision != COLLISION_RIGHT && b_collision != COLLISION_DR) {
        move_right(g_state);
      }
      break;
    case Down:
      move_down(g_state);
      break;
    case Up:
      // clear_figure(g_state);
      // move_up(g_state);
      // figure_to_field(g_state);
      break;
    case Pause:
      g_state->status.pause = !g_state->status.pause;
      g_state->status.status = PAUSE;
      break;
    default:
      if (g_state->status.is_playing && !g_state->status.pause) {
        g_state->status.status = MOVING;
      }
      break;
  }
}

void on_attach_state(Game_state_t *g_state, UserAction_t action) {
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

      if (!f_collision && b_collision != COLLISION_DOWN && b_collision &&
          b_collision != COLLISION_DL && b_collision != COLLISION_DR &&
          !f_collision) {
        g_state->status.status = MOVING;
      } else {
        collapse_full_lines(g_state);
        g_state->status.status = SPAWN;
      }
      break;
  }
}

void shift_lines(Game_state_t *g_state, int i) {
  for (int j = i; j > 0; j--) {
    for (int k = 0; k < FIELD_M; k++) {
      g_state->field->field[j][k] = g_state->field->field[j - 1][k];
    }
  }
}

void collapse_full_lines(Game_state_t *g_state) {
  int num_full_lines = 0;

  for (int i = ROWS_GAME - 1; i >= 0; i--) {
    int line_is_full = 0;
    for (int j = 0; j < COLS_GAME; j++) {
      line_is_full += g_state->field->field[i][j];
    }

    if (line_is_full == COLS_GAME) {
      shift_lines(g_state, i);
      num_full_lines++;
      i++;
    }
  }

  update_score_and_level(g_state, num_full_lines);
}

void update_score_and_level(Game_state_t *g_state, int num_full_lines) {
  g_state = get_game_state();

  switch (num_full_lines) {
    case 1:
      g_state->stats.score += 100;
      break;
    case 2:
      g_state->stats.score += 300;
      break;
    case 3:
      g_state->stats.score += 700;
      break;
    case 4:
      g_state->stats.score += 1500;
      break;
    default:
      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  Game_state_t *g_state = get_game_state();
  int current_fsm_state = g_state->status.status;
  bool f_collision = bottom_figure_collision(g_state);
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
        if (action != Action) {
          clear_figure(g_state);
          on_move_state(g_state, action);
          figure_to_field(g_state);
        }
      }

      if (b_collision == COLLISION_DOWN || b_collision == COLLISION_DL ||
          b_collision == COLLISION_DR || f_collision) {
        g_state->status.status = ATTACHING;
      }
      break;
    case ATTACHING:
      on_attach_state(g_state, action);
      break;
    default:
      break;
  }
}