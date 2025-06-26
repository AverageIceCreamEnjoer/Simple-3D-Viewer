#include "matrix.h"

// Constructors/Destructors

Matrix::Matrix() noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {}  // Default constructor

Matrix::Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ < 0 || cols_ < 0)
    throw std::length_error("Matrix size must be non-negative");  // exception
  matrix_ = new float[rows_ * cols_]{};
}  // matrix rows*cols size

Matrix::Matrix(const Matrix& other) : rows_{other.rows_}, cols_{other.cols_} {
  matrix_ = new float[rows_ * cols_];
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}  // copy

Matrix::Matrix(Matrix&& other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}  // move

Matrix::~Matrix() noexcept { Free(); }  // Destructor

// getters

int Matrix::GetRows() const noexcept { return rows_; }  // getter/accessor

int Matrix::GetCols() const noexcept { return cols_; }  // getter/accessor

// setters

void Matrix::SetRows(int row) {
  if (row < 0) throw std::length_error("Matrix size must be non-negative");
  if (row != rows_) {
    Matrix temp(row, cols_);
    int min = std::min(rows_, row);
    for (int i = 0; i < min; i++)
      for (int j = 0; j < cols_; j++) temp(i, j) = (*this)(i, j);
    *this = std::move(temp);
  }
}  // setter/mutator

void Matrix::SetCols(int col) {
  if (col < 0) throw std::length_error("Matrix size must be non-negative");
  if (col != cols_) {
    Matrix temp(rows_, col);
    int min = std::min(cols_, col);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < min; j++) temp(i, j) = (*this)(i, j);
    *this = std::move(temp);
  }
}  // setter/mutator

// Public methods

bool Matrix::EqMatrix(const Matrix& other) const noexcept {
  bool result = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    result = true;
    for (int i = 0; i < rows_ && result; i++)
      for (int j = 0; j < cols_ && result; j++)
        if (std::abs(other(i, j) - (*this)(i, j)) > 1e-7) result = false;
  }
  return result;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (!(rows_ == other.rows_ && cols_ == other.cols_))
    throw std::out_of_range("Different matrix sizes");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) += other(i, j);
}

void Matrix::SubMatrix(const Matrix& other) {
  if (!(rows_ == other.rows_ && cols_ == other.cols_))
    throw std::out_of_range("Different matrix sizes");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) -= other(i, j);
}

void Matrix::MulNumber(const float value) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) *= value;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range("Incorrect matrixes size for multiplication");
  Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < cols_; k++) temp(i, j) += (*this)(i, k) * other(k, j);
  *this = std::move(temp);
}

Matrix Matrix::Transpose() noexcept {
  Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res(j, i) = (*this)(i, j);
  return res;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res(i, j) = Minor(i, j);
      if ((i + j) % 2) res(i, j) = -res(i, j);
    }
  }
  return res;
}

// Gauss method
float Matrix::Determinant() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  float res = 1;
  Matrix tmp(*this);
  int size = rows_;
  for (int i = 0; i < size; i++) {
    int pivoting = i;
    for (int j = i + 1; j < size; j++)
      if (std::abs(tmp(j, i)) > std::abs(tmp(pivoting, i))) pivoting = j;

    if (std::abs(tmp(pivoting, i)) < 1e-7) {
      res = 0;
      break;
    }
    if (i != pivoting) {
      res = -res;
      for (int j = 0; j < cols_; j++) std::swap(tmp(i, j), tmp(pivoting, j));
    }
    res *= tmp(i, i);
    for (int j = i + 1; j < size; j++) {
      float koef = tmp(j, i) / tmp(i, i);
      for (int k = i; k < size; k++) tmp(j, k) -= tmp(i, k) * koef;
    }
  }
  return res;
}

Matrix Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  float det = Determinant();
  if (std::abs(det) < 1e-7)
    throw std::out_of_range("Determinant must be non-zero");
  return CalcComplements().Transpose() * (1.0 / det);
}

// operators

bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix Matrix::operator*(float value) const noexcept {
  Matrix tmp(*this);
  tmp.MulNumber(value);
  return tmp;
}

Matrix operator*(float value, const Matrix& matrix) noexcept {
  Matrix tmp = matrix * value;
  return tmp;
}

Matrix& Matrix::operator*=(float value) {
  MulNumber(value);
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator=(const Matrix& other) {
  SetRows(other.rows_);
  SetCols(other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) = other(i, j);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    Free();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

float& Matrix::operator()(int row, int col) & {
  return const_cast<float&>(GetElem(row, col));
}

const float& Matrix::operator()(int row, int col) const& {
  return GetElem(row, col);
}

// Private methods

const float& Matrix::GetElem(int row, int col) const {
  if (!(row < rows_ && col < cols_ && row >= 0 && col >= 0)) {
    std::cout << row << ' ' << col << std::endl;
    throw std::out_of_range("Index is out of range this matrix");
  }
  return matrix_[row * cols_ + col];
}

void Matrix::Free() noexcept {
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

float Matrix::Minor(int row, int col) const {
  Matrix temp(rows_ - 1, rows_ - 1);
  int shift_i = 0;
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == row) shift_i = 1;
    int shift_j = 0;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) shift_j = 1;
      temp(i, j) = (*this)(i + shift_i, j + shift_j);
    }
  }
  return temp.Determinant();
}