#ifndef ROTATIONMAN_H_
#define ROTATIONMAN_H_

#include <stdlib.h>
#include <SDL.h>
//#include <SDL_image.h>
#include <math.h>

#include "../../Tools/pixel_operations.h"

struct Tuple{int x; int y;};
SDL_Surface* ManualRotation(SDL_Surface* image_surface , int degrees);

#endif
