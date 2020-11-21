#ifndef ROTATIONMAN_H_
#define ROTATIONMAN_H_

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../../pixel_operations.h"
#include "../../help4display.h"

SDL_Surface* ManualRotation(SDL_Surface* image_surface , int degrees);

#endif
