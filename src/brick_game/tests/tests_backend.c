#include "tests_main.h"

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

START_TEST(test_copy_game_to_gi) {
  Game_state_t *g_state = get_game_state();
  GameInfo_t game_info;

  init_game_state(g_state);

  for (int i = 0; i < ROWS_GAME; i++) {
    for (int j = 0; j < COLS_GAME; j++) {
      g_state->field.field[i][j] = 2;
    }
  }

  g_state->stats.speed = 3;

  copy_game_to_gi(g_state, &game_info);

  ck_assert_int_eq(game_info.score, g_state->stats.score);

  for (int i = 0; i < ROWS_GAME; i++) {
    for (int j = 0; j < COLS_GAME; j++) {
      ck_assert_int_eq(g_state->field.field[i][j], game_info.field[i][j]);
    }
  }

  free_game(g_state);
  free_game_gi(&game_info);

  g_state = NULL;
  game_info.field = NULL;
  game_info.next = NULL;

  ck_assert_ptr_eq(g_state, NULL);
  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);

  ck_assert_ptr_eq(game_info.field, NULL);
  ck_assert_ptr_eq(game_info.next, NULL);
}
END_TEST

START_TEST(test_figure_min_height) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  g_state->figure.type = I_SHAPE;

  int figure_height_I = figure_min_height(g_state);

  g_state->figure.type = J_SHAPE;

  int figure_height_J = figure_min_height(g_state);

  g_state->figure.type = L_SHAPE;

  int figure_height_L = figure_min_height(g_state);

  g_state->figure.type = T_SHAPE;

  int figure_height_T = figure_min_height(g_state);

  g_state->figure.type = O_SHAPE;

  int figure_height_O = figure_min_height(g_state);

  ck_assert_int_eq(figure_height_O, 2);

  g_state->figure.type = S_SHAPE;

  int figure_height_S = figure_min_height(g_state);

  g_state->figure.type = Z_SHAPE;

  int figure_height_Z = figure_min_height(g_state);

  ck_assert_int_eq(figure_height_I, 1);
  ck_assert_int_eq(figure_height_J, 3);
  ck_assert_int_eq(figure_height_L, 3);
  ck_assert_int_eq(figure_height_T, 2);
  ck_assert_int_eq(figure_height_O, 2);
  ck_assert_int_eq(figure_height_S, 2);
  ck_assert_int_eq(figure_height_Z, 2);

  free_game(g_state);
}
END_TEST

START_TEST(test_figure_min_width) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  g_state->figure.type = I_SHAPE;

  int figure_width_I = figure_min_width(g_state);

  g_state->figure.type = J_SHAPE;

  int figure_width_J = figure_min_width(g_state);

  g_state->figure.type = L_SHAPE;

  int figure_width_L = figure_min_width(g_state);

  g_state->figure.type = T_SHAPE;

  int figure_width_T = figure_min_width(g_state);

  g_state->figure.type = O_SHAPE;

  int figure_width_O = figure_min_width(g_state);

  g_state->figure.type = S_SHAPE;

  int figure_width_S = figure_min_width(g_state);

  g_state->figure.type = Z_SHAPE;

  int figure_width_Z = figure_min_width(g_state);

  ck_assert_int_eq(figure_width_I, 4);
  ck_assert_int_eq(figure_width_J, 2);
  ck_assert_int_eq(figure_width_L, 2);
  ck_assert_int_eq(figure_width_T, 3);
  ck_assert_int_eq(figure_width_O, 2);
  ck_assert_int_eq(figure_width_S, 3);
  ck_assert_int_eq(figure_width_Z, 3);

  free_game(g_state);
}
END_TEST

START_TEST(test_border_collision) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);
  g_state->figure.type = O_SHAPE;
  g_state->figure.y = 5;

  g_state->figure.x = 0;
  ck_assert_int_eq(border_collision(g_state), COLLISION_LEFT);

  g_state->figure.x = 8;
  ck_assert_int_eq(border_collision(g_state), COLLISION_RIGHT);

  g_state->figure.y = 18;
  g_state->figure.x = 0;
  ck_assert_int_eq(border_collision(g_state), COLLISION_DL);

  g_state->figure.y = 18;
  g_state->figure.x = 8;
  ck_assert_int_eq(border_collision(g_state), COLLISION_DR);

  g_state->figure.y = 18;
  g_state->figure.x = 4;
  ck_assert_int_eq(border_collision(g_state), COLLISION_DOWN);

  free_game(g_state);
}
END_TEST

