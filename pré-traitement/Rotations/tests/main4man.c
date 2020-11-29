#include "../../../pixel_operations.h"
#include "../rotationMAN.h"
#include "../../../help4display.h"
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main()
{ 
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* surface_image;
    init_sdl();

    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
  
    surface_image = ManualRotation(image_surface, 30);
    screen_surface = display_image(surface_image);
    update_surface(screen_surface, surface_image);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(surface_image);
    return 0;


}

