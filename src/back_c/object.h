#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_c/matrix.h"

#define MAX_VERTEX 1000000  // миллион

typedef struct {
  matrix_t vertices;           // значение вершин (xyz)
  unsigned int** faces;        // значение face
  unsigned int* face_sizes;    // размеры каждого face
  unsigned int amount_vertex;  // количество координат вершин
  unsigned int number_vertex;  // количество вершин
  unsigned int number_face;    // количество ребер
  unsigned int amount_face;    // итоговое количество face
} Object;

void init_object(Object* obj);
bool readObject(Object* obj, const char* path);
void free_object(Object* obj);
void center(Object* obj);
void normalize(Object* obj);
void scale(Object* obj, float scope);
void rotateX(Object* obj, float angleX);
void rotateY(Object* obj, float angleY);
void rotateZ(Object* obj, float angleZ);
void translate(Object* obj, float x, float y, float z);

#endif  // __OBJECT_H__