#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Tools/help4display.h"
#include "../Tools/image_operations.h"
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "../pré-traitement/Rotations/rotationAUTO.h"
#include "../pré-traitement/Rotations/rotationMAN.h"
#include "../pré-traitement/binarisation/binarisation.h"
#include "../segmentation/rlsa.h"
#include "../segmentation/testxycut/segmentationXYtest.h"

void MakeOCR (char *txt, char *image)
{
  SDL_Surface* img;
  init_sdl();
  img = SDL_LoadBMP(image);
    
   printf("after init \n"); 
    double skew=0;
  ManualRotation(img ,skew);
  printf("after manual rotation \n");
  Matrix matrice1 = surface_to_matrix_grayscale(img); //matrice contenant les valeurs de gris des pixels
  printf("grayscale \n");
  int seuil = otsu(img); // calcul du seuil
  Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ; //matrice binaire finale
  printf("before seg \n");
  beginSeg(matricef,txt);
    
  printf("after seg \n");
  SDL_FreeSurface(img);


}

