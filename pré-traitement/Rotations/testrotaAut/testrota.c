#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <string.h>
#include "../rotationAUTO.h"
#include "../../../Tools/pixel_operations.h"
#include "../../../Tools/image_operations.h"
#include "../../../Tools/matrix.h"



int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* surface_image;
    init_sdl();

    image_surface = load_image("../testrotaAUT/Img/loremipsum.bmp");
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
    //                                       \  /
    //here is the angle you want to modify    v
    surface_image = ManualRot(image_surface, -2);
    screen_surface = display_image(surface_image);
    update_surface(screen_surface,surface_image);

    wait_for_keypressed();

    double angle = getSkewAngle(surface_image,screen_surface);
    printf("%f\n", angle);
    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(surface_image);

    return 0;
}
