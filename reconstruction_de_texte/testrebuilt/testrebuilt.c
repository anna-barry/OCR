#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/help4display.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/matrix.h"
#include "../../Tools/tree.h"
#include "../../pré-traitement/binarisation/binarisation.h"
//#include "../../segmentation/rlsa.h"
//#include "../../segmentation/segmentationXY.h"
#include "../rebuilt.h"

int main()
{
    // SDL_Surface* img;
    // init_sdl();
    //
    // //load image in bmp
    // //here is the path you should modify if you want to get an other image :
    // //                \           /
    // //                \          /
    // img = SDL_LoadBMP("lorem.bmp");
    //
    // Matrix matrice1 = surface_to_matrix_grayscale(img); //matrice contenant les valeurs de gris des pixels
    //
    // int seuil = otsu(img); // calcul du seuil
    //
    // Matrix matricef =  matrix_grayscale_to_binar(matrice1, seuil) ; //matrice binaire finale
    //
    // Tree *tree = beginSeg(matricef);
    //
    int arr[] = {-3,-2,-1,97};

    Tree *tree = createAtree(arr, 4);

    dfs_printer(tree);//print the tree to make sure the tree is corectly done.

    char *theTexte = textBuider(tree, "Your text is : ");

    printf("%s\n", theTexte);

    free(theTexte);

    //free(tree);

    freeTree(tree);
    //SDL_FreeSurface(img);


return 0;

}
