#ifndef DEFINES_H
#define DEFINES_H

#define GAME_BORDER_WIDTH 14
#define GAME_BORDER_HEIGHT 22

#define ROWS_GAME 20
#define COLS_GAME 10

#define FIELD_N 20
#define FIELD_M 10

#define NEXT_FIELD_X 10
#define NEXT_FIELD_Y 10

#define KEY_T 't'
#define KEY_P 'p'
#define KEY_Q 'q'
#define KEY_Z 'z'

// _______frogger's__________________________
#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define GET_USER_INPUT getch()

#define PRINT_FROG(x, y) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), "@")
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

#define INTRO_MESSAGE "Press \"t\" to start tetris!"
#define INTRO_MESSAGE_LEN 28

#define MAX_WIN_COUNT 10

#define FIGURE_N 4
#define FIGURE_M 4

#endif