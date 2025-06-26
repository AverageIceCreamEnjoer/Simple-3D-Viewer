#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "matrix/matrix.h"

#define MAX_VERTEX 1000000

namespace viewer {

class Object {
 private:
  int CountNumber(std::string& line);
  void ParseVertex(std::string& line, int row);
  void ParseFace(std::string& line);

 public:
  Matrix vertices;  // значение вершин (xyz)
  std::vector<std::unique_ptr<std::vector<unsigned int>>>
      faces;                   // значение face
  unsigned int amount_vertex;  // количество координат вершин
  unsigned int number_vertex;  // количество вершин
  unsigned int number_face;    // количество ребер
  unsigned int amount_face;    // итоговое количество face

  Object();
  bool ReadObject(const std::string path);
  ~Object();

  /// @brief Центрирует объект в 0, 0, 0
  void Center();

  /// @brief Нормализует объект в рамку 1, 1, 1
  void Normalize();

  /// @brief Масштабирует объект
  /// @param scope - коэфицент увеличения
  void Scale(double scope = 1);

  /// @brief Возвращает длину максимального полигона
  /// @return Длина макс. полигона для массива вершин
  unsigned int GetMaxFaceSize() const;

  void RotateX(double angle);
  void RotateY(double angle);
  void RotateZ(double angle);

  void Translate(double x, double y, double z);
};  // class object

};  // namespace viewer