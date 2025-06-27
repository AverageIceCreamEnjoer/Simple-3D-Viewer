#ifndef __S21_VIEWER_TEST_H__
#define __S21_VIEWER_TEST_H__

#include <gtest/gtest.h>

#include "../back_cpp/model.h"

using namespace viewer;

class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    model = Model();
    model.SetObject("obj/cube.obj");
  }

  Model model;
};

#endif