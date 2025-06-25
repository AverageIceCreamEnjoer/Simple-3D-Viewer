#include "controller.h"

#include <iostream>
namespace viewer {

Controller::Controller() { model_ = ModelCreate(); }

Controller::~Controller() { ModelDestroy(model_); }

const std::string Controller::GetFilePath() const {
  return std::string(ModelGetFilePath(model_));
}

void Controller::TransformObject(int operation, double value) {
  ModelTransform(model_, operation, value);
}

double Controller::GetScale() const { return ModelGetScale(model_); }

unsigned int Controller::GetNumberVertex() const {
  return ModelGetNumberVertex(model_);
}

unsigned int Controller::GetNumberFace() const {
  return ModelGetNumberFace(model_);
}

unsigned int Controller::GetFaceSize(unsigned int index) const {
  return ModelGetFaceSize(model_, index);
}

void Controller::ToNormal() { ModelToNormal(model_); }

bool Controller::SetObject(const std::string& filePath) {
  return ModelSetObject(model_, filePath.data());
}

float Controller::GetVertex(int row, int col) const {
  return ModelGetVertex(model_, row, col);
}

bool Controller::IsSetted() const { return model_->setted; }

std::pair<unsigned int, unsigned int> Controller::GetBufSize() {
  std::pair<unsigned int, unsigned int> res(0, 0);
  ModelGetBufSize(model_, &res.first, &res.second);
  return res;
}

void Controller::LoadBuffer(float* vertex_buffer, float* edge_buffer,
                            bool load) {
  return ModelLoadBuffer(model_, vertex_buffer, edge_buffer, load);
}

}  // namespace viewer