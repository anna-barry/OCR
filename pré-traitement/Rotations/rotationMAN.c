#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
#include <stdio.h>
#include <math.h>
# include <err.h>
#include <string.h>


/*
 *          Manual Rotation algorithm by A.Barry
 *
 *  description:
 *
 *      Function that rotates a photo
 *
 *  parameters:
 *
 *      Surface corresponding to picture after otsu method
 *
 *  Version 0.3 on 15/11/2020
 */


//___________________________________________________________________
// 1- Initialisation of variables
//
// Rotation is counter-clockwise here so degrees 0 - 360 are negative


