#include <err.h>
#include "tree.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "../Tools/matrix.h"
#include <stdio.h>
#include <stdlib.h>

// by marie maturana and geoffroy du mesnil du buisson
//  15/10 -> 24/10
// grayscale and binarisation with the otsu method
// matrix creation

double myabs(double x){
  /*
  description :
  return the absolute value of a double

  parameters :
  double x : the value we want to be positive

  dates/authors :
  23/10
  geoffroy du mesnil du buisson

  */
  x = x < 0 ? -x : x;
  return x;
}

double myintpart(double x){

  /*
  description :
  return the integer part of a double but still a double

  parameters :
  double x : the value we want the integer part of

  dates/authors :
  23/10
  geoffroy du mesnil du buisson

  */

  double i = 0;

  while (!(i <= x && i+1>=x)){

    i += 1 ;
  }

  return i;
}





struct Tuple{
  int top;
  int bottom;
};
//initialize the Tuple struct to save two values in a one value

Matrix bilinearInterpolation(Matrix M, int top, int bot, int size){
  /*
   * General description:
    Function that takes a matrix and returns a new one with the right size while keeping all its content
    --> zooms in the matrix

    Parameters:
    _ Matrix M: Matrix which we'll zoom
    _ int top: the top of the matrix
    _ int bot: bottom of the matrix
    _ int size: size of the matrix

    dates/authors :
    24/10
    geoffroy du mesnil du buisson

  */

  int newSizeH, newSizeW;
  double x, y, x1, y1, x2, y2, x3, y3;
  double delta1, delta2, delta3, delta4;
  double voisin11, voisin22, voisin21,voisin12;
  double somme;

  M = cutMatrix(M, top, 0, bot-top+1, M.width); // cuts said matrix to fit rightly -> cut on the edges

  if (M.height > M.width){ // checking if the new Matrix is proportional compared to the old one

    newSizeH = size;
    newSizeW = (int) (M.width * newSizeH/(double)M.height);
     }
  else{

    newSizeW = size;
    newSizeH = (int) (M.height * newSizeW/(double)M.width);
  }

  Matrix sizeMat = newMatrix(newSizeH, newSizeW);   //new matrix of the same size

  // Bilinear Interpolation
  // For each of its 4 pixel neighbours calculate the sum of product of their differences
  for (int i = 0 ; i < sizeMat.height ; i++){
    for (int j = 0 ; j < sizeMat.width ; j++){

      x = j * M.width/sizeMat.width;
      y = i * M.height/sizeMat.height;

      // Returns integer part to get the smallest neighbour

      x1 = myintpart(x);
      y1 = myintpart(y);

      x3 = x1+1; //+ 1 to get the superior neighbour
      y3 = y1+1;

      if (x1 == M.width-1){ // getting the right neighbour
        x2 = M.width-1;
      }
      else{
x2 = x3;
      }

      if (y1 == M.width-1){
        y2 = M.width-1;
      }
      else{
        y2 = y3;
      }

      // Returns absolute number of these differences
      delta1 = myabs((x3-x)*(y3-y));
      delta2 = myabs((x3-x)*(y-y1));
      delta3 = myabs((x-x1)*(y3-y));
      delta4 = myabs((x-x1)*(y-y1));

      // Multiply delta x value of the neighbour
      voisin11 = M.matrix[(int) (y1*M.width+x1)] * delta1;
      voisin12 = M.matrix[(int) (y1*M.width+x2)] * delta2;
      voisin21 = M.matrix[(int) (y2*M.width+x1)] * delta3;
      voisin22 = M.matrix[(int) (y2*M.width+x2)] * delta4;

      // Sum of neighbours
      somme = voisin11 + voisin22 + voisin21 + voisin12;

      //if sum>0,5 then value in new matrix is 1, else 0

      if(somme > 0.5){

        sizeMat.matrix[i*sizeMat.width+j] = 1;
      }
      else{

        sizeMat.matrix[i*sizeMat.width+j] = 0;
      }
    }
  }
  return sizeMat;
}

