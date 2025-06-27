#include "model.h"

namespace viewer {

Model::Model() : file_path_(""), object_(), scale_(1) {}  // default constructor

bool Model::SetObject(const std::string& filePath) {
  file_path_ = filePath;
  setted = object_.ReadObject(filePath);
  obj_changed_ = true;
  if (setted) {
    object_.Center();
    object_.Normalize();
    max_face_size_ = object_.GetMaxFaceSize();
  }
  return setted;
}

void Model::Transform(int operation, double value) {
  switch (operation) {
    case 0:
      object_.Translate(value, 0, 0);
      break;
    case 1:
      object_.Translate(0, value, 0);
      break;
    case 2:
      object_.Translate(0, 0, value);
      break;
    case 3:
      object_.Scale(value / scale_);
      scale_ = value;
      break;
    case 4:
      object_.RotateX(value);
      break;
    case 5:
      object_.RotateY(value);
      break;
    case 6:
      object_.RotateZ(value);
      break;
  }
  changed_ = true;
}

Model::~Model() {}  // destructor

void Model::ToNormal() {
  if (object_.ReadObject(file_path_)) {
    scale_ = 1;
    object_.Normalize();
    object_.Center();
    changed_ = true;
  }
}

float Model::GetVertex(int row, int col) const {
  return object_.vertices(row, col);
}

const std::string& Model::GetFilePath() const { return file_path_; }

double Model::GetScale() const { return scale_; }

unsigned int Model::GetNumberVertex() const { return object_.number_vertex; }

unsigned int Model::GetNumberFace() const { return object_.number_face; }

unsigned int Model::GetFaceSize(unsigned int index) const {
  return object_.faces[index].size() * 3;
}

const Object& Model::GetObject() const { return object_; }

std::pair<unsigned int, unsigned int> Model::GetBufSize() {
  if (setted) {
    if (obj_changed_) {
      ver_buf_size_ = GetNumberVertex() * 3;
      edge_buf_size_ = 0;
      for (unsigned int i = 0; i < GetNumberFace(); i++) {
        edge_buf_size_ += GetFaceSize(i);
      }
      obj_changed_ = false;
    }
  } else {
    ver_buf_size_ = 0;
    edge_buf_size_ = 0;
    obj_changed_ = false;
  }
  return std::make_pair(ver_buf_size_, edge_buf_size_);
}

void Model::LoadBuffer(float* vertex_buffer, float* edge_buffer, bool load) {
  if (setted) {
    if (changed_ || load) {
      for (unsigned int i = 0; i < GetNumberVertex(); ++i) {
        vertex_buffer[i * 3] = object_.vertices(i, 0);
        vertex_buffer[i * 3 + 1] = object_.vertices(i, 1);
        vertex_buffer[i * 3 + 2] = object_.vertices(i, 2);
      }
      unsigned int index = 0;
      for (unsigned int i = 0; i < GetNumberFace() && index < edge_buf_size_;
           ++i) {
        for (unsigned int j = 0;
             j < object_.faces[i].size() && index < edge_buf_size_; ++j) {
          edge_buffer[index++] = object_.vertices(object_.faces[i][j], 0);
          edge_buffer[index++] = object_.vertices(object_.faces[i][j], 1);
          edge_buffer[index++] = object_.vertices(object_.faces[i][j], 2);
        }
      }
      changed_ = false;
    }
  }
}

}  // namespace viewer