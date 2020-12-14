#ifndef ROTATIONAUTO_H_
#define ROTATIONAUTO_H_

#include <stdlib.h>
#include <SDL.h>
#include <math.h>

#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"

SDL_Surface* ManualRot(SDL_Surface* image_surface, double degrees);
double getSkewAngle(SDL_Surface* image_surface, SDL_Surface* screen_surface);

#endif
