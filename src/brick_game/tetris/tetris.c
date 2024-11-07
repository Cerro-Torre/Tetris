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

  while (g_state->status.status == INIT) {
    key = wgetch(menu);
    userInput(get_user_action(key), false);
  }

  delwin(menu);
  refresh();

  GameInfo_t g_info = updateCurrentState();
  // ;
  // g_info = updateCurrentState();
  // g_info = copy_game_to_gi(g_state);

  WINDOW *tetris = print_tetris_overlay();
  wrefresh(tetris);

  WINDOW *status = print_status_gi(&g_info);
  wrefresh(status);

  WINDOW *next = next_display(g_state);
  wrefresh(next);

  int key2 = 0;
  WINDOW *states_info = print_states(g_state, key2);
  wrefresh(states_info);

  // printw("bw status = %d\n", g_state->status.status);

  // create_next_fig_size(g_state);

  wrefresh(states_info);
  wrefresh(tetris);
  wrefresh(status);
  wrefresh(next);

  keypad(tetris, TRUE);

  while (g_state->status.is_playing && g_state->status.status != GAMEOVER) {
    g_state = get_game_state();
    g_info = updateCurrentState();
    g_info = copy_game_to_gi(g_state);

    render_game_gi(tetris, g_info);
    wrefresh(tetris);

    if (g_state->status.status == MOVING || g_state->status.status == START) {
      // g_state = get_game_state();
      // g_info = updateCurrentState();
      // printw("inside\n");
      // wrefresh(states_info);
      key2 = wgetch(tetris);

      // if (key2 == 'l') {
      //   move_left(g_state);
      // }

      // if (key2 == 'o') {
      //   move_right(g_state);
      // }
      // int action2 = get_user_action(key2);
      // userInput(get_user_action(key2), false);
      g_info = copy_game_to_gi(g_state);
      render_game_gi(tetris, g_info);
      wrefresh(tetris);
      wrefresh(status);
      wrefresh(states_info);
      wrefresh(next);
    }

    int action = get_user_action(key2);
    userInput(action, false);

    // if (g_state->status.status == ATTACHING) {
    //   printw("ATTACHING\n");
    // }

    states_info = print_states(g_state, action);
    status = print_status_gi(&g_info);
    next = next_display(g_state);

    // clear_figure(g_state);
    wrefresh(tetris);
    wrefresh(status);
    wrefresh(states_info);
    wrefresh(next);
  }
  delwin(status);
  delwin(tetris);
  delwin(states_info);

  refresh();
  endwin();

  free_game(g_state, g_state->field);
  free_field_gi(&g_info);
  // free_next_figure_gi(&g_info);

  return 0;
}

UserAction_t get_user_action(int ch) {
  UserAction_t action = {0};
  switch (ch) {
    case KEY_T:
      action = Start;
      break;
    case KEY_P:
      action = Pause;
      break;
    case KEY_Q:
      refresh();
      action = Terminate;
      break;
    case KEY_LEFT:
      refresh();
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_Z:
      action = Action;
      break;
    default:
      action = -1;
      break;
  }

  return action;
}