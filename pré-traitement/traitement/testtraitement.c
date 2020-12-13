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


int main()
{


    init_sdl();
    
    SDL_Surface* img = load_image("lorem.bmp");
    
    Matrix f= surface_to_matrix_grayscale(img);
    
    //int seuil = otsu(img);

<<<<<<< HEAD
    image_surface = load_image("loremipsum.bmp");
    screen_surface = display_image(image_surface);
    Matrix m= surface_to_matrix_grayscale(image_surface);
    printf("matrix to grayscale [ok] \n");
    matToImg(smooth(m),"smooth");
    update_surface(screen_surface, image_surface);
    printf("update surface1 [ok] \n ");
    matToImg(contrast(m),"contrast");
    update_surface(screen_surface, image_surface);
    printf("update surface2 [ok] \n ");
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    printf("free all [ok] \n");
=======
    //Matrix f =  matrix_grayscale_to_binar(m, seuil) ;

    
    matToImgGRAY(f,"original");
    
    Matrix c=contrast(f);
    matToImgGRAY(c,"contrast");
    
    Matrix s=smooth(f);
    matToImgGRAY(s,"smooth");
    
    
    /*Matrix c=contrast(matricef);
    matToImg(c,"contrast");*/

>>>>>>> dbd8b9380455a3f2de82586c9a7c9bf7a4651d25
    return 0;


}