struct Tuple getCornerMatrix(Matrix M){
  /*
  description :
  function that return the angles of the charactere we want to resize

  parameters :
  Matrix M : the matrix of a charactere


  dates/authors :
  21/10
  geoffroy du mesnil du buisson

  */
  struct Tuple tuple;

  tuple.top =-1;//intitalization of boolean telling if the angles have been found
  tuple.bottom =-1;

  for (int i = 0; (tuple.top == -1 || tuple.bottom == -1) && i < M.height; i++) { //the loops continue while the both index have not been
    for (size_t j = 0; (tuple.top == -1 || tuple.bottom == -1) && j < M.width; j++) {//founded or we arrive at the end of the matrix

      if ((M.matrix[i*M.width+j] == 1)&&(tuple.top == -1)){
        tuple.top = i; //if the angle had not been finded top take the index of the angle
      }

      if ((M.matrix[(M.height-1-i)*M.width+j] == 1)&&(tuple.bottom == -1)) {

          tuple.bottom = M.height-1-i; //if the angle had not been finded bottom take the index of the angle
      }
    }
  }

  return tuple; //return the tuble with both the top and the bottom vulue
}

Matrix resizeMatrix(Matrix matrixChar, int size){
  /*
  description genral :

  Fonction qui prend une matrice d'un charachtere et qui le met à une taille
  commune pour tout les chars sans deformer le charachtere

  Les parametres :

  Matrix M : Matrice sur la quelle nous allons appliquer le recadrage
  int size : la taille que nous voulons avoir pour la nouvelle mtrice


  Les dates de modifications :

  */
  /*
  description :
  function that a matrice of a char and resize it to a commun size that will be used
  for all the char without changing the shape of the char

  parameters :
  Matrix M : matrix that we want to resize
  int size : the comun size we want for all the matrix


  dates/authors :
  21/10
  geoffroy du mesnil du buisson

  */

  Matrix resized = newMatrix(size,size); //initialize a matrix in the good size

  struct Tuple tuple;

  tuple = getCornerMatrix(matrixChar);

  int top = tuple.top;//top corner
  int bot = tuple.bottom;//botom corner
if (top == -1){//there is no char, the matrix is full of 0

    return resized;
  }
  else{//there is a char so we put in the good size

    Matrix sizeMat = bilinearInterpolation(matrixChar,top, bot, size);

    for (int i = 0; i < sizeMat.height; i++) {
      for (size_t j = 0; j < sizeMat.width; j++) {

        resized.matrix[i*resized.width+j] = sizeMat.matrix[i*sizeMat.width+j];
      }
    }

    freeMatrix(sizeMat);
    return resized; //return the good sized matrix
  }
}


void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);

