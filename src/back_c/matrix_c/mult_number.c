#include "matrix.h"

int MultNum(Matrix *a, float number) {
  int res = ERR_MATRIX;
  if (CheckMatrix(a)) {
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++) a->matrix[i][j] *= number;
    res = OK;
  }
  return res;
}