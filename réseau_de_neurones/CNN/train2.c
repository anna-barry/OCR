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
 *                  version 1.2 11/12/2020
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
#include <time.h>
#include "../../Tools/pixel_operations.h"
#include "../../Tools/image_operations.h"
#include "../../Tools/matrix.h"
#include "../../pré-traitement/binarisation/binarisation.h"

#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )

int seed= 0;
void RandomFilter2(struct Matrix *m, int range)
{
    double *indexx = NULL;
    indexx = m->matrix;

    srand(seed);
   for (int k = 0 ; k < range ; k++){
        double random5=  ( (double)rand()/(double)RAND_MAX );
        indexx[k] = random5;
      }
   seed+=1;

}


int main()
{

    //______________________________________________________________________________________

    //Inititalise layers

    //______________________________________________________________________________________

    //Filters 1
    //
    srand( (unsigned)time( NULL ) );

    struct ALLFilters1 *A1_1st;
    A1_1st = malloc (sizeof(struct ALLFilters1));
    Matrix *m1;
    m1= malloc(sizeof(Matrix));
    m1->width= DIM_FILTER;
    m1->height=DIM_FILTER;
    m1->matrix = calloc(DIM_FILTER*DIM_FILTER ,sizeof(double));
    A1_1st->m=m1;
    RandomFilter2(m1, DIM_FILTER*DIM_FILTER);

    struct ALLFilters1 *A1_2nd;
    A1_2nd= malloc (sizeof(struct ALLFilters1));
    Matrix *m2;
    m2= malloc (sizeof(Matrix));
    m2->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2->width= DIM_FILTER;
    m2->height=DIM_FILTER;
    A1_2nd->m=m2;
    RandomFilter2(A1_2nd->m, DIM_FILTER*DIM_FILTER);
    A1_1st->next=A1_2nd;

    struct ALLFilters1 *A1_3rd;
    A1_3rd= malloc (sizeof(struct ALLFilters1));
    Matrix *m3;
    m3= malloc (sizeof(Matrix));
    m3->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m3->width= DIM_FILTER;
    m3->height=DIM_FILTER;
    A1_3rd->m=m3;
    RandomFilter2(A1_3rd->m, DIM_FILTER*DIM_FILTER);
    A1_2nd->next=A1_3rd;

    struct ALLFilters1 *A1_4th;
    A1_4th= malloc (sizeof(struct ALLFilters1));
    Matrix *m4;
    m4= malloc (sizeof(Matrix));
    m4->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m4->width= DIM_FILTER;
    m4->height=DIM_FILTER;
    A1_4th->m=m4;
    RandomFilter2(A1_4th->m, DIM_FILTER*DIM_FILTER);
    A1_3rd->next=A1_4th;

    struct ALLFilters1 *A1_5th;
    A1_5th= malloc (sizeof(struct ALLFilters1));
    Matrix *m5;
    m5= malloc (sizeof(Matrix));
    m5->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m5->width= DIM_FILTER;
    m5->height=DIM_FILTER;
    A1_5th->m=m5;
    RandomFilter2(A1_5th->m, DIM_FILTER*DIM_FILTER);
    A1_4th->next=A1_5th;

    struct ALLFilters1 *A1_6th;
    A1_6th= malloc (sizeof(struct ALLFilters1));
    Matrix *m6;
    m6= malloc (sizeof(Matrix));
    m6->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m6->width= DIM_FILTER;
    m6->height=DIM_FILTER;
    A1_6th->m=m6;
    RandomFilter2(A1_6th->m, DIM_FILTER*DIM_FILTER);
    A1_5th->next=A1_6th;
    A1_6th->next=NULL;

    //printf("All filters1 loaded [ok] \n" );

    //______________________________________________________________________________________
    //Convolution Layer1
    struct ALLFM1 *convo1;
    convo1 = malloc (sizeof(struct ALLFM1));
    Matrix *cf1;
    cf1= malloc (sizeof(Matrix));
    cf1->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf1->width= DIM_C1;
    cf1->height=DIM_C1;
    convo1->m=cf1;

    struct ALLFM1 *convo2;
    convo2 = malloc (sizeof(struct ALLFM1));
    Matrix *cf2;
    cf2= malloc (sizeof(Matrix));
    cf2->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf2->width= DIM_C1;
    cf2->height=DIM_C1;
    convo2->m=cf2;
    convo1->next=convo2;

    struct ALLFM1 *convo3;
    convo3 = malloc (sizeof(struct ALLFM1));
    Matrix *cf3;
    cf3=malloc (sizeof(Matrix));
    cf3->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf3->width= DIM_C1;
    cf3->height=DIM_C1;
    convo3->m=cf3;
    convo2->next=convo3;

    struct ALLFM1 *convo4;
    convo4 = malloc (sizeof(struct ALLFM1));
    Matrix *cf4;
    cf4=malloc (sizeof(Matrix));
    cf4->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf4->width= DIM_C1;
    cf4->height=DIM_C1;
    convo4->m=cf4;
    convo3->next=convo4;

    struct ALLFM1 *convo5;
    convo5 = malloc (sizeof(struct ALLFM1));
    Matrix *cf5;
    cf5=malloc (sizeof(Matrix));
    cf5->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf5->width= DIM_C1;
    cf5->height=DIM_C1;
    convo5->m=cf5;
    convo4->next=convo5;

    struct ALLFM1 *convo6;
    convo6 = malloc (sizeof(struct ALLFM1));
    Matrix *cf6;
    cf6=malloc (sizeof(Matrix));
    cf6->matrix= calloc(DIM_C1*DIM_C1,sizeof(double));
    cf6->width= DIM_C1;
    cf6->height=DIM_C1;
    convo6->m=cf6;
    convo5->next=convo6;
    convo6->next=NULL;



  // printf("All convolution1 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer1
    struct PoolC1 *poolC1;
    poolC1 = malloc (sizeof(struct PoolC1));
    Matrix *pc1;
    pc1=malloc (sizeof(Matrix));
    pc1->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc1->width= DIM_POOL1;
    pc1->height=DIM_POOL1;
    poolC1->m=pc1;

    struct PoolC1 *poolC2;
    poolC2 = malloc (sizeof(struct PoolC1));
    Matrix *pc2;
    pc2=malloc (sizeof(Matrix));
    pc2->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc2->width= DIM_POOL1;
    pc2->height=DIM_POOL1;
    poolC2->m=pc2;
    poolC1->next=poolC2;

    struct PoolC1 *poolC3;
    poolC3 = malloc (sizeof(struct PoolC1));
    Matrix *pc3;
    pc3= malloc (sizeof(Matrix));
    pc3->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc3->width= DIM_POOL1;
    pc3->height=DIM_POOL1;
    poolC3->m=pc3;
    poolC2->next=poolC3;

    struct PoolC1 *poolC4;
    poolC4 = malloc (sizeof(struct PoolC1));
    Matrix *pc4;
    pc4=malloc (sizeof(Matrix));
    pc4->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc4->width= DIM_POOL1;
    pc4->height=DIM_POOL1;
    poolC4->m=pc4;
    poolC3->next=poolC4;

    struct PoolC1 *poolC5;
    poolC5 = malloc (sizeof(struct PoolC1));
    Matrix *pc5;
    pc5=malloc (sizeof(Matrix));
    pc5->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc5->width= DIM_POOL1;
    pc5->height=DIM_POOL1;
    poolC5->m=pc5;
    poolC4->next=poolC5;

    struct PoolC1 *poolC6;
    poolC6 = malloc (sizeof(struct PoolC1));
    Matrix *pc6;
    pc6=malloc (sizeof(Matrix));
    pc6->matrix= calloc(DIM_POOL1*DIM_POOL1,sizeof(double));
    pc6->width= DIM_POOL1;
    pc6->height=DIM_POOL1;
    poolC6->m=pc6;
    poolC5->next=poolC6;
    poolC6->next=NULL;


    printf("All pooling init1 [ok] \n" );

    //______________________________________________________________________________________
    //Filters and Convolution Layer2

    //Filters 2
    struct ALLFilters2 *A2_1st;
    A2_1st = malloc (sizeof(struct ALLFilters2));
    Matrix *m2_1;
    m2_1=malloc (sizeof(Matrix));
    m2_1->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_1->width= DIM_FILTER;
    m2_1->height=DIM_FILTER;
    A2_1st->m=m2_1;
    RandomFilter2(A2_1st->m, DIM_FILTER*DIM_FILTER);

    struct ALLFilters2 *A2_2nd;
    A2_2nd= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_2;
    m2_2= malloc (sizeof(Matrix));
    m2_2->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_2->width= DIM_FILTER;
    m2_2->height=DIM_FILTER;
    A2_2nd->m=m2_2;
    RandomFilter2(A2_2nd->m, DIM_FILTER*DIM_FILTER);
    A2_1st->next=A2_2nd;

    struct ALLFilters2 *A2_3rd;
    A2_3rd= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_3;
    m2_3= malloc (sizeof(Matrix));
    m2_3->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_3->width= DIM_FILTER;
    m2_3->height=DIM_FILTER;
    A2_3rd->m=m2_3;
    RandomFilter2(A2_3rd->m, DIM_FILTER*DIM_FILTER);
    A2_2nd->next=A2_3rd;

    struct ALLFilters2 *A2_4th;
    A2_4th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_4;
    m2_4= malloc (sizeof(Matrix));
    m2_4->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_4->width= DIM_FILTER;
    m2_4->height=DIM_FILTER;
    A2_4th->m=m2_4;
    RandomFilter2(A2_4th->m, DIM_FILTER*DIM_FILTER);
    A2_3rd->next=A2_4th;

    struct ALLFilters2 *A2_5th;
    A2_5th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_5;
    m2_5= malloc (sizeof(Matrix));
    m2_5->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_5->width= DIM_FILTER;
    m2_5->height=DIM_FILTER;
    A2_5th->m=m2_5;
    RandomFilter2(A2_5th->m, DIM_FILTER*DIM_FILTER);
    A2_4th->next=A2_5th;

    struct ALLFilters2 *A2_6th;
    A2_6th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_6;
    m2_6= malloc (sizeof(Matrix));
    m2_6->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_6->width= DIM_FILTER;
    m2_6->height=DIM_FILTER;
    A2_6th->m=m2_6;
    RandomFilter2(A2_6th->m, DIM_FILTER*DIM_FILTER);
    A2_5th->next=A2_6th;

    struct ALLFilters2 *A2_7th;
    A2_7th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_7;
    m2_7= malloc (sizeof(Matrix));
    m2_7->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_7->width= DIM_FILTER;
    m2_7->height=DIM_FILTER;
    A2_7th->m=m2_7;
    RandomFilter2(A2_7th->m, DIM_FILTER*DIM_FILTER);
    A2_6th->next=A2_7th;

    struct ALLFilters2 *A2_8th;
    A2_8th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_8;
    m2_8= malloc (sizeof(Matrix));
    m2_8->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_8->width= DIM_FILTER;
    m2_8->height=DIM_FILTER;
    A2_8th->m=m2_8;
    RandomFilter2(A2_8th->m, DIM_FILTER*DIM_FILTER);
    A2_7th->next=A2_8th;

    struct ALLFilters2 *A2_9th;
    A2_9th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_9;
    m2_9= malloc (sizeof(Matrix));
    m2_9->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_9->width= DIM_FILTER;
    m2_9->height=DIM_FILTER;
    A2_9th->m=m2_9;
    RandomFilter2(A2_9th->m, DIM_FILTER*DIM_FILTER);
    A2_8th->next=A2_9th;

    struct ALLFilters2 *A2_10th;
    A2_10th= malloc (sizeof(struct ALLFilters2));
    Matrix *m2_10;
    m2_10= malloc (sizeof(Matrix));
    m2_10->matrix= calloc(DIM_FILTER*DIM_FILTER,sizeof(double));
    m2_10->width= DIM_FILTER;
    m2_10->height=DIM_FILTER;
    A2_10th->m=m2_10;
    RandomFilter2(A2_10th->m, DIM_FILTER*DIM_FILTER);
    A2_9th->next=A2_10th;
    A2_10th->next=NULL;

   // printf("All filters2 loaded [ok] \n" );


    //______________________________________________________________________________________
    //Convolution Layer2

    struct ALLFM2 *convl1;
    convl1 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf1;
    cvf1=malloc (sizeof(Matrix));
    cvf1->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf1->width= DIM_C2;
    cvf1->height=DIM_C2;
    convl1->m=cvf1;

    struct ALLFM2 *convl2;
    convl2 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf2;
    cvf2=malloc (sizeof(Matrix));
    cvf2->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf2->width= DIM_C2;
    cvf2->height=DIM_C2;
    convl2->m=cvf2;
    convl1->next=convl2;

    struct ALLFM2 *convl3;
    convl3 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf3;
    cvf3=malloc (sizeof(Matrix));
    cvf3->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf3->width= DIM_C2;
    cvf3->height=DIM_C2;
    convl3->m=cvf3;
    convl2->next=convl3;

    struct ALLFM2 *convl4;
    convl4 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf4;
    cvf4=malloc (sizeof(Matrix));
    cvf4->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf4->width= DIM_C2;
    cvf4->height=DIM_C2;
    convl4->m=cvf4;
    convl3->next=convl4;

    struct ALLFM2 *convl5;
    convl5 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf5;
    cvf5=malloc (sizeof(Matrix));
    cvf5->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf5->width= DIM_C2;
    cvf5->height=DIM_C2;
    convl5->m=cvf5;
    convl4->next=convl5;

    struct ALLFM2 *convl6;
    convl6 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf6;
    cvf6=malloc (sizeof(Matrix));
    cvf6->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf6->width= DIM_C2;
    cvf6->height=DIM_C2;
    convl6->m=cvf6;
    convl5->next=convl6;

    struct ALLFM2 *convl7;
    convl7 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf7;
    cvf7=malloc (sizeof(Matrix));
    cvf7->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf7->width= DIM_C2;
    cvf7->height=DIM_C2;
    convl7->m=cvf7;
    convl6->next=convl7;

    struct ALLFM2 *convl8;
    convl8 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf8;
    cvf8=malloc (sizeof(Matrix));
    cvf8->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf8->width= DIM_C2;
    cvf8->height=DIM_C2;
    convl8->m=cvf8;
    convl7->next=convl8;

    struct ALLFM2 *convl9;
    convl9 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf9;
    cvf9=malloc (sizeof(Matrix));
    cvf9->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf9->width= DIM_C2;
    cvf9->height=DIM_C2;
    convl9->m=cvf9;
    convl8->next=convl9;

    struct ALLFM2 *convl10;
    convl10 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf10;
    cvf10=malloc (sizeof(Matrix));
    cvf10->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf10->width= DIM_C2;
    cvf10->height=DIM_C2;
    convl10->m=cvf10;
    convl9->next=convl10;

    struct ALLFM2 *convl11;
    convl11 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf11;
    cvf11=malloc (sizeof(Matrix));
    cvf11->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf11->width= DIM_C2;
    cvf11->height=DIM_C2;
    convl11->m=cvf11;
    convl10->next=convl11;

    struct ALLFM2 *convl12;
    convl12 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf12;
    cvf12=malloc (sizeof(Matrix));
    cvf12->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf12->width= DIM_C2;
    cvf12->height=DIM_C2;
    convl12->m=cvf12;
    convl11->next=convl12;

    struct ALLFM2 *convl13;
    convl13 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf13;
    cvf13=malloc (sizeof(Matrix));
    cvf13->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf13->width= DIM_C2;
    cvf13->height=DIM_C2;
    convl13->m=cvf13;
    convl12->next=convl13;

    struct ALLFM2 *convl14;
    convl14 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf14;
    cvf14=malloc (sizeof(Matrix));
    cvf14->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf14->width= DIM_C2;
    cvf14->height=DIM_C2;
    convl14->m=cvf14;
    convl13->next=convl14;

    struct ALLFM2 *convl15;
    convl15 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf15;
    cvf15=malloc (sizeof(Matrix));
    cvf15->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf15->width= DIM_C2;
    cvf15->height=DIM_C2;
    convl15->m=cvf15;
    convl14->next=convl15;

    struct ALLFM2 *convl16;
    convl16 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf16;
    cvf16=malloc (sizeof(Matrix));
    cvf16->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf16->width= DIM_C2;
    cvf16->height=DIM_C2;
    convl16->m=cvf16;
    convl15->next=convl16;

    struct ALLFM2 *convl17;
    convl17 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf17;
    cvf17=malloc (sizeof(Matrix));
    cvf17->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf17->width= DIM_C2;
    cvf17->height=DIM_C2;
    convl17->m=cvf17;
    convl16->next=convl17;

    struct ALLFM2 *convl18;
    convl18 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf18;
    cvf18=malloc (sizeof(Matrix));
    cvf18->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf18->width= DIM_C2;
    cvf18->height=DIM_C2;
    convl18->m=cvf18;
    convl17->next=convl18;

    struct ALLFM2 *convl19;
    convl19 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf19;
    cvf19=malloc (sizeof(Matrix));
    cvf19->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf19->width= DIM_C2;
    cvf19->height=DIM_C2;
    convl19->m=cvf19;
    convl18->next=convl19;

    struct ALLFM2 *convl20;
    convl20 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf20;
    cvf20=malloc (sizeof(Matrix));
    cvf20->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf20->width= DIM_C2;
    cvf20->height=DIM_C2;
    convl20->m=cvf20;
    convl19->next=convl20;

    struct ALLFM2 *convl21;
    convl21 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf21;
    cvf21=malloc (sizeof(Matrix));
    cvf21->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf21->width= DIM_C2;
    cvf21->height=DIM_C2;
    convl21->m=cvf21;
    convl20->next=convl21;

    struct ALLFM2 *convl22;
    convl22 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf22;
    cvf22=malloc (sizeof(Matrix));
    cvf22->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf22->width= DIM_C2;
    cvf22->height=DIM_C2;
    convl22->m=cvf22;
    convl21->next=convl22;

    struct ALLFM2 *convl23;
    convl23 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf23;
    cvf23=malloc (sizeof(Matrix));
    cvf23->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf23->width= DIM_C2;
    cvf23->height=DIM_C2;
    convl23->m=cvf23;
    convl22->next=convl23;

    struct ALLFM2 *convl24;
    convl24 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf24;
    cvf24=malloc (sizeof(Matrix));
    cvf24->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf24->width= DIM_C2;
    cvf24->height=DIM_C2;
    convl24->m=cvf24;
    convl23->next=convl24;

struct ALLFM2 *convl25;
    convl25 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf25;
    cvf25=malloc (sizeof(Matrix));
    cvf25->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf25->width= DIM_C2;
    cvf25->height=DIM_C2;
    convl25->m=cvf25;
    convl24->next=convl25;

    struct ALLFM2 *convl26;
    convl26 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf26;
    cvf26=malloc (sizeof(Matrix));
    cvf26->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf26->width= DIM_C2;
    cvf26->height=DIM_C2;
    convl26->m=cvf26;
    convl25->next=convl26;

    struct ALLFM2 *convl27;
    convl27 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf27;
    cvf27=malloc (sizeof(Matrix));
    cvf27->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf27->width= DIM_C2;
    cvf27->height=DIM_C2;
    convl27->m=cvf27;
    convl26->next=convl27;

    struct ALLFM2 *convl28;
    convl28 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf28;
    cvf28=malloc (sizeof(Matrix));
    cvf28->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf28->width= DIM_C2;
    cvf28->height=DIM_C2;
    convl28->m=cvf28;
    convl27->next=convl28;

    struct ALLFM2 *convl29;
    convl29 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf29;
    cvf29=malloc (sizeof(Matrix));
    cvf29->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf29->width= DIM_C2;
    cvf29->height=DIM_C2;
    convl29->m=cvf29;
    convl28->next=convl29;

    struct ALLFM2 *convl30;
    convl30 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf30;
    cvf30=malloc (sizeof(Matrix));
    cvf30->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf30->width= DIM_C2;
    cvf30->height=DIM_C2;
    convl30->m=cvf30;
    convl29->next=convl30;

    struct ALLFM2 *convl31;
    convl31 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf31;
    cvf31=malloc (sizeof(Matrix));
    cvf31->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf31->width= DIM_C2;
    cvf31->height=DIM_C2;
    convl31->m=cvf31;
    convl30->next=convl31;

    struct ALLFM2 *convl32;
    convl32 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf32;
    cvf32=malloc (sizeof(Matrix));
    cvf32->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf32->width= DIM_C2;
    cvf32->height=DIM_C2;
    convl32->m=cvf32;
    convl31->next=convl32;

    struct ALLFM2 *convl33;
    convl33 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf33;
    cvf33=malloc (sizeof(Matrix));
    cvf33->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf33->width= DIM_C2;
    cvf33->height=DIM_C2;
    convl33->m=cvf33;
    convl32->next=convl33;

    struct ALLFM2 *convl34;
    convl34 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf34;
    cvf34=malloc (sizeof(Matrix));
    cvf34->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf34->width= DIM_C2;
    cvf34->height=DIM_C2;
    convl34->m=cvf34;
    convl33->next=convl34;

    struct ALLFM2 *convl35;
    convl35 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf35;
    cvf35=malloc (sizeof(Matrix));
    cvf35->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf35->width= DIM_C2;
    cvf35->height=DIM_C2;
    convl35->m=cvf35;
    convl34->next=convl35;

    struct ALLFM2 *convl36;
    convl36 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf36;
    cvf36=malloc (sizeof(Matrix));
    cvf36->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf36->width= DIM_C2;
    cvf36->height=DIM_C2;
    convl36->m=cvf36;
    convl35->next=convl36;

    struct ALLFM2 *convl37;
    convl37 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf37;
    cvf37=malloc (sizeof(Matrix));
    cvf37->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf37->width= DIM_C2;
    cvf37->height=DIM_C2;
    convl37->m=cvf37;
    convl36->next=convl37;

    struct ALLFM2 *convl38;
    convl38 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf38;
    cvf38=malloc (sizeof(Matrix));
    cvf38->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf38->width= DIM_C2;
    cvf38->height=DIM_C2;
    convl38->m=cvf38;
    convl37->next=convl38;

    struct ALLFM2 *convl39;
    convl39 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf39;
    cvf39=malloc (sizeof(Matrix));
    cvf39->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf39->width= DIM_C2;
    cvf39->height=DIM_C2;
    convl39->m=cvf39;
    convl38->next=convl39;

    struct ALLFM2 *convl40;
    convl40 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf40;
    cvf40=malloc (sizeof(Matrix));
    cvf40->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf40->width= DIM_C2;
    cvf40->height=DIM_C2;
    convl40->m=cvf40;
    convl39->next=convl40;


    struct ALLFM2 *convl41;
    convl41 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf41;
    cvf41=malloc (sizeof(Matrix));
    cvf41->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf41->width= DIM_C2;
    cvf41->height=DIM_C2;
    convl41->m=cvf41;
    convl40->next=convl41;

    struct ALLFM2 *convl42;
    convl42 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf42;
    cvf42=malloc (sizeof(Matrix));
    cvf42->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf42->width= DIM_C2;
    cvf42->height=DIM_C2;
    convl42->m=cvf42;
    convl41->next=convl42;

    struct ALLFM2 *convl43;
    convl43 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf43;
    cvf43=malloc (sizeof(Matrix));
    cvf43->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf43->width= DIM_C2;
    cvf43->height=DIM_C2;
    convl43->m=cvf43;
    convl42->next=convl43;

    struct ALLFM2 *convl44;
    convl44 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf44;
    cvf44=malloc (sizeof(Matrix));
    cvf44->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf44->width= DIM_C2;
    cvf44->height=DIM_C2;
    convl44->m=cvf44;
    convl43->next=convl44;

struct ALLFM2 *convl45;
    convl45 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf45;
    cvf45=malloc (sizeof(Matrix));
    cvf45->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf45->width= DIM_C2;
    cvf45->height=DIM_C2;
    convl45->m=cvf45;
    convl44->next=convl45;

    struct ALLFM2 *convl46;
    convl46 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf46;
    cvf46=malloc (sizeof(Matrix));
    cvf46->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf46->width= DIM_C2;
    cvf46->height=DIM_C2;
    convl46->m=cvf46;
    convl45->next=convl46;

    struct ALLFM2 *convl47;
    convl47 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf47;
    cvf47=malloc (sizeof(Matrix));
    cvf47->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf47->width= DIM_C2;
    cvf47->height=DIM_C2;
    convl47->m=cvf47;
    convl46->next=convl47;

    struct ALLFM2 *convl48;
    convl48 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf48;
    cvf48=malloc (sizeof(Matrix));
    cvf48->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf48->width= DIM_C2;
    cvf48->height=DIM_C2;
    convl48->m=cvf48;
    convl47->next=convl48;
    struct ALLFM2 *convl49;
    convl49 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf49;
    cvf49=malloc (sizeof(Matrix));
    cvf49->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf49->width= DIM_C2;
    cvf49->height=DIM_C2;
    convl49->m=cvf49;
    convl48->next=convl49;

    struct ALLFM2 *convl50;
    convl50 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf50;
    cvf50=malloc (sizeof(Matrix));
    cvf50->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf50->width= DIM_C2;
    cvf50->height=DIM_C2;
    convl50->m=cvf50;
    convl49->next=convl50;

    struct ALLFM2 *convl51;
    convl51 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf51;
    cvf51=malloc (sizeof(Matrix));
    cvf51->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf51->width= DIM_C2;
    cvf51->height=DIM_C2;
    convl51->m=cvf51;
    convl50->next=convl51;
    struct ALLFM2 *convl52;
    convl52 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf52;
    cvf52=malloc (sizeof(Matrix));
    cvf52->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf52->width= DIM_C2;
    cvf52->height=DIM_C2;
    convl52->m=cvf52;
    convl51->next=convl52;

    struct ALLFM2 *convl53;
    convl53 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf53;
    cvf53=malloc (sizeof(Matrix));
    cvf53->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf53->width= DIM_C2;
    cvf53->height=DIM_C2;
    convl53->m=cvf53;
    convl52->next=convl53;

    struct ALLFM2 *convl54;
    convl54 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf54;
    cvf54=malloc (sizeof(Matrix));
    cvf54->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf54->width= DIM_C2;
    cvf54->height=DIM_C2;
    convl54->m=cvf54;
    convl53->next=convl54;

    struct ALLFM2 *convl55;
    convl55 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf55;
    cvf55=malloc (sizeof(Matrix));
    cvf55->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf55->width= DIM_C2;
    cvf55->height=DIM_C2;
    convl55->m=cvf55;
    convl54->next=convl55;

    struct ALLFM2 *convl56;
    convl56 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf56;
    cvf56=malloc (sizeof(Matrix));
    cvf56->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf56->width= DIM_C2;
    cvf56->height=DIM_C2;
    convl56->m=cvf56;
    convl55->next=convl56;

    struct ALLFM2 *convl57;
    convl57 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf57;
    cvf57=malloc (sizeof(Matrix));
    cvf57->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf57->width= DIM_C2;
    cvf57->height=DIM_C2;
    convl57->m=cvf57;
    convl56->next=convl57;

    struct ALLFM2 *convl58;
    convl58 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf58;
    cvf58=malloc (sizeof(Matrix));
    cvf58->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf58->width= DIM_C2;
    cvf58->height=DIM_C2;
    convl58->m=cvf58;
    convl57->next=convl58;

    struct ALLFM2 *convl59;
    convl59 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf59;
    cvf59=malloc (sizeof(Matrix));
    cvf59->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf59->width= DIM_C2;
    cvf59->height=DIM_C2;
    convl59->m=cvf59;
    convl58->next=convl59;

    struct ALLFM2 *convl60;
    convl60 = malloc (sizeof(struct ALLFM2));
    Matrix *cvf60;
    cvf60=malloc (sizeof(Matrix));
    cvf60->matrix= calloc(DIM_C2*DIM_C2,sizeof(double));
    cvf60->width= DIM_C2;
    cvf60->height=DIM_C2;
    convl60->m=cvf60;
    convl59->next=convl60;
    convl60->next=NULL;

    //printf("All convolution2 init [ok] \n" );

    //______________________________________________________________________________________
    //Pooling Layer2
    //struct PoolC2 *poolC2_1= init_pool(60);
    struct PoolC2 *poolC2_1;
    poolC2_1 = malloc (sizeof(struct PoolC2));
    Matrix *newM1;
    newM1=malloc (sizeof(Matrix));
    newM1->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM1->width= DIM_POOL2;
    newM1->height=DIM_POOL2;
    poolC2_1->m=newM1;

    struct PoolC2 *poolC2_2;
    poolC2_2 = malloc (sizeof(struct PoolC2));
    Matrix *newM2;
    newM2=malloc (sizeof(Matrix));
    newM2->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM2->width= DIM_POOL2;
    newM2->height=DIM_POOL2;
    poolC2_2->m=newM2;
    poolC2_1->next=poolC2_2;

    struct PoolC2 *poolC2_3;
    poolC2_3 = malloc (sizeof(struct PoolC2));
    Matrix *newM3;
    newM3=malloc (sizeof(Matrix));
    newM3->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM3->width= DIM_POOL2;
    newM3->height=DIM_POOL2;
    poolC2_3->m=newM3;
    poolC2_2->next=poolC2_3;

    struct PoolC2 *poolC2_4;
    poolC2_4 = malloc (sizeof(struct PoolC2));
    Matrix *newM4;
    newM4=malloc (sizeof(Matrix));
    newM4->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM4->width= DIM_POOL2;
    newM4->height=DIM_POOL2;
    poolC2_4->m=newM4;
    poolC2_3->next=poolC2_4;

    struct PoolC2 *poolC2_5;
    poolC2_5 = malloc (sizeof(struct PoolC2));
    Matrix *newM5;
    newM5=malloc (sizeof(Matrix));
    newM5->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM5->width= DIM_POOL2;
    newM5->height=DIM_POOL2;
    poolC2_5->m=newM5;
    poolC2_4->next=poolC2_5;

    struct PoolC2 *poolC2_6;
    poolC2_6 = malloc (sizeof(struct PoolC2));
    Matrix *newM6;
    newM6=malloc (sizeof(Matrix));
    newM6->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM6->width= DIM_POOL2;
    newM6->height=DIM_POOL2;
    poolC2_6->m=newM6;
    poolC2_5->next=poolC2_6;

    struct PoolC2 *poolC2_7;
    poolC2_7 = malloc (sizeof(struct PoolC2));
    Matrix *newM7;
    newM7=malloc (sizeof(Matrix));
    newM7->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM7->width= DIM_POOL2;
    newM7->height=DIM_POOL2;
    poolC2_7->m=newM7;
    poolC2_6->next=poolC2_7;

    struct PoolC2 *poolC2_8;
    poolC2_8 = malloc (sizeof(struct PoolC2));
    Matrix *newM8;
    newM8=malloc (sizeof(Matrix));
    newM8->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM8->width= DIM_POOL2;
    newM8->height=DIM_POOL2;
    poolC2_8->m=newM8;
    poolC2_7->next=poolC2_8;

    struct PoolC2 *poolC2_9;
    poolC2_9 = malloc (sizeof(struct PoolC2));
    Matrix *newM9;
    newM9=malloc (sizeof(Matrix));
    newM9->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM9->width= DIM_POOL2;
    newM9->height=DIM_POOL2;
    poolC2_9->m=newM9;
    poolC2_8->next=poolC2_9;

    struct PoolC2 *poolC2_10;
    poolC2_10 = malloc (sizeof(struct PoolC2));
    Matrix *newM10;
    newM10=malloc (sizeof(Matrix));
    newM10->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM10->width= DIM_POOL2;
    newM10->height=DIM_POOL2;
    poolC2_10->m=newM10;
    poolC2_9->next=poolC2_10;

    struct PoolC2 *poolC2_11;
    poolC2_11 = malloc (sizeof(struct PoolC2));
    Matrix *newM11;
    newM11=malloc (sizeof(Matrix));
    newM11->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM11->width= DIM_POOL2;
    newM11->height=DIM_POOL2;
    poolC2_11->m=newM11;
    poolC2_10->next=poolC2_11;

    struct PoolC2 *poolC2_12;
    poolC2_12 = malloc (sizeof(struct PoolC2));
    Matrix *newM12;
    newM12=malloc (sizeof(Matrix));
    newM12->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM12->width= DIM_POOL2;
    newM12->height=DIM_POOL2;
    poolC2_12->m=newM12;
    poolC2_11->next=poolC2_12;

    struct PoolC2 *poolC2_13;
    poolC2_13 = malloc (sizeof(struct PoolC2));
    Matrix *newM13;
    newM13=malloc (sizeof(Matrix));
    newM13->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM13->width= DIM_POOL2;
    newM13->height=DIM_POOL2;
    poolC2_13->m=newM13;
    poolC2_12->next=poolC2_13;

    struct PoolC2 *poolC2_14;
    poolC2_14 = malloc (sizeof(struct PoolC2));
    Matrix *newM14;
    newM14=malloc (sizeof(Matrix));
    newM14->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM14->width= DIM_POOL2;
    newM14->height=DIM_POOL2;
    poolC2_14->m=newM14;
    poolC2_13->next=poolC2_14;

    struct PoolC2 *poolC2_15;
    poolC2_15 = malloc (sizeof(struct PoolC2));
    Matrix *newM15;
    newM15=malloc (sizeof(Matrix));
    newM15->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM15->width= DIM_POOL2;
    newM15->height=DIM_POOL2;
    poolC2_15->m=newM15;
    poolC2_14->next=poolC2_15;

    struct PoolC2 *poolC2_16;
    poolC2_16 = malloc (sizeof(struct PoolC2));
    Matrix *newM16;
    newM16=malloc (sizeof(Matrix));
    newM16->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM16->width= DIM_POOL2;
    newM16->height=DIM_POOL2;
    poolC2_16->m=newM16;
    poolC2_15->next=poolC2_16;

    struct PoolC2 *poolC2_17;
    poolC2_17 = malloc (sizeof(struct PoolC2));
    Matrix *newM17;
    newM17=malloc (sizeof(Matrix));
    newM17->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM17->width= DIM_POOL2;
    newM17->height=DIM_POOL2;
    poolC2_17->m=newM17;
    poolC2_16->next=poolC2_17;

    struct PoolC2 *poolC2_18;
    poolC2_18 = malloc (sizeof(struct PoolC2));
    Matrix *newM18;
    newM18=malloc (sizeof(Matrix));
    newM18->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM18->width= DIM_POOL2;
    newM18->height=DIM_POOL2;
    poolC2_18->m=newM18;
    poolC2_17->next=poolC2_18;

    struct PoolC2 *poolC2_19;
    poolC2_19 = malloc (sizeof(struct PoolC2));
    Matrix *newM19;
    newM19=malloc (sizeof(Matrix));
    newM19->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM19->width= DIM_POOL2;
    newM19->height=DIM_POOL2;
    poolC2_19->m=newM19;
    poolC2_18->next=poolC2_19;

    struct PoolC2 *poolC2_20;
    poolC2_20 = malloc (sizeof(struct PoolC2));
    Matrix *newM20;
    newM20=malloc (sizeof(Matrix));
    newM20->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM20->width= DIM_POOL2;
    newM20->height=DIM_POOL2;
    poolC2_20->m=newM20;
    poolC2_19->next=poolC2_20;

    struct PoolC2 *poolC2_21;
    poolC2_21 = malloc (sizeof(struct PoolC2));
    Matrix *newM21;
    newM21=malloc (sizeof(Matrix));
    newM21->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM21->width= DIM_POOL2;
    newM21->height=DIM_POOL2;
    poolC2_21->m=newM21;
    poolC2_20->next=poolC2_21;

    struct PoolC2 *poolC2_22;
    poolC2_22 = malloc (sizeof(struct PoolC2));
    Matrix *newM22;
    newM22=malloc (sizeof(Matrix));
    newM22->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM22->width= DIM_POOL2;
    newM22->height=DIM_POOL2;
    poolC2_22->m=newM22;
    poolC2_21->next=poolC2_22;

    struct PoolC2 *poolC2_23;
    poolC2_23 = malloc (sizeof(struct PoolC2));
    Matrix *newM23;
    newM23=malloc (sizeof(Matrix));
    newM23->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM23->width= DIM_POOL2;
    newM23->height=DIM_POOL2;
    poolC2_23->m=newM23;
    poolC2_22->next=poolC2_23;

    struct PoolC2 *poolC2_24;
    poolC2_24 = malloc (sizeof(struct PoolC2));
    Matrix *newM24;
    newM24=malloc (sizeof(Matrix));
    newM24->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM24->width= DIM_POOL2;
    newM24->height=DIM_POOL2;
    poolC2_24->m=newM24;
    poolC2_23->next=poolC2_24;

struct PoolC2 *poolC2_25;
    poolC2_25 = malloc (sizeof(struct PoolC2));
    Matrix *newM25;
    newM25=malloc (sizeof(Matrix));
    newM25->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM25->width= DIM_POOL2;
    newM25->height=DIM_POOL2;
    poolC2_25->m=newM25;
    poolC2_24->next=poolC2_25;

    struct PoolC2 *poolC2_26;
    poolC2_26 = malloc (sizeof(struct PoolC2));
    Matrix *newM26;
    newM26=malloc (sizeof(Matrix));
    newM26->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM26->width= DIM_POOL2;
    newM26->height=DIM_POOL2;
    poolC2_26->m=newM26;
    poolC2_25->next=poolC2_26;

    struct PoolC2 *poolC2_27;
    poolC2_27 = malloc (sizeof(struct PoolC2));
    Matrix *newM27;
    newM27=malloc (sizeof(Matrix));
    newM27->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM27->width= DIM_POOL2;
    newM27->height=DIM_POOL2;
    poolC2_27->m=newM27;
    poolC2_26->next=poolC2_27;

    struct PoolC2 *poolC2_28;
    poolC2_28 = malloc (sizeof(struct PoolC2));
    Matrix *newM28;
    newM28=malloc (sizeof(Matrix));
    newM28->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM28->width= DIM_POOL2;
    newM28->height=DIM_POOL2;
    poolC2_28->m=newM28;
    poolC2_27->next=poolC2_28;

    struct PoolC2 *poolC2_29;
    poolC2_29 = malloc (sizeof(struct PoolC2));
    Matrix *newM29;
    newM29=malloc (sizeof(Matrix));
    newM29->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM29->width= DIM_POOL2;
    newM29->height=DIM_POOL2;
    poolC2_29->m=newM29;
    poolC2_28->next=poolC2_29;

    struct PoolC2 *poolC2_30;
    poolC2_30 = malloc (sizeof(struct PoolC2));
    Matrix *newM30;
    newM30=malloc (sizeof(Matrix));
    newM30->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM30->width= DIM_POOL2;
    newM30->height=DIM_POOL2;
    poolC2_30->m=newM30;
    poolC2_29->next=poolC2_30;

    struct PoolC2 *poolC2_31;
    poolC2_31 = malloc (sizeof(struct PoolC2));
    Matrix *newM31;
    newM31=malloc (sizeof(Matrix));
    newM31->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM31->width= DIM_POOL2;
    newM31->height=DIM_POOL2;
    poolC2_31->m=newM31;
    poolC2_30->next=poolC2_31;

    struct PoolC2 *poolC2_32;
    poolC2_32 = malloc (sizeof(struct PoolC2));
    Matrix *newM32;
    newM32=malloc (sizeof(Matrix));
    newM32->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM32->width= DIM_POOL2;
    newM32->height=DIM_POOL2;
    poolC2_32->m=newM32;
    poolC2_31->next=poolC2_32;

    struct PoolC2 *poolC2_33;
    poolC2_33 = malloc (sizeof(struct PoolC2));
    Matrix *newM33;
    newM33=malloc (sizeof(Matrix));
    newM33->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM33->width= DIM_POOL2;
    newM33->height=DIM_POOL2;
    poolC2_33->m=newM33;
    poolC2_32->next=poolC2_33;

    struct PoolC2 *poolC2_34;
    poolC2_34 = malloc (sizeof(struct PoolC2));
    Matrix *newM34;
    newM34=malloc (sizeof(Matrix));
    newM34->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM34->width= DIM_POOL2;
    newM34->height=DIM_POOL2;
    poolC2_34->m=newM34;
    poolC2_33->next=poolC2_34;

    struct PoolC2 *poolC2_35;
    poolC2_35 = malloc (sizeof(struct PoolC2));
    Matrix *newM35;
    newM35=malloc (sizeof(Matrix));
    newM35->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM35->width= DIM_POOL2;
    newM35->height=DIM_POOL2;
    poolC2_35->m=newM35;
    poolC2_34->next=poolC2_35;

    struct PoolC2 *poolC2_36;
    poolC2_36 = malloc (sizeof(struct PoolC2));
    Matrix *newM36;
    newM36=malloc (sizeof(Matrix));
    newM36->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM36->width= DIM_POOL2;
    newM36->height=DIM_POOL2;
    poolC2_36->m=newM36;
    poolC2_35->next=poolC2_36;

    struct PoolC2 *poolC2_37;
    poolC2_37 = malloc (sizeof(struct PoolC2));
    Matrix *newM37;
    newM37=malloc (sizeof(Matrix));
    newM37->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM37->width= DIM_POOL2;
    newM37->height=DIM_POOL2;
    poolC2_37->m=newM37;
    poolC2_36->next=poolC2_37;

    struct PoolC2 *poolC2_38;
    poolC2_38 = malloc (sizeof(struct PoolC2));
    Matrix *newM38;
    newM38=malloc (sizeof(Matrix));
    newM38->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM38->width= DIM_POOL2;
    newM38->height=DIM_POOL2;
    poolC2_38->m=newM38;
    poolC2_37->next=poolC2_38;

    struct PoolC2 *poolC2_39;
    poolC2_39 = malloc (sizeof(struct PoolC2));
    Matrix *newM39;
    newM39=malloc (sizeof(Matrix));
    newM39->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM39->width= DIM_POOL2;
    newM39->height=DIM_POOL2;
    poolC2_39->m=newM39;
    poolC2_38->next=poolC2_39;

    struct PoolC2 *poolC2_40;
    poolC2_40 = malloc (sizeof(struct PoolC2));
    Matrix *newM40;
    newM40=malloc (sizeof(Matrix));
    newM40->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM40->width= DIM_POOL2;
    newM40->height=DIM_POOL2;
    poolC2_40->m=newM40;
    poolC2_39->next=poolC2_40;


    struct PoolC2 *poolC2_41;
    poolC2_41 = malloc (sizeof(struct PoolC2));
    Matrix *newM41;
    newM41=malloc (sizeof(Matrix));
    newM41->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM41->width= DIM_POOL2;
    newM41->height=DIM_POOL2;
    poolC2_41->m=newM41;
    poolC2_40->next=poolC2_41;

    struct PoolC2 *poolC2_42;
    poolC2_42 = malloc (sizeof(struct PoolC2));
    Matrix *newM42;
    newM42=malloc (sizeof(Matrix));
    newM42->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM42->width= DIM_POOL2;
    newM42->height=DIM_POOL2;
    poolC2_42->m=newM42;
    poolC2_41->next=poolC2_42;

    struct PoolC2 *poolC2_43;
    poolC2_43 = malloc (sizeof(struct PoolC2));
    Matrix *newM43;
    newM43=malloc (sizeof(Matrix));
    newM43->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM43->width= DIM_POOL2;
    newM43->height=DIM_POOL2;
    poolC2_43->m=newM43;
    poolC2_42->next=poolC2_43;

    struct PoolC2 *poolC2_44;
    poolC2_44 = malloc (sizeof(struct PoolC2));
    Matrix *newM44;
    newM44=malloc (sizeof(Matrix));
    newM44->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM44->width= DIM_POOL2;
    newM44->height=DIM_POOL2;
    poolC2_44->m=newM44;
    poolC2_43->next=poolC2_44;

struct PoolC2 *poolC2_45;
    poolC2_45 = malloc (sizeof(struct PoolC2));
    Matrix *newM45;
    newM45=malloc (sizeof(Matrix));
    newM45->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM45->width= DIM_POOL2;
    newM45->height=DIM_POOL2;
    poolC2_45->m=newM45;
    poolC2_44->next=poolC2_45;

    struct PoolC2 *poolC2_46;
    poolC2_46 = malloc (sizeof(struct PoolC2));
    Matrix *newM46;
    newM46=malloc (sizeof(Matrix));
    newM46->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM46->width= DIM_POOL2;
    newM46->height=DIM_POOL2;
    poolC2_46->m=newM46;
    poolC2_45->next=poolC2_46;

    struct PoolC2 *poolC2_47;
    poolC2_47 = malloc (sizeof(struct PoolC2));
    Matrix *newM47;
    newM47=malloc (sizeof(Matrix));
    newM47->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM47->width= DIM_POOL2;
    newM47->height=DIM_POOL2;
    poolC2_47->m=newM47;
    poolC2_46->next=poolC2_47;

    struct PoolC2 *poolC2_48;
    poolC2_48 = malloc (sizeof(struct PoolC2));
    Matrix *newM48;
    newM48=malloc (sizeof(Matrix));
    newM48->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM48->width= DIM_POOL2;
    newM48->height=DIM_POOL2;
    poolC2_48->m=newM48;
    poolC2_47->next=poolC2_48;
    struct PoolC2 *poolC2_49;
    poolC2_49 = malloc (sizeof(struct PoolC2));
    Matrix *newM49;
    newM49=malloc (sizeof(Matrix));
    newM49->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM49->width= DIM_POOL2;
    newM49->height=DIM_POOL2;
    poolC2_49->m=newM49;
    poolC2_48->next=poolC2_49;

    struct PoolC2 *poolC2_50;
    poolC2_50 = malloc (sizeof(struct PoolC2));
    Matrix *newM50;
    newM50=malloc (sizeof(Matrix));
    newM50->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM50->width= DIM_POOL2;
    newM50->height=DIM_POOL2;
    poolC2_50->m=newM50;
    poolC2_49->next=poolC2_50;

    struct PoolC2 *poolC2_51;
    poolC2_51 = malloc (sizeof(struct PoolC2));
    Matrix *newM51;
    newM51=malloc (sizeof(Matrix));
    newM51->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM51->width= DIM_POOL2;
    newM51->height=DIM_POOL2;
    poolC2_51->m=newM51;
    poolC2_50->next=poolC2_51;
    struct PoolC2 *poolC2_52;
    poolC2_52 = malloc (sizeof(struct PoolC2));
    Matrix *newM52;
    newM52=malloc (sizeof(Matrix));
    newM52->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM52->width= DIM_POOL2;
    newM52->height=DIM_POOL2;
    poolC2_52->m=newM52;
    poolC2_51->next=poolC2_52;

    struct PoolC2 *poolC2_53;
    poolC2_53 = malloc (sizeof(struct PoolC2));
    Matrix *newM53;
    newM53=malloc (sizeof(Matrix));
    newM53->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM53->width= DIM_POOL2;
    newM53->height=DIM_POOL2;
    poolC2_53->m=newM53;
    poolC2_52->next=poolC2_53;

    struct PoolC2 *poolC2_54;
    poolC2_54 = malloc (sizeof(struct PoolC2));
    Matrix *newM54;
    newM54=malloc (sizeof(Matrix));
    newM54->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM54->width= DIM_POOL2;
    newM54->height=DIM_POOL2;
    poolC2_54->m=newM54;
    poolC2_53->next=poolC2_54;

    struct PoolC2 *poolC2_55;
    poolC2_55 = malloc (sizeof(struct PoolC2));
    Matrix *newM55;
    newM55=malloc (sizeof(Matrix));
    newM55->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM55->width= DIM_POOL2;
    newM55->height=DIM_POOL2;
    poolC2_55->m=newM55;
    poolC2_54->next=poolC2_55;

    struct PoolC2 *poolC2_56;
    poolC2_56 = malloc (sizeof(struct PoolC2));
    Matrix *newM56;
    newM56=malloc (sizeof(Matrix));
    newM56->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM56->width= DIM_POOL2;
    newM56->height=DIM_POOL2;
    poolC2_56->m=newM56;
    poolC2_55->next=poolC2_56;

    struct PoolC2 *poolC2_57;
    poolC2_57 = malloc (sizeof(struct PoolC2));
    Matrix *newM57;
    newM57=malloc (sizeof(Matrix));
    newM57->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM57->width= DIM_POOL2;
    newM57->height=DIM_POOL2;
    poolC2_57->m=newM57;
    poolC2_56->next=poolC2_57;

    struct PoolC2 *poolC2_58;
    poolC2_58 = malloc (sizeof(struct PoolC2));
    Matrix *newM58;
    newM58=malloc (sizeof(Matrix));
    newM58->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM58->width= DIM_POOL2;
    newM58->height=DIM_POOL2;
    poolC2_58->m=newM58;
    poolC2_57->next=poolC2_58;

    struct PoolC2 *poolC2_59;
    poolC2_59 = malloc (sizeof(struct PoolC2));
    Matrix *newM59;
    newM59=malloc (sizeof(Matrix));
    newM59->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM59->width= DIM_POOL2;
    newM59->height=DIM_POOL2;
    poolC2_59->m=newM59;
    poolC2_58->next=poolC2_59;

    struct PoolC2 *poolC2_60;
    poolC2_60 = malloc (sizeof(struct PoolC2));
    Matrix *newM60;
    newM60=malloc (sizeof(Matrix));
    newM60->matrix= calloc(DIM_POOL2*DIM_POOL2,sizeof(double));
    newM60->width= DIM_POOL2;
    newM60->height=DIM_POOL2;
    poolC2_60->m=newM60;
    poolC2_59->next=poolC2_60;
    poolC2_60->next=NULL;

    //printf("All pooling init2 [ok] \n" );


    //______________________________________________________________________________________
    struct CL_out *outin = init_out(NB_Char);

    //printf("All output [ok] \n");


    // 8) Flattern Layer -> First Fully Connected Layer
    size_t all= NB_FILTERS2 * NB_FILTERS1 * DIM_POOL2 * DIM_POOL2;
    struct FL *flatterned1 = init_fl(all);

    //printf("All flatterning [ok] \n" );


    // 9) Final Connected Layer with char as neurons
  //  struct CL_out *outin = init_out(NB_Char);

  //  printf("All output [ok] \n");

    printf("all structures are done and are up and working \n");

    //___________________________________________________________________________________
    //Getting input matrix


    // STARTING THE TRAINING
    init_sdl();

    for(int i=0; i<NB_ITERATION; i++)
    {
    struct sendback imp = GetRandomSet();

    SDL_Surface* img = load_image(imp.path);

    Matrix matrice1 = surface_to_matrix_grayscale(img);


    int seuil = otsu(img);


    Matrix input =  matrix_grayscale_to_binar(matrice1, seuil) ;
    SDL_FreeSurface(img);

    printf("image to matrice for path %s [ok] \n",imp.path );


    // Forward Propagate __________________________________________________________________________

        // 2) C1 -> Convolutional Layer with 6 filters to get 6 feature maps

        //Going -> Convolution Layer 1
        ConvolutionLayer1(convo1,A1_1st, input);

      //  printf("Convolution1   [ok]   \n");
        // 3) Relu activation function on feature maps
        ReluActiv1(convo1);

        //printf("Relu1   [ok]   \n");
        // 4) Pooling
         Pool1(convo1, poolC1);

        //printf("Pooling1   [ok]   \n");

        // 5) C2 -> Convolutional Layer with 16 filters for each feature maps to get new feature maps
        ConvolutionLayer2( A2_1st, poolC1, convl1);

        //printf("Convolution2   [ok]   \n");
        // 6) Relu activation function on the feature maps
        ReluActiv2(convl1);

        // printf("Relu2   [ok]   \n");
        // 7) Pooling
        Pool2(convl1, poolC2_1);

        //printf("Pooling2   [ok]   \n");
        // 8) Flattern Layer -> First Fully Connected Layer
        FlatternLayer( poolC2_1, flatterned1);

        //printf("Flattern Layer   [ok]   \n");
        FullyConnectedLayer1(flatterned1, outin);

       // printf("Fully Connected Layer   [ok]   \n");
        // 9) Fully connected output layer
        struct resultsfromoutput output=GetOutPut( outin);

        printf("The output is: %f and should be %d \n",output.ASCII, imp.ASCII);

        //_____________________________________________________________________________
        // BackPropagation
        //1) OutPut
        int BinIndicaor= imp.ASCII;
        if(imp.ASCII<58)
        {
          BinIndicaor-=48;
        }
        else
        {
          if (imp.ASCII<91) {
            BinIndicaor-=65;
          } else {
            BinIndicaor-=97;
          }
        }

        double cross= CrossEntropy(outin, BinIndicaor);
        printf("cross Entropy is %f \n",cross);

        BackforOutput(outin, BinIndicaor);
        printf("Back For output [ok] \n" );

        //2) Last Pooling (C2)
        //GradientsFromPoolingLast(poolC2_1, convl1);
        //printf(" Back for gradient pool C2 [ok] \n" );

        // 3) C2 Filters
        //BackForFiltersLast(A2_1st, convl1,poolC1);
        //printf("Back for filters C2 [ok] \n" );

        // 4) Pool layer C1
        //GradientsFromPooling(poolC1, convo1);
        //printf("Back for pool layers 1 [ok] \n" );

        // 5) C1 FIlters
        //BackForFilters(A1_1st, convo1, input);
        //printf("Back for filters C1 [ok] \n" );

        //free_Matrix2(input);
        //free_Matrix2(matrice1);
        freeMatrix1(input);
        freeMatrix1(matrice1);

        }
        //FREE ALL MEMORY
        //Free all of this

        //Input Matrix

        //Free 1 set of filters
        printf("until freed memory [ok] \n");
        //Free 1st layer of pooling
        free_ALLFilters1(A1_1st);

        //printf("free first filters [ok] \n");
        //Free 1st layer of convolution
        free_ALLFM1(convo1);

      //  printf("free first feature maps [ok] \n");
        //Free 1st layer of pooling
        free_PoolC1(poolC1);

        //printf("free first pooling layers [ok] \n");

        //Free 2nd set of filters
        free_ALLFilters2(A2_1st);

        //printf("free second filters [ok] \n");
        //Free 2nd layer of convolution
        free_ALLMaps2(convl1);

        //printf("free second feature maps [ok] \n");

        //Free 2nd layer of Pooling
        free_PoolC2(poolC2_1);

        //printf("free second pooling [ok] \n");

        //Free Flatterned Layer
        free_FlatternedLayer(flatterned1);

        //printf("free flattern layer [ok] \n");
        //Free output layer
        free_OutPutLayer(outin);

        //printf("free output layer [ok] \n");
        printf("all free [ok] \n");

        return 0;

}
