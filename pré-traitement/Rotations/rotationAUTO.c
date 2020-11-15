#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../binarisation/testbinarisation/pixel_operations.h"
#include "../../Tools/matrix.h"

/*
 *          Automatic Rotation algorithm by A.Barry
 *
 *  description:
 *  
 *      Function that sends back skew angle by calculating entropy 
 *      of the projection profiles
 *
 *  parameters:
 *      
 *      Matrix corresponding to picture after otsu method
 *
 *  Version 0.0 on 1/11/2020     
 */

float getSkewAngle(Matrix Mimage)
{
    Matrix m = copyMatrix(Mimage);
    int width= m.width;
    int height= m.height;
    int angleStart= -15;
    int angleEnd=15;
}

