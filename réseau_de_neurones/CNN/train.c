/*
 *
 *                  Convolutional Neural Network for OCR
 *                  built on LeNet5 structure 
 *
 *                  by M.Thunet and A.Barry
 *
 * for training:
 *              specifications:
 *                  _input is a 32x32 grayscale matrix
 *                  _output is an ASCII code representing output character
 *
 *                  version 0.0 4/12/2020
 *
 * MAIN FOR TRAINING
 *
 */
#include "LeNet.h"
 #include <stdlib.h>
 #include <stdio.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"
#include "../../Tools/matrix.h"
#include "../../pré-traitement/binarisation/binarisation.h"

#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )

int main()
{
    
    //___________________________________________________________________________________
    //Getting input matrix
    init_sdl();

    SDL_Surface* img = load_image("ocr_images_100_per_dir/train_extracted_bmps/4/train100.bmp");

    Matrix matrice1 = surface_to_matrix_grayscale(img);

    int seuil = otsu(img);

    Matrix input =  matrix_grayscale_to_binar(matrice1, seuil) ;
    SDL_FreeSurface(img);

    printf("image to matrice [ok] \n" );
    //print_Matrix(input);
    

    //______________________________________________________________________________________

    //Inititalise layers
    
    //______________________________________________________________________________________

    //Filters 1
    struct ALLFilters1 *A1;
        A1=(struct ALLFilters1 *) malloc (NB_FILTERS1*DIM_FILTER*DIM_FILTER*sizeof(double));

        if(A1 != NULL){
         free(A1);
         A1= NULL;
        }

        A1=(struct ALLFilters1 *) malloc (NB_FILTERS1*DIM_FILTER*DIM_FILTER*sizeof(double));
        for (int i=0; i<NB_FILTERS1;i++)
      {
          A1->Mall[i].height=DIM_FILTER;
          A1->Mall[i].width=DIM_FILTER;
          for (int k = 0 ; k < DIM_FILTER*DIM_FILTER ; k++){
              A1->Mall[i].matrix[k] = 0;
                }
      }
        printf("All filters1 init [ok] \n" );

        //Getting all Filters
        getFilter1(A1);
         
        printf("All filters1 loaded [ok] \n" );

    //______________________________________________________________________________________
    //Convolution Layer1
    struct ALLFM1 *cfm1;
    cfm1=(struct ALLFM1 *) malloc (NB_FILTERS1*DIM_C1*DIM_C1*sizeof(double));

    if(cfm1 != NULL){
         free(cfm1);
         cfm1 = NULL;
        }
    cfm1=(struct ALLFM1 *) malloc (NB_FILTERS1*DIM_C1*DIM_C1*sizeof(double));

    for(int i=0; i<NB_FILTERS1;i++)
    {
        cfm1->fm1[i].height=DIM_C1;
        cfm1->fm1[i].width=DIM_C1;
    
    for (int k = 0 ; k < DIM_C1*DIM_C1 ; k++)
    {   
           // printf("in for: filter=%i, k=%i \n",i,k);
            cfm1->fm1[i].matrix[k] = 0.0;
          //  printf("after \n");
    }
    }

    printf("All convolution1 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer1
    struct PoolC1 *pc1;
    pc1=(struct PoolC1 *) malloc (NB_FILTERS1*DIM_POOL1*DIM_POOL1*sizeof(double));

    for(int i=0; i<NB_FILTERS1;i++)
    {
        pc1->pool1[i].height=DIM_POOL1;
        pc1->pool1[i].width=DIM_POOL1;
        //printf("in for: filter=%i \n",i);
    
    for (int k = 0 ; k < DIM_POOL1*DIM_POOL1 ; k++)
    {
         pc1->pool1[i].matrix[k] = (double)0;
    }
    }

    printf("All pooling init1 [ok] \n" );

    //______________________________________________________________________________________
    //Filters and Convolution Layer2
    struct ALLFilters2 *A2;
    A2=(struct ALLFilters2 *) malloc (NB_FILTERS2*DIM_FILTER*DIM_FILTER*sizeof(double));

    for(int i=0; i<NB_FILTERS2;i++)
    {
        A2->Mall2[i].height=DIM_FILTER;
        A2->Mall2[i].width=DIM_FILTER;
        for (int k = 0 ; k < DIM_FILTER*DIM_FILTER ; k++)
    {
            A2->Mall2[i].matrix[k] = 0.0;
    }
    }

    printf("All filters2 loaded [ok] \n" );
    
    //Getting the filters
    //getFilter2(A2);

    struct ALLFM2 *cfm2;
    cfm2=(struct ALLFM2 *) malloc (NB_FILTERS2*DIM_POOL1*DIM_POOL1*sizeof(double));

    for(int i=0; i<NB_FILTERS2;i++)
    {
        cfm2->fm2[i].height=DIM_C2;
        cfm2->fm2[i].width=DIM_C2;
    

    for (int k = 0 ; k < DIM_C2*DIM_C2 ; k++)
    {
            cfm2->fm2[i].matrix[k] = 0.0;
    }
    }

    printf("All convolution2 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer2
    struct PoolC2 *pc2;
    pc2=(struct PoolC2 *) malloc (NB_FILTERS2*DIM_POOL2*DIM_POOL2*sizeof(double));

    for(int i=0; i<NB_FILTERS2;i++)
    {
        pc2->pool2[i].height=DIM_POOL2;
        pc2->pool2[i].width=DIM_POOL2;
    for (int k = 0 ; k < DIM_POOL2*DIM_POOL2 ; k++)
    {
            pc2->pool2[i].matrix[k] = 0.0;
    }
    }

    printf("All pooling init2 [ok] \n" );


    //______________________________________________________________________________________
    // 8) Flattern Layer -> First Fully Connected Layer
    struct FL *flatterned;
    flatterned=(struct FL *) malloc (NB_FILTERS2*DIM_POOL2*DIM_POOL2*sizeof(struct Neuron));

    for(int i=0; i<DIM_POOL2*DIM_POOL2*NB_FILTERS2; i++)
    {
        flatterned->flayer[i].input=RAND_DOUBLE;
        flatterned->flayer[i].weight=RAND_DOUBLE;
        flatterned->flayer[i].bias=RAND_DOUBLE;
    }

    printf("All flatterning [ok] \n" );
    struct CL_out *outin;
    outin=(struct CL_out *) malloc (NB_Char*sizeof(struct Neuron));
    printf("All output [ok] \n");

    printf("all structures are done and are up and working \n");
    // Forward Propagate __________________________________________________________________________

        // 2) C1 -> Convolutional Layer with 6 filters to get 6 feature maps

        //Going -> Convolution Layer 1
        ConvolutionLayer1(cfm1, A1, input);

        printf("Convolution1   [ok]   \n");
        // 3) Relu activation function on feature maps
        ReluActiv1(cfm1);

        printf("Relu1   [ok]   \n");
        // 4) Pooling
        Pool1(cfm1,pc1);

        printf("Pooling1   [ok]   \n");
        // 5) C2 -> Convolutional Layer with 16 filters for each feature maps to get new feature maps
        ConvolutionLayer2(A2, pc1,cfm2);

        printf("Convolution2   [ok]   \n");
        // 6) Relu activation function on the feature maps
        ReluActiv2(cfm2);

         printf("Relu2   [ok]   \n");
        // 7) Pooling
        Pool2(cfm2, pc2);

        printf("Pooling2   [ok]   \n");
        // 8) Flattern Layer -> First Fully Connected Layer
        FlatternLayer(pc2, flatterned);

        printf("Flattern Layer   [ok]   \n");
        FullyConnectedLayer1(flatterned,outin);

        printf("Fully Connected Layer   [ok]   \n");
        // 9) Fully connected output layer
        struct resultsfromoutput output=GetOutPut(outin);

        printf("The output is: %f",output.ASCII);

        //FREE ALL MEMORY 
        //Free all of this

        if(A1 != NULL){
         free(A1);
         A1= NULL;
        }

        if(cfm1 != NULL){
         free(cfm1);
         cfm1 = NULL;
        }

        if(pc1 != NULL){
         free(pc1);
         pc1 = NULL;
        }

        if(A2 != NULL){
         free(A2);
         A2 = NULL;
        }

        if(cfm2 != NULL){
         free(cfm2);
         cfm2 = NULL;
        }
        if(pc2 != NULL){
         free(pc2);
         pc2 = NULL;
        }

        if(flatterned != NULL){
         free(flatterned);
         flatterned = NULL;
        }

        if(outin != NULL){
         free(outin);
         outin = NULL;
        }

        return 0;

}
