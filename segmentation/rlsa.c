#include "rlsa.h"
#include "../Tools/matrix.h"
#include <stdio.h>
#include <stdlib.h>


Matrix horizonRLSA (Matrix img, int seuil){
  /*
  description genral :

  Fonction qui parcour la matrice horizontalement et qui applique l'algo RLSA

  Les parametres :

  Matrix img : Matrice sur la quelle nous allons appliquer le RLSA
  int seuil : seil que nous fixons pour le RLSA

  Les dates de modifications :

  */


  Matrix m = copyMatrix(img);

  int nbzeros;//nombres de zeros à la suite

  int j;//compteur sur la largeur de la matrice
  int k;//compteur sur les zeros à la suite

  for (int i = 0; i < m.height ; i++) {//parcours classique de la matrice

    j=0;
    while (j < m.width) {

      if (m.matrix[i*m.width+j]!=1){

        k=j;
        nbzeros=0;

        while (m.matrix[i*m.width+k]!=1&&k< m.width) {//on compte le nombre de zeros à la suite entre deux 1

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){// si le nombre de zeros est inferieur ou eguale au seuil alors les zeros se transforme en 1

          for (int l = j; l < nbzeros; l++) {

            m.matrix[i*m.width+l]=1;
          }
        }
        j+=nbzeros;//on augmente notre index du nombre de zeros que nous avons parcourus
      }//end if
      j++;
    }//end while
  }
  return m;//on retourne la matrice
}

Matrix verticRLSA (Matrix img, int seuil){
  /*
  description genral :

  Fonction qui parcour la matrice verticalement et qui applique l'algo RLSA

  Les parametres :

  Matrix img : Matrice sur la quelle nous allons appliquer le RLSA
  int seuil : seil que nous fixons pour le RLSA

  Les dates de modifications :

  */

  Matrix m = copyMatrix(img);

  int nbzeros;//nombres de zeros à la suite

  int i;
  int k;
  for (int j = 0; j < m.width ; j++) {

    i=0;
    while (i < m.height) {

      if (m.matrix[i*m.width+j]!=1){

        k=i;
        nbzeros=0;
        while (m.matrix[i*m.width+k]!=1&&k< m.height) {

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){

          for (int l = i; l < nbzeros; l++) {

            m.matrix[i*m.width+l]=1;
          }
        }
        i+=nbzeros+1;
      }
      i++;
    }
  }
  return m;
}

Matrix rlsa(Matrix img, int verticSeuil, int horizonSeuil){

  Matrix horizonMatrix = horizonRLSA(img, horizonSeuil);
  Matrix verticMatrix = verticRLSA(img, verticSeuil);

  Matrix m = andLogicMartix(horizonMatrix,verticMatrix);

  freeMatrix(horizonMatrix);
  freeMatrix(verticMatrix);

  return m;
}
