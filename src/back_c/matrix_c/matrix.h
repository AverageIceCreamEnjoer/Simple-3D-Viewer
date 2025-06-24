#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_MATRIX 1
#define ERR_CALC 2

typedef struct matrix_struct {
  float **matrix;
  int rows;
  int columns;
} matrix_t;

int check_matrix(matrix_t *a);
int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int mult_num(matrix_t *A, float number);