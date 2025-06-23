#ifndef __MODEL_H__
#define __MODEL_H__

#include <string.h>

#include "object.h"

typedef struct {
  char _filePath[256];
  Object _obj;
  float _scale;
  unsigned int _max_face_size;
  unsigned int _ver_buf_size;
  unsigned int _edge_buf_size;
  bool _changed;
  bool _obj_changed;
  bool setted;
} Model;

Model* Model_Create();
void Model_Destroy(Model* model);
bool Model_setObject(Model* model, const char* filePath);
void Model_transform(Model* model, int operation, float value);
float Model_getScale(Model* model);
const char* Model_getFilePath(Model* model);
unsigned int Model_getNumberVertex(Model* model);
unsigned int Model_getNumberFace(Model* model);
const Object* Model_getObject(Model* model);
unsigned int Model_getFaceSize(Model* model, unsigned int index);
void Model_toNormal(Model* model);
float Model_getVertex(Model* model, int row, int col);
void Model_getBufSize(Model* model, unsigned int* ver_buf_size,
                      unsigned int* edge_buf_size);
void Model_loadBuffer(Model* model, float* vertex_buffer, float* edge_buffer,
                      bool load);

#endif