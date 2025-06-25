#pragma once

#include <string.h>

#include "object.h"

typedef struct {
  char file_path[256];
  Object obj;
  float scale;
  unsigned int max_face_size;
  unsigned int ver_buf_size;
  unsigned int edge_buf_size;
  bool changed;
  bool obj_changed;
  bool setted;
} Model;

Model* ModelCreate();
void ModelDestroy(Model* model);
bool ModelSetObject(Model* model, const char* file_path);
void ModelTransform(Model* model, int operation, float value);
float ModelGetScale(Model* model);
const char* ModelGetFilePath(Model* model);
unsigned int ModelGetNumberVertex(Model* model);
unsigned int ModelGetNumberFace(Model* model);
const Object* ModelGetObject(Model* model);
unsigned int ModelGetFaceSize(Model* model, unsigned int index);
void ModelToNormal(Model* model);
float ModelGetVertex(Model* model, int row, int col);
void ModelGetBufSize(Model* model, unsigned int* ver_buf_size,
                     unsigned int* edge_buf_size);
void ModelLoadBuffer(Model* model, float* vertex_buffer, float* edge_buffer,
                     bool load);