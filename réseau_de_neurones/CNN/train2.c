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

void RandomFilter2(struct Matrix *m, int range)
{
    double *indexx = NULL;
    indexx = m->matrix;
    printf("%f\n", indexx[5]);
    for (int k = 0 ; k < range ; k++){
         double random5=  ( (double)rand()/(double)RAND_MAX );
         printf("this random %f \n",random5);
         indexx[k] = random5;

         printf("this random %f \n",random5);
      }
    printf("out of for\n");

}

void NullFilters(Matrix *m,int range)
{
    double *indexx= NULL;

    printf("caca \n");
    indexx=m->matrix;

    printf("caca \n");
    for (int k = 0 ; k < range ; k++){
         indexx[k] = 0;
          printf("%d\n ", k);
      }

    printf("caca \n");

}


int main()
{
    
    //______________________________________________________________________________________

    //Inititalise layers
    
    //______________________________________________________________________________________

    //Filters 1
    //
    
    struct ALLFilters1 *A1_1st;
    A1_1st = malloc (sizeof(struct ALLFilters1));
    Matrix *m1;
    m1= malloc(sizeof(Matrix));

    m1->width= DIM_FILTER;
    m1->height=DIM_FILTER;
    m1->matrix = calloc(DIM_FILTER*DIM_FILTER ,sizeof(double));
    A1_1st->m=m1;
    RandomFilter2(m1, DIM_FILTER*DIM_FILTER);
    //NullFilters(m1, DIM_FILTER*DIM_FILTER);

    print_Matrix(*(A1_1st->m));
    struct ALLFilters1 *A1_2nd;
    A1_2nd= malloc (sizeof(struct ALLFilters1));
    Matrix *m2;
    m2= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2->width= DIM_FILTER;
    m2->height=DIM_FILTER;
    A1_2nd->m=m2;
    RandomFilter2(A1_2nd->m, DIM_FILTER*DIM_FILTER);
    A1_1st->next=A1_2nd;
    
    struct ALLFilters1 *A1_3rd;
    A1_3rd= malloc (sizeof(struct ALLFilters1));
    Matrix *m3;
    m3= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m3->width= DIM_FILTER;
    m3->height=DIM_FILTER;
    A1_3rd->m=m3;
    RandomFilter2(A1_3rd->m, DIM_FILTER*DIM_FILTER);
    A1_2nd->next=A1_3rd;

    struct ALLFilters1 *A1_4th;
    A1_4th= malloc (sizeof(struct ALLFilters1));
    Matrix *m4;
    m4= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m4->width= DIM_FILTER;
    m4->height=DIM_FILTER;
    A1_4th->m=m4;
    RandomFilter2(A1_4th->m, DIM_FILTER*DIM_FILTER);
    A1_3rd->next=A1_4th;

    struct ALLFilters1 *A1_5th;
    A1_5th= malloc (sizeof(struct ALLFilters1));
    Matrix *m5;
    m5= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m5->width= DIM_FILTER;
    m5->height=DIM_FILTER;
    A1_5th->m=m5;
    RandomFilter2(A1_5th->m, DIM_FILTER*DIM_FILTER);
    A1_4th->next=A1_5th;

    struct ALLFilters1 *A1_6th;
    A1_6th= malloc (sizeof(struct ALLFilters1));
    Matrix *m6;
    m6= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m6->width= DIM_FILTER;
    m6->height=DIM_FILTER;
    A1_6th->m=m6;
    RandomFilter2(A1_6th->m, DIM_FILTER*DIM_FILTER);
    A1_5th->next=A1_6th;
    A1_6th->next=NULL;
    
    printf("All filters1 loaded [ok] \n" );

    //______________________________________________________________________________________
    //Convolution Layer1
    struct ALLFM1 *convo1;
    convo1 = malloc (sizeof(struct ALLFM1));
    Matrix *cf1;
    cf1= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf1->width= DIM_C1;
    cf1->height=DIM_C1;
    convo1->m=cf1;
    NullFilters(convo1->m,DIM_C1*DIM_C1);

    struct ALLFM1 *convo2;
    convo2 = malloc (sizeof(struct ALLFM1));
    Matrix *cf2;
    cf2= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf2->width= DIM_C1;
    cf2->height=DIM_C1;
    convo2->m=cf2;
    NullFilters(convo2->m,DIM_C1*DIM_C1);
    convo1->next=convo2;

    struct ALLFM1 *convo3;
    convo3 = malloc (sizeof(struct ALLFM1));
    Matrix *cf3;
    cf3= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf3->width= DIM_C1;
    cf3->height=DIM_C1;
    convo3->m=cf3;
    NullFilters(convo3->m,DIM_C1*DIM_C1);
    convo2->next=convo3;

    struct ALLFM1 *convo4;
    convo4 = malloc (sizeof(struct ALLFM1));
    Matrix *cf4;
    cf4= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf4->width= DIM_C1;
    cf4->height=DIM_C1;
    convo4->m=cf4;
    NullFilters(convo4->m,DIM_C1*DIM_C1);
    convo3->next=convo4;

    struct ALLFM1 *convo5;
    convo5 = malloc (sizeof(struct ALLFM1));
    Matrix *cf5;
    cf5= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf5->width= DIM_C1;
    cf5->height=DIM_C1;
    convo5->m=cf5;
    NullFilters(convo5->m,DIM_C1*DIM_C1);
    convo4->next=convo5;

    struct ALLFM1 *convo6;
    convo6 = malloc (sizeof(struct ALLFM1));
    Matrix *cf6;
    cf6= malloc(DIM_C1*DIM_C1*sizeof(double));
    cf6->width= DIM_C1;
    cf6->height=DIM_C1;
    convo6->m=cf6;
    NullFilters(convo6->m,DIM_C1*DIM_C1);
    convo5->next=convo6;
    convo6->next=NULL;



    printf("All convolution1 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer1
    struct PoolC1 *poolC1;
    poolC1 = malloc (sizeof(struct PoolC1));
    Matrix *pc1;
    pc1= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc1->width= DIM_POOL1;
    pc1->height=DIM_POOL1;
    poolC1->m=pc1;
    NullFilters(poolC1->m,DIM_POOL1*DIM_POOL1);

    struct PoolC1 *poolC2;
    poolC2 = malloc (sizeof(struct PoolC1));
    Matrix *pc2;
    pc2= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc2->width= DIM_POOL1;
    pc2->height=DIM_POOL1;
    poolC2->m=pc2;
    NullFilters(poolC2->m,DIM_POOL1*DIM_POOL1);
    poolC1->next=poolC2;

    struct PoolC1 *poolC3;
    poolC3 = malloc (sizeof(struct PoolC1));
    Matrix *pc3;
    pc3= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc3->width= DIM_POOL1;
    pc3->height=DIM_POOL1;
    poolC3->m=pc3;
    NullFilters(poolC3->m,DIM_POOL1*DIM_POOL1);
    poolC2->next=poolC3;

    struct PoolC1 *poolC4;
    poolC4 = malloc (sizeof(struct PoolC1));
    Matrix *pc4;
    pc4= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc4->width= DIM_POOL1;
    pc4->height=DIM_POOL1;
    poolC4->m=pc4;
    NullFilters(poolC4->m,DIM_POOL1*DIM_POOL1);
    poolC3->next=poolC4;

    struct PoolC1 *poolC5;
    poolC5 = malloc (sizeof(struct PoolC1));
    Matrix *pc5;
    pc5= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc5->width= DIM_POOL1;
    pc5->height=DIM_POOL1;
    poolC5->m=pc5;
    NullFilters(poolC5->m,DIM_POOL1*DIM_POOL1);
    poolC4->next=poolC5;

    struct PoolC1 *poolC6;
    poolC6 = malloc (sizeof(struct PoolC1));
    Matrix *pc6;
    pc6= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    pc6->width= DIM_POOL1;
    pc6->height=DIM_POOL1;
    poolC6->m=pc6;
    NullFilters(poolC6->m,DIM_POOL1*DIM_POOL1);
    poolC5->next=poolC6;
    poolC6->next=NULL;


    printf("All pooling init1 [ok] \n" );

    //______________________________________________________________________________________
    //Filters and Convolution Layer2
    
    //Filters 2
    struct ALLFilters2 *A2_1st;
    A2_1st = malloc (sizeof(struct ALLFilters2));
    Matrix *m2_1;
    m2_1= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_1->width= DIM_FILTER;
    m2_1->height=DIM_FILTER;
    A2_1st->m=m2_1;
    RandomFilter2(A2_1st->m, DIM_FILTER*DIM_FILTER);
    
    struct ALLFilters2 *A2_2nd;
    A2_2nd= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_2;
    m2_2= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_2->width= DIM_FILTER;
    m2_2->height=DIM_FILTER;
    A2_2nd->m=m2_2;
    RandomFilter2(A2_2nd->m, DIM_FILTER*DIM_FILTER);
    A2_1st->next=A2_2nd;

    struct ALLFilters2 *A2_3rd;
    A2_3rd= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_3;
    m2_3= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_3->width= DIM_FILTER;
    m2_3->height=DIM_FILTER;
    A2_3rd->m=m2_3;
    RandomFilter2(A2_3rd->m, DIM_FILTER*DIM_FILTER);
    A2_2nd->next=A2_3rd;

    struct ALLFilters2 *A2_4th;
    A2_4th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_4;
    m2_4= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_4->width= DIM_FILTER;
    m2_4->height=DIM_FILTER;
    A2_4th->m=m2_4;
    RandomFilter2(A2_4th->m, DIM_FILTER*DIM_FILTER);
    A2_3rd->next=A2_4th;

    struct ALLFilters2 *A2_5th;
    A2_5th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_5;
    m2_5= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_5->width= DIM_FILTER;
    m2_5->height=DIM_FILTER;
    A2_5th->m=m2_5;
    RandomFilter2(A2_5th->m, DIM_FILTER*DIM_FILTER);
    A2_4th->next=A2_5th;

    struct ALLFilters2 *A2_6th;
    A2_6th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_6;
    m2_6= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_6->width= DIM_FILTER;
    m2_6->height=DIM_FILTER;
    A2_6th->m=m2_6;
    RandomFilter2(A2_6th->m, DIM_FILTER*DIM_FILTER);
    A2_5th->next=A2_6th;

    struct ALLFilters2 *A2_7th;
    A2_7th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_7;
    m2_7= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_7->width= DIM_FILTER;
    m2_7->height=DIM_FILTER;
    A2_7th->m=m2_7;
    RandomFilter2(A2_7th->m, DIM_FILTER*DIM_FILTER);
    A2_6th->next=A2_7th;

    struct ALLFilters2 *A2_8th;
    A2_8th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_8;
    m2_8= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_8->width= DIM_FILTER;
    m2_8->height=DIM_FILTER;
    A2_8th->m=m2_8;
    RandomFilter2(A2_8th->m, DIM_FILTER*DIM_FILTER);
    A2_7th->next=A2_8th;

    struct ALLFilters2 *A2_9th;
    A2_9th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_9;
    m2_9= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_9->width= DIM_FILTER;
    m2_9->height=DIM_FILTER;
    A2_9th->m=m2_9;
    RandomFilter2(A2_9th->m, DIM_FILTER*DIM_FILTER);
    A2_8th->next=A2_9th;

    struct ALLFilters2 *A2_10th;
    A2_10th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_10;
    m2_10= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_10->width= DIM_FILTER;
    m2_10->height=DIM_FILTER;
    A2_10th->m=m2_10;
    RandomFilter2(A2_10th->m, DIM_FILTER*DIM_FILTER);
    A2_9th->next=A2_10th;

    struct ALLFilters2 *A2_11th;
    A2_11th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_11;
    m2_11= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_11->width= DIM_FILTER;
    m2_11->height=DIM_FILTER;
    A2_11th->m=m2_11;
    RandomFilter2(A2_11th->m, DIM_FILTER*DIM_FILTER);
    A2_10th->next=A2_11th;

    struct ALLFilters2 *A2_12th;
    A2_12th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_12;
    m2_12= malloc(DIM_FILTER*DIM_FILTER*sizeof(double));
    m2_12->width= DIM_FILTER;
    m2_12->height=DIM_FILTER;
    A2_12th->m=m2_12;
    RandomFilter2(A2_12th->m, DIM_FILTER*DIM_FILTER);
    A2_11th->next=A2_12th;
    A2_12th->next=NULL;


    printf("All filters2 loaded [ok] \n" );
    

    //______________________________________________________________________________________
    //Convolution Layer2

    struct ALLFM2 *convl1;
    convl1 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf1;
    cvf1= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf1->width= DIM_POOL1;
    cvf1->height=DIM_POOL1;
    convl1->m=cvf1;
    NullFilters(convl1->m,DIM_POOL1*DIM_POOL1);

    struct ALLFM2 *convl2;
    convl2 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf2;
    cvf2= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf2->width= DIM_POOL1;
    cvf2->height=DIM_POOL1;
    convl2->m=cvf2;
    NullFilters(convl2->m,DIM_POOL1*DIM_POOL1);
    convl1->next=convl2;

    struct ALLFM2 *convl3;
    convl3 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf3;
    cvf3= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf3->width= DIM_POOL1;
    cvf3->height=DIM_POOL1;
    convl3->m=cvf3;
    NullFilters(convl3->m,DIM_POOL1*DIM_POOL1);
    convl2->next=convl3;

    struct ALLFM2 *convl4;
    convl4 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf4;
    cvf4= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf4->width= DIM_POOL1;
    cvf4->height=DIM_POOL1;
    convl4->m=cvf4;
    NullFilters(convl4->m,DIM_POOL1*DIM_POOL1);
    convl3->next=convl4;

    struct ALLFM2 *convl5;
    convl5 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf5;
    cvf5= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf5->width= DIM_POOL1;
    cvf5->height=DIM_POOL1;
    convl5->m=cvf5;
    NullFilters(convl5->m,DIM_POOL1*DIM_POOL1);
    convl4->next=convl5;

    struct ALLFM2 *convl6;
    convl6 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf6;
    cvf6= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf6->width= DIM_POOL1;
    cvf6->height=DIM_POOL1;
    convl6->m=cvf6;
    NullFilters(convl6->m,DIM_POOL1*DIM_POOL1);
    convl5->next=convl6;

    struct ALLFM2 *convl7;
    convl7 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf7;
    cvf7= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf7->width= DIM_POOL1;
    cvf7->height=DIM_POOL1;
    convl7->m=cvf7;
    NullFilters(convl7->m,DIM_POOL1*DIM_POOL1);
    convl6->next=convl7;

    struct ALLFM2 *convl8;
    convl8 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf8;
    cvf8= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf8->width= DIM_POOL1;
    cvf8->height=DIM_POOL1;
    convl8->m=cvf8;
    NullFilters(convl8->m,DIM_POOL1*DIM_POOL1);
    convl7->next=convl8;

    struct ALLFM2 *convl9;
    convl9 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf9;
    cvf9= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf9->width= DIM_POOL1;
    cvf9->height=DIM_POOL1;
    convl9->m=cvf9;
    NullFilters(convl9->m,DIM_POOL1*DIM_POOL1);
    convl8->next=convl9;

    struct ALLFM2 *convl10;
    convl10 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf10;
    cvf10= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf10->width= DIM_POOL1;
    cvf10->height=DIM_POOL1;
    convl10->m=cvf10;
    NullFilters(convl10->m,DIM_POOL1*DIM_POOL1);
    convl9->next=convl10;

    struct ALLFM2 *convl11;
    convl11 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf11;
    cvf11= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf11->width= DIM_POOL1;
    cvf11->height=DIM_POOL1;
    convl11->m=cvf11;
    NullFilters(convl11->m,DIM_POOL1*DIM_POOL1);
    convl10->next=convl11;

    struct ALLFM2 *convl12;
    convl12 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf12;
    cvf12= malloc(DIM_POOL1*DIM_POOL1*sizeof(double));
    cvf12->width= DIM_POOL1;
    cvf12->height=DIM_POOL1;
    convl12->m=cvf12;
    NullFilters(convl12->m,DIM_POOL1*DIM_POOL1);
    convl11->next=convl12;
    convl12->next=NULL;

    printf("All convolution2 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer2
    struct PoolC2 *poolC2_1;
    poolC2_1 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_1;
    pc2_1= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_1->width= DIM_POOL2;
    pc2_1->height=DIM_POOL2;
    poolC2_1->m=pc2_1;
    NullFilters(poolC2_1->m,DIM_POOL2*DIM_POOL2);

    struct PoolC2 *poolC2_2;
    poolC2_2 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_2;
    pc2_2= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_2->width= DIM_POOL2;
    pc2_2->height=DIM_POOL2;
    poolC2_2->m=pc2_2;
    NullFilters(poolC2_2->m,DIM_POOL2*DIM_POOL2);
    poolC2_1->next=poolC2_2;

    struct PoolC2 *poolC2_3;
    poolC2_3 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_3;
    pc2_3= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_3->width= DIM_POOL2;
    pc2_3->height=DIM_POOL2;
    poolC2_3->m=pc2_3;
    NullFilters(poolC2_3->m,DIM_POOL2*DIM_POOL2);
    poolC2_2->next=poolC2_3;

    struct PoolC2 *poolC2_4;
    poolC2_4 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_4;
    pc2_4= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_4->width= DIM_POOL2;
    pc2_4->height=DIM_POOL2;
    poolC2_4->m=pc2_4;
    NullFilters(poolC2_4->m,DIM_POOL2*DIM_POOL2);
    poolC2_3->next=poolC2_4;

    struct PoolC2 *poolC2_5;
    poolC2_5 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_5;
    pc2_5= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_5->width= DIM_POOL2;
    pc2_5->height=DIM_POOL2;
    poolC2_5->m=pc2_5;
    NullFilters(poolC2_5->m,DIM_POOL2*DIM_POOL2);
    poolC2_4->next=poolC2_5;

    struct PoolC2 *poolC2_6;
    poolC2_6 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_6;
    pc2_6= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_6->width= DIM_POOL2;
    pc2_6->height=DIM_POOL2;
    poolC2_6->m=pc2_6;
    NullFilters(poolC2_6->m,DIM_POOL2*DIM_POOL2);
    poolC2_5->next=poolC2_6;

    struct PoolC2 *poolC2_7;
    poolC2_7 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_7;
    pc2_7= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_7->width= DIM_POOL2;
    pc2_7->height=DIM_POOL2;
    poolC2_7->m=pc2_7;
    NullFilters(poolC2_7->m,DIM_POOL2*DIM_POOL2);
    poolC2_6->next=poolC2_7;

    struct PoolC2 *poolC2_8;
    poolC2_8 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_8;
    pc2_8= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_8->width= DIM_POOL2;
    pc2_8->height=DIM_POOL2;
    poolC2_8->m=pc2_8;
    NullFilters(poolC2_8->m,DIM_POOL2*DIM_POOL2);
    poolC2_7->next=poolC2_8;

    struct PoolC2 *poolC2_9;
    poolC2_9 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_9;
    pc2_9= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_9->width= DIM_POOL2;
    pc2_9->height=DIM_POOL2;
    poolC2_9->m=pc2_9;
    NullFilters(poolC2_9->m,DIM_POOL2*DIM_POOL2);
    poolC2_8->next=poolC2_9;

    struct PoolC2 *poolC2_10;
    poolC2_10 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_10;
    pc2_10= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_10->width= DIM_POOL2;
    pc2_10->height=DIM_POOL2;
    poolC2_10->m=pc2_10;
    NullFilters(poolC2_10->m,DIM_POOL2*DIM_POOL2);
    poolC2_9->next=poolC2_10;

    struct PoolC2 *poolC2_11;
    poolC2_11 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_11;
    pc2_11= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_11->width= DIM_POOL2;
    pc2_11->height=DIM_POOL2;
    poolC2_11->m=pc2_11;
    NullFilters(poolC2_11->m,DIM_POOL2*DIM_POOL2);
    poolC2_10->next=poolC2_11;

    struct PoolC2 *poolC2_12;
    poolC2_12 = malloc (sizeof(struct PoolC2));
    Matrix *pc2_12;
    pc2_12= malloc(DIM_POOL2*DIM_POOL2*sizeof(double));
    pc2_12->width= DIM_POOL2;
    pc2_12->height=DIM_POOL2;
    poolC2_12->m=pc2_12;
    NullFilters(poolC2_12->m,DIM_POOL2*DIM_POOL2);
    poolC2_11->next=poolC2_12;
    poolC2_12->next=NULL;

    printf("All pooling init2 [ok] \n" );


    //______________________________________________________________________________________
    // 8) Flattern Layer -> First Fully Connected Layer
    struct FL *flatterned1;
    flatterned1=malloc (sizeof(struct FL));
    struct Neuron *neur1;
    neur1=malloc(sizeof(struct Neuron));
    neur1->input=0;
    neur1->weight=RAND_DOUBLE;
    neur1->bias=RAND_DOUBLE;
    flatterned1->n=neur1;
    flatterned1->next=NULL;

  //  for(int i=0; i<DIM_POOL2*DIM_POOL2*NB_FILTERS2; i++)

    printf("All flatterning [ok] \n" );
    struct CL_out *outin;
    outin= malloc (sizeof(struct CL_out));
    struct Neuron *on1;
    on1= malloc (sizeof(struct Neuron));
    outin->next=NULL;
    outin->n=on1;


    printf("All output [ok] \n");

    printf("all structures are done and are up and working \n");
    
    //___________________________________________________________________________________
    //Getting input matrix
    init_sdl();

    SDL_Surface* img = load_image("images/cc/c_0.bmp");

    Matrix matrice1 = surface_to_matrix_grayscale(img);

    int seuil = otsu(img);

    Matrix input =  matrix_grayscale_to_binar(matrice1, seuil) ;
    SDL_FreeSurface(img);

    printf("image to matrice [ok] \n" );


    // Forward Propagate __________________________________________________________________________

        // 2) C1 -> Convolutional Layer with 6 filters to get 6 feature maps

        //Going -> Convolution Layer 1
        ConvolutionLayer1(convo1,A1_1st, input);

        printf("Convolution1   [ok]   \n");
        // 3) Relu activation function on feature maps
        ReluActiv1(convo1);

        printf("Relu1   [ok]   \n");
        // 4) Pooling
      /*  Pool1(convo1, poolC1);

        printf("Pooling1   [ok]   \n");
        // 5) C2 -> Convolutional Layer with 16 filters for each feature maps to get new feature maps
        ConvolutionLayer2( A2_1st, poolC1, convl1);

        printf("Convolution2   [ok]   \n");
        // 6) Relu activation function on the feature maps
        ReluActiv2(convl1);

         printf("Relu2   [ok]   \n");
        // 7) Pooling
        Pool2(convl1, poolC2_1);

        printf("Pooling2   [ok]   \n");
        // 8) Flattern Layer -> First Fully Connected Layer
        FlatternLayer( poolC2_1, flatterned1);

        printf("Flattern Layer   [ok]   \n");
        FullyConnectedLayer1(flatterned1, outin);

        printf("Fully Connected Layer   [ok]   \n");
        // 9) Fully connected output layer
        struct resultsfromoutput output=GetOutPut( outin);

        printf("The output is: %f",output.ASCII);
*/
        //FREE ALL MEMORY 
        //Free all of this

        printf("until freed memory [ok] \n");
        if(A1_1st != NULL){
         while ( A1_1st && A1_1st->next)
         {
                free(A1_1st->m);
                A1_1st=A1_1st->next;
         }
             free(A1_1st);
            A1_1st= NULL;
        }

        if(convo1 != NULL){
            while(convo1&& convo1->next)
            {
                free(convo1->m);
                //free(convo1)
                convo1=convo1->next;
            }
         free(convo1);
         convo1 = NULL;
        }

        if(poolC1 != NULL){
            while(poolC1 && poolC1->next)
            {
                free(poolC1->m);
                poolC1=poolC1->next;
            }
         free(poolC1);
         poolC1 = NULL;
        }

        if(A2_1st != NULL){
            while(A2_1st && A2_1st-> next)
            {
                free(A2_1st->m);
                A2_1st=A2_1st->next;
            }
         free(A2_1st);
         A2_1st = NULL;
        }

        if(convl1 != NULL){

            while(convl1 && convl1->next)
            {
                free(convl1->m);
                convl1=convl1->next;
            }

         free(convl1);
         convl1 = NULL;
        
        }

        if(poolC2_1 != NULL){
            while(poolC2_1 && poolC2_1->next)
            {
                free(poolC2_1->m);
                poolC2_1=poolC2_1->next;
            }

         free(poolC2_1);
         poolC2_1 = NULL;
        }

        if(flatterned1 != NULL){
            while(flatterned1 && flatterned1->next)
            {
                free(flatterned1->n);
                flatterned1=flatterned1->next;
            }
         free(flatterned1);
         flatterned1 = NULL;
        }

        if(outin != NULL){
            while(outin && outin->next)
            {
                free(outin->n);
                outin=outin->next;
            }

         free(outin);
         outin = NULL;
        }

        return 0;

}
