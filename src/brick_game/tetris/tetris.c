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

  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     printf("x = %d, y = %d\n", g_state->figure.x + i, g_state->figure.y +
  //     j);
  //   }
  // }

  if (g_state->status.is_playing == 1) {
    WINDOW *tetris = print_tetris_overlay();
    wrefresh(tetris);

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

    next_figure_to_current(&g_state->figure);

    figure_to_field(g_state, figures);

    render_game(tetris, g_state);

    // __________________

    // fill_field(g_state);

    // for (int i = 0; i < ROWS_GAME; i++) {
    //   for (int j = 0; j < COLS_GAME; j++) {
    //     // wprintw(tetris, "%c", g_state->field->field[i][j]);
    //     mvwprintw(tetris, i, j, "%c", g_state->field->field[i][j]);
    //   }
    //   // wprintw(tetris, "\n");
    // }
    // wrefresh(tetris);

    // wprintw(tetris, "\nstatus = %d\n", g_state->status.is_playing);

    key = wgetch(tetris);

    // while (key != 'q') {
    //   game_loop_here;
    //   ;
    // }
    // Game_state_t *g_state = get_game_state();

    // printf("field.x = %d\n\n\n", g_state->field->x);
    // printf("field.y = %d\n\n\n", g_state->field->y);

    // g_state->figure.figure_size = 4;
    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     g_state->figure.figure[i][j] = figure[i][j];
    //   }
    // }
    // wgetch(tetris);
    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     wprintw(tetris, "%c", g_state->figure.figure[i][j]);
    //   }
    // update_field(g_state);
    //   wrefresh(tetris);
    //   getch();
    //   // free_field_gs(g_state);
    // }

    // refresh();
    // endwin();
    // }
    // printf("\nfield.x = %d\n", g_state->field->x);
    free_game(g_state, g_state->field);
    // return 0;
  }

  refresh();
  endwin();
  return 0;
}