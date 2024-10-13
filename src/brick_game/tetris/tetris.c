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
    WINDOW *tetris = print_tetris_overlay();
    wrefresh(tetris);
    // fill_field(g_state);
    // for (int i = 1; i < ROWS_MAP - 1; i++) {
    //   for (int j = 1; j < COLS_MAP - 1; j++) {
    //     wprintw(tetris, "%c", g_state->field->field[i][j]);
    //   }
    //   wprintw(tetris, "\n");
    // }
    // wrefresh(tetris);

    // wprintw(tetris, "\nstatus = %d\n", g_state->status.is_playing);

    key = wgetch(tetris);

    // while (key != 'q') {
    //   game_loop_here;
    //   ;
    // }
    // Game_state_t *g_state = get_game_state();

    int figure[FIGURE_M][FIGURE_N] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    };

    // printf("field.x = %d\n\n\n", g_state->field->x);
    // printf("field.y = %d\n\n\n", g_state->field->y);

    g_state->figure.figure_size = 4;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        g_state->figure.figure[i][j] = figure[i][j];
      }
    }
    wgetch(tetris);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        wprintw(tetris, "%c", g_state->figure.figure[i][j]);
      }
      update_field(g_state);
      wrefresh(tetris);
      getch();
      // free_field_gs(g_state);
    }
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