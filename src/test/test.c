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
  Model* model = ModelCreate();
  const char* testFilePath = "obj/cube.obj";
  ModelSetObject(model, testFilePath);
  ck_assert_str_eq(ModelGetFilePath(model), testFilePath);
  ck_assert_int_eq(ModelGetNumberVertex(model), 8);
  ck_assert_int_eq(ModelGetNumberFace(model), 12);
  ModelDestroy(model);
}
END_TEST

START_TEST(set_object_failure) {
  Model* model = ModelCreate();
  const char* invalidFilePath = "nonexistent_file.obj";
  ModelSetObject(model, invalidFilePath);
  ck_assert_str_eq(ModelGetFilePath(model), invalidFilePath);
  ck_assert_int_eq(ModelGetNumberVertex(model), 0);
  ck_assert_int_eq(ModelGetNumberFace(model), 0);
  ModelDestroy(model);
}
END_TEST

// Тест для метода transform
START_TEST(transform_translate_x) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 0, 1.0);
  double expected[8][3] = {
      {2.0, -1.0, -1.0}, {2.0, -1.0, 1.0}, {0.0, -1.0, 1.0}, {0.0, -1.0, -1.0},
      {2.0, 1.0, -1.0},  {2.0, 1.0, 1.0},  {0.0, 1.0, 1.0},  {0.0, 1.0, -1.0}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_translate_y) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 1, 2.0);
  double expected[8][3] = {
      {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0},
      {1.0, 3.0, -1.0}, {1.0, 3.0, 1.0}, {-1.0, 3.0, 1.0}, {-1.0, 3.0, -1.0}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_translate_z) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 2, 3.0);
  double expected[8][3] = {
      {1.0, -1.0, 2.0}, {1.0, -1.0, 4.0}, {-1.0, -1.0, 4.0}, {-1.0, -1.0, 2.0},
      {1.0, 1.0, 2.0},  {1.0, 1.0, 4.0},  {-1.0, 1.0, 4.0},  {-1.0, 1.0, 2.0}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_scale) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 3, 2.0);
  double expected[8][3] = {{2.0, -2.0, -2.0}, {2.0, -2.0, 2.0},
                           {-2.0, -2.0, 2.0}, {-2.0, -2.0, -2.0},
                           {2.0, 2.0, -2.0},  {2.0, 2.0, 2.0},
                           {-2.0, 2.0, 2.0},  {-2.0, 2.0, -2.0}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_rotate_x) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 4, M_PI / 2);
  float expected[8][3] = {{1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
                          {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_rotate_y) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 5, M_PI / 2);
  float expected[8][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
                          {1.0, -1.0, 1.0},   {-1.0, -1.0, 1.0},
                          {-1, 1, -1},        {1, 1, -1},
                          {1, 1, 1},          {-1, 1, 1}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

START_TEST(transform_rotate_z) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 6, M_PI / 2);
  float expected[8][3] = {{1, 1, -1},  {1, 1, 1},  {1, -1, 1},  {1, -1, -1},
                          {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}, {-1, -1, -1}};
  ck_matrix_eq(model->obj.vertices.matrix, expected, 8, 3);
  ModelDestroy(model);
}
END_TEST

// Тест для метода getFaceData
START_TEST(get_face_size) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  int face_size = ModelGetFaceSize(model, 0);
  ck_assert_int_eq(face_size, 9);
  ModelDestroy(model);
}
END_TEST

// Тест для метода toNormal
START_TEST(to_normal) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ModelTransform(model, 3, 2.0);  // Масштабируем на 2
  ModelToNormal(model);
  ck_assert_float_eq(model->scale, 1.0);
  ModelDestroy(model);
}
END_TEST

// Тест для метода getVertex
START_TEST(get_vertex) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  ck_assert_double_eq(ModelGetVertex(model, 0, 0), 1.0);
  ck_assert_double_eq(ModelGetVertex(model, 0, 1), -1.0);
  ck_assert_double_eq(ModelGetVertex(model, 0, 2), -1.0);
  ck_assert_double_eq(ModelGetVertex(model, 1, 0), 1.0);
  ck_assert_double_eq(ModelGetVertex(model, 1, 1), -1.0);
  ck_assert_double_eq(ModelGetVertex(model, 1, 2), 1.0);
  ModelDestroy(model);
}
END_TEST

// Тест для метода getBufSize
START_TEST(get_buf_size) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  unsigned int verbuf, edgbuf;
  ModelGetBufSize(model, &verbuf, &edgbuf);
  ck_assert_int_eq(verbuf, 24);
  ck_assert_int_eq(edgbuf, 108);
  ModelDestroy(model);
}
END_TEST

// Тест для метода loadBuffer
START_TEST(load_buffer) {
  Model* model = ModelCreate();
  ModelSetObject(model, "obj/cube.obj");
  unsigned int verbuf, edgbuf;
  ModelGetBufSize(model, &verbuf, &edgbuf);
  float verbuf2[24], edgbuf2[108];
  ModelLoadBuffer(model, verbuf2, edgbuf2, true);
  for (int i = 0; i < 24; ++i) {
    ck_assert_double_eq(verbuf2[i], model->obj.vertices.matrix[i / 3][i % 3]);
  }
  ModelDestroy(model);
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