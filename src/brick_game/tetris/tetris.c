#include "../inc/tetris.h"

int main() {
  initscr();
  noecho();
  curs_set(0);

  // int key = 0;

  // GameInfo_t g_info;
  Game_state_t *g_state = get_game_state();

  // init_game(&ups);
  // init_game_state(game_state);

  // init_field(&g_state->field);
  // init_figure(&g_state->figure);
  // init_game_status(&g_state->status);
  // init_game_stats(&g_state->stats);

  init_game_state(g_state);
  printf("type = %d", g_state->figure.figure_size);
  printf(" %d", g_state->field.x);

  // free_field(&g_state->field);
  free_field_gs(g_state);
  // printf("%d", asd.field.x);

  int figure[FIGURE_M][FIGURE_N] = {
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
  };

  g_state->figure.figure_size = 4;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      g_state->figure.figure[i][j] = figure[i][j];
    }
  }

  UserAction_t action = -1;

  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     figure[i][j] = 1;
  //   }
  // }

  // create_figure(1, figure, figures[1][FIGURE_M][FIGURE_N]);
  // create_figure(1, figure, figures);

  print_overlay();

  get_user_action(action);
  wprintw(stdscr, "action = %d", action);
  // refresh();

  // update_field(g_state);

  // free_game(&ups);
  // free_field(&game_state->field);

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
