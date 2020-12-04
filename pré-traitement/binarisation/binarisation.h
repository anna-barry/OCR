#ifndef BINARISATION_H
#define BINARISATION_H

//otsu threshold calculation function
Matrix matrix_grayscale_to_binar(Matrix M, int threshold); 

Matrix surface_to_matrix_grayscale(SDL_Surface *img);

int otsu(SDL_Surface* img);

int matToImg(Matrix M, char *str);

#endif
