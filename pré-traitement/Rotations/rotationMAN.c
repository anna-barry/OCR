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
 *  Version 1.2 on 27/11/2020
 */


//___________________________________________________________________
// 1- Initialisation of variables
//
// Rotation is counter-clockwise here so degrees 0 - 360 are negative
double getNewX(int x,int y,double sinA,double cosA, int xori,int yori)
{
    return ((-sinA * (y- yori))+ (cosA*(x-xori)))+ xori;
}

int getNewY(int x,int y,double sinA,double cosA, int xori,int yori)
{
    return ((cosA*(y-yori))+(sinA*(x-xori)))+yori;
}
#define max(a,b) (a>=b?a:b)
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

    int OriW = image_surface->w;
    int OriH = image_surface->h;

    //New height and width Range
    double topss=max(getNewX(0,0, sinA, cosA, OriW/2, OriH/2),getNewX((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double downss=max(getNewX(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewX((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double NewW1=max(topss,downss);

    int NewW= (int)(NewW1);

    double t2=max(getNewY(0,0,sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double d2=max(getNewY(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double NewH2=max(t2,d2);

    int NewH=(int)(NewH2);
    // New surface
    SDL_Surface* result=NULL;
    result=SDL_CreateRGBSurface (0, NewW, NewH, 32, 0, 0, 0, 0);

    // Initialize with black pixels
    for (int i = 0; i < NewH; ++i)
    {
        for (int j = 0; j < NewW; ++j)
        {
            // initialise with black pixels
            Uint32 pixel = SDL_MapRGB(result->format, 0, 0, 0);
            put_pixel(result,j,i,pixel);
        }
    }


    printf("Original surface = %i x %i and new Surface= %i x %i \n",OriW,OriH,NewW,NewH);
    printf("SinA is %f and CosA= %f \n \n",sinA, cosA);

    for(y=0; y<= OriH; y++)
    {
        for(x=0; x<=OriW; x++)
        {

             if(x==OriW/2 && y==OriH/2)
            {
                put_pixel(result,x,y,get_pixel(image_surface,x,y));
                continue;
            }



            xO=getNewX(x,y, sinA, cosA, OriW/2, OriH/2);
            yO=getNewY(x,y, sinA, cosA, OriW/2, OriH/2);
            if (yO>0 && yO<NewH && xO>0 && xO<NewW)
            {

                //ORIGINAL COLOURS
                put_pixel(result,xO,yO,get_pixel(image_surface,x,y));

            }
            

        }
    }

    return result;

}
