#ifndef MATRIX2_H
#define MATRIX2_H

#include <stdlib.h>

typedef struct Matrix{
  int width;
  int height;
  double matrix[width*height];

} Matrix;

Matrix newMatrix(int H, int W);

double matrix_get(Matrix m, int w, int h);

void matrix_put(Matrix m, size_t w, size_t h, double value);

Matrix andLogicMartix(Matrix m1,Matrix m2);

Matrix cutMatrix(Matrix M, int x ,int y,int height,int width);

Matrix copyMatrix(Matrix M);

void freeMatrix(Matrix M);

void print_Matrix(Matrix M);

#endif
