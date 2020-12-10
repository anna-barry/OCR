#include "matrix2.h"

#include <stdlib.h>
#include <stdio.h>

Matrix newMatrix(int H, int W){
/*
description :

initialization of a new matrix

parameters :

int H : the height of the matrix
int W : the width of the matrix

dates/authors :
12/10
geoffroy du mesnil du buisson

*/
  Matrix M;

  M.height = H;
  M.width = W;

  for (int i = 0 ; i < H*W ; i++){

      M.matrix[i] = 0.0;
  }
  return M;
}

void print_Matrix(Matrix M){
  /*
  description :
  print a matrix and the nuber of element in the matrix

  parameters :
  Matrix M : the matrix that we want to print

  dates/authors :
  25/10
  geoffroy du mesnil du buisson

  */
  int n = 0;
    for (int i = 0 ; i < M.height ; i++){

                for (int j = 0 ; j < M.width ; j++){

                  printf("%i  ,", (int)M.matrix[i*M.width+j]);
                  n++;
                }
                printf("\n");
    }
    printf("\n");
    printf("%i\n", n);
}

