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

void print_test() {
  char test[4][4] = {{'0', '0', '0', '0'},
                     {'1', '1', '1', '1'},
                     {'0', '0', '0', '0'},
                     {'0', '0', '0', '0'}};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // printw("%c", test[i]);
      if (test[i][j] == '1') {
        printw("%c", ACS_BLOCK);
      }
      // printw("%c", test[i][j]);
    }
  }
}

void init_game(GameInfo_t *game) {
  game->level = 1;
  game->score = 1;
  game->high_score = 1;
  game->speed = 1;
  game->pause = 1;
  game->next = (int **)calloc(GAME_SCREEN_WIDTH, sizeof(int *));

  for (int i = 0; i < GAME_SCREEN_WIDTH; i++) {
    game->next[i] = (int *)calloc(COLS, sizeof(int));
  }

  game->field = (int **)calloc(GAME_SCREEN_WIDTH, sizeof(int *));

  for (int i = 0; i < GAME_SCREEN_WIDTH; i++) {
    game->field[i] = (int *)calloc(COLS, sizeof(int));
  }
}

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
