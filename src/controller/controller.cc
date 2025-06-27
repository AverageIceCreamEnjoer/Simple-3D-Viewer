#include "controller.h"

namespace viewer {

Controller::Controller() : model_() {}

Controller::~Controller() {}

const std::string Controller::GetFilePath() const {
  return model_.GetFilePath();
}

void Controller::TransformObject(int operation, double value) {
  model_.Transform(operation, value);
}

double Controller::GetScale() const { return model_.GetScale(); }

unsigned int Controller::GetNumberVertex() const {
  return model_.GetNumberVertex();
}

unsigned int Controller::GetNumberFace() const {
  return model_.GetNumberFace();
}

unsigned int Controller::GetFaceSize(unsigned int index) const {
  return model_.GetFaceSize(index);
}

void Controller::ToNormal() { model_.ToNormal(); }

bool Controller::SetObject(const std::string& filePath) {
  return model_.SetObject(filePath.data());
}

float Controller::GetVertex(int row, int col) const {
  return model_.GetVertex(row, col);
}

bool Controller::IsSetted() const { return model_.IsSetted(); }

std::pair<unsigned int, unsigned int> Controller::GetBufSize() {
  return model_.GetBufSize();
}

void Controller::LoadBuffer(float* vertex_buffer, float* edge_buffer,
                            bool load) {
  return model_.LoadBuffer(vertex_buffer, edge_buffer, load);
}

}  // namespace viewer