#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include <math.h>
# include <err.h>
#include <string.h>


/*
 *          Manual Rotation algorithm by A.Barry
 *
 *  description:
 *
 *      Function that rotates a photo
 *
 *  parameters:
 *
 *      Surface corresponding to the input picture
 *
 *  Version 3.4 on 1/12/2020
 */

static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void init_sdl()
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

#define max(a,b) (a>=b?a:b)
#define min(a,b) ((a) < (b) ? (a) : (b))

#define Pi 3.141592653589
struct Tuple{int x; int y;};

struct Tuple shear3(double angle,int x, int y) {
    // shear 1
    double tangent=tan(angle/2);
    int new_x=round(x - y * tangent);
    int new_y=y;
    
    // shear 2
    new_y=round(new_x * sin(angle) + new_y);
    
    //shear 3
    new_x=round(new_x - new_y * tangent);
    
    struct Tuple x_y_return = { new_x, new_y };
    
    return x_y_return;
}

SDL_Surface* ManualRotation(SDL_Surface* image_surface, double degrees)
{
    //Rotation Angle
    double angle = degrees * Pi / 180;
    double cosine=cos(angle);
    double sine=sin(angle);

    int OriW = image_surface->w;
    int OriH = image_surface->h;
    

    //New height and width
    int new_height = round(fabs(OriH * cosine) + fabs(OriW * sine)) + 1;
    int new_width  = round(fabs(OriW * cosine) + fabs(OriH * sine)) + 1;
    

    //Centre of the image about which we have to rotate the image
    int original_centre_height = round(((OriH+1)/2)-1);
    int original_centre_width = round(((OriW+1)/2)-1);
    
    
    //Centre of the new image that will be obtained
    int new_centre_height = round(((new_height+1)/2)-1);
    int new_centre_width = round(((new_width+1)/2)-1);
    
    //printf("new_centre_height: %d, new_centre_width: %d\n", new_centre_height, new_centre_width);
    
    // New surface
    SDL_Surface* result=NULL;
    result=SDL_CreateRGBSurface (0, new_width, new_height, 32, 0, 0, 0, 0);

    // Initialize with white pixels
    for (int i = 0; i < new_height; ++i)
    {
        for (int j = 0; j < new_width; ++j)
        {
            // initialise with white pixels
            Uint32 pixel = SDL_MapRGB(result->format, 255, 255, 255);
            put_pixel(result,j,i,pixel);
        }
    }

    for(int i=0; i<OriH; ++i)
    {
        for(int j=0; j<OriW; ++j)
        {
            //co-ordinates of pixel with respect to the centre of original image
            int y = OriH - 1 - i - original_centre_height;
            int x = OriW - 1 - j - original_centre_width;
            
            //Applying shear Transformation
            struct Tuple sheared_x_y = shear3(angle,x,y);
            
            int new_y = new_centre_height - sheared_x_y.y;
            int new_x = new_centre_width - sheared_x_y.x;

            put_pixel(result, new_x, new_y, get_pixel(image_surface,j,i));
        }
    }

    return result;
}



int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    SDL_Surface* surface_image;
    init_sdl();

    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    wait_for_keypressed();
    
    surface_image = ManualRotation(image_surface, 45);
    screen_surface = display_image(surface_image);
    update_surface(screen_surface,surface_image);
    wait_for_keypressed();


    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    SDL_FreeSurface(surface_image);

    return 0;


}
