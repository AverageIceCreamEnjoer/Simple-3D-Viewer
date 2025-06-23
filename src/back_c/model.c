#include "model.h"

Model* Model_Create() {
  Model* model = (Model*)malloc(sizeof(Model));
  if (model != NULL) {
    strcpy(model->_filePath, "");
    model->_scale = 1;
    init_object(&model->_obj);
    model->setted = false;
    model->_obj_changed = false;
    model->_changed = false;
    model->_ver_buf_size = 0;
    model->_edge_buf_size = 0;
  }
  return model;
}

void Model_Destroy(Model* model) {
  if (model != NULL) {
    free_object(&model->_obj);
    free(model);
  }
}

bool Model_setObject(Model* model, const char* filePath) {
  strcpy(model->_filePath, filePath);
  if (model->setted) {
    free_object(&model->_obj);
    init_object(&model->_obj);
  }
  model->setted = readObject(&model->_obj, model->_filePath);
  model->_obj_changed = true;
  if (model->setted) {
    center(&model->_obj);
    normalize(&model->_obj);
  }
  return model->setted;
}

void Model_transform(Model* model, int operation, float value) {
  switch (operation) {
    case 0:
      translate(&model->_obj, value, 0, 0);
      break;
    case 1:
      translate(&model->_obj, 0, value, 0);
      break;
    case 2:
      translate(&model->_obj, 0, 0, value);
      break;
    case 3:
      scale(&model->_obj, value / model->_scale);
      model->_scale = value;
      break;
    case 4:
      rotateX(&model->_obj, value);
      break;
    case 5:
      rotateY(&model->_obj, value);
      break;
    case 6:
      rotateZ(&model->_obj, value);
      break;
  }
  model->_changed = true;
}

void Model_toNormal(Model* model) {
  if (readObject(&model->_obj, model->_filePath)) {
    model->_scale = 1;
    normalize(&model->_obj);
    center(&model->_obj);
    model->_changed = true;
  }
}

float Model_getVertex(Model* model, int row, int col) {
  return model->_obj.vertices.matrix[row][col];
}

const char* Model_getFilePath(Model* model) { return model->_filePath; }

float Model_getScale(Model* model) { return model->_scale; }

unsigned int Model_getNumberVertex(Model* model) {
  return model->_obj.number_vertex;
}

unsigned int Model_getNumberFace(Model* model) {
  return model->_obj.number_face;
}

unsigned int Model_getFaceSize(Model* model, unsigned int index) {
  return model->_obj.face_sizes[index] * 3;
}

const Object* Model_getObject(Model* model) { return &model->_obj; }

void Model_getBufSize(Model* model, unsigned int* ver_buf_size,
                      unsigned int* edge_buf_size) {
  if (model->setted) {
    if (model->_obj_changed) {
      *ver_buf_size = model->_obj.number_vertex * 3;
      *edge_buf_size = 0;
      for (unsigned int i = 0; i < model->_obj.number_face; i++) {
        *edge_buf_size += model->_obj.face_sizes[i] * 3;
      }
      model->_ver_buf_size = *ver_buf_size;
      model->_edge_buf_size = *edge_buf_size;
      model->_obj_changed = false;
    } else {
      *ver_buf_size = model->_ver_buf_size;
      *edge_buf_size = model->_edge_buf_size;
    }
  } else {
    *ver_buf_size = 0;
    *edge_buf_size = 0;
    model->_obj_changed = false;
  }
}

void Model_loadBuffer(Model* model, float* vertex_buffer, float* edge_buffer,
                      bool load) {
  if (model->setted) {
    if (model->_changed || load) {
      for (unsigned int i = 0; i < model->_obj.number_vertex; ++i) {
        vertex_buffer[i * 3] = model->_obj.vertices.matrix[i][0];
        vertex_buffer[i * 3 + 1] = model->_obj.vertices.matrix[i][1];
        vertex_buffer[i * 3 + 2] = model->_obj.vertices.matrix[i][2];
      }
      unsigned int index = 0;
      for (unsigned int i = 0; i < model->_obj.number_face; ++i) {
        for (unsigned int j = 0;
             j < model->_obj.face_sizes[i] &&
             model->_obj.faces[i][j] < model->_obj.number_vertex;
             ++j) {
          edge_buffer[index++] =
              model->_obj.vertices.matrix[model->_obj.faces[i][j]][0];
          edge_buffer[index++] =
              model->_obj.vertices.matrix[model->_obj.faces[i][j]][1];
          edge_buffer[index++] =
              model->_obj.vertices.matrix[model->_obj.faces[i][j]][2];
        }
      }
      model->_changed = false;
    }
  }
}