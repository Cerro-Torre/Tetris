#include "../inc/tetris.h"

int main() {
  initscr();
  noecho();
  curs_set(0);

  WINDOW *menu = print_menu();
  wrefresh(menu);

  Game_field_t field_t = {0};
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state, &field_t);

  int key = 0;

  while (key != 'q') {
    key = wgetch(menu);

    if (key == 't') {
      g_state->status.is_playing = 1;
      delwin(menu);
      refresh();
      break;
    }
  }

  if (g_state->status.is_playing == 1) {
    GameInfo_t g_info = update_current_state(g_state);

    WINDOW *tetris = print_tetris_overlay();
    wrefresh(tetris);

    WINDOW *status = print_status(g_state);
    wrefresh(status);
    // fill_field(g_state);

    // _______________
    create_figure_2(&g_state->figure, Z_SHAPE, 6, 3);
    create_next_figure(&g_state->figure, T_SHAPE, 12, 3);
    // create_figure_2(&g_state->figure, T_SHAPE, 12, 3);

    // wprintw(tetris, "fig_x = %d, fig_y = %d", g_state->figure.x,
    //         g_state->figure.y);

    int figures[NUM_SHAPES][4][4] = {
        // I-образная фигура
        {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // J-образная фигура
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // L-образная фигура
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // O-образная фигура
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // S-образная фигура
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // T-образная фигура
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        // Z-образная фигура
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

    // fill_field(g_state);
    if ((g_state->figure.type > 0) && (g_state->figure.type < 7)) {
      figure_to_field(g_state, figures);
    }

    // next_figure_to_current(&g_state->figure);

    // figure_to_field(g_state, figures);

    // g_info = update_current_state(g_state);
    // render_game_gi(tetris, g_info);
    // free_field_gi(&g_info);

    // __________________
    // start the game after any button is pressed

    // key = wgetch(tetris);
    int key2 = wgetch(status);
    // mvwprintw(status, 10, 1, "Key: %c", get_user_action(key2));

    while (key2 != 'q') {
      // g_state = get_game_state();
      // g_info = update_current_state(g_state);

      user_input(g_state, get_user_action(key2));
      g_info = update_current_state(g_state);
      render_game_gi(tetris, g_info);
      wrefresh(tetris);
      mvwprintw(status, 10, 1, "Key: %d", get_user_action(key2));

      // key = wgetch(tetris);

      key2 = wgetch(status);
      wrefresh(status);
    }
    // _______________

    free_game(g_state, g_state->field);
    free_field_gi(&g_info);

    // return 0;

    delwin(status);
  }

  refresh();
  endwin();
  return 0;
}

// void game_loop(WINDOW *tetris) {
//   // g_state->status.is_playing = 1;

//   while (1) {
//     Game_state_t *g_state = get_game_state();
//     GameInfo_t gi = update_current_state(g_state);

//     int ch = wgetch(tetris);
//     free_field_gi(&gi);

//     while (ch != 'q') {
//       init_game_state(g_state, g_state->field);
//     }

//     user_input(g_state, get_user_action(ch));
//   }
// }