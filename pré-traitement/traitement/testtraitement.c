#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../../Tools/matrix.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
#include "traitement.h"
#include "../binarisation/binarisation.h"

int matToImgGRAY(Matrix M, char *str)
{

  SDL_Surface* img;

  Uint32 pixel;

  init_sdl();
    int pix=0;

  img = SDL_CreateRGBSurface(0, M.width, M.height, 32, 0, 0, 0, 0);

  for (int h=0; h<M.height; h++){
    for (int w=0; w<M.width; w++){

        pix= M.matrix[h*M.width+w];
    
        pixel = SDL_MapRGB(img->format, pix, pix, pix);
      
        put_pixel(img,w ,h, pixel);
    }
  }

  SDL_SaveBMP(img, str);

  SDL_FreeSurface(img);

  return 0;
}


void traitement(char *image)
{
  SDL_Surface* img;
  init_sdl();

  img = SDL_LoadBMP(image);
    
  Matrix f= surface_to_matrix_grayscale(img);
        
  Matrix c=contrast(f);
  matToImgGRAY(c,"contrast.bmp");
    
  Matrix s=smooth(f);
  matToImgGRAY(s,"smooth.bmp");


}



int main()
{


    init_sdl();
    
    SDL_Surface* img = load_image("loremipsum.bmp");
    
    Matrix f= surface_to_matrix_grayscale(img);
    
    //int seuil = otsu(img);
    //Matrix f =  matrix_grayscale_to_binar(m, seuil) ;
    
    matToImgGRAY(f,"original");
    
    Matrix s=smooth(f);
    matToImgGRAY(s,"smooth");
    
    Matrix c=contrast(f);
    matToImgGRAY(c,"contrast");
    
    
    /*Matrix c=contrast(matricef);
    matToImg(c,"contrast");*/
    return 0;


}
