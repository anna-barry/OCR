#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#undef ManualRotation
//#undef update_surface
//#include <stdio.h>
#include "../../../Tools/matrix.h"
#include "../../../Tools/pixel_operations.h"
#include "../../binarisation/binarisation.h"
//#include "../../../Tools/matrix.h"
#include "../rotationMAN.h"

/*void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}


SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = SDL_LoadBMP(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);
*/


int main()
{ 
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* surface_image;
    init_sdl();

    /*_______ Init SDL
    SDL_Init(SDL_INIT_VIDEO);

    image_surface = SDL_LoadBMP("loremipsum.bmp");
    
    //________ Display Image 
*/
    screen_surface = display_image(image_surface);
    //screen_surface = SDL_SetVideoMode(image_surface->w, image_surface->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    
   // SDL_UpdateRect(screen_surface, 0, 0, image_surface->w, image_surface->h);
    
    /*Wait_for_Keypressed();
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
    */
    wait_for_keypressed();
  
    surface_image = ManualRotation(image_surface, 30);
    screen_surface = display_image(surface_image);
    //screen_surface = SDL_SetVideoMode(surface_image->w, surface_image->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    
    //SDL_UpdateRect(screen_surface, 0, 0, surface_image->w, surface_image->h);


    update_surface(screen_surface, surface_image);
    //wait_for_keypressed();
    //Wait_for_Keypressed
    //SDL_Event event;

    /* Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);

*/
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(surface_image);
    return 0;


}

