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

    SDL_Surface* img = load_image("../testresize/Img/theImageForResize.bmp");

    Matrix matrice1 = surface_to_matrix_grayscale(img);

    int seuil = otsu(img);

    Matrix matimage =  matrix_grayscale_to_binar(matrice1, seuil) ;

    Matrix shrunk = cutMatrix(matimage,0,0,20,20);

    matToImg(shrunk, "the original mat.bmp");

    Matrix theResizeMatrix = resizeMatrix(shrunk, 10);

    matToImg(theResizeMatrix, "The new one.bmp");

    SDL_FreeSurface(img);

    return 0;
}
