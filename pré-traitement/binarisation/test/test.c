
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../../Tools/pixel_operations.h"
#include "../../../Tools/image_operations.h"
#include "../../../Tools/matrix.h"
#include "../binarisation.h"

// by marie maturana 
// test for grayscale and binarisation with the otsu method


int main()
{

    init_sdl();
    
    SDL_Surface* img = load_image("loremipsum.bmp");
  
    Matrix matrice = surface_to_matrix_grayscale(img); 

    int seuil = otsu(img); 

    Matrix matricefi =  matrix_grayscale_to_binar(matrice, seuil) ;

    matToImg(matricefi, "new");

    ///////////////////////////////////////////////////////////////////

    SDL_Surface* imga = load_image("lorem.bmp");
  
    Matrix matrice1 = surface_to_matrix_grayscale(imga); 

    int seuil1 = otsu(imga); 

    Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil1) ;

    matToImg(matricef, "new1");

    ////////////////////////////////////////////////////////////////////

    SDL_Surface* img2 = load_image("gafa-stop.bmp");
  
    Matrix matricee = surface_to_matrix_grayscale(img2); 

    int seuill = otsu(img2); 

    Matrix matricefii =  matrix_grayscale_to_binar(matricee, seuill) ;

    matToImg(matricefii, "new2");



    return 0; 
    
}
