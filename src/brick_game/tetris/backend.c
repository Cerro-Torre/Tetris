
#include "../inc/tetris_backend.h"

int **init_array(int rows, int cols) {
  // array = NULL;

  // int error = 0;
  int **array = (int **)calloc(rows, sizeof(int *));

  if (array != NULL) {
    for (int i = 0; i < rows; i++) {
      array[i] = (int *)calloc(cols, sizeof(int));
    }
  } else {
    free(array);
    array = NULL;
    // error = 1;
  }

  return array;
}

void free_array(int rows, int **array) {
  if (array != NULL) {
    for (int i = 0; i < rows; i++) {
      free(array[i]);
    }
    free(array);
  }

  array = NULL;
}

GameInfo_t init_game_info() {
  GameInfo_t g_info = updateCurrentState();

  g_info.field = init_array(ROWS_GAME, COLS_GAME);
  g_info.next = init_array(4, 4);

  g_info.score = 0;
  g_info.high_score = 0;
  g_info.level = 0;
  g_info.speed = 0;
  g_info.pause = 0;

  return g_info;
}

GameInfo_t updateCurrentState() {
  static GameInfo_t g_info;
  return g_info;
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

void fill_next_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  for (int i = 0; i < g_state->figure.next_figure_height; i++) {
    for (int j = 0; j < g_state->figure.next_figure_width; j++) {
      g_state->figure.next_figure[i][j] =
          figures[g_state->figure.next_type][i][j];
    }
  }
}

void init_next_figure(Game_state_t *g_state) {
  g_state = get_game_state();

  srand(time(NULL));
  int rnd_figure = rand() % 6;
  g_state->figure.next_type = rnd_figure;

  g_state->figure.next_figure = init_array(4, 4);

  g_state->figure.next_x = 0;
  g_state->figure.next_y = 0;

  int figure_height = 4;
  int figure_width = 4;
  g_state->figure.next_figure_height = figure_height;
  g_state->figure.next_figure_width = figure_width;

  if ((g_state != NULL) && (g_state->figure.next_figure != NULL)) {
    fill_next_figure(g_state);
  }
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

void init_game_stats(Game_stats_t *game_stats) {
  game_stats->level = 1;
  game_stats->score = 0;
  game_stats->high_score = 0;
  game_stats->speed = 1;
}

Game_state_t *get_game_state() {
  static Game_state_t game_state = {0};
  return &game_state;
}

void init_game_state(Game_state_t *g_state) {
  g_state = get_game_state();

  // init_field(g_state);
  // init_array(ROWS_GAME, COLS_GAME, g_state->field.field);
  // g_state->field = field;

  g_state->field.field = init_array(ROWS_GAME, COLS_GAME);
  // g_state->figure.next_figure = init_array(4, 4);

  init_next_figure(g_state);

  // if (!error_on_init_next) {
  init_figure(g_state);
  // }

  init_game_status(&g_state->status);

  init_game_stats(&g_state->stats);
}

void free_game(Game_state_t *g_state) {
  g_state = get_game_state();
  GameInfo_t g_info = updateCurrentState();

  if (g_state->field.field) {
    free_array(ROWS_GAME, g_state->field.field);
    g_state->field.field = NULL;
  }

  if (g_info.field) {
    free_array(ROWS_GAME, g_info.field);
    g_info.field = NULL;
  }

  if (g_state->figure.next_figure) {
    free_array(4, g_state->figure.next_figure);
    g_state->figure.next_figure = NULL;
  }

  if (g_info.next) {
    free_array(4, g_info.next);
    g_info.next = NULL;
  }

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

void free_game_gi(GameInfo_t *g_info) {
  if (g_info) {
    if (g_info->field) {
      free_array(ROWS_GAME, g_info->field);
      g_info->field = NULL;
    }

    if (g_info->next) {
      free_array(4, g_info->next);
      g_info->next = NULL;
    }
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

      if ((g_state->field.field) && (y < ROWS_GAME - 1) &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1 &&
          (g_state->field.field[y + 1][x] == 9))

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

      if (g_state->field.field && (g_state->figure.figure[type][i][j] == 1)) {
        g_state->field.field[field_y][field_x] = 1;
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

      if (g_state->field.field &&
          (g_state->figure.figure[g_state->figure.type][i][j] == 1) &&
          (g_state->field.field[field_y][field_x] == 1)) {
        g_state->field.field[field_y][field_x] = 0;
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

void copy_game_to_gi(Game_state_t *g_state, GameInfo_t *g_info) {
  g_info->score = g_state->stats.score;
  g_info->high_score = g_state->stats.high_score;
  g_info->level = g_state->stats.level;
  g_info->speed = g_state->stats.speed;
  g_info->pause = g_state->status.pause;

  g_info->field = init_array(ROWS_GAME, COLS_GAME);
  copy_field(ROWS_GAME, COLS_GAME, g_state->field.field, g_info->field);

  g_info->next = init_array(4, 4);
  copy_field(4, 4, g_state->figure.next_figure, g_info->next);
}

void shift_lines(Game_state_t *g_state, int i) {
  for (int row = i; row > 0; row--) {
    for (int k = 0; k < FIELD_M; k++) {
      g_state->field.field[row][k] = g_state->field.field[row - 1][k];
    }
  }
}

void collapse_full_lines(Game_state_t *g_state) {
  int num_full_lines = 0;

  for (int i = ROWS_GAME - 1; i >= 0; i--) {
    int line_is_full = 0;
    for (int j = 0; j < COLS_GAME; j++) {
      line_is_full += g_state->field.field[i][j];
    }

    if (line_is_full / 9 == COLS_GAME) {
      shift_lines(g_state, i);
      num_full_lines++;
      i++;
    }
  }

  update_score(g_state, num_full_lines);
}

void update_score(Game_state_t *g_state, int num_full_lines) {
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