//otsu threshold calculation function
float compteOtsuseuil(float hist[],int width, int height )
{

  int nombrep = width * height; //number of pixel
  int t = 0; //threshold

  float w1 = 0; //sum of probability 1
  float w2 = 0;//sum of probability 2
    int q1 = 0;
    int q2 = 0;
    float max = 0; //max variance

    for (int i = 0; i <= 255; i++)
    {
      w1 += i * ((int)hist[i]);
    }

    for (int i = 0 ; i <= 255 ; i++)
      {
      q1 += hist[i];
      q2 = nombrep - q1;


      w2 += (float) (i * ((int)hist[i]));
      float m1 = w2 / q1; //average calculation 1
      float m2 = (w1 - w2) / q2; //average calculation 2


      //variance calculation for t
      float res = (float) q1 * (float) q2 * (m1 - m2) * (m1 - m2);

      //choose the max
      if (res > max)
      {
        max = res;
        t = i;
      }

      }

    return t;
}
//geoffroy
//transform the image to matrix
//use the binarisation method (otsu)
Matrix imgToMat(SDL_Surface* img){
  int width = img->w;

  int height = img->h;

  Uint8 r,v,b;

  for (int x = 0; x < width; x++){
       for (int y = 0; y < height; y++){

         Uint32 pixel = get_pixel(img, x, y);

         SDL_GetRGB(pixel, img->format, &r, &v, &b);

         Uint8 valeur_pixel = 0.3*r + 0.59*v + 0.11*b;

         Uint32 pixel1 = SDL_MapRGB(img->format, valeur_pixel, valeur_pixel, valeur_pixel);

         put_pixel(img,x,y,pixel1);
       }
  }

  float histo[256];

  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){

      Uint32 pixel = get_pixel(img, x, y);
      SDL_GetRGB(pixel, img->format, &r, &v, &b);

      histo[r]+=1;
    }
  }

  float seuil = compteOtsuseuil(histo, width, height );

  Matrix derhistoMat = newMatrix(height, width);

  for (int i = 0; i < derhistoMat.width; i++){
       for (int j = 0; j < derhistoMat.height; j++){

         Uint32 pixel = get_pixel(img, i, j);
         SDL_GetRGB(pixel, img->format, &r, &v,&b);

         if( r <= (int)seuil ){

           Uint32 pixel1 = SDL_MapRGB(img->format, 0, 0, 0);
           put_pixel(img,i,j,pixel1);

           derhistoMat.matrix[i*derhistoMat.width+j] = 1;

         }
         else{

           Uint32 pixel1 = SDL_MapRGB(img->format, 255,255, 255);
           put_pixel(img,i,j,pixel1);

           derhistoMat.matrix[i*derhistoMat.width+j] = 0;
         }
      }
  }
  return derhistoMat;//return the matrix derhistoMat

  SDL_FreeSurface(img);
}

//geoffroy
//transform the matrix to image
//use the binarisation method (otsu)

int matToImg(Matrix M, char *str){//geoffroy
  SDL_Surface* img;

  Uint32 pixel;

  init_sdl();

  img = SDL_CreateRGBSurface(0, M.width, M.height, 32, 0, 0, 0, 0);

  for (int i=0; i<M.height; i++){
    for (int j=0; j<M.width; j++){

      if (M.matrix[i*M.width+j]==1){

        pixel = SDL_MapRGB(img->format, 0, 0, 0);
      }
      else{

        pixel = SDL_MapRGB(img->format, 255, 255, 255);
      }

      put_pixel(img, i, j, pixel);
    }
  }

  SDL_SaveBMP(img, str);

  SDL_FreeSurface(img);

  return 0;
}

// void print_Matrix(Matrix M)    // Print a matrix
// {
//   int n = 0;
//     for (int i = 0 ; i < M.height ; i++)
//         {
//                 for (int j = 0 ; j < M.width ; j++){
//                   printf("%i  ,", (int)M.matrix[i*M.width+j]);
//                   n++;
//                 }
//                 printf("\n");
//         }
//
//     printf("\n");
//     printf("%i\n", n);
// }

// Matrix new_alea_Matrix(int H, int W)    // Create a new matrix init with random double
// {
//     Matrix M;
//
//         M.height = H;
//         M.width = W;
//
//         M.matrix = malloc(H*W*sizeof(double));
//         for (int i = 0 ; i < H*W ; i++)
//         {
//                 M.matrix[i] = rand() % 2;
//         }
//
//         return M;
//
// }

Matrix horizonRLSA (Matrix img, int seuil){
  /*
  description :
  function that go thru a matrix from horizontal way
  and apply to it the RLSA algorthm

  parameters :
  Matrix img : matrix where we are going to apply the RLSA algorthm
  int seuil : limite the we fix for the RLSA system


  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */


  Matrix m = copyMatrix(img);

  int nbzeros;//nubers of 0 followed

  int j;//index on the width of the matrix
  int k;//index on the nubers of 0 followed

  for (int i = 0; i < m.height ; i++) {//classic search in the matrix

    j=0;
    while (j < m.width) {

      if ((int)m.matrix[i*m.width+j]!=1){

        k=j;
        nbzeros=0;

        while (((int)m.matrix[i*m.width+k]!=1)&&(k< m.width)) {//counting the numbers of 0 followed between two 1

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){//if the numbers of 0 is lower or equal to the limite (seuil) all the 0 pass to 1

          for (int l = j; l < nbzeros+j; l++) {

            m.matrix[i*m.width+l]=1;
          }
        }
        j+=nbzeros;//we increment the index of the number of 0 we had seen
      }//end if
      j++;
    }//end while
  }
  return m;//return the matrix
}

