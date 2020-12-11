#ifndef RESIZEMATRIX_H
#define RESIZEMATRIX_H

#include "../Tools/matrix.h"
#include "../Tools/minifunc.h"
#include <stdio.h>
#include <stdlib.h>


struct Tuple{
  int top;
  int bottom;
};
//initialize the Tuple struct to save two values in a one value

Matrix resizeMatrix(Matrix matrixChar, int size);

#endif
