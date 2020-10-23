#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>

Matrix new_Matrix(int H, int W){
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
  Matrix m3 = new_Matrix(m1.height, m1.with);
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

void freeMatrix(Matrix M){
    free(M.matrix);
    M.width = 0;
    M.height = 0;
}

Matrix cutMatrix(Matrix M, int x ,int xlen,int height)
{
    Matrix cutted= new_Matrix(xlen,height);
    for (int xi=0; xi<xlen; x++)
    {
        for (int yi=0; yi<height; y++)
        {
            cutted[xi*xlen+yi]=M[(x+xi)*xlen+(yi+y)];
        }
    }
    return cutted;
}

