#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include <stdio.h>
#include <math.h>
#include "rotationAUTO.h"

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
float interpolar1(float a, float b, float c)
{
  float res;
  res=a+(b-a)*c;
  return res;
}

float interpolar2(float c00, float c10, float c01, float c11, float tx, float ty)
{
  return interpolar1(interpolar1(c00,c10,tx),interpolar1(c01,c11,tx),ty);
}

double getNewX(int x,int y,double sinA,double cosA, int xori,int yori)
{
    return ((-sinA * (y- yori))+ (cosA*(x-xori)))+ xori;
}

int getNewY(int x,int y,double sinA,double cosA, int xori,int yori)
{
    return ((cosA*(y-yori))+(sinA*(x-xori)))+yori;
}


#define max(a,b) (a>=b?a:b)
#define min(a,b) ((a) < (b) ? (a) : (b))

#define Pi 3.141592653589
SDL_Surface* ManualRot(SDL_Surface* image_surface, double degrees)
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

    int NewW= (int) OriH;
    if (degrees!=90)
    {
        NewW= (int)max((NewW1-TotalMinW),NewW1);
    }

    double t2=max(getNewY(0,0,sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double d2=max(getNewY(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));
    //Minimum
    double TD2=min(getNewY(0,0,sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),0,sinA, cosA, OriW/2, OriH/2));
    double dd2=min(getNewY(0,(OriH-1),sinA, cosA, OriW/2, OriH/2),getNewY((OriW-1),(OriH-1),sinA, cosA, OriW/2, OriH/2));

    double NewH2=max(t2,d2);
    double totalMin= min(TD2,dd2);

    int NewH= (int) OriW;
    if (degrees!=90)

    {
        NewH=(int)max(NewH2,(NewH2-totalMin));
    }
    // New surface
    SDL_Surface* result=NULL;
    result=SDL_CreateRGBSurface (0, NewW, NewH, 32, 0, 0, 0, 0);
    //printf("New min is yO=%d and last min is %f \n",getNewY(0,0,sinA, cosA, OriW/2, OriH/2),totalMin);

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


    //printf("Original surface = %i x %i and new Surface= %i x %i \n",OriW,OriH,NewW,NewH);
    //printf("SinA is %f and CosA= %f \n \n",sinA, cosA);

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

            if(yO>0 && y<NewH && xO>0 && xO<NewW)
            {

                //ORIGINAL COLOURS
                //put_pixel(result,xO,yO,get_pixel(image_surface,x,y));
                if (y>0 && y<(OriH-1) && x>0 && x<(OriW-1))
            {
                    //printf("in here \n");
                    //ORIGINAL COLOURS
                    //put_pixel(result,xO,yO,get_pixel(image_surface,x,y));

                    //printf("pb here for xO= %f and yO=%f and xMax=%d and yMAx=%d ? \n",xO,yO,(OriW-1),(OriH-1));
                    if (x>0 && y>0 && x<(OriW-1) && y<(OriH-1)  ) {


                    //Bilinear Interpolation
                    //double xS=(double)floor(x);
                    //double xL=(double)ceil(x);
                    //double yS= (double)floor(y);
                    //double yL= (double)ceil(y);
                    //printf("pb here for xO= %f and yO=%f ?? \n",xO,yO);

                    //q12x TOP LEFT = xS
                    //q12y TOP LEFT = yS
                    //q22x TOP RIGHT = XL
                    //q22y TOP RIGHT = yS
                    //q11x BOTTOM LEFT = xS
                    //q11y BOTTOM LEFT = yL
                    //q21x BOTTOM RIGHT = xL
                    //q21y BOTTOM RIGHT = yL


                    double xS=x-1;
                    double xL= x+1;
                    double yS=y-1;
                    double yL=y+1;
                    // Pixel values around pixel(i,j)
                    // Top Left
                    Uint32 topLeft= get_pixel(image_surface,xS,yS); //c00
                    Uint8 rclrTopLeft, gTopLeft, bTopLeft;
                    SDL_GetRGB(topLeft, image_surface->format, &rclrTopLeft, &gTopLeft, &bTopLeft);

                    // Top Right
                    Uint32 topRight= get_pixel(image_surface,xL,yS); //c10
                    Uint8 rTR, gTR, bTR;
                    SDL_GetRGB(topRight, image_surface->format, &rTR, &gTR, &bTR);

                    // Bottom Left
                    Uint32 botLeft= get_pixel(image_surface,xS,yL);  //c01
                    Uint8 rBL, gBL, bBL;
                    SDL_GetRGB(botLeft, image_surface->format, &rBL, &gBL, &bBL);

                    //Bottom Right
                    Uint32 botRight= get_pixel(image_surface,xL,yL); //c11
                    Uint8 rBR, gBR, bBR;
                    SDL_GetRGB(botRight, image_surface->format, &rBR, &gBR, &bBR);

                    double factor1;
                    double factor2;

                    if(xL==xS)
                    {
                      factor1=1;
                      factor2=0;

                    }
                    else
                    {
                      factor1= (((double)xL - (double)x)/((double)xL - (double)xS));
                      factor2= (((double)x - (double)xS)/((double)xL - (double)xS));
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
				                   factor3 = ((double)yS - y)/((double)yS - (double)yL);
				                   factor4 = (y - (double)yL)/((double)yS - (double)yL);
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
                    //printf("pb here for x0= %i and y0=%i ?? \n",x,y);
                    }else
                    {
                        put_pixel(result,xO,yO,get_pixel(image_surface,x,y));
                    }
            }
            }
        }
    }

    return result;
}
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
  double temp, child;
  Uint8 r,v,b;
  Uint32 pixel;

  double entro_Hori=0,entro_Verti=0;

  for (int i = 0; i < width; i++){
    Uint8 sum_pixel=0;
    for (int j = 0; j < height; j++){
      pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
      sum_pixel += r + v + b;
    }
    temp = (double)sum_pixel;
    if (temp>0) {
      child= log(temp);
      temp = child * -temp;
    }
    entro_Hori += temp;
  }
  //printf("entro_Hori : %f\n", entro_Hori);

  for (int i = 0; i < height; i++){
    Uint8 sum_pixel=0;
    for (int j = 0; j < width; j++){
      pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
      sum_pixel += r + v + b;
    }
    temp = (double)sum_pixel;
    if (temp>0) {
      child= log(temp);
      temp = child * -temp;
    }
    entro_Verti += temp;
  }
  //printf("entro_Verti : %f\n", entro_Hori);
  return fmax(entro_Verti,entro_Hori);
}

