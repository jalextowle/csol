#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../../src/lexical/scanner/comments.h"
#include "../../src/lexical/scanner/whitespace.h"

int file_equal(char* _src1, char* _src2) {
  char c1, c2;
  FILE *src1, *src2;
  src1 = fopen(_src1, "r");
  src2 = fopen(_src2, "r");
  if (src1 == NULL || src2 == NULL) {
    return 0;
  }

  c1 = getc(src1);
  c2 = getc(src2);

  while(c1 != EOF && c2 != EOF) {
    if (c1 != c2) {
      printf("%c %c\n", c1, c2);
      return 0;
    } 
    c1 = getc(src1);
    c2 = getc(src2);
  }
  return c1 == c2;
}

START_TEST(single_line_code) 
{
  ck_assert_int_eq(comment_scanner("/Users/alextowle/csol/test/lexical/mock/source1.sol", "/Users/alextowle/csol/test/lexical/mock/target1.sol"), 0);
} END_TEST

START_TEST(single_line_correctness) {
  ck_assert_int_eq(file_equal("/Users/alextowle/csol/test/lexical/mock/expected1.sol", "/Users/alextowle/csol/test/lexical/mock/target1.sol"), 1);
} END_TEST

START_TEST(multi_line_code1) 
{
  ck_assert_int_eq(multi_comment_scanner("/Users/alextowle/csol/test/lexical/mock/source2.sol", "/Users/alextowle/csol/test/lexical/mock/target2.sol"), 0);
} END_TEST

START_TEST(multi_line_correctness1) 
{
  ck_assert_int_eq(file_equal("/Users/alextowle/csol/test/lexical/mock/expected2.sol", "/Users/alextowle/csol/test/lexical/mock/target2.sol"), 1);
} END_TEST

START_TEST(multi_line_error1) 
{
  ck_assert_int_eq(multi_comment_scanner("/Users/alextowle/csol/test/lexical/mock/source3.sol", "/Users/alextowle/csol/test/lexical/mock/target3.sol"), 1);
} END_TEST

Suite* single_line_suite() {
  Suite *s; 
  TCase *tc_core;
  s = suite_create("Single-Line Scanner");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, single_line_code); 
  tcase_add_test(tc_core, single_line_correctness); 
  suite_add_tcase(s, tc_core);

  return s;
}

Suite* multi_line_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Multi-Line Scanner");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, multi_line_code1);
  tcase_add_test(tc_core, multi_line_correctness1);
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

  // FIXME - Remove and add to test suite
  whitespace_scanner("/Users/alextowle/csol/test/lexical/mock/source4.sol", "/Users/alextowle/csol/test/lexical/mock/target4.sol");

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
