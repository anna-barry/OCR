#include "../Tools/matrix.h"
#include "../Tools/minifunc.h"

#include <stdio.h>
#include <stdlib.h>

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size){
  /*
  description genral :
  general description :

  Fonction qui prend une matrice et la retourne en etant à la bonne taille tout en gardant le contenu (fonction qui zoom)


  Les parametres :

  Matrix M : Matrice sur la quelle nous allons appliquer le zoom

  Les dates de modifications :

  */

  int newSizeH, newSizeW;
  double x, y, x1, y1, x2, y2, x3, y3;
  double delta1, delta2, delta3, delta4;
  double voisin11, voisin22, voisin21,voisin12;
  double somme;

  M = cutMatrix(M, top, 0, bot-top+1, M.width);	// coupe la matrice pour ne garder que le char

  if (M.height > M.width){ // produit en croix pour que la nouvelle matrice soit proportinel à l'ancienne

    newSizeH = size;
    newSizeW = (int) (M.width * newSizeH/(double)M.height);
  }
  else{

    newSizeW = size;
    newSizeH = (int) (M.height * newSizeW/(double)M.width);
  }

  Matrix sizeMat = newMatrix(newSizeH, newSizeW);	//nouvelle matrice de la bonne taille (size)

  for (int i = 0 ; i < sizeMat.height ; i++){
    for (int j = 0 ; j < sizeMat.width ; j++){ //algorithme d'interpolation bilinéaire qui pour les quatres voisins d'un point retourne la somme du produit de leurs difference

      x = j * M.width/sizeMat.width;
      y = i * M.height/sizeMat.height;

      x1 = myintpart(x); //retourne la partie entiere pour avoir le voisin entier inferieur
      y1 = myintpart(y);

      x3 = x1+1; //ajoute 1 pour avoir le voisin entier superieur
      y3 = y1+1;

      if (x1 == M.width-1){ // determination de quel est le bon voisin
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

      delta1 = myabs((x3-x)*(y3-y)); //retourne la valeur absolue du produit des diference
      delta2 = myabs((x3-x)*(y-y1));
      delta3 = myabs((x-x1)*(y3-y));
      delta4 = myabs((x-x1)*(y-y1));

      voisin11 = M.matrix[(int) (y1*M.width+x1)] * delta1; //multiplie delta par la valeur à lemplacement voisin
      voisin12 = M.matrix[(int) (y1*M.width+x2)] * delta2;
      voisin21 = M.matrix[(int) (y2*M.width+x1)] * delta3;
      voisin22 = M.matrix[(int) (y2*M.width+x2)] * delta4;

      somme = voisin11 + voisin22 + voisin21 + voisin12; //somme des voisins

      if(somme > 0.5){//si la somme des voisins est superieur à 0.5 alors la valeur dans la nouvelle matrice est passé à 1 sinon 0

        sizeMat.matrix[i*sizeMat.width+j] = 1;
      }
      else{

        sizeMat.matrix[i*sizeMat.width+j] = 0;
      }
    }
  }
  return sizeMat;
}




int *getCornerMatrix(Matrix M){
  /*
  description genral :

  Fonction qui retourne un tableau composé des angles d'en haut à guanche et en bas à droite

  Les parametres :

  Matrix M : Matrice dont on veut connaitre les angles

  Les dates de modifications :

  */

  int array_top_bot[2];//intitalisation du tableau

  int topindex =-1;//intitalisation de boolean indiquant si les angles on etait trouvé
  int botindex =-1;

  for (int i = 0; (topindex == -1 || botindex == -1) && i < M.height; i++) { // les boucles tournent tant que les deux index ne sont
    for (size_t j = 0; (topindex == -1 || botindex == -1) && j < M.width; j++) {//pas trouvé ou que la matrice n'as pas encore etait parcourus entierment

      if ((M.matrix[i*M.width+j] == 1)&&(topindex == -1)){//si l'angle n'avais pas etait trouvé topindex prend la coordoné de l'angle

          topindex = i;
      }

      if ((M.matrix[(M.height-1-i)*M.width+j] == 1)&&(botindex == -1)) {//si l'angle n'avais pas etait trouvé botindex prend la coordoné de l'angle

          botindex = M.height-1-i;
      }
    }
  }

  array_top_bot[0]=topindex; //rentre la coordoné des angles dans le tableau
  array_top_bot[1]=botindex;

  return array_top_bot; //retourn de tableau
}




Matrix resizeMatrix(Matrix matrixChar, int size){
  /*
  description genral :

  Fonction qui prend une matrice d'un charachtere et qui le met à une taille
  commune pour tout les chars sans deformer le charachtere

  Les parametres :

  Matrix M : Matrice sur la quelle nous allons appliquer le recadrage
  int size : la taille que nous voulons avoir pour la nouvelle mtrice


  Les dates de modifications :

  */

  Matrix resized = newMatrix(size,size);

  int array_top_bot[2];
  array_top_bot = getCornerMatrix(matrixChar);

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
