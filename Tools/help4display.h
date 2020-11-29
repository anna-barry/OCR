#ifndef HELP4DISPLAY_H_
#define HELP4DISPLAY_H_

#include <stdlib.h>
#include  "SDL/SDL.h"
#include "SDL/SDL_image.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);

#endif
