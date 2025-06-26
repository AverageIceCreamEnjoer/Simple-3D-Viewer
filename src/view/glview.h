#pragma once

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets>
#include <array>

#include "../ctrl_c/controller.h"

namespace viewer {
/// @brief Describes the game selection menu
class GLView : public QOpenGLWidget {
 private:
  std::shared_ptr<Controller> controller_;
  unsigned int ver_buf_size_ = 0;
  unsigned int edg_buf_size_ = 0;
  std::unique_ptr<float> vertex_buffer_;
  std::unique_ptr<float> edge_buffer_;
  int face_data_size_ = 0;
  int vertex_size_ = 1;
  int vertex_mode_ = 0;
  int edge_size_ = 1;
  std::array<float, 3> edge_color_;
  std::array<float, 3> vertex_color_;
  std::array<float, 3> field_color_;
  bool projection_mode_ = false;
  bool change_projection_ = false;
  bool edge_mode_ = false;
  float x_rot_ = 0, y_rot_ = 0, z_rot_ = 0;
  QPoint mouse_position_;

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
  bool UpdateBuf();

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
  void PaintReferenceSystem();

  /// @brief Paints the edges of the object
  ///
  /// This function is called in paintGL() to draw the edges of the object.
  void PaintEdges();

  /// @brief Paints the vertices of the object
  ///
  /// This function is called in paintGL() to draw the vertices of the object.
  void PaintVertices();

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
  GLView(std::shared_ptr<Controller> c, QWidget *w = Q_NULLPTR);

  /// @brief Destroys a GLView object
  ///
  /// This function is called when a GLView object is destroyed. It is used to
  /// release any resources that are allocated by the object.
  ~GLView();

  /// @brief Updates the view
  ///
  /// This function is called to update the view whenever the game state
  /// changes.
  void UpdateView();

  /// @brief Sets the projection mode
  ///
  /// This function is called to set the projection mode of the view.
  /// @param mode The mode to set.
  void SetProjectionMode(bool mode);

  /// @brief Sets the edge mode
  ///
  /// This function is called to set the edge mode of the view.
  /// @param mode The mode to set.
  void SetEdgeMode(bool mode);

  /// @brief Sets the vertex size
  ///
  /// This function is called to set the vertex size of the view.
  /// @param size The new size of the vertices.
  void SetVertexSize(int size);

  /// @brief Sets the vertex mode
  ///
  /// This function is called to set the vertex mode of the view.
  /// @param mode The mode to set.
  void SetVertexMode(int mode);

  /// @brief Sets the edge size
  ///
  /// This function is called to set the edge size of the view.
  /// @param size The new size of the edges.
  void SetEdgeSize(int size);

  /// @brief Sets the edge color
  ///
  /// This function is called to set the edge color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void SetEdgeColor(float r, float g, float b);

  /// @brief Sets the vertex color
  ///
  /// This function is called to set the vertex color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void SetVertexColor(float r, float g, float b);

  /// @brief Sets the field color
  ///
  /// This function is called to set the field color of the view.
  /// @param r The red component of the color.
  /// @param g The green component of the color.
  /// @param b The blue component of the color.
  void SetFieldColor(float r, float g, float b);

  /// @brief Sets the rotation
  ///
  /// This function is called to set the rotation of the view.
  /// @param x The x component of the rotation.
  /// @param y The y component of the rotation.
  /// @param z The z component of the rotation.
  void SetRotation(float x, float y, float z);
};
}  // namespace viewer