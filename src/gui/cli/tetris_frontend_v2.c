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

// void print_overlay() {
//   // int key = 0;

//   // WINDOW *menu = print_menu();
//   // wrefresh(menu);
//   // key = wgetch(menu);

//   // while (key != 't') {
//   //   print_menu();
//   //   wrefresh(menu);
//   //   key = wgetch(menu);
//   // }

//   // delwin(menu);
//   // refresh();

//   WINDOW *menu = print_menu();
//   int key = 0;
//   print_menu();
//   key = wgetch(menu);

//   // wrefresh(menu);
//   // delwin(menu);

//   while (key != 't') {
//     print_menu();
//     wrefresh(menu);
//     key = wgetch(menu);
//   }
//   delwin(menu);

//   // int key = 0;
//   // WINDOW *tetris = print_tetris_overlay();
//   // wrefresh(tetris);
//   // key = wgetch(tetris);

//   // while (key != 'q') {
//   //   print_tetris_overlay();
//   //   wrefresh(tetris);
//   //   key = wgetch(tetris);
//   // }

//   // delwin(tetris);

//   WINDOW *tetris = print_tetris_overlay();
//   print_tetris_overlay();
//   wrefresh(tetris);
//   delwin(tetris);

//   // key = wgetch(menu);

//   // if (key == 't') {
//   // print_tetris_overlay();
//   // refresh();
//   // }

//   // print_tetris_overlay();
//   // print_figure();
// }

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
  WINDOW *tetris =
      newwin(GAME_BORDER_HEIGHT, GAME_BORDER_WIDTH, yMax / 10, xMax / 4);

  box(tetris, 0, 0);

  wrefresh(tetris);

  return tetris;
}

WINDOW *print_status_gi(GameInfo_t *g_info) {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *status = newwin(GAME_BORDER_HEIGHT / 2, GAME_BORDER_WIDTH * 1.2,
                          yMax / 10, xMax / 2.5 + 5);

  box(status, 0, 0);

  wrefresh(status);

  mvwprintw(status, 1, 1, "Score: %d", g_info->score);
  mvwprintw(status, 4, 1, "High Score: %d", g_info->high_score);
  mvwprintw(status, 2, 1, "Level: %d", g_info->level);
  mvwprintw(status, 3, 1, "Speed: %d", g_info->speed);
  mvwprintw(status, 6, 1, "Pause: %s", g_info->pause ? "ON" : "OFF");

  Game_state_t *g_state = get_game_state();

  mvwprintw(status, 7, 1, "Status: %d", g_state->status.status);
  // printw("Key: %d", get_user_action(action));

  // mvwprintw(status, 7, 1, "Status: %d", g_info->status.status);
  // mvwprintw(status, 8, 1, "Win: %s", g_info->status.win ? "TRUE" : "FALSE");
  // mvwprintw(status, 9, 1, "Playing: %s",
  //           g_info->status.is_playing ? "TRUE" : "FALSE");
  // mvwprintw(status, 10, 1, "Key: %d", g_info->status.status);

  // int key = wgetch(status);
  // while (key != 'q') {
  //   key = wgetch(status);
  //   mvwprintw(status, 10, 1, "Key: %d", get_user_action(key));
  // }

  // wrefresh(status);

  return status;
}

WINDOW *print_states(Game_state_t *g_state, int key) {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *status = newwin(GAME_BORDER_HEIGHT / 1, GAME_BORDER_WIDTH * 1.2,
                          yMax / 10, xMax / 1.25);

  box(status, 0, 0);

  wrefresh(status);

  // bool attaching = figure_is_attaching(g_state);

  mvwprintw(status, 1, 1, "Key: %d", key);
  mvwprintw(status, 2, 1, "Status: %d", g_state->status.status);
  mvwprintw(status, 3, 1, "Win: %d", g_state->status.win);
  mvwprintw(status, 4, 1, "Playing: %d", g_state->status.is_playing);
  // mvwprintw(status, 5, 1, "Attaching: %d", attaching);

  mvwprintw(status, 6, 1, "Coord: %d, %d", g_state->figure.x,
            g_state->figure.y);

  int collision = check_collision(g_state);
  switch (collision) {
    case 1:
      mvwprintw(status, 9, 1, "Collision: LEFT");
      break;
    case 2:
      mvwprintw(status, 9, 1, "Collision: RIGHT");
      break;
    case 3:
      mvwprintw(status, 9, 1, "Collision: DOWN");
      break;
    case 4:
      mvwprintw(status, 9, 1, "Collision: FIGURE");
      break;
    case 5:
      mvwprintw(status, 9, 1, "Collision: DL");
      break;
    case 6:
      mvwprintw(status, 9, 1, "Collision: DR");
      break;
    default:
      mvwprintw(status, 9, 1, "Collision: NONE");
      break;
  }

  mvwprintw(status, 11, 1, "Fig_height: %d", trim_figure_height(g_state));
  mvwprintw(status, 12, 1, "Fig_width: %d", trim_figure_width(g_state));

  mvwprintw(status, 13, 1, "y+height: %d",
            g_state->figure.y + trim_figure_height(g_state));

  int figure_width = trim_figure_width(g_state);
  int figure_height = trim_figure_height(g_state);
  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      mvwprintw(status, 14, 1, "curr x: %d", x);
      mvwprintw(status, 15, 1, "curr y: %d", y);
    }
  }

  // int fig_coll = 0;
  mvwprintw(status, 16, 1, "bot_fig_coll: %d",
            bottom_figure_collision(g_state));

  // int right_coll = right_figure_collision(g_state);
  // mvwprintw(status, 17, 1, "fiig_R_coll: %d", right_coll);

  // mvwprintw(status, 13, 1, "Win: %s", g_state->status.win ? "TRUE" :
  // "FALSE"); mvwprintw(status, 14, 1, "Playing: %s",
  //           g_state->status.is_playing ? "TRUE" : "FALSE");

  return status;
}

