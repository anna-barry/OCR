#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"
#include "../../Tools/matrix.h"

// by marie maturana and geoffroy du mesnil du buisson
//  15/10 -> 24/10
// grayscale and binarisation with the otsu method
// matrix creation


Matrix matrix_grayscale_to_binar(Matrix M, int threshold)
{
	Matrix THEmatrix = newMatrix(M.height,M.width);

	for (int h = 0; h < M.width; h++)
	{
		for (int w = 0; w < M.height; w++)
		{
			matrix_put(THEmatrix, w, h, matrix_get(M, w, h) < threshold);
		}
	}

	return THEmatrix;
}

Matrix surface_to_matrix_grayscale(SDL_Surface *img)
{
  int width = img->w;
  int height = img->h;
  
  Matrix M = newMatrix(height, width);
 
  for (int h = 0; h < M.width; h++)
    {
      for (int w = 0; w < M.height; w++)
	{
	  Uint8 r, g, b;
	  Uint32 pixel = get_pixel(img, w, h);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  Uint8 valeur = 0.3*r + 0.59*g + 0.11*b;
	  matrix_put(M, w, h, valeur);
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

int max(int a, int b)
{
	if (a < b) return b;
	return a;
}

int histogram_max(Matrix histogram)
{
	int maxi = 0;

	for (int i = 0; i < 256; i++)
	{
		maxi = max(maxi, matrix_get(histogram, i, 0));
	}

	return maxi;
}


//Otsu's algorithm, calculate the optimal threshold
int otsu(Matrix m)
{
	Matrix histogram = create_histogram(m);

	int total_pixels = m.width * m.height;
	int total_weight = 0;
	for (int i = 0; i < 256; i++)
		total_weight += i * matrix_get(histogram, i, 0);

	int foreground_weight = 0;
	int background_weight = total_weight;
	int foreground_pixels = 0;
	int background_pixels = total_pixels;
	float variance_max = 0;
	int threshold = 0;

	int i = 0;
	while (!matrix_get(histogram, i, 0)) i++;
	while (i < 255 && background_pixels > 0)
	{
		int pixels = matrix_get(histogram, i, 0);
		if (pixels != 0)
		{
			int weight = i * pixels;
			foreground_pixels += pixels;
			background_pixels -= pixels;
			foreground_weight += weight;
			background_weight -= weight;

			float average_foreground = (float) foreground_weight/\
															foreground_pixels;
			float average_background = (float) background_weight/\
															background_pixels;
			float average_diff = average_foreground - average_background;

			float variance = average_diff * average_diff * foreground_pixels *\
						 background_pixels;

			if (variance > variance_max)
			{
				variance_max = variance;
				threshold = i;
			}
		}
		i++;
	}

	freeMatrix(histogram);

	return threshold;
}

int matToImg(Matrix M, char *str){
  
  SDL_Surface* img;

  Uint32 pixel;

  init_sdl();

  img = SDL_CreateRGBSurface(0, M.width, M.height, 32, 0, 0, 0, 0);

  for (int i=0; i<M.width; i++){
    for (int j=0; j<M.height; j++){

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
