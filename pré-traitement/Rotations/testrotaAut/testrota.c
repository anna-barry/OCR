#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../../Tools/pixel_operations.h"
#include "../../../Tools/image_operations.h"
#include "../../../Tools/matrix.h"
#include "../../binarisation/binarisation.h"
#include "../rotationMAN.h"
//#include "../rotationAUTO.h"


int main()
{
    init_sdl();

    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    image_surface = load_image("../testrotaAut/Img/loremipsum.bmp");

    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    image_surface = ManualRotation(image_surface, -1);

    //double angle = getSkewAngle(image_surface);

    //printf("%f\n", angle);

    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    update_surface(screen_surface, image_surface);

    image_surface = ManualRotation(image_surface, 1);

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
