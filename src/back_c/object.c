#include "object.h"

int count_number(char* line) {
  int count = 0;
  char* token = strtok(line, " ");
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }
  return count - 1;  // Исключаем первый элемент ('v' или 'f')
}

void parse_vertex(Object* obj, char* line, int row) {
  char* token = strtok(line, " ");
  int i = 0;
  while ((token = strtok(NULL, " ")) != NULL) {
    float tmp = atof(token);
    obj->vertices.matrix[row][i++] = tmp;
  }
}

void parse_face(Object* obj, char* line, int face_index) {
  char* token = strtok(line, " ");
  unsigned int* one_face = (unsigned int*)malloc(sizeof(unsigned int) * 4);
  int count = 0;
  while ((token = strtok(NULL, " ")) != NULL) {
    unsigned int tmp = atoi(token) - 1;
    one_face[count++] = tmp;
  }
  obj->faces[face_index] = one_face;
  obj->face_sizes[face_index] = count;
}

void init_object(Object* obj) {
  obj->faces = NULL;
  obj->face_sizes = NULL;
  obj->amount_vertex = 0;
  obj->number_vertex = 0;
  obj->number_face = 0;
  obj->amount_face = 0;
}

bool readObject(Object* obj, const char* path) {
  FILE* object_to_pars = fopen(path, "r");
  bool result = true;
  if (object_to_pars == NULL) {
    result = false;
  }
  obj->amount_vertex = 0;  // итоговое количество vertex (x+y+z)
  obj->number_vertex = 0;  // количество строк vertex
  obj->number_face = 0;    // количество строк face
  obj->amount_face = 0;    // итоговое количество face
  obj->face_sizes = NULL;
  obj->faces = NULL;
  char line[256];
  while (result && fgets(line, sizeof(line), object_to_pars)) {
    if (obj->number_vertex <= MAX_VERTEX + 1) {
      if (line[0] == 'v' && line[1] == ' ') {
        obj->amount_vertex += count_number(line);
        obj->number_vertex++;
      } else if (line[0] == 'f' && line[1] == ' ') {
        obj->number_face++;
        obj->amount_face += count_number(line);
      }
    } else {
      fclose(object_to_pars);
      result = false;
    }
  }
  result = result && !(obj->number_vertex == 0);
  if (result) {
    int r = create_matrix(obj->number_vertex, 3, &obj->vertices);
    if (r == 0) {
      obj->faces =
          (unsigned int**)malloc(sizeof(unsigned int*) * obj->number_face);
      obj->face_sizes =
          (unsigned int*)malloc(sizeof(unsigned int) * obj->number_face);
      rewind(object_to_pars);
      int row = 0, face_index = 0;
      while (fgets(line, sizeof(line), object_to_pars)) {
        if (line[0] == 'v' && line[1] == ' ') {
          parse_vertex(obj, line, row++);
        } else if (line[0] == 'f' && line[1] == ' ') {
          parse_face(obj, line, face_index++);
        }
      }
    } else
      result = false;
    fclose(object_to_pars);
  }
  return result;
}

void free_object(Object* obj) {
  remove_matrix(&obj->vertices);
  if (obj->faces) {
    for (unsigned int i = 0; i < obj->number_face; ++i) {
      free(obj->faces[i]);
    }
    free(obj->faces);
  }
  if (obj->face_sizes) {
    free(obj->face_sizes);
  }
}

void center(Object* obj) {
  double cX = 0, cY = 0, cZ = 0;
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    cX += obj->vertices.matrix[i][0];
    cY += obj->vertices.matrix[i][1];
    cZ += obj->vertices.matrix[i][2];
  }
  cX /= obj->number_vertex;
  cY /= obj->number_vertex;
  cZ /= obj->number_vertex;
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    obj->vertices.matrix[i][0] -= cX;
    obj->vertices.matrix[i][1] -= cY;
    obj->vertices.matrix[i][2] -= cZ;
  }
}

void normalize(Object* obj) {
  double m = fabs(obj->vertices.matrix[0][0]);
  for (unsigned int i = 0; i < obj->number_vertex; i++) {
    if (fabs(obj->vertices.matrix[i][0]) > m)
      m = fabs(obj->vertices.matrix[i][0]);
    if (fabs(obj->vertices.matrix[i][1]) > m)
      m = fabs(obj->vertices.matrix[i][1]);
    if (fabs(obj->vertices.matrix[i][2]) > m)
      m = fabs(obj->vertices.matrix[i][2]);
  }
  if (m != 0)
    m = 1 / m;
  else
    m = 0.0000001;
  mult_num(&obj->vertices, m);
}

void scale(Object* obj, float scope) {
  if (scope != 0) mult_num(&obj->vertices, scope);
}
