#include "../inc/tetris.h"

int main() {
  initscr();
  noecho();
  curs_set(0);

  // int key = 0;

  // GameInfo_t ups;
  Game_state_t asd;
  // Game_state_t *game_state = get_game_state();

  // init_game(&ups);
  // init_game_state(game_state);

  init_field(&asd.field);
  free_field(&asd.field);
  printf("%d", asd.field.x);

  print_overlay();

  // free_game(&ups);
  // free_field(&game_state->field);

  // print_rectangle(0, GAME_SCREEN_HEIGHT + 1, 0, GAME_SCREEN_WIDTH + 1);
  // refresh();

  // while (key != 'q') {
  //   if (key == 'd') {
  //     // draw_figure_1(&ups);
  //     print_test();
  //     refresh();
  //   }
  //   // userInput(key, false);
  //   key = getch();
  // }

  endwin();
  return 0;
}
