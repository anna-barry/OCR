
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../../Tools/pixel_operations.h"
#include "../../../Tools/image_operations.h"
#include "../../../Tools/matrix.h"
#include "../binarisation.h"

// by marie maturana and geoffroy du mesnil du buisson
//  15/10 -> 24/10
// grayscale and binarisation with the otsu method
// matrix creation


int main()
{

    init_sdl();
    
    SDL_Surface* img = load_image("loremipsum.bmp");
  
    Matrix matrice1 = surface_to_matrix_grayscale(img); 

    int seuil = otsu(img); 

    Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ;

    matToImg(matricef, "new");

    return 0; 
    
}
