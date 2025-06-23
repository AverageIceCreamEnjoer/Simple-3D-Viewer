#include "controller.h"

#include <iostream>
namespace viewer {

Controller::Controller() { _model = Model_Create(); }

Controller::~Controller() { Model_Destroy(_model); }

const std::string Controller::getFilePath() const {
  return std::string(Model_getFilePath(_model));
}

void Controller::transformObject(int operation, double value) {
  Model_transform(_model, operation, value);
}

double Controller::getScale() const { return Model_getScale(_model); }

unsigned int Controller::getNumberVertex() const {
  return Model_getNumberVertex(_model);
}

unsigned int Controller::getNumberFace() const {
  return Model_getNumberFace(_model);
}

unsigned int Controller::getFaceSize(unsigned int index) const {
  return Model_getFaceSize(_model, index);
}

void Controller::toNormal() { Model_toNormal(_model); }

bool Controller::setObject(const std::string& filePath) {
  return Model_setObject(_model, filePath.data());
}

float Controller::getVertex(int row, int col) const {
  return Model_getVertex(_model, row, col);
}

bool Controller::isSetted() const { return _model->setted; }

std::pair<unsigned int, unsigned int> Controller::getBufSize() {
  std::pair<unsigned int, unsigned int> res(0, 0);
  Model_getBufSize(_model, &res.first, &res.second);
  return res;
}

void Controller::loadBuffer(float* vertex_buffer, float* edge_buffer,
                            bool load) {
  return Model_loadBuffer(_model, vertex_buffer, edge_buffer, load);
}

}  // namespace viewer