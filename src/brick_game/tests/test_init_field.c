#include "tests_backend.h"

START_TEST(test_init_field_success) {
  Game_field_t field_t;
  int error = init_field(&field_t);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_ne(field_t.field, NULL);
  for (int i = 0; i < ROWS_GAME; i++) {
    ck_assert_ptr_ne(field_t.field[i], NULL);
  }

  int *p_x = &field_t.x;
  int *p_y = &field_t.y;
  ck_assert_ptr_nonnull(p_x);
  ck_assert_ptr_nonnull(p_y);

  free_field(&field_t);
  ck_assert_ptr_eq(field_t.field, NULL);
}
END_TEST

START_TEST(test_init_field_game_info_success) {
  GameInfo_t g_info;
  int error = init_field_gi(&g_info);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_ne(g_info.field, NULL);
  for (int i = 0; i < ROWS_GAME; i++) {
    ck_assert_ptr_ne(g_info.field[i], NULL);
  }

  free_field_gi(&g_info);
  ck_assert_ptr_eq(g_info.field, NULL);
}
END_TEST

START_TEST(test_init_game_state) {
  Game_state_t *game_state = get_game_state();

  Game_field_t field_t = {0};
  // init_field(&field_t);
  // game_state->field = &field_t;

  init_game_state(game_state, &field_t);

  ck_assert_ptr_ne(game_state, NULL);
  ck_assert_ptr_ne(game_state->field, NULL);
  ck_assert_int_lt(game_state->figure.type, 7);
  ck_assert_int_eq(game_state->status.is_playing, 0);
  ck_assert_int_eq(game_state->stats.score, 0);

  // free_field(game_state->field);
  free_game(game_state);
}

// START_TEST(test_on_pause_state) {
//   Game_state_t g_state;

//   init_game_state(&g_state, NULL);

//   UserAction_t action = Pause;

//   on_pause_state(&g_state, action);

//   ck_assert_int_eq(g_state.status.pause, true);
//   ck_assert_int_eq(g_state.status.status, PAUSE);

//   on_pause_state(&g_state, action);

//   ck_assert_int_eq(g_state.status.pause, false);
//   ck_assert_int_eq(g_state.status.status, MOVING);
// }
// END_TEST

END_TEST

Suite *test_init_field_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_init_field");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_field_success);
  tcase_add_test(tc_core, test_init_field_game_info_success);
  tcase_add_test(tc_core, test_init_game_state);
  // tcase_add_test(tc_core, test_on_pause_state);

  suite_add_tcase(s, tc_core);

  return s;
}

// int main(void) {
//   Suite *s1 = suite_create("Core");
//   TCase *tc1_1 = tcase_create("Core");
//   SRunner *sr = srunner_create(s1);

//   tcase_add_test(tc1_1, test_on_pause_state);
//   suite_add_tcase(s1, tc1_1);

//   srunner_run_all(sr, CK_ENV);
//   int number_failed = srunner_ntests_failed(sr);
//   srunner_free(sr);

//   return (number_failed == 0) ? 0 : 1;
// }

int test_init_field(void) {
  Suite *s = test_init_field_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
