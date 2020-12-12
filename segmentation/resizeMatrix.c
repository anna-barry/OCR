#include "resizeMatrix.h"

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size){
  /*
   * General description:
    Function that takes a matrix and returns a new one with the right size while keeping all its content
    --> zooms in the matrix

    Parameters:
    _ Matrix M: Matrix which we'll zoom
    _ int top: the top of the matrix
    _ int bot: bottom of the matrix
    _ int size: size of the matrix

    dates/authors :
    24/10
    geoffroy du mesnil du buisson

  */

  int newSizeH, newSizeW;
  double x, y, x1, y1, x2, y2, x3, y3;
  double delta1, delta2, delta3, delta4;
  double voisin11, voisin22, voisin21,voisin12;
  double somme;

  M = cutMatrix(M, top, 0, bot-top+1, M.width);	// cuts said matrix to fit rightly -> cut on the edges

  if (M.height > M.width){ // checking if the new Matrix is proportional compared to the old one

    newSizeH = size;
    newSizeW = (int) (M.width * newSizeH/(double)M.height);
  }
  else{

    newSizeW = size;
    newSizeH = (int) (M.height * newSizeW/(double)M.width);
  }

  Matrix sizeMat = newMatrix(newSizeH, newSizeW);	//new matrix of the same size

  // Bilinear Interpolation
  // For each of its 4 pixel neighbours calculate the sum of product of their differences
  for (int i = 0 ; i < sizeMat.height ; i++){
    for (int j = 0 ; j < sizeMat.width ; j++){

      x = j * M.width/sizeMat.width;
      y = i * M.height/sizeMat.height;

      // Returns integer part to get the smallest neighbour

      x1 = myintpart(x);
      y1 = myintpart(y);

      x3 = x1+1; //+ 1 to get the superior neighbour
      y3 = y1+1;

      if (x1 == M.width-1){ // getting the right neighbour
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

      // Returns absolute number of these differences
      delta1 = myabs((x3-x)*(y3-y));
      delta2 = myabs((x3-x)*(y-y1));
      delta3 = myabs((x-x1)*(y3-y));
      delta4 = myabs((x-x1)*(y-y1));

      // Multiply delta x value of the neighbour
      voisin11 = M.matrix[(int) (y1*M.width+x1)] * delta1;
      voisin12 = M.matrix[(int) (y1*M.width+x2)] * delta2;
      voisin21 = M.matrix[(int) (y2*M.width+x1)] * delta3;
      voisin22 = M.matrix[(int) (y2*M.width+x2)] * delta4;

      // Sum of neighbours
      somme = voisin11 + voisin22 + voisin21 + voisin12;

      //if sum>0,5 then value in new matrix is 1, else 0

      if(somme > 0.5){

        sizeMat.matrix[i*sizeMat.width+j] = 1;
      }
      else{

        sizeMat.matrix[i*sizeMat.width+j] = 0;
      }
    }
  }
  return sizeMat;
}




struct Tuple getCornerMatrix(Matrix M){
  /*
  description :
  function that return the angles of the charactere we want to resize

  parameters :
  Matrix M : the matrix of a charactere


  dates/authors :
  21/10
  geoffroy du mesnil du buisson

  */
  struct Tuple tuple;

  tuple.top =-1;//intitalization of boolean telling if the angles have been found
  tuple.bottom =-1;

  for (int i = 0; (tuple.top == -1 || tuple.bottom == -1) && i < M.height; i++) { //the loops continue while the both index have not been
    for (int j = 0; (tuple.top == -1 || tuple.bottom == -1) && j < M.width; j++) {//founded or we arrive at the end of the matrix

      if ((M.matrix[i*M.width+j] == 0)&&(tuple.top == -1)){

          tuple.top = i; //if the angle had not been finded top take the index of the angle
      }

      if ((M.matrix[(M.height-1-i)*M.width+j] == 1)&&(tuple.bottom == -1)) {

          tuple.bottom = M.height-1-i; //if the angle had not been finded bottom take the index of the angle
      }
    }
  }

  return tuple; //return the tuble with both the top and the bottom vulue
}




Matrix resizeMatrix(Matrix matrixChar, int size){
  /*
  description :
  function that take a matrice of a char and resize it to a commun size that will be used
  for all the char without changing the shape of the char

  parameters :
  Matrix M : matrix that we want to resize
  int size : the comun size we want for all the matrix


  dates/authors :
  21/10
  geoffroy du mesnil du buisson

  */

  //printf("the original matrix\n");

  //print_gMatrix(matrixChar);

  Matrix resized = newMatrix(size,size); //initialize a matrix in the good size

  struct Tuple tuple;

  tuple = getCornerMatrix(matrixChar);

  int top = tuple.top;//top corner
  int bot = tuple.bottom;//botom corner

  if (top == -1){//there is no char, the matrix is full of 0

    return resized;
  }
  else{//there is a char so we put in the good size

    Matrix sizeMat = bilinearInterpolation(matrixChar,top, bot, size);

    //printf("the bil matrix\n");

    //print_gMatrix(sizeMat);

    for (int i = 0; i < sizeMat.height; i++) {
      for (int j = 0; j < sizeMat.width; j++) {

        resized.matrix[i*resized.width+j] = sizeMat.matrix[i*sizeMat.width+j];
      }
    }

    //printf("the final matrix\n");

    //print_gMatrix(resized);

    freeMatrix(sizeMat);
    return resized; //return the good sized matrix
  }
}
