#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/help4display.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/matrix.h"
#include "../../Tools/tree.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include "../rlsa.h"
#include "../segmentationXY.h"

int main()
{
    printf("okkkkk\n");
    SDL_Surface* img;
    printf("okkkkk\n");
    init_sdl();


    
//load image in bmp
    printf("okkkkk\n");
    img = SDL_LoadBMP("loremipsum.bmp");
    
    printf("okkkkk\n");
    Matrix matrice1 = surface_to_matrix_grayscale(img); //matrice contenant les valeurs de gris des pixels
    printf("okkkkk\n");
    int seuil = otsu(img); // calcul du seuil
    printf("okkkkk\n");
    Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ; //matrice binaire finale
    
    //matToImg(matricef, "new"); // transforme la matrice en image
    printf("okkkkk\n");
    beginSeg(matricef);
    
    //matToImg(m, "test_soutenance");

    SDL_FreeSurface(img);


return 0;

}
