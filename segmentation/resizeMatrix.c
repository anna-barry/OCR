#include "segmentation.h"
#include "rlsa.h"
#include "../Tools/matrix.h"

#include <stdio.h>
#include <sdio.h>

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size){

  int newSizeH, newSizeW;
  double x, y, x1, y1, x2, y2, x3, y3;
  double delta1, delta2, delta3, delta4;
  double voisin11, voisin22, voisin21,voisin12;

  M = cutMatrix(M, top, 0, bot-top+1, M.width);	// coupe la matrice pour ne garder que le char

  if (M.height > M.width){

    newSizeH = size;
    newSizeW = (int) (M.width * newSizeH/(double)M.height);
  }
  else{

    newSizeW = size;
    newSizeH = (int) (M.height * newSizeW/(double)M.width);
  }

  Matrix sizeMat = newMatrix(newSizeH, newSizeW);	//nouvelle matrice de la bonne taille (size)

  for (int i = 0 ; i < sizeMat.height ; i++){
    for (int j = 0 ; j < sizeMat.width ; j++){

      x = j * M.width/sizeMat.width;
      y = i * M.height/sizeMat.height;

      x1 = myintpart(x);
      y1 = myintpart(y);

      x3 = x1+1;
      y3 = y1+1;

      if (x1 == M.width-1){
        x2 = M.width-1;
      }
      else{
        x2 = x3;
      }

      if (y1 == M.width-1){
        y2 = M.width-1;
      }
      else{
        y2 = y3;
      }

      delta1 = myabs((x3-x)*(y3-y));
      delta2 = myabs((x3-x)*(y-y1));
      delta3 = myabs((x-x1)*(y3-y));
      delta4 = myabs((x-x1)*(y-y1));

      voisin11 = M.matrix[(int) (y1*M.width+x1)] * delta1;
      voisin12 = M.matrix[(int) (y1*M.width+x2)] * delta2;
      voisin21 = M.matrix[(int) (y2*M.width+x1)] * delta3;
      voisin22 = M.matrix[(int) (y2*M.width+x2)] * delta4;

      somme = voisin11 + voisin22 + voisin21 + voisin12;

      if(somme > 0.5){

        sizeMat.matrix[i*sizeMat.width+j] = 1;
      }
      else{

        sizeMat.matrix[i*sizeMat.width+j] = 0;
      }
}




int *getCornerMatrix(Matrix M){

  int array_top_bot[2];

  int topindex =-1;
  int botindex =-1;

  for (int i = 0; (topindex == -1 || botindex_i == -1) && i < M.height; i++) {
    for (size_t j = 0; (topindex == -1 || botindex_i == -1) && j < M.width; j++) {

      if ((M.matrix[i*M.width+j] == 1)&&(topindex == -1)){

          topindex = i;
      }

      if ((M.matrix[(M.height-1-i)*M.width+j] == 1)&&(botindex_i == -1)) {

          botindex_i = M.height-1-i;
      }
    }
  }

  array_top_bot[0]=topindex;
  array_top_bot[1]=botindex;

  return array_top_bot;
}




Matrix resizeMatrix(Matrix matrixChar, int size){

  Matrix resized = newMatrix(size,size);

  int array_top_bot[2] = getCornerMatrix(matrixChar);

  int top = array_top_bot[0];//top corner
  int bot = array_top_bot[1];//botom corner

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
