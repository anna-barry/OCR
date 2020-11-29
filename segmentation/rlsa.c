#include "rlsa.h"
#include "../Tools/matrix.h"
#include <stdio.h>
#include <stdlib.h>


Matrix horizonRLSA (Matrix img, int seuil){
  /*
  description :
  function that go thru a matrix from horizontal way
  and apply to it the RLSA algorthm

  parameters :
  Matrix img : matrix where we are going to apply the RLSA algorthm
  int seuil : limite the we fix for the RLSA system


  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */


  Matrix m = copyMatrix(img);

  int nbzeros;//nubers of 0 followed

  int j;//index on the width of the matrix
  int k;//index on the nubers of 0 followed

  for (int i = 0; i < m.height ; i++) {//classic search in the matrix

    j=0;
    while (j < m.width) {

      if ((int)m.matrix[i*m.width+j]!=1){

        k=j;
        nbzeros=0;

        while (((int)m.matrix[i*m.width+k]!=1)&&(k< m.width)) {//counting the numbers of 0 followed between two 1

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){//if the numbers of 0 is lower or equal to the limite (seuil) all the 0 pass to 1

          for (int l = j; l < nbzeros+j; l++) {

            m.matrix[i*m.width+l]=1;
          }
        }
        j+=nbzeros;//we increment the index of the number of 0 we had seen
      }//end if
      j++;
    }//end while
  }
  return m;//return the matrix
}

Matrix verticRLSA (Matrix img, int seuil){
  /*
  description :
  function that go thru a matrix from vertical way
  and apply to it the RLSA algorthm

  parameters :
  Matrix img : matrix where we are going to apply the RLSA algorthm
  int seuil : limite the we fix for the RLSA system


  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */

  Matrix m = copyMatrix(img);

  int nbzeros;//nubers of 0 followed

  int y;//index on the height of the matrix
  int k;//index on the nubers of 0 followed
  for (int x = 0; x < m.width ; x++) {//vertical search in the matrix

    y=0;
    while (y < m.height) {

      if ((int)m.matrix[y*m.width+x]!=1){

        k=y;
        nbzeros=0;
        while ((int)m.matrix[k*m.width+x]!=1&&k< m.height) {//counting the numbers of 0 followed between two 1

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){//if the numbers of 0 is lower or equal to the limite (seuil) all the 0 pass to 1

          for (int l = y; l < nbzeros+y; l++) {

            m.matrix[l*m.width+x]=1;
          }
        }
        y+=nbzeros;//we increment the index of the number of 0 we had seen
      }//end if
      y++;
    }//end while
  }
  return m;//return the matrix
}

Matrix rlsa(Matrix img, int verticSeuil, int horizonSeuil){
  /*
  description :
  return the mix of horizonRLSA and verticRLSA in a new matrix m

  parameters :
  Matrix img : the matrix of the whole image only compose with somme 0 and 1
  int verticSeuil : the limite of zero we want for the RLSA in vertical
  int horizonSeuil : the limite of zero we want for the RLSA in horizontal

  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */

  Matrix horizonMatrix = horizonRLSA(img, horizonSeuil);
  Matrix verticMatrix = verticRLSA(img, verticSeuil);

  Matrix m = andLogicMartix(horizonMatrix,verticMatrix);

  freeMatrix(horizonMatrix);
  freeMatrix(verticMatrix);

  return m;//return the new matrix
}
