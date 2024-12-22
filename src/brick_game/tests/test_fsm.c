#include "tests_main.h"

START_TEST(test_on_init_state) {
  Game_state_t *g_state = get_game_state();

  on_init_state(g_state, Down);

  ck_assert_int_eq(g_state->status.status, INIT);

  on_init_state(g_state, Terminate);

  ck_assert_int_eq(g_state->status.status, GAMEOVER);

  on_init_state(g_state, Start);

  ck_assert_int_eq(g_state->status.status, START);

  userInput(Start, false);

  ck_assert_int_eq(g_state->status.status, SPAWN);

  g_state->status.status = INIT;

  userInput(Down, false);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_start_state) {
  Game_state_t *g_state = get_game_state();
  UserAction_t action = {0};

  g_state->status.is_playing = true;

  on_start_state(g_state, action);

  ck_assert_int_eq(g_state->status.status, SPAWN);

  on_start_state(g_state, Terminate);

  ck_assert_int_eq(g_state->status.status, GAMEOVER);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_spawn_state) {
  Game_state_t *g_state = get_game_state();
  UserAction_t action = {Down};

  g_state->status.is_playing = true;

  on_spawn_state(g_state, action);

  ck_assert_int_eq(g_state->status.status, MOVING);

  g_state->status.status = SPAWN;

  userInput(Down, false);

  ck_assert_int_eq(g_state->status.status, MOVING);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_move_state) {
  Game_state_t *g_state = get_game_state();

  on_move_state(g_state, Down);

  ck_assert_int_eq(g_state->status.status, MOVING);

  on_move_state(g_state, Right);

  ck_assert_int_eq(g_state->status.status, MOVING);

  on_move_state(g_state, Left);

  ck_assert_int_eq(g_state->status.status, MOVING);

  on_move_state(g_state, Pause);

  ck_assert_int_eq(g_state->status.status, PAUSE);

  g_state->status.status = MOVING;

  userInput(Down, false);

  ck_assert_int_eq(g_state->status.status, MOVING);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_attach_state) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  g_state->status.status = ATTACHING;

  userInput(Left, false);

  ck_assert_int_eq(g_state->status.status, MOVING);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_pause_state) {
  Game_state_t *g_state = get_game_state();
  UserAction_t action = {Down};

  on_move_state(g_state, action);

  userInput(Pause, false);

  ck_assert_int_eq(g_state->status.status, PAUSE);

  g_state->status.status = PAUSE;

  userInput(Pause, false);

  free_game(g_state);
}
END_TEST

START_TEST(test_on_shift_state) {
  Game_state_t *g_state = get_game_state();
  UserAction_t action = {0};

  on_shift_state(g_state, action);

  ck_assert_int_eq(g_state->status.status, MOVING);

  on_shift_state(g_state, Pause);

  ck_assert_int_eq(g_state->status.status, PAUSE);

  userInput(Down, false);

  g_state->status.status = SHIFTING;
  userInput(Down, false);

  free_game(g_state);
}

END_TEST

START_TEST(test_move_left) {
  Game_state_t *g_state = get_game_state();
  init_game_state(g_state);

  g_state->figure.x = 5;
  g_state->figure.figure_height = 2;
  g_state->figure.figure_width = 2;

  g_state->figure.figure[g_state->figure.type][0][0] = 1;
  g_state->figure.figure[g_state->figure.type][0][1] = 1;
  g_state->figure.figure[g_state->figure.type][1][0] = 1;
  g_state->figure.figure[g_state->figure.type][1][1] = 1;

  move_left(g_state);

  ck_assert_int_eq(g_state->figure.x, 4);

  g_state->field.field[g_state->figure.y][g_state->figure.x - 1] = 9;
  move_left(g_state);

  ck_assert_int_eq(g_state->figure.x, 4);

  free_game(g_state);
}
END_TEST

START_TEST(test_move_right) {
  Game_state_t *g_state = get_game_state();
  init_game_state(g_state);

  g_state->figure.x = 5;
  g_state->figure.figure_height = 2;
  g_state->figure.figure_width = 2;

  g_state->figure.figure[g_state->figure.type][0][0] = 1;
  g_state->figure.figure[g_state->figure.type][0][1] = 1;
  g_state->figure.figure[g_state->figure.type][1][0] = 1;
  g_state->figure.figure[g_state->figure.type][1][1] = 1;

  move_right(g_state);

  ck_assert_int_eq(g_state->figure.x, 6);

  g_state->field.field[g_state->figure.y]
                      [g_state->figure.x + g_state->figure.figure_width] = 9;
  move_right(g_state);

  ck_assert_int_eq(g_state->figure.x, 6);

  free_game(g_state);
}
END_TEST

START_TEST(test_figure_is_attaching) {
  Game_state_t *g_state = get_game_state();

  init_game_state(g_state);

  g_state->figure.type = O_SHAPE;
  g_state->figure.x = 5;
  g_state->figure.y = 18;
  g_state->figure.figure_height = 2;
  g_state->figure.figure_width = 2;

  ck_assert_int_eq(figure_is_attaching(g_state), 0);

  move_down(g_state);
  ck_assert_int_eq(figure_is_attaching(g_state), 1);

  free_game(g_state);
}
END_TEST

Suite *test_fsm_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_fsm");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_on_init_state);
  tcase_add_test(tc_core, test_on_start_state);
  tcase_add_test(tc_core, test_on_spawn_state);
  tcase_add_test(tc_core, test_on_move_state);
  tcase_add_test(tc_core, test_on_attach_state);
  tcase_add_test(tc_core, test_on_pause_state);
  tcase_add_test(tc_core, test_on_shift_state);
  tcase_add_test(tc_core, test_move_left);
  tcase_add_test(tc_core, test_move_right);
  tcase_add_test(tc_core, test_figure_is_attaching);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_fsm(void) {
  Suite *s = test_fsm_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
