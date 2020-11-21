#include "../../../pixel_operations.h"
#include "../rotationMAN.h"
#include "../../../help4display.h"
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main()
{ 
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
  
    screen_surface = ManualRotation(image_surface, 30);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);

    SDL_FreeSurface(screen_surface);

    return 0;


}

