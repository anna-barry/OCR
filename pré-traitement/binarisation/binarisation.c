#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/matrix.h"
#include "../../Tools/image_operations.h"
#include "binarisation.h"

// by marie maturana and geoffroy du mesnil du buisson
//  15/10 -> 24/10
// grayscale and binarisation with the otsu method
// matrix creation


Matrix matrix_grayscale_to_binar(Matrix M, int seuil)
{
  Matrix THEmatrix = newMatrix(M.height,M.width);

  for (int h = 0; h < M.height; h++)
    {
      for (int w = 0; w < M.width; w++)
	{

	  if( M.matrix[h*M.width+w] < seuil )
	    {

	      THEmatrix.matrix[h*THEmatrix.width+w] = 1;
	    }

	  else
	    {

	      THEmatrix.matrix[h*THEmatrix.width+w] = 0;
	    }
	}

    }

  return THEmatrix;
}



Matrix surface_to_matrix_grayscale(SDL_Surface *img)
{
  int width = img->w;
  int height = img->h;

  Matrix M = newMatrix(height, width);

  for (int h = 0; h < M.height; h++)
    {
      for (int w = 0; w < M.width; w++)
	{
	  Uint8 r, g, b;
	  Uint32 pixel = get_pixel(img, w, h);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  Uint8 valeur = 0.3*r + 0.59*g + 0.11*b;
	  M.matrix[h*M.width+w] = valeur;
	}
    }

  return M;
}


Matrix create_histogram(Matrix M)
{
	Matrix histogram = newMatrix(256, 1);

	for (int h = 0; h < M.height; h++)
	{
		for (int w = 0; w < M.width; w++)
		{
			histogram.matrix[h*M.width+w] += 1;
		}
	}

	return histogram;
}


//Otsu's algorithm, calculate the optimal threshold
int otsu(SDL_Surface* img)
{

  int width = img->w;
  int height = img->h;
  float hist[256];

  for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
	{
	  Uint8 r, v, b;
	  Uint32 pixel = get_pixel(img, x, y);
	  SDL_GetRGB(pixel, img->format, &r, &v, &b);
	  hist[r]+=1;
	}
    }

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

  return t-20;
}

int matToImg(Matrix M, char *str)
{

  SDL_Surface* img;

  Uint32 pixel;

  init_sdl();

  img = SDL_CreateRGBSurface(0, M.width, M.height, 32, 0, 0, 0, 0);

  for (int h=0; h<M.height; h++){
    for (int w=0; w<M.width; w++){

      if (M.matrix[h*M.width+w]==1)
	{

        pixel = SDL_MapRGB(img->format, 0, 0, 0);
	}
      else
	{

        pixel = SDL_MapRGB(img->format, 255, 255, 255);
      }

      put_pixel(img,w ,h, pixel);
    }
  }

  SDL_SaveBMP(img, str);

  SDL_FreeSurface(img);

  return 0;
}
