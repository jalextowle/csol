#include <stdlib.h>
#include <check.h>
#include "comments.h"

START_TEST(single_line1) 
{
  ck_assert_int_eq(comment_scanner("/Users/alextowle/csol/src/lexical/scanner/mock/source1.sol", "/Users/alextowle/csol/src/lexical/scanner/mock/target1.sol"), 0);
  // FIXME - Ensure that the target program is correct
} END_TEST

START_TEST(multi_line1) 
{
  ck_assert_int_eq(multi_comment_scanner("/Users/alextowle/csol/src/lexical/scanner/mock/source2.sol", "/Users/alextowle/csol/src/lexical/scanner/mock/target2.sol"), 0);
  // FIXME - Ensure that the target program is correct
} END_TEST

START_TEST(multi_line_error1) 
{
  ck_assert_int_eq(multi_comment_scanner("/Users/alextowle/csol/src/lexical/scanner/mock/source3.sol", "/Users/alextowle/csol/src/lexical/scanner/mock/target3.sol"), 1);
} END_TEST

Suite* single_line_suite() {
  Suite *s; 
  TCase *tc_core;
  s = suite_create("Single-Line Scanner");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, single_line1); 
  suite_add_tcase(s, tc_core);

  return s;
}

Suite* multi_line_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Multi-Line Scanner");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, multi_line1);
  tcase_add_test(tc_core, multi_line_error1);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed1, number_failed2;
  Suite *s1;
  Suite *s2;
  SRunner *sr1;
  SRunner *sr2;

  s1 = single_line_suite();
  s2 = multi_line_suite();
  sr1 = srunner_create(s1);
  sr2 = srunner_create(s2);

  srunner_run_all(sr1, CK_NORMAL);
  srunner_run_all(sr2, CK_NORMAL);
  number_failed1 = srunner_ntests_failed(sr1);
  number_failed2 = srunner_ntests_failed(sr2);
  srunner_free(sr1);
  srunner_free(sr2);
  return (number_failed1 == 0 && number_failed2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
