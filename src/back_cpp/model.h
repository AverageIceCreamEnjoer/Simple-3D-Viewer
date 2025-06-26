#pragma once

#include "object.h"

namespace viewer {

class Model {
 private:
  std::string file_path_;
  Object object_;
  double scale_ = 1;
  unsigned int max_face_size_ = 0;
  unsigned int ver_buf_size_ = 0;
  unsigned int edge_buf_size_ = 0;
  bool changed_ = false;
  bool obj_changed_ = false;

 public:
  bool setted = false;
  bool SetObject(const std::string& file_path);
  void Transform(int operation, double value);
  const std::string& GetFilePath() const;
  double GetScale() const;
  unsigned int GetNumberVertex() const;
  unsigned int GetNumberFace() const;
  const Object& GetObject() const;
  unsigned int GetFaceSize(unsigned int index) const;
  void ToNormal();
  float GetVertex(int row, int col) const;
  std::pair<unsigned int, unsigned int> GetBufSize();
  void LoadBuffer(float* vertex_buffer, float* edge_buffer, bool load);
  Model();
  ~Model();
};
}  // namespace viewer