#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct Matrix{
  int width;
  int height;
  double *matrix;
} Matrix;

Matrix new_Matrix(int H, int W);

Matrix andLogicMartix(Matrix m1,Matrix m2);

Matrix copyMatrix(Matrix M);

Matrix cutMatrix(Matrix M, int x, int y, int height, int width);

void freeMatrix(Matrix M);

#endif
