#ifndef _3D_VIEWER_MAIN_H_
#define _3D_VIEWER_MAIN_H_

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QMovie>
#include <QTimer>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <fstream>

#include "ctrl_c/controller.h"
#include "view/glview.h"

namespace viewer {
class TestQt : public QWidget {
 private:
  QHBoxLayout *_mainLayout;
  Controller *_cntrlr;
  GLView *_glview;

 public:
  TestQt(QWidget *w = Q_NULLPTR)
      : QWidget(w),
        _mainLayout(nullptr),
        _cntrlr(new Controller()),
        _glview(new GLView(_cntrlr, this)) {
    setWindowTitle("3DViewer_v2.0");
    showMaximized();
    setNewLayout(w);
    _mainLayout->addWidget(_glview);
    setLayout(_mainLayout);
  }

  ~TestQt() {
    delete _mainLayout;
    delete _glview;
    delete _cntrlr;
  }

  void getFrame(QImage *frame) {
    *frame =
        _glview->grabFramebuffer().scaled(_glview->width(), _glview->height());
  }

  int getWidth() { return _glview->width(); }

  int getHeight() { return _glview->height(); }

  void Save_image(const QString &filePath) {
    if (_glview) {
      QPixmap pixmap = _glview->grab();
      if (pixmap.isNull()) {
        return;
      }
      if (!pixmap.save(filePath)) {
        return;
      }
    }
  }

  bool change_obj(std::string name) {
    bool result = _cntrlr->setObject(name);
    _glview->updateView();
    return result;
  }

  unsigned int getVertex() { return _cntrlr->getNumberVertex(); }

  unsigned int getFace() { return _cntrlr->getNumberFace(); }

  void X_move(double distance) {
    _cntrlr->transformObject(0, distance);
    _glview->updateView();
  }

  void Y_move(double distance) {
    _cntrlr->transformObject(1, distance);
    _glview->updateView();
  }

  void Z_move(double distance) {
    _cntrlr->transformObject(2, distance);
    _glview->updateView();
  }

  void X_rotate(double distance) {
    _cntrlr->transformObject(4, distance);
    _glview->updateView();
  }

  void Y_rotate(double distance) {
    _cntrlr->transformObject(5, distance);
    _glview->updateView();
  }

  void Z_rotate(double distance) {
    _cntrlr->transformObject(6, distance);
    _glview->updateView();
  }

  void change_scale(double number) { _cntrlr->transformObject(3, number); }

  void edge_color(double r, double g, double b) {
    _glview->setEdgeColor(r, g, b);
  }

  void vertex_color(double r, double g, double b) {
    _glview->setVertexColor(r, g, b);
  }
  void edge_size(int size) {
    _glview->setEdgeSize(size);
    _glview->updateView();
  }

  void vertex_size(int size) {
    _glview->setVertexSize(size);
    _glview->updateView();
  }

  void vertex_mode(int mode) {
    _glview->setVertexMode(mode);
    _glview->updateView();
  }

  void EdgeMode_false() {
    _glview->setEdgeMode(false);
    _glview->updateView();
  }

  void EdgeMode_true() {
    _glview->setEdgeMode(true);
    _glview->updateView();
  }

  void update_view() { _glview->updateView(); }

  void parallel_proj() {
    _glview->setProjectionMode(false);
    _glview->updateView();
  }

  void central_proj() {
    _glview->setProjectionMode(true);
    _glview->updateView();
  }

  void field_color(double r, double g, double b) {
    _glview->setFieldColor(r, g, b);
  }

 private:
  void setNewLayout(QWidget *w) {
    if (_mainLayout != nullptr) delete _mainLayout;
    _mainLayout = new QHBoxLayout();
    setLayout(_mainLayout);
  }
};
}  // namespace viewer
#endif