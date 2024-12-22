#include "./tests_main.h"

int main(void) {
  int number_failed = test_inits();
  number_failed += test_backend();
  number_failed += test_fsm();
  return number_failed;
}