Matrix verticRLSA (Matrix img, int seuil){
  /*
  description :
  function that go thru a matrix from vertical way
  and apply to it the RLSA algorthm

  parameters :
  Matrix img : matrix where we are going to apply the RLSA algorthm
  int seuil : limite the we fix for the RLSA system


  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */

  Matrix m = copyMatrix(img);

  int nbzeros;//nubers of 0 followed

  int y;//index on the height of the matrix
  int k;//index on the nubers of 0 followed
  for (int x = 0; x < m.width ; x++) {//vertical search in the matrix

    y=0;
    while (y < m.height) {

      if ((int)m.matrix[y*m.width+x]!=1){

        k=y;
        nbzeros=0;
        while ((int)m.matrix[k*m.width+x]!=1&&k< m.height) {//counting the numbers of 0 followed between two 1

          nbzeros++;
          k++;
        }
        if (nbzeros<=seuil){//if the numbers of 0 is lower or equal to the limite (seuil) all the 0 pass to 1

          for (int l = y; l < nbzeros+y; l++) {

            m.matrix[l*m.width+x]=1;
          }
        }
        y+=nbzeros;//we increment the index of the number of 0 we had seen
      }//end if
      y++;
    }//end while
  }
  return m;//return the matrix
}

Matrix rlsa(Matrix img, int verticSeuil, int horizonSeuil){
  /*
  description :
  return the mix of horizonRLSA and verticRLSA in a new matrix m

  parameters :
  Matrix img : the matrix of the whole image only compose with somme 0 and 1
  int verticSeuil : the limite of zero we want for the RLSA in vertical
  int horizonSeuil : the limite of zero we want for the RLSA in horizontal

  dates/authors :
  14/10
  geoffroy du mesnil du buisson

  */

  Matrix horizonMatrix = horizonRLSA(img, horizonSeuil);
  Matrix verticMatrix = verticRLSA(img, verticSeuil);

  Matrix m = andLogicMartix(horizonMatrix,verticMatrix);

  freeMatrix(horizonMatrix);
  freeMatrix(verticMatrix);

  return m;//return the new matrix
}


Matrix vertical(Matrix M)
{

/*
description :
-on this function we recon that noises and spots were treated
-traces a black column if 1 pixel is in the column
-goes along each colum, it will help to detect easily

parameters :

Matric M: the matrix of the picture

dates/authors :
17/10
marine thunet

    */
    int h_size = M.height;
    int w_size = M.width;
    int y=0;
    //Detect zone spaces
    //principle
    //if there is a black pixel-> it is a separation
    //the column becomes black

    for (int x=0; x<w_size ;x++)
    {
        y=0;
        while ((y<h_size) && (M.matrix[y*w_size + x]=!1))
        {
            y++;
        }
        if (y!=h_size)
        {
            for (int i=0; i<h_size; i++)

            {
                M.matrix[i*w_size + x]=1;
            }
        }
    }
    return M;
}


