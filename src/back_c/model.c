#include "model.h"

Model* ModelCreate() {
  Model* model = (Model*)malloc(sizeof(Model));
  if (model != NULL) {
    strcpy(model->file_path, "");
    model->scale = 1;
    InitObject(&model->obj);
    model->setted = false;
    model->obj_changed = false;
    model->changed = false;
    model->ver_buf_size = 0;
    model->edge_buf_size = 0;
  }
  return model;
}

void ModelDestroy(Model* model) {
  if (model != NULL) {
    FreeObject(&model->obj);
    free(model);
  }
}

bool ModelSetObject(Model* model, const char* file_path) {
  strcpy(model->file_path, file_path);
  if (model->setted) {
    FreeObject(&model->obj);
    InitObject(&model->obj);
  }
  model->setted = ReadObject(&model->obj, model->file_path);
  model->obj_changed = true;
  if (model->setted) {
    Center(&model->obj);
    Normalize(&model->obj);
  }
  return model->setted;
}

void ModelTransform(Model* model, int operation, float value) {
  switch (operation) {
    case 0:
      Translate(&model->obj, value, 0, 0);
      break;
    case 1:
      Translate(&model->obj, 0, value, 0);
      break;
    case 2:
      Translate(&model->obj, 0, 0, value);
      break;
    case 3:
      Scale(&model->obj, value / model->scale);
      model->scale = value;
      break;
    case 4:
      RotateX(&model->obj, value);
      break;
    case 5:
      RotateY(&model->obj, value);
      break;
    case 6:
      RotateZ(&model->obj, value);
      break;
  }
  model->changed = true;
}

void ModelToNormal(Model* model) {
  if (ReadObject(&model->obj, model->file_path)) {
    model->scale = 1;
    Normalize(&model->obj);
    Center(&model->obj);
    model->changed = true;
  }
}

float ModelGetVertex(Model* model, int row, int col) {
  return model->obj.vertices.matrix[row][col];
}

const char* ModelGetFilePath(Model* model) { return model->file_path; }

float ModelGetScale(Model* model) { return model->scale; }

unsigned int ModelGetNumberVertex(Model* model) {
  return model->obj.number_vertex;
}

unsigned int ModelGetNumberFace(Model* model) { return model->obj.number_face; }

unsigned int ModelGetFaceSize(Model* model, unsigned int index) {
  return model->obj.face_sizes[index] * 3;
}

const Object* ModelGetObject(Model* model) { return &model->obj; }

void ModelGetBufSize(Model* model, unsigned int* ver_buf_size,
                     unsigned int* edge_buf_size) {
  if (model->setted) {
    if (model->obj_changed) {
      *ver_buf_size = model->obj.number_vertex * 3;
      *edge_buf_size = 0;
      for (unsigned int i = 0; i < model->obj.number_face; i++) {
        *edge_buf_size += model->obj.face_sizes[i] * 3;
      }
      model->ver_buf_size = *ver_buf_size;
      model->edge_buf_size = *edge_buf_size;
      model->obj_changed = false;
    } else {
      *ver_buf_size = model->ver_buf_size;
      *edge_buf_size = model->edge_buf_size;
    }
  } else {
    *ver_buf_size = 0;
    *edge_buf_size = 0;
    model->obj_changed = false;
  }
}

void ModelLoadBuffer(Model* model, float* vertex_buffer, float* edge_buffer,
                     bool load) {
  if (model->setted) {
    if (model->changed || load) {
      for (unsigned int i = 0; i < model->obj.number_vertex; ++i) {
        vertex_buffer[i * 3] = model->obj.vertices.matrix[i][0];
        vertex_buffer[i * 3 + 1] = model->obj.vertices.matrix[i][1];
        vertex_buffer[i * 3 + 2] = model->obj.vertices.matrix[i][2];
      }
      unsigned int index = 0;
      for (unsigned int i = 0; i < model->obj.number_face; ++i) {
        for (unsigned int j = 0;
             j < model->obj.face_sizes[i] &&
             model->obj.faces[i][j] < model->obj.number_vertex;
             ++j) {
          edge_buffer[index++] =
              model->obj.vertices.matrix[model->obj.faces[i][j]][0];
          edge_buffer[index++] =
              model->obj.vertices.matrix[model->obj.faces[i][j]][1];
          edge_buffer[index++] =
              model->obj.vertices.matrix[model->obj.faces[i][j]][2];
        }
      }
      model->changed = false;
    }
  }
}