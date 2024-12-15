#include "../../brick_game/inc/tetris.h"
#include "../../brick_game/inc/tetris_frontend.h"

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

  WINDOW *status = newwin(GAME_BORDER_HEIGHT / 2, GAME_BORDER_WIDTH * 1.3,
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

  switch (g_state->status.status) {
    case INIT:
      mvwprintw(status, 8, 1, "Status: INIT");
      break;
    case START:
      mvwprintw(status, 8, 1, "Status: START");
      break;
    case SPAWN:
      mvwprintw(status, 8, 1, "Status: SPAWN");
      break;
    case MOVING:
      mvwprintw(status, 8, 1, "Status: MOVING");
      break;
    case ATTACHING:
      mvwprintw(status, 8, 1, "Status: ATTACHING");
      break;
    case SHIFTING:
      mvwprintw(status, 8, 1, "Status: SHIFTING");
      break;
    case GAMEOVER:
      mvwprintw(status, 8, 1, "Status: GAMEOVER");
      break;
    case PAUSE:
      mvwprintw(status, 8, 1, "Status: PAUSE");
      break;
    default:
      mvwprintw(status, 8, 1, "Status: UNKNOWN");
      break;
  }

  // mvwprintw(status, 9, 1, "t: %ld", g_state->time);
  // mvwprintw(status, 10, 1, "test: %ld", g_state->test);
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

  mvwprintw(status, 1, 1, "Key: %d", key);
  mvwprintw(status, 2, 1, "Status: %d", g_state->status.status);
  mvwprintw(status, 3, 1, "Win: %d", g_state->status.win);
  mvwprintw(status, 4, 1, "Playing: %d", g_state->status.is_playing);
  // mvwprintw(status, 5, 1, "Attaching: %d", attaching);

  mvwprintw(status, 6, 1, "Coord: %d, %d", g_state->figure.x,
            g_state->figure.y);

  int b_collision = border_collision(g_state);
  switch (b_collision) {
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

  mvwprintw(status, 11, 1, "Fig_height: %d", figure_min_height(g_state));
  mvwprintw(status, 12, 1, "Fig_width: %d", figure_min_width(g_state));

  mvwprintw(status, 13, 1, "y+height: %d",
            g_state->figure.y + figure_min_height(g_state));

  int figure_width = figure_min_width(g_state);
  int figure_height = figure_min_height(g_state);
  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      mvwprintw(status, 14, 1, "curr x: %d", x);
      mvwprintw(status, 15, 1, "curr y: %d", y);
    }
  }

  mvwprintw(status, 16, 1, "bot_fig_coll: %d",
            bottom_figure_collision(g_state));

  return status;
}

void render_game_gi(WINDOW *tetris_window, GameInfo_t g_info) {
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
      } else if (g_info.field[i][j] == 0) {
        mvwprintw(tetris_window, i + 1, j + 2, "-");
      }
    }
  }
  wrefresh(tetris_window);
}

WINDOW *next_display(GameInfo_t *g_info) {
  int yMax = 0;
  int xMax = 0;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *next = newwin(GAME_BORDER_HEIGHT / 2, GAME_BORDER_WIDTH * 1.3,
                        yMax / 10 + (GAME_BORDER_HEIGHT / 2), xMax / 2.5 + 5);

  box(next, 0, 0);

  wrefresh(next);
  if (g_info->next != NULL) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (g_info->next[i][j] == 1) {
          mvwprintw(next, i + 2 + 4, (j + 2 + NEXT_FIELD_X / 2) + (4 / 2) - 2,
                    "#");
        }
      }
    }
  }

  // mvwprintw(next, 1, 1, "cur_height: %d", g_state->figure.figure_height);
  // mvwprintw(next, 2, 1, "cur_width: %d", g_state->figure.figure_width);

  // mvwprintw(next, 3, 1, "x: %d", g_state->figure.x);
  // mvwprintw(next, 4, 1, "y: %d", g_state->figure.y);
  // mvwprintw(next, 5, 1, "height: %d", figure_min_height(g_state));
  // mvwprintw(next, 6, 1, "width: %d", figure_min_width(g_state));
  // mvwprintw(next, 7, 1, "type: %d", g_state->figure.type);

  // // mvwprintw(next, 7, 1, "nxt_x: %d", g_state->figure.next_x);
  // // mvwprintw(next, 8, 1, "nxt_y: %d", g_state->figure.next_y);
  // mvwprintw(next, 8, 1, "nxt_height: %d",
  // g_state->figure.next_figure_height); mvwprintw(next, 9, 1, "nxt_width: %d",
  // g_state->figure.next_figure_width);

  wrefresh(next);
  return next;
}