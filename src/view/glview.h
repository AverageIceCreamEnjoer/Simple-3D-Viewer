#ifndef __GLVIEW_H__
#define __GLVIEW_H__

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>

#include "../ctrl_c/controller.h"

namespace viewer {
/// @brief Describes the game selection menu
class GLView : public QOpenGLWidget {
 private:
  Controller *_cntrlr = nullptr;
  unsigned int _ver_buf_size = 0;
  unsigned int _edg_buf_size = 0;
  float *_vertex_buffer = nullptr;
  float *_edge_buffer = nullptr;
  int _face_data_size = 0;
  int _vertexSize = 1;
  int _vertexMode = 0;
  int _edgeSize = 1;
  float *_edgeColor = nullptr;
  float *_vertexColor = nullptr;
  float *_fieldColor = nullptr;
  bool _projectionMode = false;
  bool _changeProjection = false;
  bool _edgeMode = false;
  float _xRot = 0, _yRot = 0, _zRot = 0;
  QPoint mPos;

  /// @brief Initialization of the OpenGL rendering context
  ///
  /// This function is called when the OpenGL rendering context is
  /// initialized. It sets up the OpenGL viewport and projection matrix.
  ///
  /// @param w The width of the viewport.
  /// @param h The height of the viewport.
  void initializeGL() override;

  /// @brief Updates the vertex and edge buffers
  ///
  /// This function is used to update the vertex and edge buffers when the
  /// model is changed. It is called from the paintGL() function.
  ///
  /// @return true if the buffers were updated, false otherwise.
  bool updateBuf();

  /// @brief Resizes the OpenGL rendering context
  ///
  /// This function is called when the OpenGL rendering context is
  /// resized. It updates the OpenGL viewport and projection matrix.
  ///
  /// @param w The new width of the viewport.
  /// @param h The new height of the viewport.
  void resizeGL(int w, int h) override;

  /// @brief Paints the reference system
  ///
  /// This function is called in paintGL() to draw the reference system.
  void paintReferenceSystem();

  /// @brief Paints the edges of the object
  ///
  /// This function is called in paintGL() to draw the edges of the object.
  void paintEdges();

  /// @brief Paints the vertices of the object
  ///
  /// This function is called in paintGL() to draw the vertices of the object.
  void paintVertices();

  /// @brief Redraws the entire OpenGL widget
  ///
  /// This function is called by the system when the OpenGL widget needs to be
  /// redrawn. It delegates to the paintGL() function.
  void paintGL() override;

  /// @brief Called when the user presses a mouse button
  ///
  /// This function is called when the user presses a mouse button. It stores
  /// the position of the mouse cursor in the mPos member variable.
  void mousePressEvent(QMouseEvent *mo) override;

  /// @brief Called when the user moves the mouse
  ///
  /// This function is called when the user moves the mouse. It updates the
  /// rotation of the object by modifying the _xRot, _yRot, and _zRot member
  /// variables.
  void mouseMoveEvent(QMouseEvent *mo) override;

 public:
  /// @brief Creates a new GLView object
  ///
  /// This function creates a new GLView object. It is called by the constructor
  /// of the class.
  ///
  /// @param c The controller object that manages the game state.
  /// @param w The parent widget of the GLView object.
  GLView(Controller *c, QWidget *w = Q_NULLPTR);

  /// @brief Destroys a GLView object
  ///
  /// This function is called when a GLView object is destroyed. It is used to
  /// release any resources that are allocated by the object.
  ~GLView();

  /// @brief Updates the view
  ///
  /// This function is called to update the view whenever the game state
  /// changes.
  void updateView();

  /// @brief Sets the projection mode
  ///
  /// This function is called to set the projection mode of the view.
  /// @param mode The mode to set.
  void setProjectionMode(bool mode);

  /// @brief Sets the edge mode
  ///
  /// This function is called to set the edge mode of the view.
  /// @param mode The mode to set.
  void setEdgeMode(bool mode);

  /// @brief Sets the vertex size
  ///
  /// This function is called to set the vertex size of the view.
  /// @param size The new size of the vertices.
  void setVertexSize(int size);

  /// @brief Sets the vertex mode
  ///
  /// This function is called to set the vertex mode of the view.
  /// @param mode The mode to set.
  void setVertexMode(int mode);

  /// @brief Sets the edge size
  ///
  /// This function is called to set the edge size of the view.
  /// @param size The new size of the edges.
  void setEdgeSize(int size);

  /// @brief Sets the edge color
  ///
  /// This function is called to set the edge color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void setEdgeColor(float r, float g, float b);

  /// @brief Sets the vertex color
  ///
  /// This function is called to set the vertex color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void setVertexColor(float r, float g, float b);

  /// @brief Sets the field color
  ///
  /// This function is called to set the field color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void setFieldColor(float r, float g, float b);

  /// @brief Sets the rotation
  ///
  /// This function is called to set the rotation of the view.
  /// @param x The x component of the rotation.
  /// @param y The y component of the rotation.
  /// @param z The z component of the rotation.
  void setRotation(float x, float y, float z);
};
}  // namespace viewer

#endif