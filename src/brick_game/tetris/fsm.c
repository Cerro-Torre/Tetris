#include "../inc/tetris_fsm.h"

void init_game_status(Game_status_t *game_status) {
  game_status->status = INIT;
  game_status->pause = 0;
  game_status->win = 0;
  game_status->is_playing = 0;
}

// void finish_game(Game_state_t *g_state) {
//   if (g_state->status.status != GAMEOVER && !g_state->status.win) {
//     g_state->status.is_playing = false;
//     free_game(g_state);
//   }
// }

void on_init_state(Game_state_t *g_state, UserAction_t action) {
  switch (action) {
    case Start:
      g_state->status.is_playing = true;
      g_state->status.status = START;
      break;
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      g_state->status.status = INIT;
      break;
  }
}

void on_start_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      if (g_state->status.is_playing) {
        fill_next_figure(g_state);

        g_state->status.status = SPAWN;
      }
      break;
  }
}

void on_spawn_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  g_state->figure.type = g_state->figure.next_type;
  // g_state->figure.rotated = false;

  int figure_height = figure_min_height(g_state);
  int figure_width = figure_min_width(g_state);

  g_state->figure.figure_height = figure_height;
  g_state->figure.figure_width = figure_width;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      if (g_state->figure.next_figure) {
        g_state->figure.figure[g_state->figure.type][i][j] =
            g_state->figure.next_figure[i][j];
      }
    }
  }

  // create rnd next figure
  srand(time(NULL));
  int rnd_figure = rand() % 7;
  g_state->figure.next_type = rnd_figure;

  fill_next_figure(g_state);

  g_state->figure.x = COLS_GAME / 2 - g_state->figure.figure_width / 2;
  g_state->figure.y = 0;

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:
      if (g_state->status.is_playing) {
        g_state->status.status = MOVING;
      }
      break;
  }
}

void move_left(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  bool figure_collision = false;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field.field &&
          g_state->field.field[field_y][field_x - 1] == 1 &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  if (!figure_collision) {
    g_state->figure.x--;
  }
}

void move_right(Game_state_t *g_state) {
  g_state = get_game_state();

  int figure_height = g_state->figure.figure_height;
  int figure_width = g_state->figure.figure_width;

  bool figure_collision = false;

  for (int i = 0; i < figure_height; i++) {
    for (int j = 0; j < figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;

      if (g_state->field.field &&
          g_state->field.field[field_y][field_x + 1] == 1 &&
          g_state->figure.figure[g_state->figure.type][i][j] == 1) {
        figure_collision = true;
      }
    }
  }

  if (!figure_collision) {
    g_state->figure.x++;
  }
}

void move_down(Game_state_t *g_state) {
  g_state = get_game_state();

  g_state->figure.y++;
}

// void move_up(Game_state_t *g_state) {
//   g_state = get_game_state();

//   g_state->figure.y--;
// }

bool figure_is_attaching(Game_state_t *g_state) {
  bool is_attaching = false;

  for (int i = 0; i < g_state->figure.figure_height && !is_attaching; i++) {
    for (int j = 0; j < g_state->figure.figure_width && !is_attaching; j++) {
      int x = g_state->figure.x + j;
      int y = g_state->figure.y + i;

      if ((y > FIELD_N - 1 || (y > -1 && (g_state->field.field[y][x] == 1)))) {
        is_attaching = true;
      }
    }
  }

  return is_attaching;
}

void on_move_state(Game_state_t *g_state, UserAction_t action) {
  int b_collision = border_collision(g_state);

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Left:
      if (b_collision != COLLISION_LEFT && b_collision != COLLISION_DL &&
          g_state->status.pause == false) {
        move_left(g_state);
      }
      break;
    case Right:
      if (b_collision != COLLISION_RIGHT && b_collision != COLLISION_DR &&
          g_state->status.pause == false) {
        move_right(g_state);
      }
      break;
    case Down:
      if (g_state->status.pause == false) {
        move_down(g_state);
      }
      break;
    // case Up:
    //   break;
    case Pause:
      g_state->status.pause = true;
      g_state->status.status = PAUSE;
      break;
    default:
      break;
  }
}

void on_attach_state(Game_state_t *g_state, UserAction_t action) {
  bool f_collision = bottom_figure_collision(g_state);
  int b_collision = border_collision(g_state);

  if (g_state->figure.y <= 0 && f_collision) {
    g_state->status.is_playing = false;
    g_state->status.status = GAMEOVER;
  }

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    default:

      if (!f_collision && b_collision != COLLISION_DOWN && b_collision &&
          b_collision != COLLISION_DL && b_collision != COLLISION_DR &&
          !f_collision) {
        g_state->status.status = MOVING;
      } else {
        collapse_full_lines(g_state);
        g_state->status.status = SPAWN;
      }

      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  Game_state_t *g_state = get_game_state();
  int current_fsm_state = g_state->status.status;
  bool f_collision = bottom_figure_collision(g_state);
  int b_collision = border_collision(g_state);
  g_state->time = clock();

  (hold) ? printf("hold") : false;

  switch (current_fsm_state) {
    case INIT:
      on_init_state(g_state, action);
      break;
    case START:
      on_start_state(g_state, action);
      break;
    case SPAWN:
      on_spawn_state(g_state, action);
      figure_to_field(g_state);
      break;
    case MOVING:
      f_collision = bottom_figure_collision(g_state);

      if (b_collision != COLLISION_DOWN && b_collision != COLLISION_DL &&
          b_collision != COLLISION_DR && !f_collision &&
          g_state->status.pause == false) {
        if (action != Action && g_state->status.status != SHIFTING) {
          clear_figure(g_state);
          on_move_state(g_state, action);
          figure_to_field(g_state);
        }
      }

      if (b_collision == COLLISION_DOWN || b_collision == COLLISION_DL ||
          b_collision == COLLISION_DR || f_collision) {
        g_state->status.status = ATTACHING;
      }
      if (!g_state->status.pause && action >= 0) {
        g_state->status.status = SHIFTING;
      }
      break;

    case SHIFTING:
      on_shift_state(g_state, action);
      break;
    case ATTACHING:
      on_attach_state(g_state, action);
      break;
    case PAUSE:
      on_pause_state(g_state, action);
      break;
    default:
      break;
  }
}

void on_shift_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  bool f_collision = bottom_figure_collision(g_state);
  int b_collision = border_collision(g_state);

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Pause:
      g_state->status.pause = true;
      g_state->status.status = PAUSE;
      break;
    default:
      if (b_collision != COLLISION_DOWN && b_collision != COLLISION_DL &&
          b_collision != COLLISION_DR && !f_collision &&
          g_state->status.pause == false) {
        clear_figure(g_state);
        on_move_state(g_state, Down);
        figure_to_field(g_state);
        g_state->status.status = MOVING;
      }

      if (b_collision == COLLISION_DOWN || b_collision == COLLISION_DL ||
          b_collision == COLLISION_DR || f_collision) {
        g_state->status.status = ATTACHING;
      }
      break;
  }
}

void on_pause_state(Game_state_t *g_state, UserAction_t action) {
  g_state = get_game_state();

  switch (action) {
    case Terminate:
      g_state->status.is_playing = false;
      g_state->status.status = GAMEOVER;
      break;
    case Pause:
      g_state->status.pause = !g_state->status.pause;
      if (!g_state->status.pause) {
        g_state->status.status = SHIFTING;
      }
      break;
    default:
      break;
  }
}