void _trycut(Matrix M, int line, Tree *T)
{
    /*
    description :

    -the function cuts vertical lines
    -adds each segmente to the tree
        -if word then level -1
        -if char then level 0

    parameters :

    Matric M: the matrix of the picture
    int line: boolean teeling us if we are cutting a line or a word
    Tree *T: the pointer to the tree that is building

    dates/authors :
    15/10
    marine thunet

    */

    //copying the og matrix
    Matrix reel = copyMatrix(M);

    int y = 0;
    int h_size = M.height;
    int w_size = M.width;


    //___________________________TO DO_____________________________________//
    //we should get the lines as thin as possible: horzontal path//
    //get the technique better: histogrammes if spots and grains left...//

    //either lines or word, so vertical exam
    //for now we assume their isn't any defaults left

    M=vertical(M);
    //black blocks matrix
    //now choose if it's cuting line or words
    //it's not made the same way

/*_____________INITIALISATION VARIABLES COMMUNES________________*/

    int previous=0; //previous pixel value

    int x=0;
    //first value of the x of  the element

    //booléens pour se repérer dans les fonctions
    int begin=0; //1 if the word has started
    int end=0;   //1 if it is the last pixel of the line

    Matrix createseg;

    int totalspace=0;//number of white pixel/separation

    //_______LINEAR CUT______________________________________________
    if (line==1)
    {
        int nbspace=-1;  //number of white pixel suite
                        //begins at -1 because it counts one more

        /*_______Detect spaces &  average of spaces_____________*/
        for (int c=0; c<w_size; c++)
        {

            if (M.matrix[c] == 0)
            {
                totalspace++;
            }
            else
            {
                if (previous==0)
                {
                    nbspace++;
                }
                previous=1;
            }
        }

        int average= totalspace/nbspace;
        //average space between word and char

        //reinitialisation
        totalspace=0;
        previous=0;

        for (int ix=0; ix<w_size; ix++)
        {
            if (ix+1==w_size)
            {
                end=1;
            }

            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //word starts
                {
                    begin=1;
                    x=ix; //word begins at x=xi here y doesn't matter
                }
                else
                {

                    if (totalspace>average || end == 1 )
                    {
                        //matrix of the word that was found
                        createseg=cutMatrix(reel,x,0,ix-totalspace,h_size);

                        Tree *Child = newTree(-1);
                        AddChild(T, Child);
                        _trycut(createseg,0,Child);

                        freeMatrix(createseg);
                        begin=0;
                    }
                }
                totalspace=0;
            }
            else
            {
                totalspace++;

            }
        }

    }
    //____________________WORD_CUTTING____________________________________

    else
    {
        int letter=0;//the code og the letter to put in the tree then
        for (int ix=0; ix<w_size; ix++)
        {

            if (ix+1==w_size)
            {
                end=1;
            }

            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //the letter starts
                {
                    begin=1;
                    x=ix; //the letter starts at the xy: x=xi
                    //xlen=1;
                }
                else
                {
                //xlen+= totalspace;

                    if ( begin==1 && end == 1 )
                    {

                        //creating a matrix for the caracter that was found
                        createseg=cutMatrix(reel,x,0,ix-totalspace,h_size);

                        createseg=resizeMatrix(createseg,30);

                        //____FINAL___________
                        //intergrate the fonction when the
                        //neural network is created

                        //for now that is how it works but useless,
                        //we'll have to send the ascii code of the char
                        //letter=ascii code;

                        Tree *Child = newTree(0);
                        AddChild(T, 0); //will be the value of the char

                        //reinitialisation
                        freeMatrix(createseg);
                        begin=0;
                    }
                }
                totalspace=0;
            }

        else
            {
                //number of space adds up
                totalspace++;
            }
        }
    }

    freeMatrix(reel);
    //return *T;
}


//__________________CUTTING HORIZONTAL BLANKS______________________________
void verticalcut(Tree *T,Matrix M,Matrix og,int horizontal,int vertical, int line);

