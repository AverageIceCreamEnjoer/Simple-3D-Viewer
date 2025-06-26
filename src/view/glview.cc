#include "glview.h"

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <iostream>

namespace viewer {
GLView::GLView(std::shared_ptr<Controller> c, QWidget *w)
    : QOpenGLWidget(w),
      controller_(c),
      edge_color_{1, 1, 0},
      vertex_color_{1, 0, 1},
      field_color_{0.5, 0.5, 0.5} {
  setGeometry(100, 100, 1000, 1000);
}

GLView::~GLView() {}

void GLView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_mode_)
    glFrustum(-1, 1, -1, 1, 1, 100);
  else
    glOrtho(-1, 1, -1, 1, -10, 10);
}

void GLView::paintGL() {
  glClearColor(field_color_[0], field_color_[1], field_color_[2], 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (change_projection_) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projection_mode_) {
      glFrustum(-1, 1, -1, 1, 1, 100);
    } else {
      glOrtho(-1, 1, -1, 1, -10, 10);
    }
    change_projection_ = false;
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (projection_mode_) glTranslated(0, 0, -2);
  glRotatef(x_rot_, 1, 0, 0);
  glRotatef(y_rot_, 0, 1, 0);
  glRotatef(z_rot_, 0, 0, 1);
  PaintReferenceSystem();
  if (controller_->IsSetted()) {
    bool reload = UpdateBuf();
    controller_->LoadBuffer(vertex_buffer_.get(), edge_buffer_.get(), reload);
    PaintVertices();
    PaintEdges();
  }
}

bool GLView::UpdateBuf() {
  std::pair<unsigned int, unsigned int> size = controller_->GetBufSize();
  bool t1 = ver_buf_size_ != size.first, t2 = edg_buf_size_ != size.second;
  if (t1) {
    // if (ver_buf_size_ != 0) delete[] vertex_buffer_;
    ver_buf_size_ = size.first;
    vertex_buffer_ = (ver_buf_size_ > 0)
                         ? std::unique_ptr<float>(new float[ver_buf_size_])
                         : nullptr;
  }
  if (t2) {
    // if (edg_buf_size_ != 0) delete[] edge_buffer_;
    edg_buf_size_ = size.second;
    edge_buffer_ = (edg_buf_size_ > 0)
                       ? std::unique_ptr<float>(new float[edg_buf_size_])
                       : nullptr;
  }
  return t1 || t2;
}

//  Рисуем систему координат
void GLView::PaintReferenceSystem() {
  glDisable(GL_LINE_STIPPLE);
  glLineWidth(1);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1);
  glEnd();
}

void GLView::PaintEdges() {
  glEnableClientState(GL_VERTEX_ARRAY);
  if (edge_mode_) {
    glDisable(GL_LINE_STIPPLE);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xFF00);
  }
  glLineWidth(edge_size_);
  glColor3f(edge_color_[0], edge_color_[1], edge_color_[2]);
  unsigned int index = 0;
  glVertexPointer(3, GL_FLOAT, 0, edge_buffer_.get());
  for (int i = 0; i < controller_->GetNumberFace() && index < edg_buf_size_ / 3;
       i++) {
    glDrawArrays(GL_LINE_LOOP, index, controller_->GetFaceSize(i) / 3);
    index += controller_->GetFaceSize(i) / 3;
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLView::PaintVertices() {
  if (vertex_mode_ != -1) {
    glColor3f(vertex_color_[0], vertex_color_[1], vertex_color_[2]);
    if (vertex_mode_ == 0) {
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_POINT_SMOOTH);
    } else if (vertex_mode_ == 1)
      glDisable(GL_POINT_SMOOTH);
    glPointSize(vertex_size_);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex_buffer_.get());
    glDrawArrays(GL_POINTS, 0, ver_buf_size_ / 3);
    glDisable(GL_VERTEX_ARRAY);
  }
}

void GLView::mousePressEvent(QMouseEvent *mo) { mouse_position_ = mo->pos(); }

void GLView::mouseMoveEvent(QMouseEvent *mo) {
  x_rot_ += 1 * (mo->pos().y() - mouse_position_.y()) / M_PI;
  y_rot_ += 1 * (mo->pos().x() - mouse_position_.x()) / M_PI;
  update();
}

void GLView::UpdateView() { update(); }

void GLView::SetProjectionMode(bool mode) {
  projection_mode_ = mode;
  change_projection_ = true;
}

void GLView::SetEdgeMode(bool mode) { edge_mode_ = mode; }

void GLView::SetVertexMode(int mode) { vertex_mode_ = mode; }

void GLView::SetVertexSize(int size) { vertex_size_ = size; }

void GLView::SetEdgeSize(int size) { edge_size_ = size; }

void GLView::SetEdgeColor(float r, float g, float b) {
  edge_color_[0] = r;
  edge_color_[1] = g;
  edge_color_[2] = b;
}

void GLView::SetVertexColor(float r, float g, float b) {
  vertex_color_[0] = r;
  vertex_color_[1] = g;
  vertex_color_[2] = b;
}

void GLView::SetFieldColor(float r, float g, float b) {
  field_color_[0] = r;
  field_color_[1] = g;
  field_color_[2] = b;
}

void GLView::SetRotation(float x, float y, float z) {
  x_rot_ = x;
  y_rot_ = y;
  z_rot_ = z;
}
}  // namespace viewer
