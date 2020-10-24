#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Tools/matrix.h"
#include "../binarisation/binarisation.c"
#include "../segmentation/rlsa.h"

// by marie.maturana
// 24/10
// test the function of binarisation and rlsa
// return the image of rlsa (include binarisation)

int main()
{

	//charge the image
	SDL_SURFACE* image_surface = SDL_LoadBMP("loremipsum.bmp");

	//creation of the matrix 01
	Matrix matrix1 = imgToMat(image_surface);

	//creation of the matrix after rlsa
	Matrix dernière = rlsa(matrix1, 30, 30);

	str image;
	
	//transform and return the matrix in image
	return matToImg(dernière, image); 

	return 0;
}
