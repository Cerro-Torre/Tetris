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
  int key = 0;

  WINDOW *menu = print_menu();
  wrefresh(menu);
  key = wgetch(menu);

  while (key != 't') {
    print_menu();
    wrefresh(menu);
    key = wgetch(menu);
  }

  delwin(menu);
  refresh();

  // int key = 0;
  WINDOW *tetris = print_tetris_overlay();
  wrefresh(tetris);
  key = wgetch(tetris);

  // key = wgetch(menu);

  // if (key == 't') {
  // print_tetris_overlay();
  // refresh();
  // }

  delwin(tetris);

  // print_tetris_overlay();
  // print_figure();
}

WINDOW *print_menu() {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  // yMax / 2 is the size of window (half of the screen), yMax / 4 is the
  // position of window
  WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);

  box(win, 0, 0);

  mvwprintw(win, 0, xMax / 4 - 6, "s21_BrickGame");

  mvwprintw(win, yMax / 4 - 1, xMax / 4 - (INTRO_MESSAGE_LEN / 2 - 1),
            INTRO_MESSAGE);

  // wgetch(win);
  // wrefresh(win);
  // getch();

  // delwin(win);
  return win;
}
WINDOW *print_tetris_overlay() {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  // yMax / 2 is the size of window (half of the screen), yMax / 4 is the
  // position of window
  WINDOW *win_tetris = newwin(10, 20, yMax / 4, xMax / 4);

  box(win_tetris, 0, 0);

  // delwin(win_tetris);
  return win_tetris;
}

void print_figure() {
  int figure[5][5] = {
      {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'},
      {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'},
      {'0', '0', '1', '0', '0'},
  };

  for (int i = ROWS_MAP; i < 5; i++) {
    for (int j = COLS_MAP; j < 5; j++) {
      if (figure[i][j] == '1') {
        mvaddch((GAME_SCREEN_HEIGHT - ROWS_MAP) / 2 + i,
                (GAME_SCREEN_WIDTH - COLS_MAP) / 2 + j, ACS_BLOCK);
      }
    }
  }
}