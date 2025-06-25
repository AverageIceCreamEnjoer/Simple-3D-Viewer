#pragma once

#include <string>

extern "C" {
#include "../back_c/model.h"
}
namespace viewer {
class Controller {
 private:
  Model* model_;

 public:
  /// @brief Default constructor
  Controller();

  /// @brief Destructor
  ~Controller();

  /// @brief Sets the object to be rendered
  /// @param filePath the path to the obj file
  /// @return true if the object was successfully loaded, false otherwise
  bool SetObject(const std::string& file_path);

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
  void TransformObject(int operation, double value);

  /// @brief Returns the file path of the current object
  /// @return The file path of the current object
  const std::string GetFilePath() const;

  /// @brief Returns the current scale value of the object
  /// @return The current scale value of the object
  double GetScale() const;

  /// @brief Returns the number of vertices in the object
  /// @return the number of vertices
  unsigned int GetNumberVertex() const;

  /// @brief Returns the number of faces in the object
  /// @return The number of faces in the object
  unsigned int GetNumberFace() const;

  /// @brief Returns the size of a face by index
  /// @param index index of the face
  /// @return The size of the face in terms of the number of vertices
  unsigned int GetFaceSize(unsigned int index) const;

  /// @brief Sets the object to its normal state
  /// @details This function sets all transformations of the object to 0
  void ToNormal();

  /// @brief Returns the value of a vertex by row and column
  /// @param row row of the vertex
  /// @param col column of the vertex
  /// @return The value of the vertex
  float GetVertex(int row, int col) const;

  /// @brief Checks if the object is set
  /// @return true if the object is set, false otherwise
  bool IsSetted() const;

  /// @brief Gets the sizes of the vertex and edge buffers
  /// @return A pair containing the sizes of the vertex and edge buffers
  std::pair<unsigned int, unsigned int> GetBufSize();

  /// @brief Loads the vertex and edge buffers
  /// @param vertex_buffer Pointer to the vertex buffer
  /// @param edge_buffer Pointer to the edge buffer
  /// @param load Flag indicating whether to force loading
  void LoadBuffer(float* vertex_buffer, float* edge_buffer, bool load);
};
}  // namespace viewer