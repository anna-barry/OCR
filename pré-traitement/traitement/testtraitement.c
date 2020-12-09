#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../../Tools/matrix.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/help4display.h"
#include "traitement.h"
#include "../binarisation/binarisation.h"

int main()
{

    init_sdl();
    
    SDL_Surface* img = load_image("loremipsum.bmp");
    
    Matrix m= surface_to_matrix_grayscale(img);
    
    int seuil = otsu(img);

    Matrix matricef =  matrix_grayscale_to_binar(m, seuil) ;

    
    matToImg(matricef,"original");
    
    matToImg(smooth(matricef),"smooth");
    
    matToImg(contrast(matricef),"contrast");

    return 0;


}

