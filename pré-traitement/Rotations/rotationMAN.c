#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#undef ManualRotation
//#undef update_surface
#include "../../Tools/pixel_operations.h"
#include "rotationMAN.h"
#include <stdio.h>
#include <math.h>


/*
 *          Manual Rotation algorithm by A.Barry
 *
 *  description:
 *
 *      Function that rotates a photo
 *
 *  parameters:
 *
 *      Surface corresponding to the input picture using the shear method
 *
 *  Version 3.2 on 02/12/2020
 */


//___________________________________________________________________
// 1- Initialisation of needed variables
// #define Pi 3.141592653589
// struct Tuple{int x; int y;};
//
// struct Tuple shear3(double angle,int x, int y) {
//     // shear 1
//     double tangent=tan(angle/2);
//     int new_x=round(x - y * tangent);
//     int new_y=y;
//
//     // shear 2
//     new_y=round(new_x * sin(angle) + new_y);
//
//     //shear 3
//     new_x=round(new_x - new_y * tangent);
//
//     struct Tuple x_y_return = { new_x, new_y };
//
//     return x_y_return;
// }
// SDL_Surface* ManualRotation(SDL_Surface* image_surface, double degrees)
// {
//     //Rotation Angle
//     double angle = degrees * Pi / 180;
//     double cosine=cos(angle);
//     double sine=sin(angle);
//
//     int OriW = image_surface->w;
//     int OriH = image_surface->h;
//
//
//     //New height and width
//     int new_height = round(fabs(OriH * cosine) + fabs(OriW * sine)) + 1;
//     int new_width  = round(fabs(OriW * cosine) + fabs(OriH * sine)) + 1;
//
//     //Centre of the image about which we have to rotate the image
//     int original_centre_height = round(((OriH+1)/2)-1);
//     int original_centre_width = round(((OriW+1)/2)-1);
//
//
//     //Centre of the new image that will be obtained
//     int new_centre_height = round(((new_height+1)/2)-1);
//     int new_centre_width = round(((new_width+1)/2)-1);
//
//     //printf("new_centre_height: %d, new_centre_width: %d\n", new_centre_height, new_centre_width);
//
//     // New surface
//     SDL_Surface* result=NULL;
//     result=SDL_CreateRGBSurface (0, new_width, new_height, 32, 0, 0, 0, 0);
//
//     // Initialize with white pixels
//     for (int i = 0; i < new_height; ++i)
//     {
//         for (int j = 0; j < new_width; ++j)
//         {
//             // initialise with white pixels
//             Uint32 pixel = SDL_MapRGB(result->format, 255, 255, 255);
//             put_pixel(result,j,i,pixel);
//         }
//     }
//
//     for(int i=0; i<OriH; ++i)
//     {
//         for(int j=0; j<OriW; ++j)
//         {
//             //co-ordinates of pixel with respect to the centre of original image
//             int y = OriH - 1 - i - original_centre_height;
//             int x = OriW - 1 - j - original_centre_width;
//
//             //Applying shear Transformation
//             struct Tuple sheared_x_y = shear3(angle,x,y);
//             int new_y = new_centre_height - sheared_x_y.y;
//             int new_x = new_centre_width - sheared_x_y.x;
//
//             put_pixel(result, new_x, new_y, get_pixel(image_surface,j,i));
//         }
//     }
//
//     return result;
// }

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
    
    SDL_SaveBMP(result, "manuelRotation.bmp");
    return result;
}
