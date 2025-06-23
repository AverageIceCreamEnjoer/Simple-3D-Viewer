#include "matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int res = ERR_MATRIX;
  if (result && rows > 0 && columns > 0) {
    res = OK;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (float **)malloc(sizeof(float *) * rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (float *)malloc(sizeof(float) * columns);
      for (int j = 0; j < columns; j++) result->matrix[i][j] = 0;
    }
  }
  return res;
}