#ifndef RESIZEMATRIX_H
#define RESIZEMATRIX_H

#include "../Tools/matrix.h"

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size);
int *getCornerMatrix(Matrix M);
Matrix resizeMatrix(Matrix matrixChar, int size);

#endif
