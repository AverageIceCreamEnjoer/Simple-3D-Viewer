#include "object.h"

void rotateX(Object* obj, float angleX) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_y, t_z;
    t_y = obj->vertices.matrix[i][1], t_z = obj->vertices.matrix[i][2];
    obj->vertices.matrix[i][1] = cos(angleX) * t_y - sin(angleX) * t_z;
    obj->vertices.matrix[i][2] = sin(angleX) * t_y + cos(angleX) * t_z;
  }
}

void rotateY(Object* obj, float angleY) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_x, t_z;
    t_x = obj->vertices.matrix[i][0], t_z = obj->vertices.matrix[i][2];
    obj->vertices.matrix[i][0] = cos(angleY) * t_x + sin(angleY) * t_z;
    obj->vertices.matrix[i][2] = -sin(angleY) * t_x + cos(angleY) * t_z;
  }
}

void rotateZ(Object* obj, float angleZ) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_x, t_y;
    t_x = obj->vertices.matrix[i][0], t_y = obj->vertices.matrix[i][1];
    obj->vertices.matrix[i][0] = cos(angleZ) * t_x - sin(angleZ) * t_y;
    obj->vertices.matrix[i][1] = sin(angleZ) * t_x + cos(angleZ) * t_y;
  }
}

void translate(Object* obj, float x, float y, float z) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    obj->vertices.matrix[i][0] += x;
    obj->vertices.matrix[i][1] += y;
    obj->vertices.matrix[i][2] += z;
  }
}