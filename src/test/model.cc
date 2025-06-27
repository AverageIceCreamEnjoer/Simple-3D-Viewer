#include "test.h"

// Тест для метода SetObject
TEST_F(ModelTest, SetObject_Success) {
  std::string testFilePath = "obj/cube.obj";
  bool result = model.SetObject(testFilePath);
  EXPECT_TRUE(result);
  EXPECT_EQ(model.GetFilePath(), testFilePath);
  EXPECT_EQ(model.GetNumberVertex(), 8);
  EXPECT_EQ(model.GetNumberFace(), 12);
}

TEST_F(ModelTest, SetObject_Failure) {
  std::string invalidFilePath = "nonexistent_file.obj";
  bool result = model.SetObject(invalidFilePath);
  EXPECT_FALSE(result);
  EXPECT_EQ(model.GetFilePath(), invalidFilePath);
  EXPECT_EQ(model.GetNumberVertex(), 0);
  EXPECT_EQ(model.GetNumberFace(), 0);
}

// Тест для метода Transform
TEST_F(ModelTest, Transform_TranslateX) {
  model.Transform(0, 1.0);
  std::vector<std::vector<double>> expected_src = {
      {2.0, -1.0, -1.0}, {2.0, -1.0, 1.0}, {0.0, -1.0, 1.0}, {0.0, -1.0, -1.0},
      {2.0, 1.0, -1.0},  {2.0, 1.0, 1.0},  {0.0, 1.0, 1.0},  {0.0, 1.0, -1.0}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_TranslateY) {
  model.Transform(1, 2.0);
  std::vector<std::vector<double>> expected_src = {
      {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0},
      {1.0, 3.0, -1.0}, {1.0, 3.0, 1.0}, {-1.0, 3.0, 1.0}, {-1.0, 3.0, -1.0}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_TranslateZ) {
  model.Transform(2, 3.0);
  std::vector<std::vector<double>> expected_src = {
      {1.0, -1.0, 2.0}, {1.0, -1.0, 4.0}, {-1.0, -1.0, 4.0}, {-1.0, -1.0, 2.0},
      {1.0, 1.0, 2.0},  {1.0, 1.0, 4.0},  {-1.0, 1.0, 4.0},  {-1.0, 1.0, 2.0}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_Scale) {
  model.Transform(3, 2.0);
  std::vector<std::vector<double>> expected_src = {
      {2.0, -2.0, -2.0},  {2.0, -2.0, 2.0}, {-2.0, -2.0, 2.0},
      {-2.0, -2.0, -2.0}, {2.0, 2.0, -2.0}, {2.0, 2.0, 2.0},
      {-2.0, 2.0, 2.0},   {-2.0, 2.0, -2.0}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateX) {
  model.Transform(4, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
      {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateY) {
  model.Transform(5, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0},
      {-1.0, -1.0, 1.0},  {-1, 1, -1},       {1, 1, -1},
      {1, 1, 1},          {-1, 1, 1}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

TEST_F(ModelTest, Transform_RotateZ) {
  model.Transform(6, M_PI / 2);
  std::vector<std::vector<double>> expected_src = {
      {1, 1, -1},  {1, 1, 1},  {1, -1, 1},  {1, -1, -1},
      {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}, {-1, -1, -1}};
  Matrix expectedVertices(8, 3);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 3; ++j) expectedVertices(i, j) = expected_src[i][j];
  EXPECT_TRUE(model.GetObject().vertices == expectedVertices);
}

// Тест для метода GetFaceSize
TEST_F(ModelTest, GetFaceSize) {
  double face[9];
  model.GetFaceSize(0);
  std::vector<double> expectedFace = {1.0, -1.0, 1.0,  -1.0, -1.0,
                                      1.0, -1.0, -1.0, -1.0};
  bool result = true;
  for (int i = 0; i < 9; ++i)
    if (face[i] != expectedFace[i]) result = false;
  EXPECT_TRUE(result);
}

// Тест для метода ToNormal
TEST_F(ModelTest, ToNormal) {
  Matrix expectedVertices = model.GetObject().vertices;
  model.Transform(3, 2.0);  // Масштабируем на 2
  model.ToNormal();
  Matrix vertices = model.GetObject().vertices;
  EXPECT_TRUE(vertices == expectedVertices);
  EXPECT_DOUBLE_EQ(model.GetScale(), 1.0);
}

// Тест для метода GetVertex
TEST_F(ModelTest, GetVertex) {
  EXPECT_DOUBLE_EQ(model.GetVertex(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(model.GetVertex(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(model.GetVertex(0, 2), -1.0);
  EXPECT_DOUBLE_EQ(model.GetVertex(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(model.GetVertex(1, 1), -1.0);
  EXPECT_DOUBLE_EQ(model.GetVertex(1, 2), 1.0);
}

// Тест для метода GetBufSize
TEST_F(ModelTest, GetBufSize) {
  auto buf = model.GetBufSize();
  EXPECT_EQ(buf.first, 24);
  EXPECT_EQ(buf.second, 108);
}

// Тест для метода LoadBuffer
TEST_F(ModelTest, LoadBuffer) {
  auto buf_size = model.GetBufSize();
  float vertex_buffer[buf_size.first];
  float edge_buffer[buf_size.second];
  model.LoadBuffer(vertex_buffer, edge_buffer, true);
  for (size_t i = 0; i < buf_size.first; ++i)
    EXPECT_DOUBLE_EQ(vertex_buffer[i],
                     model.GetObject().vertices(i / 3, i % 3));
}