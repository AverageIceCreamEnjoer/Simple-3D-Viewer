#include "object.h"

void RotateX(Object* obj, float angle) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_y, t_z;
    t_y = obj->vertices.matrix[i][1], t_z = obj->vertices.matrix[i][2];
    obj->vertices.matrix[i][1] = cos(angle) * t_y - sin(angle) * t_z;
    obj->vertices.matrix[i][2] = sin(angle) * t_y + cos(angle) * t_z;
  }
}

void RotateY(Object* obj, float angle) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_x, t_z;
    t_x = obj->vertices.matrix[i][0], t_z = obj->vertices.matrix[i][2];
    obj->vertices.matrix[i][0] = cos(angle) * t_x + sin(angle) * t_z;
    obj->vertices.matrix[i][2] = -sin(angle) * t_x + cos(angle) * t_z;
  }
}

void RotateZ(Object* obj, float angle) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    float t_x, t_y;
    t_x = obj->vertices.matrix[i][0], t_y = obj->vertices.matrix[i][1];
    obj->vertices.matrix[i][0] = cos(angle) * t_x - sin(angle) * t_y;
    obj->vertices.matrix[i][1] = sin(angle) * t_x + cos(angle) * t_y;
  }
}

void Translate(Object* obj, float x, float y, float z) {
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    obj->vertices.matrix[i][0] += x;
    obj->vertices.matrix[i][1] += y;
    obj->vertices.matrix[i][2] += z;
  }
}