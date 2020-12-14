#ifndef RECOGNISE_ASCII.H
#define RECOGNISE_ASCII.H
#include "LeNet.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include "SDL/SDL_image.h"
#include <time.h>
#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"
#include "../../Tools/matrix.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include <SDL.h>

#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )

void RandomFilter2(struct Matrix *m, int range);
int getASCII(Matrix M);


#endif
