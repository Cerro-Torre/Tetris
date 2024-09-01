#include "../inc/tetris.h"

int main() {
  initscr();

  int key = 0;

  GameInfo_t ups;
  init_game(&ups);

  printw("%d\n", ups.score);

  print_overlay();

  free_game(&ups);
  // print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
  refresh();

  while (key != 'q') {
    // userInput(key, false);
    key = getch();
  }

  endwin();
  return 0;
}

void init_game(GameInfo_t *game) {
  game->level = 1;
  game->score = 1;
  game->high_score = 1;
  game->speed = 1;
  game->pause = 1;
  game->next = (int **)calloc(BOARD_M, sizeof(int *));

  for (int i = 0; i < BOARD_M; i++) {
    game->next[i] = (int *)calloc(COLS, sizeof(int));
  }

  game->field = (int **)calloc(BOARD_M, sizeof(int *));

  for (int i = 0; i < BOARD_M; i++) {
    game->field[i] = (int *)calloc(COLS, sizeof(int));
  }
}

void free_game(GameInfo_t *game) {
  for (int i = 0; i < BOARD_M; i++) {
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