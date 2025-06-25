#pragma once

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
  QHBoxLayout *main_layout_;
  Controller *controller_;
  GLView *gl_view_;

 public:
  TestQt(QWidget *w = Q_NULLPTR)
      : QWidget(w),
        main_layout_(nullptr),
        controller_(new Controller()),
        gl_view_(new GLView(controller_, this)) {
    setWindowTitle("3DViewer_v2.0");
    showMaximized();
    SetNewLayout(w);
    main_layout_->addWidget(gl_view_);
    setLayout(main_layout_);
  }

  ~TestQt() {
    delete main_layout_;
    delete gl_view_;
    delete controller_;
  }

  void GetFrame(QImage *frame) {
    *frame = gl_view_->grabFramebuffer().scaled(gl_view_->width(),
                                                gl_view_->height());
  }

  int GetWidth() { return gl_view_->width(); }

  int GetHeight() { return gl_view_->height(); }

  void SaveImage(const QString &file_path) {
    if (gl_view_) {
      QPixmap pixmap = gl_view_->grab();
      if (pixmap.isNull()) {
        return;
      }
      if (!pixmap.save(file_path)) {
        return;
      }
    }
  }

  bool ChangeObj(std::string name) {
    bool result = controller_->SetObject(name);
    gl_view_->UpdateView();
    return result;
  }

  unsigned int GetVertex() { return controller_->GetNumberVertex(); }

  unsigned int GetFace() { return controller_->GetNumberFace(); }

  void XMove(double distance) {
    controller_->TransformObject(0, distance);
    gl_view_->UpdateView();
  }

  void YMove(double distance) {
    controller_->TransformObject(1, distance);
    gl_view_->UpdateView();
  }

  void ZMove(double distance) {
    controller_->TransformObject(2, distance);
    gl_view_->UpdateView();
  }

  void XRotate(double distance) {
    controller_->TransformObject(4, distance);
    gl_view_->UpdateView();
  }

  void YRotate(double distance) {
    controller_->TransformObject(5, distance);
    gl_view_->UpdateView();
  }

  void ZRotate(double distance) {
    controller_->TransformObject(6, distance);
    gl_view_->UpdateView();
  }

  void ChangeScale(double number) { controller_->TransformObject(3, number); }

  void EdgeColor(double r, double g, double b) {
    gl_view_->SetEdgeColor(r, g, b);
  }

  void VertexColor(double r, double g, double b) {
    gl_view_->SetVertexColor(r, g, b);
  }
  void EdgeSize(int size) {
    gl_view_->SetEdgeSize(size);
    gl_view_->UpdateView();
  }

  void VertexSize(int size) {
    gl_view_->SetVertexSize(size);
    gl_view_->UpdateView();
  }

  void VertexMode(int mode) {
    gl_view_->SetVertexMode(mode);
    gl_view_->UpdateView();
  }

  void EdgeModeFalse() {
    gl_view_->SetEdgeMode(false);
    gl_view_->UpdateView();
  }

  void EdgeModeTrue() {
    gl_view_->SetEdgeMode(true);
    gl_view_->UpdateView();
  }

  void UpdateView() { gl_view_->UpdateView(); }

  void ParallelProj() {
    gl_view_->SetProjectionMode(false);
    gl_view_->UpdateView();
  }

  void CentralProj() {
    gl_view_->SetProjectionMode(true);
    gl_view_->UpdateView();
  }

  void FieldColor(double r, double g, double b) {
    gl_view_->SetFieldColor(r, g, b);
  }

 private:
  void SetNewLayout(QWidget *w) {
    if (main_layout_ != nullptr) delete main_layout_;
    main_layout_ = new QHBoxLayout();
    setLayout(main_layout_);
  }
};
}  // namespace viewer