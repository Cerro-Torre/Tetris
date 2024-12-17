#include "../inc/tetris.h"

int main() {
  initscr();
  noecho();
  curs_set(0);

  WINDOW *menu = print_menu();
  wrefresh(menu);

  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);
  int key = 0;

  while (g_state->status.status == INIT) {
    key = wgetch(menu);
    userInput(get_user_action(key), false);
  }

  delwin(menu);
  refresh();

  GameInfo_t g_info = init_game_info();

  WINDOW *tetris = print_tetris_overlay();
  wrefresh(tetris);

  WINDOW *status = print_status_gi(&g_info);
  wrefresh(status);

  WINDOW *next = next_display(&g_info);
  wrefresh(next);

  int user_inp_key = 0;
  WINDOW *states_info = print_states(g_state, user_inp_key);
  wrefresh(states_info);

  wrefresh(states_info);
  wrefresh(tetris);
  wrefresh(status);
  wrefresh(next);

  keypad(tetris, TRUE);

  while (g_state->status.is_playing && g_state->status.status != GAMEOVER) {
    g_state = get_game_state();
    g_info = updateCurrentState();
    nodelay(tetris, TRUE);

    if (g_state->status.status == START || g_state->status.status == PAUSE) {
      nodelay(tetris, FALSE);

      userInput(get_user_action(wgetch(tetris)), false);
      nodelay(tetris, TRUE);
    }

    if (g_state->status.status == MOVING) {
      clock_t start_time = clock();
      while (clock() - start_time <
             CLOCKS_PER_SEC / g_state->stats.speed * 0.7) {
        nodelay(tetris, TRUE);
        int user_inp_key = wgetch(tetris);

        if (user_inp_key != ERR) {
          userInput(get_user_action(user_inp_key), false);

          g_info = copy_game_to_gi(g_state);
          render_game_gi(tetris, g_info);
        }

        if (g_state->status.status != PAUSE) {
          g_state->status.status = MOVING;
        }
      }
    }

    userInput(get_user_action(user_inp_key), false);

    g_info = copy_game_to_gi(g_state);
    render_game_gi(tetris, g_info);

    states_info = print_states(g_state, user_inp_key);
    status = print_status_gi(&g_info);
    next = next_display(&g_info);

    wrefresh(tetris);
    wrefresh(status);
    wrefresh(states_info);
    wrefresh(next);

    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 1000000 / (10 * 10);
    nanosleep(&req, NULL);
  }

  free_game(g_state);
  g_state = NULL;
  // free_game_gi(&g_info);
  // g_info.field = NULL;

  nodelay(tetris, FALSE);
  mvwprintw(tetris, 0, 3, "Game Over");
  wgetch(tetris);

  delwin(status);

  delwin(tetris);
  delwin(states_info);
  refresh();
  endwin();
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
      action = Terminate;
      break;
    case KEY_LEFT:
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