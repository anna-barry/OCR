#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../../Tools/matrix.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
#include "traitement.h"
#include "../binarisation/binarisation.h"

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;


    init_sdl();

    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    Matrix m= surface_to_matrix_grayscale(image_surface);
    printf("matrix to grayscale [ok] \n");
    matToImg(smooth(m),"smooth");
    update_surface(screen_surface, image_surface);
    printf("update surface1 [ok] \n ");
    matToImg(contrast(m),"contrast");
    update_surface(screen_surface, image_surface);
    printf("update surface2 [ok] \n ");
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    printf("free all [ok] \n");
    return 0;


}

