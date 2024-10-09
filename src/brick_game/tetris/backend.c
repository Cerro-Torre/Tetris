#include "../inc/tetris_backend.h"

// GameInfo_t updateCurrentState();

// void draw_figure_1(GameInfo_t *game) {
//   char tetro_1[4][4] = {
//       "1111",
//       "0000",
//       "0000",
//       "0000",
//   };

//   for (int i = 1; i < GAME_SCREEN_HEIGHT; i++) {
//     for (int j = 1; j < 4; j++) {
//       if (tetro_1[i][j] == '1') {
//         game->field[i][j] = 1;
//         printw("%c", game->field[i][j]);
//       }
//     }
//   }
// }

// void print_test() {
//   char test[4][4] = {{'0', '0', '0', '0'},
//                      {'1', '1', '1', '1'},
//                      {'0', '0', '0', '0'},
//                      {'0', '0', '0', '0'}};
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       // printw("%c", test[i]);
//       if (test[i][j] == '1') {
//         printw("%c", ACS_BLOCK);
//       }
//       // printw("%c", test[i][j]);
//     }
//   }
// }

void init_game(GameInfo_t *game) {
  game->level = 1;
  game->score = 1;
  game->high_score = 1;
  game->speed = 1;
  game->pause = 1;
  game->next = (int **)calloc(GAME_SCREEN_WIDTH, sizeof(int *));

  for (int i = 0; i < GAME_SCREEN_WIDTH; i++) {
    game->next[i] = (int *)calloc(COLS_MAP, sizeof(int));
  }

  game->field = (int **)calloc(GAME_SCREEN_WIDTH, sizeof(int *));

  for (int i = 0; i < GAME_SCREEN_WIDTH; i++) {
    game->field[i] = (int *)calloc(COLS_MAP, sizeof(int));
  }
}

// __________________

int init_field(Game_field_t *field_t) {
  int error = 0;
  field_t->field = (int **)calloc(ROWS_MAP, sizeof(int *));

  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_MAP; i++) {
      field_t->field[i] = (int *)calloc(COLS_MAP, sizeof(int));
    }
  } else {
    free(field_t->field);
    field_t->field = NULL;
    error = 1;
  }

  field_t->x = 21;
  field_t->y = 1;
  return error;
}

void free_field(Game_field_t *field_t) {
  for (int i = 0; i < ROWS_MAP; i++) {
    free(field_t->field[i]);
  }
  free(field_t->field);
}

void free_field_gs(Game_state_t *game_state) {
  // Game_field_t *field_t = &game_state->field;
  for (int i = 0; i < ROWS_MAP; i++) {
    free(game_state->field.field[i]);
  }
  free(game_state->field.field);
}

void init_figure(Figure_t *figure_t) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure_t->figure[i][j] = 1;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure_t->next_figure[i][j] = 0;
    }
  }

  figure_t->type = 0;
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
  game_stats->score = 21;
  game_stats->high_score = 1;
  game_stats->speed = 1;
}

Game_state_t *get_game_state() {
  static Game_state_t game_state;
  return &game_state;
}

// ________инициализация одной функцией________
void init_game_state(Game_state_t *game_state) {
  game_state = get_game_state();

  // Game_field_t field;
  init_field(&game_state->field);

  // Figure_t figure;
  init_figure(&game_state->figure);

  // Game_status_t status;
  init_game_status(&game_state->status);

  // Game_stats_t stats;
  init_game_stats(&game_state->stats);
}

// ______________

void free_game(GameInfo_t *game) {
  for (int i = 0; i < GAME_SCREEN_WIDTH; i++) {
    free(game->field[i]);
    free(game->next[i]);
  }
  free(game->field);
  free(game->next);

  game->level = 0;
  game->score = 0;
  game->high_score = 0;
  game->speed = 0;
  game->pause = 0;
}

// void userInput(UserAction_t action, bool hold) {
//   switch (action) {
//     case Start:
//       break;
//     case Pause:
//       break;
//     case Terminate:
//       break;
//     case Left:
//       break;
//     case Right:
//       break;
//     case Up:
//       break;
//     case Down:
//       break;
//     case Action:
//       break;
//     default:
//       break;
//   }

//   // updateCurrentState();

//   // if (hold) {
//   //   userInput(action, hold);
//   // }
// }