START_TEST(test_update_score) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  g_state->figure.type = O_SHAPE;
  g_state->figure.y = 5;
  g_state->figure.x = 0;

  g_state->figure.y = 18;
  g_state->figure.x = 4;

  update_score(g_state, 1);

  ck_assert_int_eq(g_state->stats.score, 100);

  g_state->stats.score = 0;
  update_score(g_state, 2);

  ck_assert_int_eq(g_state->stats.score, 300);

  g_state->stats.score = 0;
  update_score(g_state, 3);

  ck_assert_int_eq(g_state->stats.score, 700);

  g_state->stats.score = 0;
  update_score(g_state, 4);

  ck_assert_int_eq(g_state->stats.score, 1500);

  free_game(g_state);
}
END_TEST

START_TEST(test_shift_lines) {
  Game_state_t *g_state = get_game_state();
  init_game_state(g_state);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      g_state->field.field[i][j] = 1;
    }
  }

  // g_state->field.field[0][0] = 1;
  g_state->field.field[1][0] = 2;
  g_state->field.field[2][0] = 3;

  shift_lines(g_state, 2);

  // ck_assert_int_eq(g_state->field.field[0][0], 3);
  ck_assert_int_eq(g_state->field.field[1][0], 1);
  ck_assert_int_eq(g_state->field.field[2][0], 2);

  free_game(g_state);
}
END_TEST

START_TEST(test_collapse_full_lines) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < COLS_GAME - 1; j++) {
      g_state->field.field[0][j] = 1;
    }
  }

  collapse_full_lines(g_state);

  ck_assert_int_eq(g_state->stats.score, 0);

  free_game(g_state);
}
END_TEST

START_TEST(test_clear_figure) {
  int figure[4][4] = {
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
  };

  Game_state_t *g_state = get_game_state();
  init_game_state(g_state);

  // Set up a figure in the game state
  g_state->figure.x = 0;
  g_state->figure.y = 0;
  g_state->figure.type = I_SHAPE;
  g_state->figure.figure_height = figure_min_height(g_state);
  g_state->figure.figure_width = figure_min_width(g_state);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      g_state->figure.figure[g_state->figure.type][i][j] = figure[i][j];
    }
  }

  // Place the figure in the field
  figure_to_field(g_state);

  // Verify that the figure is in the field
  for (int i = 0; i < g_state->figure.figure_height; i++) {
    for (int j = 0; j < g_state->figure.figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;
      ck_assert_int_eq(g_state->field.field[field_y][field_x], 1);
    }
  }

  // Clear the figure from the field
  clear_figure(g_state);

  // Verify that the figure has been cleared
  for (int i = 0; i < g_state->figure.figure_height; i++) {
    for (int j = 0; j < g_state->figure.figure_width; j++) {
      int field_y = g_state->figure.y + i;
      int field_x = g_state->figure.x + j;
      ck_assert_int_eq(g_state->field.field[field_y][field_x], 0);
    }
  }

  free_game(g_state);
}
END_TEST

START_TEST(test_bottom_figure_collision) {
  Game_state_t *g_state = get_game_state();
  init_game_state(g_state);

  g_state->figure.type = O_SHAPE;
  g_state->figure.y = 18;
  g_state->figure.x = 0;

  ck_assert_int_eq(bottom_figure_collision(g_state), 0);

  g_state->figure.type = O_SHAPE;
  g_state->figure.y = ROWS_GAME - 1;
  g_state->figure.x = 0;

  ck_assert_int_eq(bottom_figure_collision(g_state), 0);

  free_game(g_state);
}
END_TEST

Suite *test_backend_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_backend");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_copy_field);
  tcase_add_test(tc_core, test_copy_game_to_gi);
  tcase_add_test(tc_core, test_figure_min_height);
  tcase_add_test(tc_core, test_figure_min_width);
  tcase_add_test(tc_core, test_border_collision);
  tcase_add_test(tc_core, test_update_score);
  tcase_add_test(tc_core, test_shift_lines);
  tcase_add_test(tc_core, test_shift_lines);
  tcase_add_test(tc_core, test_collapse_full_lines);
  tcase_add_test(tc_core, test_clear_figure);
  tcase_add_test(tc_core, test_bottom_figure_collision);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_backend(void) {
  Suite *s = test_backend_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
