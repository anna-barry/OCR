#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct Matrix{
  int width;
  int height;
  double *matrix;
} Matrix;

Matrix newMatrix(int H, int W);

Matrix andLogicMartix(Matrix m1,Matrix m2);

Matrix copyMatrix(Matrix M);

void freeMatrix(Matrix M);

Matrix cutMatrix(Matrix M, int x ,int xlen,int height);

#endif
