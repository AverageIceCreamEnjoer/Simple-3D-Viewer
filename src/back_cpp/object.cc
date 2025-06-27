#include "object.h"

namespace viewer {

Object::Object() : vertices(), faces() {
  amount_vertex = 0;
  number_vertex = 0;
  number_face = 0;
  amount_face = 0;
}

bool Object::ReadObject(const std::string path) {
  std::ifstream object_to_pars;
  object_to_pars.open(path);
  bool result = true;
  // открываем файл
  if (!object_to_pars.is_open()) {
    // выводим ошибку в вьюере
    result = false;
  }
  amount_vertex = 0;  // итоговое количество vertex (x+y+z)
  number_vertex = 0;  // количество строк vertex
  number_face = 0;    // количество строк face
  amount_face = 0;
  std::string line;
  while (std::getline(object_to_pars, line) && result) {
    if (number_vertex <= MAX_VERTEX + 1) {
      if (line[0] == 'v' && line[1] == ' ') {
        amount_vertex += CountNumber(line);  // cчитаем слова в строчке
        number_vertex++;
      }

      else if (line[0] == 'f' && line[1] == ' ') {
        number_face++;
        amount_face += CountNumber(line);
      }
    } else {
      // выводим ошибку в вьюере
      object_to_pars.close();
      result = false;
    }
  }
  result = result && !(number_vertex == 0);
  if (result) {
    vertices = Matrix(number_vertex, 3);
    faces.clear();
    faces.reserve(amount_face);  // так быстрее чем создавать новые вроде >_<
    object_to_pars.clear();
    object_to_pars.seekg(0, std::ios::beg);  // возвращаемся в начало
    int row = 0;
    while (std::getline(object_to_pars, line)) {
      if (line[0] == 'v' && line[1] == ' ') {
        ParseVertex(line, row++);
      }

      if (line[0] == 'f' && line[1] == ' ') {
        ParseFace(line);
      }
    }

    object_to_pars.close();
  }
  return result;
}

int Object::CountNumber(std::string& line) {
  std::istringstream iss(line);
  std::string token;
  int count = 0;
  while (iss >> token) {
    count++;
  }
  return count - 1;  // Исключаем первый элемент ('v' или 'f')
}

void Object::ParseVertex(std::string& line, int row) {
  std::istringstream iss(line);
  std::string token;
  int i = 0;
  iss >> token;
  while (iss >> token) {
    double tmp = std::stod(token);
    vertices(row, i++) = tmp;
  }
}

void Object::ParseFace(std::string& line) {
  std::istringstream iss(line);
  std::string token;
  std::vector<unsigned int> one_face = std::vector<unsigned int>();

  iss >> token;
  while (iss >> token) {
    unsigned int tmp = std::atoi(token.c_str());
    one_face.push_back(tmp - 1);
  }
  faces.push_back(std::move(one_face));
}

Object::~Object() {}

void Object::Center() {
  double cX = 0, cY = 0, cZ = 0;
  for (unsigned int i = 0; i < number_vertex; i++) {
    cX += vertices(i, 0);
    cY += vertices(i, 1);
    cZ += vertices(i, 2);
  }
  cX /= number_vertex;
  cY /= number_vertex;
  cZ /= number_vertex;
  for (unsigned int i = 0; i < number_vertex; i++) {
    vertices(i, 0) -= cX;
    vertices(i, 1) -= cY;
    vertices(i, 2) -= cZ;
  }
}

void Object::Normalize() {
  double m = fabs(vertices(0, 0));
  for (unsigned int i = 0; i < number_vertex; i++) {
    if (fabs(vertices(i, 0)) > m) m = fabs(vertices(i, 0));
    if (fabs(vertices(i, 1)) > m) m = fabs(vertices(i, 1));
    if (fabs(vertices(i, 2)) > m) m = fabs(vertices(i, 2));
  }
  if (m != 0)
    m = 1 / m;
  else
    m = 0.0000001;
  vertices *= m;
}

void Object::Scale(double scope) {
  if (scope != 0) vertices *= scope;
}

/// @brief Returns the maximum size of a face in the object
/// @return The maximum size of a face in the object (in vertices)
unsigned int Object::GetMaxFaceSize() const {
  unsigned int result = 0;
  for (size_t i = 0; i < faces.size(); ++i)
    if (faces[i].size() > result) result = faces[i].size() * 3;
  return result;
}
};  // namespace viewer