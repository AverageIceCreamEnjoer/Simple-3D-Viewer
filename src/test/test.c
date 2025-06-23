#include <check.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../back_c/model.h"

#define M_PI 3.14159265358979323846

// Макрос для сравнения матриц
#define ck_matrix_eq(actual, expected, rows, cols) \
  for (int i = 0; i < rows; ++i)                   \
    for (int j = 0; j < cols; ++j)                 \
  ck_assert_int_eq(actual[i][j] - expected[i][j] < 1e-6, 1)

// Тест для метода setObject
START_TEST(set_object_success) {
  Model* model = Model_Create();
  const char* testFilePath = "obj/cube.obj";
  Model_setObject(model, testFilePath);
  ck_assert_str_eq(Model_getFilePath(model), testFilePath);
  ck_assert_int_eq(Model_getNumberVertex(model), 8);
  ck_assert_int_eq(Model_getNumberFace(model), 12);
  Model_Destroy(model);
}
END_TEST

START_TEST(set_object_failure) {
  Model* model = Model_Create();
  const char* invalidFilePath = "nonexistent_file.obj";
  Model_setObject(model, invalidFilePath);
  ck_assert_str_eq(Model_getFilePath(model), invalidFilePath);
  ck_assert_int_eq(Model_getNumberVertex(model), 0);
  ck_assert_int_eq(Model_getNumberFace(model), 0);
  Model_Destroy(model);
}
END_TEST

// Тест для метода transform
START_TEST(transform_translate_x) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 0, 1.0);
  double expected[8][3] = {
      {2.0, -1.0, -1.0}, {2.0, -1.0, 1.0}, {0.0, -1.0, 1.0}, {0.0, -1.0, -1.0},
      {2.0, 1.0, -1.0},  {2.0, 1.0, 1.0},  {0.0, 1.0, 1.0},  {0.0, 1.0, -1.0}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_translate_y) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 1, 2.0);
  double expected[8][3] = {
      {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0},
      {1.0, 3.0, -1.0}, {1.0, 3.0, 1.0}, {-1.0, 3.0, 1.0}, {-1.0, 3.0, -1.0}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_translate_z) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 2, 3.0);
  double expected[8][3] = {
      {1.0, -1.0, 2.0}, {1.0, -1.0, 4.0}, {-1.0, -1.0, 4.0}, {-1.0, -1.0, 2.0},
      {1.0, 1.0, 2.0},  {1.0, 1.0, 4.0},  {-1.0, 1.0, 4.0},  {-1.0, 1.0, 2.0}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_scale) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 3, 2.0);
  double expected[8][3] = {{2.0, -2.0, -2.0}, {2.0, -2.0, 2.0},
                           {-2.0, -2.0, 2.0}, {-2.0, -2.0, -2.0},
                           {2.0, 2.0, -2.0},  {2.0, 2.0, 2.0},
                           {-2.0, 2.0, 2.0},  {-2.0, 2.0, -2.0}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_rotate_x) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 4, M_PI / 2);
  float expected[8][3] = {{1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
                          {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_rotate_y) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 5, M_PI / 2);
  float expected[8][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
                          {1.0, -1.0, 1.0},   {-1.0, -1.0, 1.0},
                          {-1, 1, -1},        {1, 1, -1},
                          {1, 1, 1},          {-1, 1, 1}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

START_TEST(transform_rotate_z) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 6, M_PI / 2);
  float expected[8][3] = {{1, 1, -1},  {1, 1, 1},  {1, -1, 1},  {1, -1, -1},
                          {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}, {-1, -1, -1}};
  ck_matrix_eq(model->_obj.vertices.matrix, expected, 8, 3);
  Model_Destroy(model);
}
END_TEST

// Тест для метода getFaceData
START_TEST(get_face_size) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  int face_size = Model_getFaceSize(model, 0);
  ck_assert_int_eq(face_size, 9);
  Model_Destroy(model);
}
END_TEST

// Тест для метода toNormal
START_TEST(to_normal) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  Model_transform(model, 3, 2.0);  // Масштабируем на 2
  Model_toNormal(model);
  ck_assert_float_eq(model->_scale, 1.0);
  Model_Destroy(model);
}
END_TEST

// Тест для метода getVertex
START_TEST(get_vertex) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  ck_assert_double_eq(Model_getVertex(model, 0, 0), 1.0);
  ck_assert_double_eq(Model_getVertex(model, 0, 1), -1.0);
  ck_assert_double_eq(Model_getVertex(model, 0, 2), -1.0);
  ck_assert_double_eq(Model_getVertex(model, 1, 0), 1.0);
  ck_assert_double_eq(Model_getVertex(model, 1, 1), -1.0);
  ck_assert_double_eq(Model_getVertex(model, 1, 2), 1.0);
  Model_Destroy(model);
}
END_TEST

// Тест для метода getBufSize
START_TEST(get_buf_size) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  unsigned int verbuf, edgbuf;
  Model_getBufSize(model, &verbuf, &edgbuf);
  ck_assert_int_eq(verbuf, 24);
  ck_assert_int_eq(edgbuf, 108);
  Model_Destroy(model);
}
END_TEST

// Тест для метода loadBuffer
START_TEST(load_buffer) {
  Model* model = Model_Create();
  Model_setObject(model, "obj/cube.obj");
  unsigned int verbuf, edgbuf;
  Model_getBufSize(model, &verbuf, &edgbuf);
  float verbuf2[24], edgbuf2[108];
  Model_loadBuffer(model, verbuf2, edgbuf2, true);
  for (int i = 0; i < 24; ++i) {
    ck_assert_double_eq(verbuf2[i], model->_obj.vertices.matrix[i / 3][i % 3]);
  }
  Model_Destroy(model);
}
END_TEST

// Определение набора тестов
Suite* model_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("Model");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, set_object_success);
  tcase_add_test(tc_core, set_object_failure);
  tcase_add_test(tc_core, transform_translate_x);
  tcase_add_test(tc_core, transform_translate_y);
  tcase_add_test(tc_core, transform_translate_z);
  tcase_add_test(tc_core, transform_scale);
  tcase_add_test(tc_core, transform_rotate_x);
  tcase_add_test(tc_core, transform_rotate_y);
  tcase_add_test(tc_core, transform_rotate_z);
  tcase_add_test(tc_core, get_face_size);
  tcase_add_test(tc_core, to_normal);
  tcase_add_test(tc_core, get_vertex);
  tcase_add_test(tc_core, get_buf_size);
  tcase_add_test(tc_core, load_buffer);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = model_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}