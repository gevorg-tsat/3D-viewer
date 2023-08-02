#include <check.h>
#include <math.h>

#include "affine.h"
#include "file_to_object.h"
START_TEST(cube_pars_test) {
  char filename[] = "obj_samples/cube.obj";
  file_data obj;
  int err = parse_file(filename, &obj);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(obj.triangle_cnt, 12);
  clear_obj(&obj);
}
END_TEST

START_TEST(err_test) {
  char filename[] = "no_file.obj";
  file_data obj;
  int err = parse_file(filename, &obj);
  ck_assert_int_eq(err, 1);
  // clear_obj(&obj);
}
END_TEST

START_TEST(affine_test) {
  char filename[] = "obj_samples/cube.obj";
  file_data obj;
  parse_file(filename, &obj);
  double prev_value_x = obj.vertices[0], prev_value_y = obj.vertices[1],
         prev_value_z = obj.vertices[2];
  translate_ox_object(&obj, 1);
  translate_oy_object(&obj, 1);
  translate_oz_object(&obj, 1);
  ck_assert_double_eq_tol(prev_value_x + 1, obj.vertices[0], 1e-07);
  ck_assert_double_eq_tol(prev_value_y + 1, obj.vertices[1], 1e-07);
  ck_assert_double_eq_tol(prev_value_z + 1, obj.vertices[2], 1e-07);
  rotate_ox_object(&obj, M_PI);
  rotate_oy_object(&obj, M_PI);
  rotate_oz_object(&obj, M_PI);
  clear_obj(&obj);
}
END_TEST

Suite *parser_tests() {
  Suite *parser;
  TCase *parser_ts;
  parser = suite_create("Object File Parser");
  parser_ts = tcase_create("tests");
  tcase_add_test(parser_ts, cube_pars_test);
  tcase_add_test(parser_ts, err_test);
  tcase_add_test(parser_ts, affine_test);
  suite_add_tcase(parser, parser_ts);
  return parser;
}

int main() {
  Suite *parser = parser_tests();

  SRunner *parser_runner = srunner_create(parser);
  int number_failed;
  srunner_run_all(parser_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(parser_runner);
  srunner_free(parser_runner);

  return number_failed == 0 ? 0 : 1;
}
