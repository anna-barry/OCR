#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>

Matrix newMatrix(int H, int W){

  Matrix M;

  M.height = H;
  M.width = W;

  M.matrix = malloc(H*W*sizeof(double));

  for (int i = 0 ; i < H*W ; i++){

      M.matrix[i] = 0.0;
  }
  return M;
}

Matrix andLogicMartix(Matrix m1,Matrix m2){

  Matrix m3;

  m3.height = m1.height;
  m3.width = m1.width;
  m3.matrix = malloc(m3.height*m3.width*sizeof(double));

  for (int i = 0 ; i < m1.height ; i++){
      for (int j = 0 ; j < m1.width ; j++){

              m3.matrix[i*m3.width+j]=m1.matrix[i*m1.width+j]*m2.matrix[i*m2.width+j];
      }
  }
  return m3;
}

Matrix copyMatrix(Matrix M){

    Matrix mcopy;

    mcopy.height = M.height;
    mcopy.width = M.width;
    mcopy.matrix = malloc(mcopy.height*mcopy.width*sizeof(double));

    for (int i = 0 ; i < mcopy.height*mcopy.width ; i++){

      mcopy.matrix[i] = M.matrix[i];
    }
    return mcopy;
}

Matrix cutMatrix(Matrix M, int x, int y, int height, int width){
        Matrix cut;
        cut.height = height;
        cut.width = width;
        cut.matrix = malloc(height*width*sizeof(double));

        for (int i = x ; i < x+cut.height ; i++){
          for (int j = y ; j < y+cut.width ; j++){

            cut.matrix[(i-x)*cut.width+(j-y)] = M.matrix[i*M.width+j];
          }
        }
        return cut;
}

void freeMatrix(Matrix M){
    free(M.matrix);
    M.width = 0;
    M.height = 0;
}
