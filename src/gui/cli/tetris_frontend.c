// #include "../../brick_game/inc/tetris_frontend.h"

// void print_overlay(void) {
//   print_menu();

//   print_rectangle(0, GAME_SCREEN_HEIGHT + 1, GAME_SCREEN_WIDTH + 2,
//                   GAME_SCREEN_WIDTH + HUD_WIDTH + 3);

//   // for (int i = 0; i < GAME_SCREEN_HEIGHT + MAP_PADDING; i++) {
//   //   for (int j = 0; j < GAME_SCREEN_WIDTH; j++) {
//   //     mvaddch(i, j, '#');
//   //   }
//   // }

//   // bkgd('x');

//   // clear_menu();
//   print_tetris_overlay();
//   // print_figure();

//   PRINT_FROG(ROWS_MAP, COLS_MAP);

//   // print_rectangle(1, 3, GAME_SCREEN_WIDTH + 3,
//   //                 GAME_SCREEN_WIDTH + HUD_WIDTH + 2);
//   // print_rectangle(4, 6, GAME_SCREEN_WIDTH + 3,
//   //                 GAME_SCREEN_WIDTH + HUD_WIDTH + 2);
//   // print_rectangle(7, 9, GAME_SCREEN_WIDTH + 3,
//   //                 GAME_SCREEN_WIDTH + HUD_WIDTH + 2);
//   // print_rectangle(10, 12, GAME_SCREEN_WIDTH + 3,
//   //                 GAME_SCREEN_WIDTH + HUD_WIDTH + 2);

//   // MVPRINTW(2, GAME_SCREEN_WIDTH + 5, "LEVEL");
//   // MVPRINTW(5, GAME_SCREEN_WIDTH + 5, "SCORE");
//   // MVPRINTW(8, GAME_SCREEN_WIDTH + 5, "SPEED");
//   // MVPRINTW(11, GAME_SCREEN_WIDTH + 5, "LIVES");
// }

// void print_menu() {
//   print_rectangle(0, GAME_SCREEN_HEIGHT + 1, 0, GAME_SCREEN_WIDTH + 1);

//   // attr_on(A_BLINK, INTRO_MESSAGE);

//   MVPRINTW(GAME_SCREEN_HEIGHT / 2,
//            (GAME_SCREEN_WIDTH - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
//   noecho();
//   getch();

//   // attr_off(A_BLINK, INTRO_MESSAGE);
// }

// void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
//   MVADDCH(top_y, left_x, ACS_ULCORNER);

//   for (int i = left_x + 1; i < right_x; i++) {
//     MVADDCH(top_y, i, ACS_HLINE);
//   }
//   MVADDCH(top_y, right_x, ACS_URCORNER);

//   for (int i = top_y + 1; i < bottom_y; i++) {
//     MVADDCH(i, left_x, ACS_VLINE);
//     MVADDCH(i, right_x, ACS_VLINE);
//   }

//   MVADDCH(bottom_y, left_x, ACS_LLCORNER);

//   for (int i = left_x + 1; i < right_x; i++) {
//     MVADDCH(bottom_y, i, ACS_HLINE);
//   }
//   MVADDCH(bottom_y, right_x, ACS_LRCORNER);
// }

// void print_tetris_overlay() {
//   print_rectangle((GAME_SCREEN_HEIGHT - ROWS_MAP) / 2, ROWS_MAP,
//                   (GAME_SCREEN_WIDTH - COLS_MAP) / 2, COLS_MAP);
//   mvprintw(ROWS_MAP / 2 - 1, COLS_MAP / 2 + 2, "TETRIS");
// }

// void clear_menu() {
//   for (int i = 0; i < GAME_SCREEN_HEIGHT + 1; i++) {
//     for (int j = 0; j < GAME_SCREEN_WIDTH; j++) {
//       mvaddch(i, j, ' ');
//     }
//   }
//   // CLEAR_BACKPOS(0, 0);
// }

// void print_figure() {
//   int figure[5][5] = {
//       {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'},
//       {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'},
//       {'0', '0', '1', '0', '0'},
//   };

//   for (int i = ROWS_MAP; i < 5; i++) {
//     for (int j = COLS_MAP; j < 5; j++) {
//       if (figure[i][j] == '1') {
//         mvaddch((GAME_SCREEN_HEIGHT - ROWS_MAP) / 2 + i,
//                 (GAME_SCREEN_WIDTH - COLS_MAP) / 2 + j, ACS_BLOCK);
//       }
//     }
//   }
// }