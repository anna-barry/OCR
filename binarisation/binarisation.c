#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "../Tools/matrix.h"

// by marie maturana and geoffroy du mesnil du buisson
//  15/10 -> 24/10
// grayscale and binarisation with the otsu method
// matrix creation


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
    img = IMG_Load(path);
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

//otsu threshold calculation function 
float compteOtsuseuil(float hist[],int width, int height )
{

  int nombrep = width * height; //number of pixel
  int t = 0; //threshold

  float w1 = 0; //sum of probability 1
  float w2 = 0;//sum of probability 2
    int q1 = 0;
    int q2 = 0;
    float max = 0; //max variance

    for (int i = 0; i <= 255; i++)
    {
      w1 += i * ((int)hist[i]);
    }

    for (int i = 0 ; i <= 255 ; i++)
      {
      q1 += hist[i];
      q2 = nombrep - q1;


      w2 += (float) (i * ((int)hist[i]));
      float m1 = w2 / q1; //average calculation 1
      float m2 = (w1 - w2) / q2; //average calculation 2


      //variance calculation for t
      float res = (float) q1 * (float) q2 * (m1 - m2) * (m1 - m2);

      //choose the max
      if (res > max)
      {
        max = res;
        t = i;
      }

      }

    return t;
}
//geoffroy
//transform the image to matrix
//use the binarisation method (otsu) 
Matrix imgToMat(SDL_Surface* img){
  int width = img->w;

  int height = img->h;

  Uint8 r,v,b;

  for (int x = 0; x < width; x++){
       for (int y = 0; y < height; y++){

         Uint32 pixel = get_pixel(img, x, y);

         SDL_GetRGB(pixel, img->format, &r, &v, &b);

         Uint8 valeur_pixel = 0.3*r + 0.59*v + 0.11*b;

         Uint32 pixel1 = SDL_MapRGB(img->format, valeur_pixel, valeur_pixel, valeur_pixel);

         put_pixel(img,x,y,pixel1);
       }
  }

  float histo[256];

  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){

      Uint32 pixel = get_pixel(img, x, y);
      SDL_GetRGB(pixel, img->format, &r, &v, &b);

      histo[r]+=1;
    }
  }

  float seuil = compteOtsuseuil(histo, width, height );

  Matrix derhistoMat = newMatrix(height, width);

  for (int i = 0; i < derhistoMat.width; i++){
       for (int j = 0; j < derhistoMat.height; j++){

         Uint32 pixel = get_pixel(img, i, j);
         SDL_GetRGB(pixel, img->format, &r, &v,&b);

         if( r <= (int)seuil ){

           Uint32 pixel1 = SDL_MapRGB(img->format, 255, 255, 255);
           put_pixel(img,i,j,pixel1);

           derhistoMat.matrix[i*derhistoMat.width+j] = 0; 

         }
         else{

           Uint32 pixel1 = SDL_MapRGB(img->format, 0, 0, 0);
           put_pixel(img,i,j,pixel1);

           derhistoMat.matrix[i*derhistoMat.width+j] = 1;
         }
      }
  }
  return derhistoMat;//return the matrix derhistoMat

  SDL_FreeSurface(img);
}

//geoffroy
//transform the matrix to image
//use the binarisation method (otsu) 

int matToImg(Matrix M, char *str){//geoffroy
  SDL_Surface* img;

  Uint32 pixel;

  init_sdl();

  img = SDL_CreateRGBSurface(0, M.width, M.height, 32, 0, 0, 0, 0);

  for (int i=0; i<M.height; i++){
    for (int j=0; j<M.width; j++){

      if (M.matrix[i*M.width+j]==1){

        pixel = SDL_MapRGB(img->format, 0, 0, 0);
      }
      else{

        pixel = SDL_MapRGB(img->format, 255, 255, 255);
      }

      put_pixel(img, i, j, pixel);
    }
  }

  SDL_SaveBMP(img, str);

  SDL_FreeSurface(img);

  return 0;
}

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

		         Uint32 pixel1 = SDL_MapRGB(image_surface->format, 255, 255, 255);
		         put_pixel(image_surface,i,j,pixel1);

             derhistoMat.matrix[i*derhistoMat.width+j] = 0; 

	         }
	         else{

		         Uint32 pixel1 = SDL_MapRGB(image_surface->format, 0, 0, 0);
		         put_pixel(image_surface,i,j,pixel1);

		         derhistoMat.matrix[i*derhistoMat.width+j] = 1; 
	         }
	      }
    }

    //put the image in white and black
    //to show in the firt soutenance if the binarisation is done

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);

    SDL_FreeSurface(screen_surface);

    return 0;
}
