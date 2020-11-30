#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/matrix.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include "../rlsa.h"

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    //load image in bmp

    image_surface = SDL_LoadBMP("loremipsum.bmp");

    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    int width = image_surface->w;

    int height = image_surface->h;


    //grayscale
    Uint8 r,v,b;

    for (int x = 0; x < width; x++){
         for (int y = 0; y < height; y++){

	   // have pixel and rvb

	         Uint32 pixel = get_pixel(image_surface, x, y);

	         SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);

		 // calculation of grayscale

	         Uint8 valeur_pixel = 0.3*r + 0.59*v + 0.11*b;

	         Uint32 pixel1 = SDL_MapRGB(image_surface->format, valeur_pixel, valeur_pixel, valeur_pixel);

	         put_pixel(image_surface,x,y,pixel1);
	       }
	  }

    //change image

    update_surface(screen_surface,image_surface);

    //calculation of number of pixel for
    //each level of 0 to 255

    float histo[256];

    for (int x = 0; x < width; x++){
	    for (int y = 0; y < height; y++){

	      Uint32 pixel = get_pixel(image_surface, x, y);
	      SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);

	      histo[r]+=1;
	    }
    }

    //calculation of otsu level

    float seuil = compteOtsuseuil(histo, width, height );

    Matrix derhistoMat = newMatrix(height, width);

    wait_for_keypressed();

    //put in black and white with the threshold

    for (int i = 0; i < derhistoMat.width; i++){
         for (int j = 0; j < derhistoMat.height; j++){

	         Uint32 pixel = get_pixel(image_surface, i, j);
	         SDL_GetRGB(pixel, image_surface->format, &r, &v,&b);

	         if( r <= (int)seuil ){

		         Uint32 pixel1 = SDL_MapRGB(image_surface->format, 0, 0, 0);
		         put_pixel(image_surface,i,j,pixel1);

             derhistoMat.matrix[i*derhistoMat.width+j] = 1;

	         }
	         else{

		         Uint32 pixel1 = SDL_MapRGB(image_surface->format, 255, 255, 255);
		         put_pixel(image_surface,i,j,pixel1);

		         derhistoMat.matrix[i*derhistoMat.width+j] = 0;
	         }
	      }
    }
    //Matrix derhistoMat = imgToMat(image_surface);

    //put the image in white and black
    //to show in the firt soutenance if the binarisation is done

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    Matrix m = rlsa(derhistoMat,200,1000);

    matToImg(m, "test_soutenance");

    SDL_FreeSurface(image_surface);

    SDL_FreeSurface(screen_surface);

    return 0;
}
