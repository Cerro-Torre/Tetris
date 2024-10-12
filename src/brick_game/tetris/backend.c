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
  if (field_t->field != NULL) {
    for (int i = 0; i < ROWS_MAP; i++) {
      free(field_t->field[i]);
    }
    free(field_t->field);
  }
}

void free_field_gs(Game_state_t *game_state) {
  // Game_field_t *field_t = &game_state->field;
  if (game_state->field.field != NULL) {
    for (int i = 0; i < ROWS_MAP; i++) {
      free(game_state->field.field[i]);
    }
    free(game_state->field.field);
  }
}

void init_figure(Figure_t *figure_t) {
  figure_t->x = 0;
  figure_t->y = 0;

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
  game_status->is_playing = 1;
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

void free_game(Game_state_t *game) {
  free_field_gs(game);

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
}

UserAction_t get_user_action(int ch) {
  UserAction_t action = {-1};

  if (ch == KEY_R) {
    action = Start;
  } else if (ch == KEY_P)
    action = Pause;
  else if (ch == KEY_Q)
    action = Terminate;
  else if (ch == KEY_LEFT)
    action = Left;
  else if (ch == KEY_RIGHT)
    action = Right;
  else if (ch == KEY_UP)
    action = Up;
  else if (ch == KEY_DOWN)
    action = Down;
  else if (ch == KEY_Z)
    action = Action;

  return action;
}

// void userInput(Game_state_t *gs, UserAction_t action) {
//   if (gs->status == Initial) {
//     if (action == Terminate)
//       finish_game(gs);
//     else if (action == Start)
//       gs->status = Spawn;

//   } else if (gs->status == Spawn) {
//     if (action == Terminate || gs->win)
//       finish_game(gs);
//     else
//       spawn_figure(gs);

//   } else if (gs->status == Moving) {
//     move_figure(gs, action);
//   } else if (gs->status == Shifting) {
//     move_down(gs);
//   } else if (gs->status == Attaching) {
//     attach_figure(gs);
//   } else if (gs->status == GameOver) {
//     finish_game(gs);
//   }
// }

//   // updateCurrentState();

//   // if (hold) {
//   //   userInput(action, hold);
//   // }
// }

void create_figure(ShapeType type, int figure[4][4], int *figures[type][4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure[i][j] = *figures[type][i][j];
    }
  }
}

void update_field(Game_state_t *game_state) {
  for (int i = 0; i < FIGURE_M; i++) {
    for (int j = 0; j < FIGURE_N; j++) {
      int x = game_state->figure.x + i;
      int y = game_state->figure.y + j;

      if (game_state->figure.figure[i][j] == 1 && game_state->figure.y > -1 &&
          game_state->field.y < COLS_MAP && game_state->figure.x > -1 &&
          game_state->field.x < ROWS_MAP) {
        game_state->field.field[x][y] = game_state->figure.figure[i][j];
      }
    }
  }
}
// bool check_collision(Game_field_t * field_t, Figure_t * figure_t) {
//   ;
//   ;
// }