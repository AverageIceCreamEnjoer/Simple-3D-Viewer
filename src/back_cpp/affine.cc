#include "object.h"

namespace viewer {

void Object::RotateX(double angle) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_y, t_z;
    t_y = vertices(i, 1), t_z = vertices(i, 2);
    vertices(i, 1) = cos(angle) * t_y - sin(angle) * t_z;
    vertices(i, 2) = sin(angle) * t_y + cos(angle) * t_z;
  }
}

void Object::RotateY(double angle) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_x, t_z;
    t_x = vertices(i, 0), t_z = vertices(i, 2);
    vertices(i, 0) = cos(angle) * t_x + sin(angle) * t_z;
    vertices(i, 2) = -sin(angle) * t_x + cos(angle) * t_z;
  }
}

void Object::RotateZ(double angle) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    double t_x, t_y;
    t_x = vertices(i, 0), t_y = vertices(i, 1);
    vertices(i, 0) = cos(angle) * t_x - sin(angle) * t_y;
    vertices(i, 1) = sin(angle) * t_x + cos(angle) * t_y;
  }
}

void Object::Translate(double x, double y, double z) {
  for (unsigned int i = 0; i < number_vertex; i++) {
    vertices(i, 0) += x;
    vertices(i, 1) += y;
    vertices(i, 2) += z;
  }
}
}  // namespace viewer