#include "affine_transform.h"

void move_model(float *matrix_of_vertex, int axis, int number, float value) {
  for (int i = 0 + axis; i < number; i += 3) matrix_of_vertex[i] += value;
}

void rotation_by_ox(float *matrix_of_vertex, int number, float angle) {
  for (int i = 0; i < number * 3; i += 3) {
    float y = matrix_of_vertex[i + 1];
    float z = matrix_of_vertex[i + 2];
    matrix_of_vertex[i + 1] = y * cos(angle) - z * sin(angle);
    matrix_of_vertex[i + 2] = y * sin(angle) + z * cos(angle);
  }
}

void rotation_by_oy(float *matrix_of_vertex, int number, float angle) {
  for (int i = 0; i < number * 3; i += 3) {
    float x = matrix_of_vertex[i];
    float z = matrix_of_vertex[i + 2];
    matrix_of_vertex[i] = x * cos(angle) + z * sin(angle);
    matrix_of_vertex[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void rotation_by_oz(float *matrix_of_vertex, int number, float angle) {
  for (int i = 0; i < number * 3; i += 3) {
    float x = matrix_of_vertex[i];
    float y = matrix_of_vertex[i + 1];
    matrix_of_vertex[i] = x * cos(angle) - y * sin(angle);
    matrix_of_vertex[i + 1] = x * sin(angle) + y * cos(angle);
  }
}

void scale_model(float *matrix_of_vertex, int number, float value) {
  if (fabs(value) > 1e-8) {
    for (int i = 0; i < number; i++) matrix_of_vertex[i] *= value;
  }
}
