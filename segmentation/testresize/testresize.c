#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"
#include "../../Tools/matrix.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include "../resizeMatrix.h"

int main()
{


    init_sdl();



    //load image in bmp

    SDL_Surface* img = load_image("lorem.bmp");

    Matrix matrice1 = surface_to_matrix_grayscale(img);

    int seuil = otsu(img);

    Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ;

    // Matrix s = rlsa(matricef,250,1200);
    //
    // Matrix m = rlsa(s,400,200);
    //
    // matToImg(m, "line");
    //
    // Matrix p = rlsa(matricef,250,1200);
    //
    // Matrix q = rlsa(p,400,1300);

    matToImg(q, "para");

    SDL_FreeSurface(img);

    return 0;
}
