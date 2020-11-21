#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
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
 *      Surface corresponding to picture after otsu method
 *
 *  Version 0.3 on 15/11/2020
 */


//___________________________________________________________________
// 1- Initialisation of variables
//
// Rotation is counter-clockwise here so degrees 0 - 360 are negative

#define Pi 3.141592653589
SDL_Surface* ManualRotation(SDL_Surface* image_surface , int degrees)
{
    //Rotation Angle
    double angle = degrees * Pi / 180.;
    double cosA=cos(angle);
    double sinA=sin(angle);

    //Coordinates 
    int x,y;
    double xO=0;
    double yO=0;

    // New surface
    SDL_Surface* result= image_surface;

    int OriW = image_surface->w;
    int OriH = image_surface->h;
    // Initialize with black pixels
    for (int i = 0; i < OriH; ++i)
    {
        for (int j = 0; j < OriW; ++j)
        {
            // initialise with black pixels
            Uint32 pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
            put_pixel(result,j,i,pixel);
        }
    }

//New height and width Range
    int NewW= OriW*fabs(sinA)+OriH*fabs(cosA);
    int NewH= OriW*fabs(cosA)+OriH*fabs(sinA);

    //Offset (x=ay+b where b is the offset)
    // Temp Width and Height
    int temp=sqrt((double)OriW * OriW + (double)OriH *OriH) + 10;

    int xOff=temp/2;
    int yOff=temp/2;

    //Max and Min original Pixels to rotate
    int yMin=(temp-NewH)/2.;
    int yMax=yMin+NewH+1;
    int xMin=(temp-NewW)/2.;
    int xMax=xMin+NewW +1;

for(y=yMin; y<=yMax; y++)
    {
        for(x=xMin; x<=xMax; x++)
        {
            //Getting Original Coordinates
            yO=sinA*(double)(x-xOff)+cosA*(double)(y-yOff);
            yO+=(double)((int)(OriH/2));
            xO=cosA*(double)(x-xOff)-sinA*(double)(y-yOff);
            xO+=(double)((int)(OriW/2));

            //If in original range -> if not just black
            if (yO>=0. && yO<OriH-0.5 && xO>=0. && xO<OriW-0.5)
            {
                    //Bilinear Interpolation
                    int xS=floor(xO);
                    int xL=ceil(xO);
                    int yS= floor(yO);
                    int yL= ceil(yO);

                    int fDeltaX=xO- (double)xS;
                    int fDeltaY=yO- (double)yS;
                    // Pixel values around pixel(i,j) xS= TopLeft xL=TopRight
                    // yS= Bottom Left yL BottomRight
                    Uint32 topLeft= get_pixel(image_surface,xS,yS);
                    Uint32 topRight= get_pixel(image_surface,xL,yS);
                    Uint32 botLeft= get_pixel(image_surface,xS,yL);

                    double fTopRed = (1 - fDeltaX) * rclrTopLeft + fDeltaX * rTR;
                    double fTopGreen = (1 - fDeltaX) * gTopLeft + fDeltaX * gTR;
                    double fTopBlue = (1 - fDeltaX) * bTopLeft + fDeltaX * bTR;

                    // Horizontal linear interpolation between bottom neighbours
                    Uint8 rBL, gBL, bBL;
                    SDL_GetRGB(botLeft, image_surface->format, &rBL, &gBL, &bBL);

                    Uint8 rBR, gBR, bBR;
                    SDL_GetRGB(botRight, image_surface->format, &rBR, &gBR, &bBR);

double fTopRed = (1 - fDeltaX) * rclrTopLeft + fDeltaX * rTR;
                    double fTopGreen = (1 - fDeltaX) * gTopLeft + fDeltaX * gTR;
                    double fTopBlue = (1 - fDeltaX) * bTopLeft + fDeltaX * bTR;

                    // Horizontal linear interpolation between bottom neighbours
                    Uint8 rBL, gBL, bBL;
                    SDL_GetRGB(botLeft, image_surface->format, &rBL, &gBL, &bBL);

                    Uint8 rBR, gBR, bBR;
                    SDL_GetRGB(botRight, image_surface->format, &rBR, &gBR, &bBR);


                    double fBottomRed = (1 - fDeltaX) * rBL + fDeltaX * rBR;
                    double fBottomGreen = (1 - fDeltaX) * gBL + fDeltaX * gBR;
                    double fBottomBlue = (1 - fDeltaX) * bBL + fDeltaX * bBR;

                    //Vertical linear interpolation between top and bottom results
                    int iRed = (int)(round((1 - fDeltaY) * fTopRed + fDeltaY * fBottomRed));
                    int iGreen = (int)(round((1 - fDeltaY) * fTopGreen + fDeltaY * fBottomGreen));
                    int iBlue = (int)(round((1 - fDeltaY) * fTopBlue + fDeltaY * fBottomBlue));

                    //Valid Colours
                    if (iRed < 0) iRed = 0;
                    if (iRed > 255) iRed = 255;
                    if (iGreen < 0) iGreen = 0;
                    if (iGreen > 255) iGreen = 255;
                    if (iBlue < 0) iBlue = 0;
                    if (iBlue > 255) iBlue = 255;


                    put_pixel(result,y, x,SDL_MapRGB(image_surface->format, iRed, iGreen, iBlue));
            }

        }
    }

    return result;
}
