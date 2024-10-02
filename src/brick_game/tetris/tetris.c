#include "../inc/tetris.h"

int main() {
  initscr();
  noecho();
  curs_set(0);

  // int key = 0;

  GameInfo_t ups;
  init_game(&ups);

  // printw("%d\n", ups.score);

  print_overlay();

  // print_menu();
  // refresh();
  // if (key == 't') {
  //   print_tetris_overlay();
  //   refresh();
  //   getch();
  // }

  // print_figure();

  free_game(&ups);
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
