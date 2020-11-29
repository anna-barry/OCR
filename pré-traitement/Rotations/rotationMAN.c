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

    //Minimum
    double topsM=min(getNewX(0,0, sinA, cosA, OriW/2, OriH/2),getNewX((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double downsM=min(getNewX(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewX((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double TotalMinW= min(topsM,downsM);

    int NewW= (int)max((NewW1-TotalMinW),NewW1);

    double t2=max(getNewY(0,0,sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double d2=max(getNewY(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double NewH2=max(t2,d2);

    /Minimum
    double TD2=min(getNewY(0,0,sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double dd2=min(getNewY(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double NewH2=max(t2,d2);
    double totalMin= min(TD2,dd2);

    int NewH=(int)max(NewH2,(NewH2-totalMin));

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



    for(y=0; y<= OriH; y++)
    {
        for(x=0; x<=OriW; x++)
        {

             if(x==OriW/2 && y==OriH/2)
            {
                put_pixel(result,x-TotalMinW,y-totalMin,get_pixel(image_surface,x,y));
                continue;
            }



            xO=getNewX(x,y, sinA, cosA, OriW/2, OriH/2)-TotalMinW;
            yO=getNewY(x,y, sinA, cosA, OriW/2, OriH/2)-totalMin;
            if (yO>0 && yO<NewH && xO>0 && xO<NewW)
            {
                if (y>0 && y<(OriH-1) && x>0 && x<(OriW-1))
            {
                //_________________________________________________________________________
                ////Bilinear Interpolation
                //_________________________________________________________________________
                    
                    double xS=(double)floor(x);
                    double xL=(double)ceil(x);
                    double yS= (double)floor(y);
                    double yL= (double)ceil(y);
            
                    // Top Left
                    Uint32 topLeft= get_pixel(image_surface,xS,yL); //c00
                    Uint8 rclrTopLeft, gTopLeft, bTopLeft;
                    SDL_GetRGB(topLeft, image_surface->format, &rclrTopLeft, &gTopLeft, &bTopLeft);

                    // Top Right
                    Uint32 topRight= get_pixel(image_surface,xL,yL); //c10
                    Uint8 rTR, gTR, bTR;
                    SDL_GetRGB(topRight, image_surface->format, &rTR, &gTR, &bTR);

                    // Top Left
                    Uint32 botLeft= get_pixel(image_surface,xS,yS);  //c01
                    Uint8 rBL, gBL, bBL;
                    SDL_GetRGB(botLeft, image_surface->format, &rBL, &gBL, &bBL);

                    //Top Right
                    Uint32 botRight= get_pixel(image_surface,xL,yS); //c11
                    Uint8 rBR, gBR, bBR;
                    SDL_GetRGB(botRight, image_surface->format, &rBR, &gBR, &bBR);
                    double factor1;
                    double factor2;

                    if(xL==xS)
                    { factor1=1;
                      factor2=0; }
                    else{
                      factor1= (((double)xL - (double)xO)/((double)xL - (double)xS));
                      factor2= (((double)xO - (double)xS)/((double)xL - (double)xS));
                    }

                    double R1r = factor1 * (double)rBL + factor2*(double)rBR;
                    double R1g = factor1 * (double)gBL + factor2*(double)gBR;
                    double R1b = factor1 * (double)bBL + factor2*(double)bBR;
                    double R2r = factor1 * (double)rclrTopLeft + factor2*(double)rTR;
                    double R2g = factor1 * (double)gTopLeft + factor2*(double)gTR;
                    double R2b = factor1 * (double)bTopLeft + factor2*(double)bTR;


                    double factor3;
                    double factor4;
                    if (yL == yS) // special case to avoid divide by zero
                             {
                                   factor3 = 1;
                                   factor4 = 0;
                              }
                          else
                             {
                                   factor3 = ((double)yL - yO)/((double)yL - (double)yS);
                                   factor4 = (yO - (double)yS)/((double)yL - (double)yS);
                              }
                    int finalR = (int)((factor3 * R1r) + (factor4*R2r));
                        int finalG = (int)((factor3 * R1g) + (factor4*R2g));
                        int finalB = (int)((factor3 * R1b) + (factor4*R2b));

                        finalR = min(255, finalR);
                        finalR = max(0, finalR);
                        finalG = min(255, finalG);
                        finalG = max(0, finalG);
                        finalB = min(255, finalB);
                        finalB = max(0, finalB);
                        put_pixel(result,xO, yO,SDL_MapRGB(result->format, finalR, finalG, finalB));
            }
                else
                {
                    put_pixel(result,xO,yO,get_pixel(image_surface,x,y));
                }
            
            }
            

        }
    }

    return result;

}
