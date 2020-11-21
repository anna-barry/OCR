#ifndef BINARISATION_H
#define BINARISATION_H

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);
float compteOtsuseuil(float hist[],int width, int height );
int matToImg(Matrix M, char *str);



#endif
