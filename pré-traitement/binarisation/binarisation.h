#ifndef BINARISATION_H
#define BINARISATION_H

//otsu threshold calculation function
Matrix matrix_grayscale_to_binar(Matrix M, int threshold); 

Matrix surface_to_matrix_grayscale(SDL_Surface *img);

Matrix create_histogram(Matrix M);

int max(int a, int b);

int histogram_max(Matrix histogram);

int otsu(Matrix m);

int matToImg(Matrix M, char *str);

#endif
