#include "segmentation.h"
#include "rlsa.h"
#include "../Tools/matrix.h"

#include <stdio.h>
#include <sdio.h>

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size){
  //TODO
}

int *cornerMatrix(Matrix M){

  int array_top_bot[2];

  int topindex =-1;
  int botindex =-1;

  for (int i = 0; (topindex == -1 || botindex_i == -1) && i < M.height; i++) {
    for (size_t j = 0; (topindex == -1 || botindex_i == -1) && j < M.width; j++) {
      if (M.matrix[i*M.width+j] == 1){

        if (topindex == -1)
          topindex = i;
      }
      if (M.matrix[(M.height-1-i)*M.width+j] == 1) {

        if (botindex_i == -1)
          botindex_i = M.height-1-i;
      }
    }
  }

  array_top_bot[0]=topindex;
  array_top_bot[1]=botindex;

  return array_top_bot;
}


Matrix resizeMatrix(Matrix matrixChar, int size){

  Matrix resized = new_Matrix(size,size);

  int array_top_bot[2] = cornerMatrix(matrixChar);

  int top = array_top_bot[0];
  int bot = array_top_bot[1];

  if (top == -1){
    return resized;
  }
  else{

    Matrix sizeMat = bilinearInterpolation(matrixChar,top, bot, size);

    for (int i = 0; i < sizeMat.height; i++) {
      for (size_t j = 0; j < sizeMat.width; j++) {
        resized.matrix[i*resized.width+j] = sizeMat.matrix[i*sizeMat.width+j];
      }
    }

    freeMatrix(sizeMat);
    return resized;
  }
}
