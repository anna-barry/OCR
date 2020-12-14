#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Tools/help4display.h"
#include "../Tools/image_operations.h"
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "../pré-traitement/binarisation/binarisation.h"
#include "../segmentation/rlsa.h"
#include "../segmentation/testxycut/segmentationXYtest.h"

void MakeOCR ()
{
  SDL_Surface* img;
  init_sdl();

  img = SDL_LoadBMP("/Users/marie/Documents/OCR/pré-traitement/binarisation/test/lorem.bmp");
    
  Matrix matrice1 = surface_to_matrix_grayscale(img); //matrice contenant les valeurs de gris des pixels
    
  int seuil = otsu(img); // calcul du seuil
    
  Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ; //matrice binaire finale
    
  beginSeg(matricef);
    

  SDL_FreeSurface(img);

}

