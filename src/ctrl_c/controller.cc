#include "controller.h"

#include <iostream>
namespace viewer {

Controller::Controller() { _model = ModelCreate(); }

Controller::~Controller() { ModelDestroy(_model); }

const std::string Controller::getFilePath() const {
  return std::string(ModelGetFilePath(_model));
}

void Controller::transformObject(int operation, double value) {
  ModelTransform(_model, operation, value);
}

double Controller::getScale() const { return ModelGetScale(_model); }

unsigned int Controller::getNumberVertex() const {
  return ModelGetNumberVertex(_model);
}

unsigned int Controller::getNumberFace() const {
  return ModelGetNumberFace(_model);
}

unsigned int Controller::getFaceSize(unsigned int index) const {
  return ModelGetFaceSize(_model, index);
}

void Controller::toNormal() { ModelToNormal(_model); }

bool Controller::setObject(const std::string& filePath) {
  return ModelSetObject(_model, filePath.data());
}

float Controller::getVertex(int row, int col) const {
  return ModelGetVertex(_model, row, col);
}

bool Controller::isSetted() const { return _model->setted; }

std::pair<unsigned int, unsigned int> Controller::getBufSize() {
  std::pair<unsigned int, unsigned int> res(0, 0);
  ModelGetBufSize(_model, &res.first, &res.second);
  return res;
}

void Controller::loadBuffer(float* vertex_buffer, float* edge_buffer,
                            bool load) {
  return ModelLoadBuffer(_model, vertex_buffer, edge_buffer, load);
}

}  // namespace viewer