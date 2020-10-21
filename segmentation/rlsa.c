#include "rlsa.h"
#include "../Tools/matrix.h"
#include <stdio.h>
#include <stdlib.h>


Matrix horizonRLSA (Matrix img, int seuil){
  Matrix m = copyMatrix(img);
  int nbzeros;//nombres de zeros à la suite
  int j;//compteur sur la largeur de la matrice
  int k;//compteur sur les zeros à la suite
  for (int i = 0; i < m.height ; i++) {
    j=0;
    while (j < m.widht) {
      if (m.matrix[i*m.width+j]!=1){
        k=j;
        nbzeros=0;
        while (m.matrix[i*m.width+k]!=1&&k< m.width) {
          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){
          for (size_t l = j; l < nbzeros; l++) {
            m.matrix[i*m.width+l]=1;
          }
        }
        j+=nbzeros
      }//end if
      j++;
    }//end while
  }
  return m;
}

Matrix verticRLSA (Matrix img, int seuil){
  Matrix m = copyMatrix(img);int nbzeros;
  int j;
  int k;
  for (int j = 0; j < m.width ; j++) {
    j=0;
    while (i < m.height) {
      if (m.matrix[i*m.width+j]!=1){
        k=i;
        nbzeros=0;
        while (m.matrix[i*m.width+k]!=1&&k< m.height) {
          nbzeros++;
          k++;
        }
        if (nbzeros<=seil){
          for (size_t l = i; l < nb; l++) {
            m.matrix[i*m.width+l]=1;
          }
        }
        i+=nbzeros+1
      }
      i++;
    }
  }
  return m
}

Matrix rlsa(Matrix img, int verticSeuil, int horizonSeuil){
  Matrix horizonMatrix = horizonRLSA(img, horizonSeuil);
  Matrix verticMatrix = verticRLSA(img, verticSeuil);
  Matrix m = andLogicMartix(horizonRLSA,verticRLSA);
  freeMatrix(horizonMatrix);
  freeMatrix(verticMatrix);
  return m;
}
