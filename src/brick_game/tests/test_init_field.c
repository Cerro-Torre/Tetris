#include "tests_backend.h"

START_TEST(test_init_array) {
  Game_state_t *g_state = get_game_state();

  g_state->field.field = init_array(ROWS_GAME, COLS_GAME);

  for (int i = 0; i < ROWS_GAME; i++) {
    for (int j = 0; j < COLS_GAME; j++) {
      ck_assert_int_eq(g_state->field.field[i][j], 0);
    }
  }

  ck_assert_ptr_ne(g_state->field.field, NULL);
  for (int i = 0; i < ROWS_GAME; i++) {
    ck_assert_ptr_ne(g_state->field.field[i], NULL);
  }

  free_array(ROWS_GAME, g_state->field.field);

  g_state->field.field = NULL;
  ck_assert_ptr_eq(g_state->field.field, NULL);
}
END_TEST

START_TEST(test_init_next_figure) {
  Game_state_t *g_state = get_game_state();

  int figures[NUM_SHAPES][4][4] = {
      // I-образная фигура
      {
          {1, 1, 1, 1},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },

      // J -образная фигура
      {
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
      },

      // L-образная фигура
      {
          {1, 0, 0, 0},
          {1, 0, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
      },

      // O-образная фигура
      {
          {1, 1, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      // S-образная фигура
      {
          {0, 1, 1, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },

      // T-образная фигура
      {
          {0, 1, 0, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },

      // Z-образная фигура
      {
          {1, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },

  };

  init_next_figure(g_state);
  ck_assert_int_ge(g_state->figure.next_type, 0);
  ck_assert_int_le(g_state->figure.next_type, 6);

  ck_assert_ptr_ne(g_state, NULL);

  ck_assert_ptr_ne(g_state->figure.next_figure, NULL);

  for (int i = 0; i < g_state->figure.next_figure_height; i++) {
    for (int j = 0; j < g_state->figure.next_figure_width; j++) {
      ck_assert_int_eq(g_state->figure.next_figure[i][j],
                       figures[g_state->figure.next_type][i][j]);
    }
  }

  free_game(g_state);
}

START_TEST(test_init_game_state) {
  Game_state_t *game_state = get_game_state();

  init_game_state(game_state);

  ck_assert_ptr_ne(game_state, NULL);
  ck_assert_ptr_ne(game_state->field.field, NULL);
  ck_assert_int_lt(game_state->figure.type, 7);
  ck_assert_int_eq(game_state->status.is_playing, 0);
  ck_assert_int_eq(game_state->stats.score, 0);

  free_game(game_state);

  ck_assert_ptr_eq(game_state->field.field, NULL);
  ck_assert_ptr_eq(game_state->figure.next_figure, NULL);

  ck_assert_int_eq(game_state->figure.figure_height, 0);
  ck_assert_int_eq(game_state->figure.figure_width, 0);
  ck_assert_int_eq(game_state->figure.type, 0);

  ck_assert_int_eq(game_state->figure.next_figure_height, 0);
  ck_assert_int_eq(game_state->figure.next_figure_width, 0);
  ck_assert_int_eq(game_state->figure.next_type, 0);

  ck_assert_int_eq(game_state->status.pause, 0);
  ck_assert_int_eq(game_state->status.win, 0);
  ck_assert_int_eq(game_state->status.is_playing, 0);

  ck_assert_int_eq(game_state->stats.score, 0);
  ck_assert_int_eq(game_state->stats.high_score, 0);
  ck_assert_int_eq(game_state->stats.level, 0);
  ck_assert_int_eq(game_state->stats.speed, 0);
}
END_TEST

START_TEST(test_init_game_info) {
  GameInfo_t game_info = init_game_info();

  ck_assert_ptr_ne(game_info.field, NULL);
  ck_assert_ptr_ne(game_info.next, NULL);

  free_game_gi(&game_info);

  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);
}
END_TEST

START_TEST(test_copy_field) {
  int **a = init_array(4, 4);
  int **b = init_array(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      a[i][j] = 3;
    }
  }

  copy_field(4, 4, a, b);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(a[i][j], b[i][j]);
    }
  }

  free_array(4, a);
  free_array(4, b);

  a = NULL;
  b = NULL;

  ck_assert_ptr_eq(a, NULL);
  ck_assert_ptr_eq(b, NULL);
}
END_TEST

START_TEST(test_init_and_free_game) {
  Game_state_t *g_state = get_game_state();
  GameInfo_t game_info = init_game_info();

  init_game_state(g_state);

  updateCurrentState();
  get_game_state();

  free_game(g_state);
  free_game_gi(&game_info);

  g_state = NULL;
  // game_info = NULL;

  ck_assert_ptr_eq(g_state, NULL);
  // ck_assert_ptr_eq(&game_info, NULL);

  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);
}
END_TEST

START_TEST(test_copy_game_to_gi) {
  Game_state_t *g_state = get_game_state();
  GameInfo_t game_info = init_game_info();

  init_game_state(g_state);

  for (int i = 0; i < ROWS_GAME; i++) {
    for (int j = 0; j < COLS_GAME; j++) {
      g_state->field.field[i][j] = 2;
    }
  }

  g_state->stats.speed = 3;

  game_info = copy_game_to_gi(g_state);

  ck_assert_int_eq(game_info.score, g_state->stats.score);

  for (int i = 0; i < ROWS_GAME; i++) {
    for (int j = 0; j < COLS_GAME; j++) {
      ck_assert_int_eq(g_state->field.field[i][j], game_info.field[i][j]);
    }
  }

  free_game(g_state);
  free_game_gi(&game_info);

  g_state = NULL;
  // game_info = NULL;

  ck_assert_ptr_eq(g_state, NULL);
  // ck_assert_ptr_eq(&game_info, NULL);

  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);
}
END_TEST

Suite *test_init_field_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_init_field");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_array);
  tcase_add_test(tc_core, test_init_next_figure);
  tcase_add_test(tc_core, test_init_game_state);
  tcase_add_test(tc_core, test_init_game_info);
  tcase_add_test(tc_core, test_init_and_free_game);
  //______________
  tcase_add_test(tc_core, test_copy_field);
  tcase_add_test(tc_core, test_copy_game_to_gi);

  suite_add_tcase(s, tc_core);

  return s;
}

int test_init_field(void) {
  Suite *s = test_init_field_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
