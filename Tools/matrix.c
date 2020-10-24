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


void freeMatrix(Matrix M){
    free(M.matrix);
    M.width = 0;
    M.height = 0;
}



// Return the cuted matrix (part of the original matrix, only vertical cut)
Matrix _cutMatrix(Matrix M, int x ,int xlen,int height)
{
    Matrix cutted= newMatrix(xlen,height);
    cutted.matrix = malloc(height*xlen*sizeof(double));
    for (int xi=0; xi<xlen; x++)
    {
        for (int yi=0; yi<height; yi++)
        {
            cutted.matrix[xi*xlen+yi]=M.matrix[(x+xi)*xlen+(yi)];
        }
    }
    return cutted;
}

