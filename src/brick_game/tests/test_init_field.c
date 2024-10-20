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

  printf("%d %d\n", *p_x, *p_y);

  free_field(&field_t);
  ck_assert_ptr_eq(field_t.field, NULL);
  printf("%d %d\n", *p_x, *p_y);
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
  ck_assert_int_lt(game_state->figure.type, 5);
  ck_assert_int_eq(game_state->status.is_playing, 0);
  ck_assert_int_eq(game_state->stats.score, 0);

  int *p_x = &field_t.x;
  int *p_y = &field_t.y;
  printf("%d %d\n", *p_x, *p_y);

  // free_field(game_state->field);
  free_game(game_state, game_state->field);
}

END_TEST

Suite *test_init_field_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_init_field");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_field_success);
  tcase_add_test(tc_core, test_init_game_state);

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