void render_game_gi(WINDOW *tetris_window, GameInfo_t g_info) {
  // unsigned int block = ACS_BLOCK;
  // attron(A_ALTCHARSET);

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (g_info.field[i][j] == 1) {
        //   // attron(A_ALTCHARSET);
        mvwprintw(tetris_window, i + 1, j + 2, "#");
        // }
        // attroff(A_ALTCHARSET);
      } else if (g_info.field[i][j] == 3) {
        mvwprintw(tetris_window, i + 1, j + 2, "*");
      } else if (g_info.field[i][j] == 9) {
        mvwprintw(tetris_window, i + 1, j + 2, "?");
      } else {
        mvwprintw(tetris_window, i + 1, j + 2, "-");
      }

      // mvwprintw(tetris_window, i + 1, j + 2, "%d", (i));

      // if (j == 9) {
      //   mvwprintw(tetris_window, i + 1, j + 2, "r");
      // }
      // if (i == 19) {
      //   mvwprintw(tetris_window, i + 1, j + 2, "b");
      // }
    }
  }
  wrefresh(tetris_window);
  // attroff(A_ALTCHARSET);
}

WINDOW *next_display(Game_state_t *g_state) {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *next = newwin(GAME_BORDER_HEIGHT / 2, GAME_BORDER_WIDTH * 1.2,
                        yMax / 10 + (GAME_BORDER_HEIGHT / 2), xMax / 2.5 + 5);

  box(next, 0, 0);

  wrefresh(next);

  switch (g_state->figure.type) {
    case 0:
      mvwprintw(next, 1, 1, "fig_type: I");
      break;
    case 1:
      mvwprintw(next, 1, 1, "fig_type: J");
      break;
    case 2:
      mvwprintw(next, 1, 1, "fig_type: L");
      break;
    case 3:
      mvwprintw(next, 1, 1, "fig_type: O");
      break;
    case 4:
      mvwprintw(next, 1, 1, "fig_type: S");
      break;
    case 5:
      mvwprintw(next, 1, 1, "fig_type: T");
      break;
    case 6:
      mvwprintw(next, 1, 1, "fig_type: Z");
      break;
    default:
      mvwprintw(next, 1, 1, "fig_type: ?");
  }

  switch (g_state->figure.next_type) {
    case 0:
      mvwprintw(next, 2, 1, "next_type: I");
      break;
    case 1:
      mvwprintw(next, 2, 1, "next_type: J");
      break;
    case 2:
      mvwprintw(next, 2, 1, "next_type: L");
      break;
    case 3:
      mvwprintw(next, 2, 1, "next_type: O");
      break;
    case 4:
      mvwprintw(next, 2, 1, "next_type: S");
      break;
    case 5:
      mvwprintw(next, 2, 1, "next_type: T");
      break;
    case 6:
      mvwprintw(next, 2, 1, "next_type: Z");
      break;
    default:
      mvwprintw(next, 2, 1, "next_type: ?");
  }

  mvwprintw(next, 3, 1, "x: %d", g_state->figure.x);
  mvwprintw(next, 4, 1, "y: %d", g_state->figure.y);
  mvwprintw(next, 5, 1, "height: %d", g_state->figure.figure_height);
  mvwprintw(next, 6, 1, "width: %d", g_state->figure.figure_width);

  mvwprintw(next, 7, 1, "nxt_x: %d", g_state->figure.next_x);
  mvwprintw(next, 8, 1, "nxt_y: %d", g_state->figure.next_y);
  mvwprintw(next, 9, 1, "nxt_height: %d", g_state->figure.next_figure_height);
  mvwprintw(next, 10, 1, "nxt_width: %d", g_state->figure.next_figure_width);

  wrefresh(next);
  return next;
}