void horizontalcut(Tree *T,Matrix M,Matrix og,int horizontal,int vertical,int line)
{
    /*
    description :

    -cuts first horizontal block founded
    -treats the block founded
    -the rest of the block is treated horizontally

    parameters :

    Tree *T : the pointer to the tree that is building
    Matric M : the matrix of the picture
    int horizontal : 2 if horizonral cuts can go further
    int vertical : 2 if vertical cuts can no go further
    int line : boolean teeling us if we are cutting a line (1) or a word (0)

    dates/authors :
    24/10
    marine thunet

    */

    int width= M.width;
    int lenght= M.height;
    int y=0;
    int x=0;
    int started=0;
    int ybeg=0;
    Matrix tocut;
    Matrix og1;
    Matrix og2;
    Matrix rest;

    if (horizontal==2 && vertical==2 && line==1)
    {
        Tree *Child = newTree(-2);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }

    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og,4,4),og,1,1,1);
    }

    while(y<lenght)
        {
            x=0;
            while(x<width && M.matrix[y*lenght+x]==0)
            {
                x++;
            }
            if (y==lenght && x==width && started==0)
            {
                horizontal=2;
            }
            if (x==width && started==1)
            {
                if (y!=lenght)
                {
                    rest=cutMatrix(M,0,y,width,lenght-y);
                    og1=cutMatrix(og,0,y,width,lenght-y);
                    horizontalcut(T,rest,og1,1,vertical,line);
                }
                if (line==0)
                {
                tocut=cutMatrix(M,0,ybeg,width,y-ybeg);
                og2=cutMatrix(og,0,ybeg,width,y-ybeg);
                verticalcut(T,tocut,og2,1,vertical,0);
                y=lenght;
                }
                if (line==1)
                {
                og2=cutMatrix(og,0,ybeg,width,lenght-y);
                Tree *Child = newTree(-2);
                AddChild(T, Child);
                _trycut(og,1,Child);
                }
            }
            else if( started==0 && x<width && M.matrix[y*lenght+x]==1)
            {
                ybeg=y;
                x=0;
                started=1;
            }
            else if (x<width && M.matrix[y*lenght+x]==1)
            {
                x=0;
            }
            y++;
        }
}


//__________________CUTTING VERTICAL BLANKS______________________________

void verticalcut(Tree *T,Matrix M,Matrix og,int horizontal,int vertical, int line)
{
    /*
    description :

    -cuts first vertical block founded
    -treats the block founed
    -the rest of the block is treated vertically

    parameters :

    Tree *T : the pointer to the tree that is building
    Matric M : the matrix of the picture
    int horizontal : 2 if horizonral cuts can go further
    int vertical : 2 if vertical cuts can no go further
    int line : boolean teeling us if we are cutting a line or a word

    dates/authors :
    24/10
    marine thunet

    */
    int width= M.width;
    int lenght= M.height;
    int y=0;
    int x=0;
    int started=0;
    int xbeg=0;
    Matrix tocut;
    Matrix og1;
    Matrix og2;
    Matrix rest;

    if (horizontal==2 && vertical==2 && line==1)
    {
        Tree *Child = newTree(-2);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }
    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og,4,4),og,1,1,1);
    }


    while(x<width)
        {
            y=0;
            while(y<lenght && M.matrix[y*lenght+x]==0)
            {
                y++;
            }
            if (y==lenght && x==width && started==0)
            {
                vertical=2;
            }
            if (y==lenght && started==1)
            {

                if (x!=width)
                {
                    rest=cutMatrix(M,xbeg,0,width-x,lenght);
                    og1=cutMatrix(og,xbeg,0,width-x,lenght);
                    horizontalcut(T,rest,og1,horizontal,vertical,line);
                }
                tocut=cutMatrix(M,x,0,x-xbeg,lenght);
                og2=cutMatrix(og,x,0,x-xbeg,lenght);
                verticalcut(T,tocut,og2,horizontal,vertical,line);
                x=width;
            }
            else if( started==0 && y<lenght && M.matrix[y*lenght+x]==1)
            {
                xbeg=x;
                y=0;
                started=1;
            }
            else if (y<lenght && M.matrix[y*lenght+x]==1)
            {
                y=0;
            }
            x++;

        }
        //return T;
}





//________________begining_________________________//


