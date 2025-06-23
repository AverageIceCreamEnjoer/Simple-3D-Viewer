#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <string>

extern "C" {
#include "../back_c/model.h"
}
namespace viewer {
class Controller {
 private:
  Model* _model;

 public:
  /// @brief Default constructor
  Controller();

  /// @brief Destructor
  ~Controller();

  /// @brief Sets the object to be rendered
  /// @param filePath the path to the obj file
  /// @return true if the object was successfully loaded, false otherwise
  bool setObject(const std::string& filePath);

  /// @brief Transforms the object by a given value
  /// @param operation the transformation operation type:
  /// 0 - translate by X
  /// 1 - translate by Y
  /// 2 - translate by Z
  /// 3 - scale
  /// 4 - rotate by X
  /// 5 - rotate by Y
  /// 6 - rotate by Z
  /// @param value the value of the transformation
  void transformObject(int operation, double value);

  /// @brief Returns the file path of the current object
  /// @return The file path of the current object
  const std::string getFilePath() const;

  /// @brief Returns the current scale value of the object
  /// @return The current scale value of the object
  double getScale() const;

  /// @brief Returns the number of vertices in the object
  /// @return the number of vertices
  unsigned int getNumberVertex() const;

  /// @brief Returns the number of faces in the object
  /// @return The number of faces in the object
  unsigned int getNumberFace() const;

  /// @brief Returns the size of a face by index
  /// @param index index of the face
  /// @return The size of the face in terms of the number of vertices
  unsigned int getFaceSize(unsigned int index) const;

  /// @brief Sets the object to its normal state
  /// @details This function sets all transformations of the object to 0
  void toNormal();

  /// @brief Returns the value of a vertex by row and column
  /// @param row row of the vertex
  /// @param col column of the vertex
  /// @return The value of the vertex
  float getVertex(int row, int col) const;

  /// @brief Checks if the object is set
  /// @return true if the object is set, false otherwise
  bool isSetted() const;

  /// @brief Gets the sizes of the vertex and edge buffers
  /// @return A pair containing the sizes of the vertex and edge buffers
  std::pair<unsigned int, unsigned int> getBufSize();

  /// @brief Loads the vertex and edge buffers
  /// @param vertex_buffer Pointer to the vertex buffer
  /// @param edge_buffer Pointer to the edge buffer
  /// @param load Flag indicating whether to force loading
  void loadBuffer(float* vertex_buffer, float* edge_buffer, bool load);
};
}  // namespace viewer

#endif