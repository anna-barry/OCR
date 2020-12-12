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

    Matrix matricechar =  matrix_grayscale_to_binar(matrice1, seuil) ;

    //Matrix theResizeMatrix = resizeMatrix(matricechar, 32);

    matToImg(matricechar, "oh boy");

    SDL_FreeSurface(img);

    return 0;
}
