#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "maths.h"

/*
 *          Automatic Rotation algorithm by A.Barry and G.Du Mesnil du Buisson
 *
 *  description:
 *  
 *      Function that sends back skew angle by calculating entropy 
 *      of the projection profiles
 *
 *  parameters:
 *      
 *      Surface* of image
 *
 *  Version 0.0 on 1/11/2020     
 */

//Entropy Calculation Function






//________________________________________________________________________
//Function getSkewAngle
double getSkewAngle(SDL_Surface* image_surface)
{
    SDL_Surface* result= image_surface;

    int OriW = image_surface->w;
    int OriH = image_surface->h;

    double angleStart= -15;
    double angleEnd=15;
    double step=1;
    double anglePrefinal;
    double angleFinal;

    result= ManualRotation(image_surface, angleStart);
    double anglePrefinal=Entro(result);
    for(double i=(angleStart+1); i<=angleEnd;i+=step)
    {
        result= ManualRotation(image_surface, i);
        anglePrefinal=(min(anglePrefinal,Entro(result)));
    }

    result= ManualRotation(image_surface, (anglePrefinal-step));
    double stepf=0.1;

    angleFinal=anglePrefinal;
    for(double i=(anglePrefinal-(step/2)); i<=(anglePrefinal+(step/2));i+=stepf)
    {
        result= ManualRotation(image_surface, i);
        angleFinal=(min(angleFinal,Entro(result)));
    }

    return angleFinal;
}

