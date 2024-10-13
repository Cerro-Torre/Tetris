#include "../../brick_game/inc/tetris.h"
#include "../../brick_game/inc/tetris_frontend.h"

// int main() {
//   initscr();
//   noecho();
//   curs_set(0);

//   print_overlay();
//   // refresh();
//   // print_figure();

//   endwin();

//   return 0;
// }

void print_overlay() {
  // int key = 0;

  // WINDOW *menu = print_menu();
  // wrefresh(menu);
  // key = wgetch(menu);

  // while (key != 't') {
  //   print_menu();
  //   wrefresh(menu);
  //   key = wgetch(menu);
  // }

  // delwin(menu);
  // refresh();

  WINDOW *menu = print_menu();
  int key = 0;
  print_menu();
  key = wgetch(menu);

  // wrefresh(menu);
  // delwin(menu);

  while (key != 't') {
    print_menu();
    wrefresh(menu);
    key = wgetch(menu);
  }
  delwin(menu);

  // int key = 0;
  // WINDOW *tetris = print_tetris_overlay();
  // wrefresh(tetris);
  // key = wgetch(tetris);

  // while (key != 'q') {
  //   print_tetris_overlay();
  //   wrefresh(tetris);
  //   key = wgetch(tetris);
  // }

  // delwin(tetris);

  WINDOW *tetris = print_tetris_overlay();
  print_tetris_overlay();
  wrefresh(tetris);
  delwin(tetris);

  // key = wgetch(menu);

  // if (key == 't') {
  // print_tetris_overlay();
  // refresh();
  // }

  // print_tetris_overlay();
  // print_figure();
}

// prin_menu_v2
WINDOW *print_menu() {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  // yMax / 2 is the size of window (half of the screen), yMax / 4 is the
  // position of window
  WINDOW *menu = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);

  box(menu, 0, 0);

  mvwprintw(menu, 0, xMax / 4 - 6, "s21_BrickGame");

  mvwprintw(menu, yMax / 4 - 1, xMax / 4 - (INTRO_MESSAGE_LEN / 2 - 1),
            INTRO_MESSAGE);

  wrefresh(menu);

  return menu;
}

// print_tetris_overlay_v2
WINDOW *print_tetris_overlay() {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  // yMax / 2 is the size of window (half of the screen), yMax / 4 is the
  // position of window
  WINDOW *tetris = newwin(20, 10, yMax / 10, xMax / 4);

  box(tetris, 0, 0);

  wrefresh(tetris);

  return tetris;
}