#include "matrix.h"

int mult_num(matrix_t *A, float number) {
  int res = ERR_MATRIX;
  if (check_matrix(A)) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) A->matrix[i][j] *= number;
    res = OK;
  }
  return res;
}