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

WINDOW *print_status_gi(GameInfo_t *g_info, UserAction_t action) {
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

  mvwprintw(status, 7, 1, "Status: %d", get_user_action(action));
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

  WINDOW *status = newwin(GAME_BORDER_HEIGHT / 2, GAME_BORDER_WIDTH * 1.2,
                          yMax / 10, xMax / 1.25);

  box(status, 0, 0);

  wrefresh(status);

  mvwprintw(status, 1, 1, "Action: %d", key);
  mvwprintw(status, 2, 1, "Status: %d", g_state->status.status);
  mvwprintw(status, 3, 1, "Win: %d", g_state->status.win);
  mvwprintw(status, 4, 1, "Playing: %d", g_state->status.is_playing);
  mvwprintw(status, 5, 1, "Key: %d", g_state->status.status);

  // mvwprintw(status, 7, 1, "Status: %d", g_state->status.status);
  mvwprintw(status, 8, 1, "Win: %s", g_state->status.win ? "TRUE" : "FALSE");
  mvwprintw(status, 9, 1, "Playing: %s",
            g_state->status.is_playing ? "TRUE" : "FALSE");

  return status;
}

void render_game_gi(WINDOW *tetris_window, GameInfo_t g_info) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (g_info.field[i][j] == 1) {
        mvwprintw(tetris_window, i + 1, j + 2, "#");
      } else {
        mvwprintw(tetris_window, i + 1, j + 2, "-");
      }
    }
  }
  wrefresh(tetris_window);
}

// void render_game_gs(WINDOW *tetris_window, Game_state_t *g_state) {
//   for (int i = 0; i < 20; i++) {
//     for (int j = 0; j < 10; j++) {
//       if (g_state->field->field[i][j] == 1) {
//         mvwprintw(tetris_window, i + 1, j + 2, "#");
//       } else {
//         mvwprintw(tetris_window, i + 1, j + 2, "-");
//       }
//     }
//   }
//   wrefresh(tetris_window);
// }