#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_c/matrix.h"

#define MAX_VERTEX 1000000  // миллион

typedef struct {
  Matrix vertices;             // значение вершин (xyz)
  unsigned int** faces;        // значение face
  unsigned int* face_sizes;    // размеры каждого face
  unsigned int amount_vertex;  // количество координат вершин
  unsigned int number_vertex;  // количество вершин
  unsigned int number_face;    // количество ребер
  unsigned int amount_face;    // итоговое количество face
} Object;

void InitObject(Object* obj);
bool ReadObject(Object* obj, const char* path);
void FreeObject(Object* obj);
void Center(Object* obj);
void Normalize(Object* obj);
void Scale(Object* obj, float scope);
void RotateX(Object* obj, float angle);
void RotateY(Object* obj, float angle);
void RotateZ(Object* obj, float angle);
void Translate(Object* obj, float x, float y, float z);