#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../../Tools/matrix.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
#include "traitement.h"
#include "../binaristion/binarisation.h"

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    Matrix m= surface_to_matrix_grayscale(image_surface);
  
    wait_for_keypressed();
    screen_surface = smooth(m);
    update_surface(screen_surface, image_surface);
    
    wait_for_keypressed();
    screen_surface = contrast(m);
    update_surface(screen_surface, image_surface);
    
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;


}

