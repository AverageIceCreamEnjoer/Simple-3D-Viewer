#include "matrix.h"

int CheckMatrix(Matrix *a) {
  int res = 0;
  if (a != NULL) {
    if (a->matrix != NULL) {
      if (a->rows > 0 && a->columns > 0) res = 1;
    }
  }
  return res;
}