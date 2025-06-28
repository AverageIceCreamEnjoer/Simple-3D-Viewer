#pragma once

#include <exception>
#include <iostream>
#include <utility>

class Matrix final {
 public:
  Matrix() noexcept;                    // Default constructor
  explicit Matrix(int rows, int cols);  // matrix rows*cols size
  Matrix(const Matrix& other);          // copy
  Matrix(Matrix&& other) noexcept;      // move
  ~Matrix() noexcept;                   // Destructor

  int GetRows() const noexcept;  // accessor
  int GetCols() const noexcept;  // accessor

  void SetRows(int row);  // mutator
  void SetCols(int col);  // mutator

  void SumMatrix(const Matrix& other);
  bool EqMatrix(const Matrix& other) const noexcept;
  void SubMatrix(const Matrix& other);
  void MulNumber(const float value) noexcept;
  void MulMatrix(const Matrix& other);
  Matrix Transpose() noexcept;
  Matrix CalcComplements() const;
  float Determinant() const;
  Matrix InverseMatrix() const;

  bool operator==(const Matrix& other) const;
  Matrix operator+(const Matrix& other) const;
  Matrix& operator+=(const Matrix& other);
  Matrix operator-(const Matrix& other) const;
  Matrix& operator-=(const Matrix& other);
  Matrix operator*(float value) const noexcept;
  Matrix operator*(const Matrix& other) const;
  friend Matrix operator*(float value, const Matrix& other) noexcept;
  Matrix& operator*=(float value);
  Matrix& operator*=(const Matrix& other);

  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);

  float& operator()(int row, int col) &;
  float& operator()(int row, int col) && = delete;
  const float& operator()(int row, int col) const&;
  const float& operator()(int row, int col) const&& = delete;

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  float* matrix_;    // Pointer to the memory where the matrix is allocated

  // Private methods
  void Free() noexcept;
  const float& GetElem(int row, int col) const;
  float Minor(int row, int col) const;
};