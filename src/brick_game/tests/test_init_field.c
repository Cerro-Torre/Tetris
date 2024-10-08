#include "tests_backend.h"

START_TEST(test_init_field_1) {
  Game_field_t field_t;
  init_field(&field_t);
  int res = field_t.field[0][0];

  ck_assert_int_eq(res, 0);

  free_field(&field_t);
}
END_TEST

// START_TEST(test_s21_create_matrix_2) {
//   matrix_t mtx;

//   int res = s21_create_matrix(1, 0, &mtx);

//   ck_assert_int_eq(res, INCORRECT_MATRIX);
// }
// END_TEST

// START_TEST(test_s21_create_matrix_3) {
//   matrix_t mtx;

//   int res = s21_create_matrix(0, 1, &mtx);

//   ck_assert_int_eq(res, INCORRECT_MATRIX);
// }
// END_TEST

// START_TEST(test_s21_create_matrix_4) {
//   matrix_t mtx;

//   int res = s21_create_matrix(1, 1, &mtx);

//   ck_assert_int_eq(res, OK);
//   s21_remove_matrix(&mtx);
// }
// END_TEST

Suite *test_init_field_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_init_field");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init_field_1);
  //   tcase_add_test(tc_core, test_s21_create_matrix_2);
  //   tcase_add_test(tc_core, test_s21_create_matrix_3);
  //   tcase_add_test(tc_core, test_s21_create_matrix_4);
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