Tree *beginSeg(Matrix M)
{
    /*
    description :

    -fonction to help begin the others
    -starting the segmentation

    parameters :

    Matric M: the matrix of the picture

    dates/authors :
    24/10
    marine thunet

    */
    Tree *txt = newTree(-4);
    Matrix og= copyMatrix(M);
    M = rlsa(M,10,10);
    horizontalcut(txt,M,og,1,1,0);

    return txt;

}

void printTree(Tree T,char name[])
{
    if (T.key)
    {
        for (int i=0; T.children[i]!=NULL; i++)
        {
            //name+=i;
           prinTree(T.children[i],name+".%i",i)
        }
        
        matToImg(T.key, name);
        
    }
}

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    //load image in bmp

    image_surface = SDL_LoadBMP("loremipsum.bmp");

    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    // int width = image_surface->w;
    //
    // int height = image_surface->h;
    //
    //
    // //grayscale
    // Uint8 r,v,b;
    //
    // for (int x = 0; x < width; x++){
    //      for (int y = 0; y < height; y++){
    //
    //    // have pixel and rvb
    //
    //          Uint32 pixel = get_pixel(image_surface, x, y);
    //
    //          SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
    //
    //      // calculation of grayscale
    //
    //          Uint8 valeur_pixel = 0.3*r + 0.59*v + 0.11*b;
    //
    //          Uint32 pixel1 = SDL_MapRGB(image_surface->format, valeur_pixel, valeur_pixel, valeur_pixel);
    //
    //          put_pixel(image_surface,x,y,pixel1);
    //        }
    //   }
    //
    // //change image
    //
    // update_surface(screen_surface,image_surface);
    //
    // //calculation of number of pixel for
    // //each level of 0 to 255
    //
    // float histo[256];
    //
    // for (int x = 0; x < width; x++){
    //     for (int y = 0; y < height; y++){
    //
    //       Uint32 pixel = get_pixel(image_surface, x, y);
    //       SDL_GetRGB(pixel, image_surface->format, &r, &v, &b);
    //
    //       histo[r]+=1;
    //     }
    // }
    //
    // //calculation of otsu level
    //
    // float seuil = compteOtsuseuil(histo, width, height );
    //
    // Matrix derhistoMat = newMatrix(height, width);
    //
    //
    //
    // wait_for_keypressed();
    //
    // //put in black and white with the threshold
    //
    // for (int i = 0; i < derhistoMat.width; i++){
    //      for (int j = 0; j < derhistoMat.height; j++){
    //
    //          Uint32 pixel = get_pixel(image_surface, i, j);
    //          SDL_GetRGB(pixel, image_surface->format, &r, &v,&b);
    //
    //          if( r <= (int)seuil ){
    //
    //              Uint32 pixel1 = SDL_MapRGB(image_surface->format, 0, 0, 0);
    //              put_pixel(image_surface,i,j,pixel1);
    //
    //          derhistoMat.matrix[i*derhistoMat.width+j] = 1;
    //
    //          }
    //          else{
    //
    //              Uint32 pixel1 = SDL_MapRGB(image_surface->format, 255, 255, 255);
    //              put_pixel(image_surface,i,j,pixel1);
    //
    //              derhistoMat.matrix[i*derhistoMat.width+j] = 0;
    //          }
    //       }
    // }

    //put the image in white and black
    //to show in the firt soutenance if the binarisation is done

    Matrix derhistoMat = imgToMat(image_surface);

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    // //print_Matrix(derhistoMat);
    // Matrix m = new_alea_Matrix(5,5);
    //
    // print_Matrix(m);
    //
    // Matrix t = horizonRLSA(m,1);
    //
    // print_Matrix(t);
    //
    // Matrix l = verticRLSA(m,1);
    //
    // print_Matrix(l);
    //
    // m = andLogicMartix(t,l);
    //
    //


    //Matrix m = rlsa(rlsa(derhistoMat,1000000000,1000000000),1000000000,1000000000);
    beginSeg(derhistoMat);
    printTree(txt,level1)

    SDL_FreeSurface(image_surface);

    SDL_FreeSurface(screen_surface);

    return 0;
}