//________________________________________________________________________
//Function getSkewAngle
double getSkewAngle(SDL_Surface* image_surface, SDL_Surface* screen_surface)
{
    SDL_Surface* result= image_surface;
    //SDL_Surface* ano;

    double angleStart= -15;
    double angleEnd=15;
    double step=1;
    double anglePrefinal;
    double angleFinal;
    double angleEntro;
    double entro;

    result= ManualRot(image_surface, angleStart);
    update_surface(screen_surface,result);
    anglePrefinal = angleStart;
    angleEntro=Entro(result);
    for(double i=(angleStart+1); i<=angleEnd;i+=step)
    {
        printf("the angle is : %f\n", i);
        result= ManualRot(image_surface, i);
        update_surface(screen_surface,result);
        entro = Entro(result);
        printf("Entropie is : %f\n", entro);
        anglePrefinal = entro > angleEntro ? i : anglePrefinal;
        angleEntro=(fmax(angleEntro, entro));
    }
    printf("the anglePrefinal is here in case u : %f\n", anglePrefinal);
    result= ManualRot(image_surface, anglePrefinal);
    update_surface(screen_surface,result);
    double stepf=0.1;
    angleFinal=anglePrefinal;

    for(double i=(angleFinal-(step/2)); i<=(angleFinal+(step/2));i+=stepf)
    {
        printf("the angle %f\n", i);
        result= ManualRot(image_surface, i);
        update_surface(screen_surface,result);
        entro = Entro(result);
        angleFinal = entro > angleEntro ? i : angleFinal;
        angleEntro=(fmax(angleEntro, entro));
    }

    return angleFinal;
}

// int main()
// {
//     SDL_Surface* image_surface;
//     SDL_Surface* screen_surface;
//     SDL_Surface* surface_image;
//     init_sdl();
//
//     image_surface = load_image("loremipsum.bmp");
//     screen_surface = display_image(image_surface);
//     wait_for_keypressed();
//
//     surface_image = ManualRotation(image_surface, 0);
//     screen_surface = display_image(surface_image);
//     update_surface(screen_surface,surface_image);
//     double angle = getSkewAngle(surface_image,screen_surface);
//     printf("%f\n", angle);
//     wait_for_keypressed();
//
//     SDL_FreeSurface(image_surface);
//     SDL_FreeSurface(screen_surface);
//     SDL_FreeSurface(surface_image);
//
//     return 0;
//
//
// }
