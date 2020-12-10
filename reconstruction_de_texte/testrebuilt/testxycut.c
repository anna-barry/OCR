#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/help4display.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/matrix.h"
#include "../../Tools/tree.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include "../../segmentation/rlsa.h"
#include "../../segmentation/segmentationXY.h"
#include "../rebuilt.h"

int main()
{
    SDL_Surface* img;
    init_sdl();



//load image in bmp
    img = SDL_LoadBMP("lorem.bmp");

    Matrix matrice1 = surface_to_matrix_grayscale(img); //matrice contenant les valeurs de gris des pixels

    int seuil = otsu(img); // calcul du seuil

    Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ; //matrice binaire finale

    //matToImg(matricef, "new"); // transforme la matrice en image
    Tree *tree = beginSeg(matricef);

    char *theMFTexte = textBuider(tree, "chicoungounia");

    printf("%s\n", theMFTexte);

    //free(theMFTexte);

    free(tree);

    //matToImg(m, "test_soutenance");

    SDL_FreeSurface(img);


return 0;

}
