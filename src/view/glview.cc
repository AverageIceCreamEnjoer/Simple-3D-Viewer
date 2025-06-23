#include "glview.h"

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <iostream>

namespace viewer {
GLView::GLView(Controller *c, QWidget *w) : QOpenGLWidget(w), _cntrlr(c) {
  _edgeColor = new float[3];
  _edgeColor[0] = 1;
  _edgeColor[1] = 1;
  _edgeColor[2] = 0;
  _vertexColor = new float[3];
  _vertexColor[0] = 1;
  _vertexColor[1] = 0;
  _vertexColor[2] = 1;
  _fieldColor = new float[3];
  _fieldColor[0] = 0.5;
  _fieldColor[1] = 0.5;
  _fieldColor[2] = 0.5;
  setGeometry(100, 100, 1000, 1000);
}

GLView::~GLView() {
  delete[] _vertex_buffer;
  delete[] _edge_buffer;
  delete[] _edgeColor;
  delete[] _vertexColor;
  delete[] _fieldColor;
}

void GLView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_projectionMode)
    glFrustum(-1, 1, -1, 1, 1, 100);
  else
    glOrtho(-1, 1, -1, 1, -10, 10);
}

void GLView::paintGL() {
  glClearColor(_fieldColor[0], _fieldColor[1], _fieldColor[2], 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (_changeProjection) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (_projectionMode) {
      glFrustum(-1, 1, -1, 1, 1, 100);
    } else {
      glOrtho(-1, 1, -1, 1, -10, 10);
    }
    _changeProjection = false;
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (_projectionMode) glTranslated(0, 0, -2);
  glRotatef(_xRot, 1, 0, 0);
  glRotatef(_yRot, 0, 1, 0);
  glRotatef(_zRot, 0, 0, 1);
  paintReferenceSystem();
  if (_cntrlr->isSetted()) {
    bool reload = updateBuf();
    _cntrlr->loadBuffer(_vertex_buffer, _edge_buffer, reload);
    paintVertices();
    paintEdges();
  }
}

bool GLView::updateBuf() {
  std::pair<unsigned int, unsigned int> size = _cntrlr->getBufSize();
  bool t1 = _ver_buf_size != size.first, t2 = _edg_buf_size != size.second;
  if (t1) {
    if (_ver_buf_size != 0) delete[] _vertex_buffer;
    _ver_buf_size = size.first;
    if (_ver_buf_size > 0)
      _vertex_buffer = new float[_ver_buf_size];
    else
      _vertex_buffer = nullptr;
  }
  if (t2) {
    if (_edg_buf_size != 0) delete[] _edge_buffer;
    _edg_buf_size = size.second;
    if (_edg_buf_size > 0)
      _edge_buffer = new float[_edg_buf_size];
    else
      _edge_buffer = nullptr;
  }
  return t1 || t2;
}

//  Рисуем систему координат
void GLView::paintReferenceSystem() {
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

void GLView::paintEdges() {
  glEnableClientState(GL_VERTEX_ARRAY);
  if (_edgeMode) {
    glDisable(GL_LINE_STIPPLE);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xFF00);
  }
  glLineWidth(_edgeSize);
  glColor3f(_edgeColor[0], _edgeColor[1], _edgeColor[2]);
  unsigned int index = 0;
  glVertexPointer(3, GL_FLOAT, 0, _edge_buffer);
  for (int i = 0; i < _cntrlr->getNumberFace() && index < _edg_buf_size / 3;
       i++) {
    glDrawArrays(GL_LINE_LOOP, index, _cntrlr->getFaceSize(i) / 3);
    index += _cntrlr->getFaceSize(i) / 3;
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLView::paintVertices() {
  if (_vertexMode != -1) {
    glColor3f(_vertexColor[0], _vertexColor[1], _vertexColor[2]);
    if (_vertexMode == 0) {
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_POINT_SMOOTH);
    } else if (_vertexMode == 1)
      glDisable(GL_POINT_SMOOTH);
    glPointSize(_vertexSize);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, _vertex_buffer);
    glDrawArrays(GL_POINTS, 0, _ver_buf_size / 3);
    glDisable(GL_VERTEX_ARRAY);
  }
}

void GLView::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void GLView::mouseMoveEvent(QMouseEvent *mo) {
  _xRot += 1 * (mo->pos().y() - mPos.y()) / M_PI;
  _yRot += 1 * (mo->pos().x() - mPos.x()) / M_PI;
  update();
}

void GLView::updateView() { update(); }

void GLView::setProjectionMode(bool mode) {
  _projectionMode = mode;
  _changeProjection = true;
}

void GLView::setEdgeMode(bool mode) { _edgeMode = mode; }

void GLView::setVertexMode(int mode) { _vertexMode = mode; }

void GLView::setVertexSize(int size) { _vertexSize = size; }

void GLView::setEdgeSize(int size) { _edgeSize = size; }

void GLView::setEdgeColor(float r, float g, float b) {
  _edgeColor[0] = r;
  _edgeColor[1] = g;
  _edgeColor[2] = b;
}

void GLView::setVertexColor(float r, float g, float b) {
  _vertexColor[0] = r;
  _vertexColor[1] = g;
  _vertexColor[2] = b;
}

void GLView::setFieldColor(float r, float g, float b) {
  _fieldColor[0] = r;
  _fieldColor[1] = g;
  _fieldColor[2] = b;
}

void GLView::setRotation(float x, float y, float z) {
  _xRot = x;
  _yRot = y;
  _zRot = z;
}
}  // namespace viewer
