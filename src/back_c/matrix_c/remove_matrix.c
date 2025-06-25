#include "matrix.h"

void RemoveMatrix(Matrix *a) {
  if (a) {
    if (a->matrix) {
      for (int i = 0; i < a->rows; i++) {
        if (a->matrix[i]) free(a->matrix[i]);
      }
      free(a->matrix);
    }
    a->rows = 0;
    a->columns = 0;
  }
}
