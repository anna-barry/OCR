#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
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
 *      Matrix corresponding to picture after otsu method
 *
 *  Version 0.3 on 15/11/2020
 */



// Needed functions for tests:
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

//___________________________________________________________________
// 1- Initialisation of variables
//
// Rotation is counter-clockwise here so degrees 0 - 360 are negative
// 180 deg = PI/6 rad
#define Pi 3.141592653589


SDL_Surface* ManualRotation(SDL_Surface* image_surface , int degrees)
{
    // 1- Initialisation of variables
    double Angle;
    if(degrees>0)
    {
        Angle=(double)(-(Pi* degrees)/180);
    }
    else
    {
        Angle=(double)((Pi* degrees)/180);
    }

    //Cartesian Indexing
    int i, j;
    // In Matrix indexing
    int x, y;

    double fDistance, fPolarAngle;
    
    // Cartesian neighbouring indexing
    int iFloorX, iCeilingX, iFloorY, iCeilingY;

    // Cartesian calculated indexing with decimals
    double fTrueX, fTrueY;

    //_________________________________________
    //Bilinear interpolation
    // Indexing
    double fDeltaX, fDeltaY;

    // Pixel values around pixel(i,j)
    Uint32 clrTopLeft, clrTopRight, clrBottomLeft, clrBottomRight;

    // interpolated "top" pixels
    double fTopRed, fTopGreen, fTopBlue;

    // interpolated "bottom" pixels
    double fBottomRed, fBottomGreen, fBottomBlue;

    // Final interpolated colour components
    int iRed, iGreen, iBlue;
    int iCentreX, iCentreY;
    int iWidth, iHeight;
    iWidth = image_surface->w;
    iHeight = image_surface->h;

    iCentreX= iWidth/2;
    iCentreY= iHeight/2;

    SDL_Surface* step1= image_surface;
    SDL_Surface* step2= image_surface;
    SDL_Surface* step3= image_surface;

    for (i = 0; i < iHeight; ++i)
    {
        for (j = 0; j < iWidth; ++j)
        {
            // initialise with black pixels
            Uint32 pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
            put_pixel(step1,j,i,pixel);
            put_pixel(step2,j, i,pixel);
            put_pixel(step3,j, i, pixel);
        }
    }

    //_______________________________________________________________
    //2- Values from source to destination with rotation
    
    for(i=0; i<iHeight;i++)
    {
        for(j=0;j<iWidth;j++)
        {
            // Convert from Surface to Cartesian values
            x= j- iCentreX;
            y= iCentreY -i;

            // Convert Cartesian values to Polar values
            fDistance= sqrt(x*x + y*y);
            fPolarAngle= 0.0;

            if(x==0)
            { if (y==0) // Center of picture = no need for rotation
                {
                    put_pixel(step1,j,i, get_pixel(image_surface, j, i));
                            continue;
                            }
                else{
                if (y>0)
                {
                    fPolarAngle= 0.5 * Pi;
                }
                else
                {
                    fPolarAngle= 1.5* Pi;
                }
                }

            }
            else
            {
                fPolarAngle= atan2((double)y, (double)x);
            }

            // Rotation
            fPolarAngle-= Angle;

            // Converting polar -> cartesian
            x= (int)(round(fDistance * cos(fPolarAngle)));
            y= (int)(round(fDistance * sin(fPolarAngle)));

            // Cartesian -> raster
            x = x + iCentreX;
            y = iCentreY - y;

            //Check if not out of bounds
            if (x < 0 || x >= iWidth || y < 0 || y >= iHeight) continue;
            put_pixel(step1,x, y,get_pixel(image_surface, j, i));
        }
    }

    // 3- Pixels of result image -> source image
    for(i=0; i< iHeight; i++)
    {
        for(j=0; j< iWidth; j++)
        {
            // Raster -> Cartesian
            x= j- iCentreX;
            y= iCentreY -i;

            // Cartesian -> polar
            fDistance= sqrt(x*x + y*y);
            fPolarAngle= 0.0;
            if (x==0)
            {
                if (y==0) // No need to change since centre ofimage
                {
                    put_pixel(step2,j,i, get_pixel(image_surface, j, i));
                            continue;
                }
                else
                {
                    if(y>0)
                    {
                        fPolarAngle= 0.5 * Pi;
                    }
                    else
                    {
                        fPolarAngle= 1.5* Pi;
                    }
                }
            }
            else
            {
                fPolarAngle= atan2((double)y,(double)x);
            }

            fPolarAngle-= Angle;
            // Polar -> Cartesian
             x = (int)(round(fDistance * cos(fPolarAngle)));
             y = (int)(round(fDistance * sin(fPolarAngle)));

             // Cartesian -> raster
             x+= iCentreX;
             y= iCentreY -y;

             // Check if not out of bounds
             if (x < 0 || x >= iWidth || y < 0 || y >= iHeight) continue;

             // Put new pixel value
                 put_pixel(step2,j, i,get_pixel(image_surface, x, y));
        }
    }

    // 4- Image rotation with bilinear interpolation
    for(i=0; i< iHeight ; i++)
    {
        for (j=0; j<iWidth; j++)
        {
            // Raster -> Cartesian
            x= j- iCentreX;
            y= iCentreY -i ;

            // Cartesian -> polar
            fDistance= sqrt(x*x + y*y);
            fPolarAngle = 0.0;

            if (x==0)
            {
                if (y==0) // center  of pixel = no rotation
                {
                    put_pixel(step3,j,i, get_pixel(image_surface, j, i));
                    continue;
                }
                else
                {
                    if(y>0)
                    {
                        fPolarAngle = 0.5 * Pi;
                    }
                    else
                    {
                        fPolarAngle = 1.5 * Pi;
                    }
                }
            }
            else
            {
                fPolarAngle= atan2((double)y,(double)x);
            }
            
            // "Reverse" rotation
            fPolarAngle -= Angle;

            // Polar -> Cartesian
            fTrueX = fDistance * cos(fPolarAngle);
            fTrueY = fDistance * sin(fPolarAngle);

            // Cartesian -> raster
            fTrueX += (double)iCentreX;
            fTrueY = (double)iCentreY - fTrueY;
            
            iFloorX = (int)(floor(fTrueX));
            iFloorY = (int)(floor(fTrueY));
            iCeilingX = (int)(ceil(fTrueX));
            iCeilingY = (int)(ceil(fTrueY));

            // Check if not out of bounds
            if (iFloorX < 0 || iCeilingX < 0 || iFloorX >= iWidth || iCeilingX >= iWidth || iFloorY < 0 || iCeilingY < 0 || iFloorY >= iHeight || iCeilingY >= iHeight) continue;


            fDeltaX = fTrueX - (double)iFloorX;
            fDeltaY = fTrueY - (double)iFloorY;


            clrTopLeft = get_pixel(image_surface, iFloorX, iFloorY);
            clrTopRight =  get_pixel(image_surface,iCeilingX, iFloorY);
            clrBottomLeft =  get_pixel(image_surface, iFloorX, iCeilingY);
            clrBottomRight =  get_pixel(image_surface, iCeilingX, iCeilingY);

            // Horizontal linear interpolation between top neighbours
            Uint8 rclrTopLeft, gTopLeft, bTopLeft;
            SDL_GetRGB(clrTopLeft, image_surface->format, &rclrTopLeft, &gTopLeft, &bTopLeft);

            Uint8 rTR, gTR, bTR;
            SDL_GetRGB(clrTopRight, image_surface->format, &rTR, &gTR, &bTR);

            fTopRed = (1 - fDeltaX) * rclrTopLeft + fDeltaX * rTR;
            fTopGreen = (1 - fDeltaX) * gTopLeft + fDeltaX * gTR;
            fTopBlue = (1 - fDeltaX) * bTopLeft + fDeltaX * bTR;

            // Horizontal linear interpolation between bottom neighbours
            Uint8 rBL, gBL, bBL;
            SDL_GetRGB(clrBottomLeft, image_surface->format, &rBL, &gBL, &bBL);

            Uint8 rBR, gBR, bBR;
            SDL_GetRGB(clrBottomRight, image_surface->format, &rBR, &gBR, &bBR);

            fBottomRed = (1 - fDeltaX) * rBL + fDeltaX * rBR;
            fBottomGreen = (1 - fDeltaX) * gBL + fDeltaX * gBR;
            fBottomBlue = (1 - fDeltaX) * bBL + fDeltaX * bBR;

            //Vertical linear interpolation between top and bottom results
            iRed = (int)(round((1 - fDeltaY) * fTopRed + fDeltaY * fBottomRed));
            iGreen = (int)(round((1 - fDeltaY) * fTopGreen + fDeltaY * fBottomGreen));
            iBlue = (int)(round((1 - fDeltaY) * fTopBlue + fDeltaY * fBottomBlue));
            
            //Valid Colours
            if (iRed < 0) iRed = 0;
            if (iRed > 255) iRed = 255;
            if (iGreen < 0) iGreen = 0;
            if (iGreen > 255) iGreen = 255;
            if (iBlue < 0) iBlue = 0;
            if (iBlue > 255) iBlue = 255;


            put_pixel(step3,j, i,SDL_MapRGB(image_surface->format, iRed, iGreen, iBlue));
        }
    }

    SDL_FreeSurface(step1);

    SDL_FreeSurface(step2);

    return step3;
}




int main()
{   
    init_sdl();
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;
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
