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
double Entro(SDL_Surface* image_surface){
  int width = image_surface->w;
  int height = image_surface->h;
  Uint8 verti_pp[width],hori_pp[height];
  Uint8 r,v,b;
  Uint32 pixel;
  double entro_Hori=0,entro_Verti=0;

  for (int i = 0; i < width; i++){
    Uint8 sum_pixel;
    for (int j = 0; j < height; j++){
      pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
      sum_pixel += r + v + b;
    }
    hori_pp[i]=sum_pixel;
    entro_Hori += log(hori_pp[i])*(-hori_pp[i]);
  }

  for (int i = 0; i < height; i++){
    Uint8 sum_pixel;
    for (int j = 0; j < width; j++){
      pixel = get_pixel(image_surface, j, i);
      SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
      sum_pixel += r + v + b;
    }
    verti_pp[i]=sum_pixel;
    entro_Verti += log(verti_pp[i])*(-verti_pp[i]);
  }
  return min(entro_Verti,entro_Hori);
}

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
