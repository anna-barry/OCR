#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <SDL.h>

typedef struct Matrix{
  int width;
  int height;
  double *matrix;
} Matrix;

Matrix new_Matrix(int H, int W);

Matrix andLogicMartix(Matrix m1,Matrix m2);

Matrix copyMatrix(Matrix M);

void freeMatrix(Matrix M);

#endif
