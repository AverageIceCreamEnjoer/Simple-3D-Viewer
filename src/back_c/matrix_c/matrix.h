#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_MATRIX 1
#define ERR_CALC 2

typedef struct MatrixType {
  float **matrix;
  int rows;
  int columns;
} Matrix;

int CheckMatrix(Matrix *a);
int CreateMatrix(int rows, int columns, Matrix *result);
void RemoveMatrix(Matrix *a);
int MultNum(Matrix *a, float number);