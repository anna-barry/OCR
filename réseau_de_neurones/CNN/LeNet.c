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
 * These are the structures and functions needed for training
 *                  version 1.0 8/12/2020
 *
 */


// Include section
 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>
 #include "../../Tools/matrix.h"
#include <err.h>
#include <string.h>
#include <time.h>

//___________________________________________________________________________
//
////1) Model initialization
//TRAINING MODEL

struct TM
{
   Matrix M;
   int result;
 };

struct sendback
{
    char path[50];
    int ASCII;
};

//_________________________________ Needed Maths functions ___________________
// Returns int between 0 and max:
#define RANDOM_RANGE(max) ( rand() % max )
// Returns double between 0 and 1:
#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )

#define max(a,b) (a>=b?a:b)
#define min(a,b) ((a) < (b) ? (a) : (b))



//_________ Constants
#define DIM_INPUT 32
#define DIM_C1 28
#define NB_FILTERS1 6
#define DIM_FILTER 5
#define DIM_POOL1 14
#define FILTER_WP1 2
#define NB_FILTERS2 10
#define DIM_C2 10
#define DIM_POOL2 5
#define NB_Char 60
#define NB_ITERATION 1200

//__________________________________________________________________________________
//
//                                      Main
//
//__________________________________________________________________________________

/*struct ALLFilters1 *init_ALLF1()
{
    struct ALLFilters1 *my_ALL = malloc(sizeof(struct ALLFilters1));
    struct Matrix *m1 = malloc(sizeof(struct Matrix));
    m1.width =
    m1.height =
    m1->matrix =
    my_ALL->matrix = m1;
    struct ALLFilters1 *second = ma;loc
    struct ALLFilters1 *tmp = my_ALL;
    while (tmp && tmp->next)
        free(tmp->matrix->matrix)

        tmp = tmp->next;
}*/

// Filters for C1
struct ALLFilters1{
    Matrix *m;
    struct ALLFilters1 *next;
};

//Feature Maps for C1
struct ALLFM1{
    Matrix *m;
    struct ALLFM1 *next;

};

//New Matrixes for Pooling for C1
struct PoolC1{
    //NB_FILTERS1
    Matrix *m;
    struct PoolC1 *next;
};

//Filters for C2
struct ALLFilters2{
    //NB_FILTERS2
    Matrix *m;
    struct ALLFilters2 *next;

};

//Feature Maps for C2
struct ALLFM2{
    //NB_FILTERS2
  Matrix *m;
  struct ALLFM2 *next;

};

//New Matrixes for Pooling for C2
struct PoolC2{
    //NB_FILTERS2
    Matrix *m;
    struct PoolC2 *next;

};

// Neuron Structure
struct Neuron{
        double input;
        double weight;
        double bias;
};

//Flatterning Layer with neuron implementation -> Fully connected layer
struct FL{
    //DIM_POOL2*DIM_POOL2*NB_FILTERS2
    struct Neuron *n;
};


//Fully Connected Layer for output
struct CL_out{
    //NB_Char
    struct Neuron *n;
};


//______ Function for filters C1 _________________________________________________________

// "They’re usually randomly initialised and then learned over the course of training."

//________________________________________________________________________________________

//______ Function for Convolution C1 _____________________________________________________
void ConvolutionLayer1(struct ALLFM1 *cfm1, struct ALLFilters1 *A1, Matrix input)
{
    struct ALLFilters1 *currfilter =NULL;
    currfilter=A1;

    struct ALLFM1 *currFeatureMap=NULL;
    currFeatureMap=cfm1;
    printf("________________________ Convolution1 _____________________________________ \n");
    //printf("input is: \n" );
    //print_Matrix(input);

    for(int i=0; i<NB_FILTERS1; i++)
    {
        double *cfilter =NULL;
        cfilter=currfilter->m->matrix;

        double *cfeatureM=NULL;
        cfeatureM=currFeatureMap->m->matrix;

        for(int k=0; (k+4)<DIM_INPUT;k++)
        {
            for(int l=0; (l+4)<DIM_INPUT; l++)
            {
                for(int j=0;j<DIM_FILTER;j++)
                {
                cfeatureM[k*DIM_C1+l]+= input.matrix[k*DIM_INPUT+(l+j)]* (cfilter[0*DIM_FILTER+j]);
                cfeatureM[k*DIM_C1+l]+= input.matrix[(k+1)*DIM_INPUT+(l+j)]* (cfilter[1*DIM_FILTER+j]);
                cfeatureM[k*DIM_C1+l]+= input.matrix[(k+2)*DIM_INPUT+(l+j)]* (cfilter[2*DIM_FILTER+j]);
                cfeatureM[k*DIM_C1+l]+= input.matrix[(k+3)*DIM_INPUT+(l+j)]* (cfilter[3*DIM_FILTER+j]);
                cfeatureM[k*DIM_C1+l]+= input.matrix[(k+5)*DIM_INPUT+(l+j)]* (cfilter[4*DIM_FILTER+j]);
                }
            }
        }
        //printf("Filter is \n" );
        //print_Matrix(*(currfilter->m));
        //printf("output is \n" );
        //print_Matrix(*(currFeatureMap->m));

        currfilter=currfilter->next;
        currFeatureMap=currFeatureMap->next;
    }

}

//_____________________________________________________________________________________

// 3) Relu activation after C1 ________________________________________________________
void ReluActiv1(struct ALLFM1 *cfm1)
{
    /*
    for(int i=0;i<NB_FILTERS1; i++)
    {
        for(int y=0; y<DIM_C1; y++)
        {
            for(int x=0; x<DIM_C1;x++)
            {
                cfm1->fm1[i].matrix[y*DIM_C1+x]=max(0, cfm1->fm1[i].matrix[y*DIM_C1+x]);
            }
        }
    }*/
    //printf("Relu 1 _________________________________________________________\n" );
    //printf("relu n1 works? \n");
    struct ALLFM1 *currFeatureMap=NULL;
    currFeatureMap=cfm1;

    for(int i=0;i<NB_FILTERS1;i++)
    {
        double *indexConv= NULL;
        indexConv=(currFeatureMap->m->matrix);

        for(int y=0; y<DIM_C1; y++)
         {
            for(int x=0; x<DIM_C1;x++)
            {
                indexConv[y*DIM_C1+x]=max(0, indexConv[y*DIM_C1+x]);
             }
         }

         //print_Matrix(*(currFeatureMap->m));
        currFeatureMap=currFeatureMap->next;
    }
}
//_____________________________________________________________________________________


// 4) Pooling after C1's activation
void Pool1(struct ALLFM1 *cfm1,struct PoolC1 *pc1)
{

  //printf("Poooling 1 _____________________________________________________________________________________\n" );
    //printf("Pooling 1 \n");
    struct ALLFM1 *currFeatureMap=NULL;
    currFeatureMap=cfm1;

    struct PoolC1 *currPool=NULL;
    currPool= pc1;

    for(int i=0;i<NB_FILTERS1;i++)
    {
        double *indexConv= NULL;
        indexConv=(currFeatureMap->m->matrix);

        double *indexPool=NULL;
        indexPool=(currPool->m->matrix);

        int i4pool=0;
         for(int k=0; k<DIM_C1; k+=2)
        {
            for(int l=0;l<DIM_C1;l+=2)
            {

            double maxi=max(indexConv[k*DIM_C1+l],indexConv[k*DIM_C1+l+1]);
            maxi=max(maxi,max(indexConv[k*DIM_C1+l+1],indexConv[k+1*DIM_C1+l+1]));

            maxi=max(maxi,(max(indexConv[k+1*DIM_C1+l+1],indexConv[k+1*DIM_C1+l])));

            maxi=max(maxi,(max(indexConv[k*DIM_C1+l],indexConv[k+1*DIM_C1+l])));


            indexPool[i4pool]=maxi;
            i4pool+=1;
            }
            }
            //print_Matrix(*(currPool->m));
            currFeatureMap=currFeatureMap->next;
            currPool=currPool->next;
    }

}

//_____________________________________________________________________________________
// FOR C2 _____________________________________________________________________________


//______ Function for Convolution C2  _____________________________________________________
void ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1,struct ALLFM2 *cfm2)
{

    //printf("CONVOLUTION 2______________________________________________________________ \n" );

    int indexForTest=0;
    struct PoolC1 *curPool=NULL;
    curPool= pc1;

    struct ALLFilters2 *currfilter =NULL;
    currfilter=A2;

    struct ALLFM2 *currFeatureMap=NULL;
    currFeatureMap=cfm2;

    for(int i0=0; i0<NB_FILTERS1;i0++)
    {
        currfilter=A2;
        //printf("Input \n" );
        //print_Matrix(*(curPool->m));

         for(int i=0; i<NB_FILTERS2; i++)
    {
        double *cfilter =NULL;
        cfilter=currfilter->m->matrix;

        int index=0;

        double *cfeatureM=NULL;
        cfeatureM=currFeatureMap->m->matrix;

        double *cPool=NULL;
         cPool=curPool->m->matrix;

        for(int k=0; (k+4)<DIM_POOL1;k++)
        {
            for(int l=0; (l+4)<DIM_POOL1; l++)
            {
                for(int j=0;j<DIM_FILTER;j++)
                {

                cfeatureM[index]+= cPool[k*DIM_POOL1+(l+j)]* (cfilter[0*DIM_FILTER+j]);
                cfeatureM[index]+= cPool[(k+1)*DIM_POOL1+(l+j)]* (cfilter[1*DIM_FILTER+j]);
                cfeatureM[index]+= cPool[(k+2)*DIM_POOL1+(l+j)]* (cfilter[2*DIM_FILTER+j]);
                cfeatureM[index]+= cPool[(k+3)*DIM_POOL1+(l+j)]* (cfilter[3*DIM_FILTER+j]);
                cfeatureM[index]+= cPool[(k+5)*DIM_POOL1+(l+j)]* (cfilter[4*DIM_FILTER+j]);
                }
                index+=1;
            }
        }
        indexForTest+=1;

        //printf("Filter is \n" );
        //print_Matrix(*(currfilter->m));
        //printf("input is Pooling layer 1: \n" );
        //print_Matrix(*(curPool->m));
        //printf("output is \n" );
        //print_Matrix(*(currFeatureMap->m));

        currfilter=currfilter->next;
        currFeatureMap=currFeatureMap->next;
    }
        curPool=curPool->next;
    }
}

//_____________________________________________________________________________________

// 3) Relu activation after C2 ________________________________________________________
void ReluActiv2(struct ALLFM2 *cfm2)
{
    struct ALLFM2 *currFeatureMap=NULL;
    currFeatureMap=cfm2;

    for(int i=0;i<NB_FILTERS2*NB_FILTERS1;i++)
    {
        double *indexConv= NULL;
        indexConv=(currFeatureMap->m->matrix);

        for(int y=0; y<DIM_C2; y++)
         {
            for(int x=0; x<DIM_C2;x++)
            {
                indexConv[y*DIM_C2+x]=max(0, indexConv[y*DIM_C2+x]);
             }
         }
        currFeatureMap=currFeatureMap->next;
    }

}
//_____________________________________________________________________________________
struct PoolC2 *init_pool(size_t n)
{
    struct PoolC2 *new;
    new= malloc (sizeof(struct PoolC2));
    Matrix *newM;
    newM = malloc (sizeof(Matrix));
    newM->matrix = calloc(DIM_POOL2 * DIM_POOL2, sizeof(double));
    newM->width = DIM_POOL2;
    newM->height = DIM_POOL2;
    new->m = newM;
    new->next=NULL;

    size_t i = 0;

    while (i < n)
    {
        struct PoolC2 *tmp = new;

        while (tmp && tmp->next)
        {
            printf("here?\n");
            tmp=tmp->next;
        }
        struct PoolC2 *tmp2;
        tmp2= malloc (sizeof(struct PoolC2));
        Matrix *tempM;
        tempM = malloc (sizeof(Matrix));
        tempM->matrix = calloc(DIM_POOL2 * DIM_POOL2, sizeof(double));
        tempM->width = DIM_POOL2;
        tempM->height = DIM_POOL2;
        tmp2->m = tempM;
        tmp->next=tmp2;

        i++;
    }
    return new;

}
// 4) Pooling after C2's activation
void Pool2(struct ALLFM2 *cfm2,struct PoolC2 *pc2)
{
    //printf("Poooling 2 _____________________________________________________________________________________\n" );
    //printf("In pooling 2 \n");
    struct ALLFM2 *currFeatureMap=NULL;
    currFeatureMap=cfm2;

    struct PoolC2 *currPool=NULL;
    currPool= pc2;

    for(int i=0;i<(NB_FILTERS2*NB_FILTERS1);i++)
    {
        double *indexConv= NULL;
        indexConv=(currFeatureMap->m->matrix);
        double *indexPool=NULL;
        indexPool = currPool->m->matrix;

        int i4pool=0;
        for(int k=0; (k+1)<DIM_C2; k+=2)

        {
            for(int l=0;(l+1)<DIM_C2;l+=2)
            {
                double maxi=max(indexConv[k*DIM_C2+l],indexConv[k*DIM_C2+(l+1)]);
                        maxi=max(maxi,max(indexConv[k*DIM_C2+(l+1)],indexConv[(k+1)*DIM_C2+(l+1)]));
                        maxi=max(maxi,(max(indexConv[(k+1)*DIM_C2+(l+1)],indexConv[(k+1)*DIM_C2+l])));
                        maxi=max(maxi,(max(indexConv[k*DIM_C2+l],indexConv[(k+1)*DIM_C2+l])));

                    indexPool[i4pool]=maxi;
                    i4pool+=1;

            }
        }
        //print_Matrix(*(currPool->m));
        currFeatureMap=currFeatureMap->next;
        currPool=currPool->next;

    }

}

//____________________________________________________________________________________
// 8) Flattern Layer + First Fully Connected Layer
struct FL *init_fl(int n)
{
    struct FL *new;
    new= malloc (sizeof ( struct FL ));
    struct Neuron *newN;
    newN = malloc(n * sizeof(struct Neuron));
    for(int i=0;i<n;i++)
    {
        double random1=RAND_DOUBLE;
        double random2=RAND_DOUBLE;
        //printf("both randoms are %f and %f for flattern layer for n°%d \n",random1, random2,i);
        newN[i].input=0;
        newN[i].weight=random1;
        newN[i].bias=random2;
    }
    new->n = newN;
    return new;
}

//Init Fully Connected Layer
struct CL_out *init_out(int n)
{

    struct CL_out *newCL;
    newCL= malloc(sizeof (struct CL_out));
    struct Neuron *newN2;
    newN2 = malloc(n * sizeof(struct Neuron));
    for(int i=0;i<(int)n;i++)
    {
        double random1=RAND_DOUBLE;
        double random2=RAND_DOUBLE;
        //printf("both randoms are %f and %f for output layer \n",random1, random2);
        newN2[i].input=0;
        newN2[i].weight=random1;
        newN2[i].bias=random2;
    }
    newCL->n = newN2;

    return newCL;
}



//Works
void FlatternLayer(struct PoolC2 *pc2,struct FL *res)
{

    struct PoolC2 *currPool = NULL;
    currPool = pc2;

    struct Neuron *CurNeu=NULL;
    CurNeu= res->n;
    //printf("before loop Current wieght and bias for 512 %f %f\n", CurNeu[512].weight,CurNeu[512].bias);

    int indexForFlat=0;

    for (int i = 0; i < NB_FILTERS2 * NB_FILTERS1 ; i++)
    {
        double *indexPool= NULL;
        indexPool=(currPool->m->matrix);

        //print_Matrix(*(currPool->m));

        //printf("in for i Current wieght and bias for 512 %f %f\n", CurNeu[512].weight,CurNeu[512].bias);
        for(int j=0; j< DIM_POOL2; j++)
        {
            for(int k=0; k< DIM_POOL2;k++ )
            {
              //printf("in double for Current wieght and bias for 512 %f %f\n", CurNeu[512].weight,CurNeu[512].bias);
                CurNeu[indexForFlat].input= indexPool[(j*DIM_POOL2)+k];

                //printf("Current input for fully connected is %f with weight=%f and bias=%f for n°%d \n",CurNeu[indexForFlat].input,CurNeu[indexForFlat].weight,CurNeu[indexForFlat].bias, indexForFlat);
                indexForFlat+=1;

            }
        }
        currPool=currPool->next;
    }

    indexForFlat=0;
    double sum=0;
    for (int i = 0; i < (NB_FILTERS2 * NB_FILTERS1*DIM_POOL2*DIM_POOL2) ; i++)
    {
        sum=sum+exp(CurNeu[indexForFlat].input);
        indexForFlat+=1;
    }

    indexForFlat=0;

    for (int i = 0; i < (NB_FILTERS2 * NB_FILTERS1*DIM_POOL2*DIM_POOL2) ; i++)
    {
        CurNeu[indexForFlat].input= exp(CurNeu[indexForFlat].input)/sum;
        indexForFlat+=1;
    }

   /* for(int w=0;w<NB_FILTERS2 * NB_FILTERS1;w++)
    {
        printf("value n°%d is %f \n",w,CurNeu[w].input);
    }*/

}

//____________________________________________________________________________________
//9) Fully Connected Layer

double GetInputFromFC(struct FL *flatterned)
{

    double res=0;
    struct Neuron *CurNeu=NULL;
    CurNeu= flatterned->n;


    for(int i=0; i<NB_FILTERS1*NB_FILTERS2*DIM_POOL2*DIM_POOL2; i++)
    {
        //Dropout -> not all features are seen for better performance

        double drop= ( (double)rand()/(double)RAND_MAX );
        //printf("probability is %f \n",drop );
        if(drop>0.4)
        {

              //printf(" the input is %f for n°%d with weights =%f and bias=%f \n", (CurNeu[i].input*CurNeu[i].weight + CurNeu[i].bias),i,CurNeu[i].weight,CurNeu[i].bias);
              //printf("res is %f for now \n",res );
            res+=max(0,(CurNeu[i].input*CurNeu[i].weight + CurNeu[i].bias));

        }

    }
    //printf("res from fc is %f \n",res );
    return max(res,0);
}



void FullyConnectedLayer1(struct FL *flatterned, struct CL_out *outin)
{
  struct CL_out *IndexOut=NULL;
  IndexOut=outin;

  struct Neuron *CurNeu=NULL;
  CurNeu=IndexOut->n;

    for(int i=0; i<NB_Char;i++)
    {
        double getres=GetInputFromFC(flatterned);
        CurNeu[i].input= getres;
        //printf("input from flattern to fully connected layer after getInputFromFC %f \n", getres);
    }
}

//10) Get output with softmax -> OutPut Layer
struct resultsfromoutput{
    double ASCII;
    double i;
    double output;
    double weight;
    double bias;
};
struct resultsfromoutput GetOutPut(struct CL_out *outin)
{
    double sum= 0;

    struct CL_out *IndexOut=NULL;
    IndexOut=outin;

    struct Neuron *outN=NULL;
    outN=IndexOut->n;


    for (int i=0;i<(NB_Char);i++)
    {
        //printf("the input is %f for n°%d \n",outN[i].input,i );
        //printf("exp of all this is %f with weight=%f and bias=%f for %i \n", exp(outN[i].input * outN[i].weight + outN[i].bias), outN[i].weight, outN[i].bias,i);
        sum=sum+exp(max(0,outN[i].input * outN[i].weight + outN[i].bias));
    }

    //printf("sum is %f \n",sum );

    //outN=IndexOut->n;

    double maxiO=exp((outN[0].input*outN[0].weight)+outN[0].bias)/sum;
    double maxA=0;
    double maxI=0;
    double maxW=outN[0].weight;
    double maxB=outN[0].bias;
    for(int i=1; i<NB_Char; i++)
    {
        double curexp=exp((outN[i].input*outN[i].weight)+outN[i].bias)/sum;
        if (curexp>maxiO)
        {
            maxiO=curexp;
            maxA=i;
            maxI=i;
            maxW=outN[i].weight;
            maxB=outN[i].bias;
        }
        //printf("current is %f \n", curexp);
    }

    // Digits
    if (maxA<10)
    {
        maxA+=48;
    }
    else
    {
        //Lower letters
        if(maxA<35)
        {
            maxA+=97;
        }
        else
        {
            //Capital letters
            maxA+=65;
        }
    }
    printf("maxA is %f \n",maxA);
    struct resultsfromoutput res={maxA,maxI,maxiO,maxW,maxB};
    return res;
}

//________________________________________________________________________
//Free functions
void free_Matrix(Matrix *m)
{
        if (!m)
            return;
        if (m->matrix)
        {
            free(m->matrix);
            m->matrix = NULL;
        }
        free(m);
        m = NULL;
}

void free_Matrix2(Matrix m)
{
    if(!m.matrix)
        return;
    if(m.matrix)
    {
        free(m.matrix);
        m.width=0;
        m.height=0;
        m.matrix=NULL;

    }

}
void freeMatrix1(Matrix M){
  free(M.matrix);
  M.width = 0;
  M.height = 0;
}
void free_FlatternedLayer(struct FL *flatterned1)
{
    if(!flatterned1)
    {
        return;
    }
    if(flatterned1->n)
    {
        free(flatterned1->n);
        flatterned1->n=NULL;
    }
    free(flatterned1);
    flatterned1= NULL;
}

void free_OutPutLayer(struct CL_out *out)
{
    if(!out)
        return;
    if(out->n)
    {
        free(out->n);
        out->n=NULL;
    }
    free(out);
    out=NULL;
}

void free_ALLFilters1(struct ALLFilters1 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_ALLFilters1(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}

void free_ALLFM1(struct ALLFM1 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_ALLFM1(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}
void free_PoolC1(struct PoolC1 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_PoolC1(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}

void free_ALLFilters2(struct ALLFilters2 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_ALLFilters2(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}

void free_ALLMaps2(struct ALLFM2 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_ALLMaps2(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}
void free_PoolC2(struct PoolC2 *p)
{
    if (!p)
            return;
    if (p->m)
    {
        free_Matrix(p->m);
        p->m = NULL;
    }
    if (p->next)
    {
        free_PoolC2(p->next);
        p->next = NULL;
    }
    free(p);
    p = NULL;
}

//____________________________ Random training sets

struct sendback GetRandomSet()
{

    char Limages[434][50]={"images/Arial_Unicode.ttf/0_1.bmp", "images/Arial_Unicode.ttf/1_2.bmp",
        "images/Arial_Unicode.ttf/2_3.bmp",  "images/Arial_Unicode.ttf/3_4.bmp",
        "images/Arial_Unicode.ttf/4_5.bmp","images/Arial_Unicode.ttf/5_6.bmp",
         "images/Arial_Unicode.ttf/6_7.bmp", "images/Arial_Unicode.ttf/7_8.bmp",
         "images/Arial_Unicode.ttf/8_9.bmp",  "images/Arial_Unicode.ttf/9_10.bmp",
          "images/Arial_Unicode.ttf/a_11.bmp",
        "images/Arial_Unicode.ttf/A_37.bmp", "images/Arial_Unicode.ttf/b_12.bmp",
        "images/Arial_Unicode.ttf/B_38.bmp", "images/Arial_Unicode.ttf/c_13.bmp",
        "images/Arial_Unicode.ttf/C_39.bmp", "images/Arial_Unicode.ttf/d_14.bmp",
        "images/Arial_Unicode.ttf/D_40.bmp", "images/Arial_Unicode.ttf/e_15.bmp",
        "images/Arial_Unicode.ttf/E_41.bmp", "images/Arial_Unicode.ttf/f_16.bmp",
        "images/Arial_Unicode.ttf/F_42.bmp", "images/Arial_Unicode.ttf/g_17.bmp",
         "images/Arial_Unicode.ttf/G_43.bmp", "images/Arial_Unicode.ttf/h_18.bmp",
          "images/Arial_Unicode.ttf/H_44.bmp",  "images/Arial_Unicode.ttf/i_19.bmp",
            "images/Arial_Unicode.ttf/I_45.bmp", "images/Arial_Unicode.ttf/j_20.bmp",
            "images/Arial_Unicode.ttf/J_46.bmp", "images/Arial_Unicode.ttf/k_21.bmp",
            "images/Arial_Unicode.ttf/K_47.bmp", "images/Arial_Unicode.ttf/l_22.bmp",
            "images/Arial_Unicode.ttf/L_48.bmp",  "images/Arial_Unicode.ttf/m_23.bmp",
            "images/Arial_Unicode.ttf/M_49.bmp",  "images/Arial_Unicode.ttf/n_24.bmp",
             "images/Arial_Unicode.ttf/N_50.bmp",  "images/Arial_Unicode.ttf/o_25.bmp",
              "images/Arial_Unicode.ttf/O_51.bmp",  "images/Arial_Unicode.ttf/p_26.bmp",
               "images/Arial_Unicode.ttf/P_52.bmp",  "images/Arial_Unicode.ttf/q_27.bmp",
                "images/Arial_Unicode.ttf/Q_53.bmp",  "images/Arial_Unicode.ttf/r_28.bmp",
                  "images/Arial_Unicode.ttf/R_54.bmp",  "images/Arial_Unicode.ttf/s_29.bmp",
                    "images/Arial_Unicode.ttf/S_55.bmp",  "images/Arial_Unicode.ttf/t_30.bmp",
                      "images/Arial_Unicode.ttf/T_56.bmp",  "images/Arial_Unicode.ttf/u_31.bmp",
                  "images/Arial_Unicode.ttf/U_57.bmp",  "images/Arial_Unicode.ttf/v_32.bmp",
                   "images/Arial_Unicode.ttf/V_58.bmp",  "images/Arial_Unicode.ttf/w_33.bmp",
                    "images/Arial_Unicode.ttf/W_59.bmp", "images/Arial_Unicode.ttf/x_34.bmp",
                    "images/Arial_Unicode.ttf/X_60.bmp",  "images/Arial_Unicode.ttf/y_35.bmp",
                      "images/Arial_Unicode.ttf/Y_61.bmp",  "images/Arial_Unicode.ttf/z_36.bmp",
                        "images/Arial_Unicode.ttf/Z_62.bmp", "images/Avenir.ttc/0_1.bmp",
                         "images/Avenir.ttc/1_2.bmp", "images/Avenir.ttc/2_3.bmp",
                         "images/Avenir.ttc/3_4.bmp", "images/Avenir.ttc/4_5.bmp",
                          "images/Avenir.ttc/5_6.bmp", "images/Avenir.ttc/6_7.bmp",
                           "images/Avenir.ttc/7_8.bmp", "images/Avenir.ttc/8_9.bmp",
                            "images/Avenir.ttc/9_10.bmp",  "images/Avenir.ttc/a_11.bmp",
                             "images/Avenir.ttc/A_37.bmp", "images/Avenir.ttc/b_12.bmp",
                               "images/Avenir.ttc/B_38.bmp", "images/Avenir.ttc/c_13.bmp",
                                "images/Avenir.ttc/C_39.bmp", "images/Avenir.ttc/d_14.bmp",
                                 "images/Avenir.ttc/D_40.bmp", "images/Avenir.ttc/e_15.bmp",
                          "images/Avenir.ttc/E_41.bmp", "images/Avenir.ttc/f_16.bmp",
                           "images/Avenir.ttc/F_42.bmp", "images/Avenir.ttc/g_17.bmp"
                           , "images/Avenir.ttc/G_43.bmp", "images/Avenir.ttc/h_18.bmp",
                            "images/Avenir.ttc/H_44.bmp",  "images/Avenir.ttc/i_19.bmp",
                             "images/Avenir.ttc/I_45.bmp", "images/Avenir.ttc/j_20.bmp",
                              "images/Avenir.ttc/J_46.bmp", "images/Avenir.ttc/k_21.bmp",
                              "images/Avenir.ttc/K_47.bmp", "images/Avenir.ttc/l_22.bmp",
                               "images/Avenir.ttc/L_48.bmp",  "images/Avenir.ttc/m_23.bmp",
                                 "images/Avenir.ttc/M_49.bmp",  "images/Avenir.ttc/n_24.bmp",
                                   "images/Avenir.ttc/N_50.bmp",  "images/Avenir.ttc/o_25.bmp",
                                     "images/Avenir.ttc/O_51.bmp",  "images/Avenir.ttc/p_26.bmp",
                                       "images/Avenir.ttc/P_52.bmp",  "images/Avenir.ttc/q_27.bmp",
                                      "images/Avenir.ttc/Q_53.bmp",  "images/Avenir.ttc/r_28.bmp",
                                        "images/Avenir.ttc/R_54.bmp",  "images/Avenir.ttc/s_29.bmp",
                                          "images/Avenir.ttc/S_55.bmp",  "images/Avenir.ttc/t_30.bmp",
                                      "images/Avenir.ttc/T_56.bmp",  "images/Avenir.ttc/u_31.bmp",
                                       "images/Avenir.ttc/U_57.bmp",  "images/Avenir.ttc/v_32.bmp",
                                        "images/Avenir.ttc/V_58.bmp",  "images/Avenir.ttc/w_33.bmp",
                                         "images/Avenir.ttc/W_59.bmp", "images/Avenir.ttc/x_34.bmp",
                                         "images/Avenir.ttc/X_60.bmp",  "images/Avenir.ttc/y_35.bmp",
                                           "images/Avenir.ttc/Y_61.bmp",  "images/Avenir.ttc/z_36.bmp",
                                            "images/Avenir.ttc/Z_62.bmp",  "images/Courier.dfont/0_1.bmp",
                                      "images/Courier.dfont/1_2.bmp", "images/Courier.dfont/2_3.bmp",
                                      "images/Courier.dfont/3_4.bmp", "images/Courier.dfont/4_5.bmp",
                                       "images/Courier.dfont/5_6.bmp", "images/Courier.dfont/6_7.bmp",
                                        "images/Courier.dfont/7_8.bmp", "images/Courier.dfont/8_9.bmp",
                                      "images/Courier.dfont/9_10.bmp",  "images/Courier.dfont/a_11.bmp",
                                       "images/Courier.dfont/A_37.bmp", "images/Courier.dfont/b_12.bmp",
                                        "images/Courier.dfont/B_38.bmp", "images/Courier.dfont/c_13.bmp",
                                     "images/Courier.dfont/C_39.bmp", "images/Courier.dfont/d_14.bmp",
                                     "images/Courier.dfont/D_40.bmp", "images/Courier.dfont/e_15.bmp",
                                     "images/Courier.dfont/E_41.bmp", "images/Courier.dfont/f_16.bmp",
                                     "images/Courier.dfont/F_42.bmp", "images/Courier.dfont/g_17.bmp",
                                     "images/Courier.dfont/G_43.bmp", "images/Courier.dfont/h_18.bmp",
                                      "images/Courier.dfont/H_44.bmp",  "images/Courier.dfont/i_19.bmp",
                                        "images/Courier.dfont/I_45.bmp", "images/Courier.dfont/j_20.bmp",
                                         "images/Courier.dfont/J_46.bmp", "images/Courier.dfont/k_21.bmp",
                                          "images/Courier.dfont/K_47.bmp", "images/Courier.dfont/l_22.bmp",
                                         "images/Courier.dfont/L_48.bmp",  "images/Courier.dfont/m_23.bmp",
                                           "images/Courier.dfont/M_49.bmp",  "images/Courier.dfont/n_24.bmp",
                                        "images/Courier.dfont/N_50.bmp",  "images/Courier.dfont/o_25.bmp",
                                       "images/Courier.dfont/O_51.bmp",  "images/Courier.dfont/p_26.bmp",
                                     "images/Courier.dfont/P_52.bmp",  "images/Courier.dfont/q_27.bmp",
                                   "images/Courier.dfont/Q_53.bmp",  "images/Courier.dfont/r_28.bmp",
                                    "images/Courier.dfont/R_54.bmp",  "images/Courier.dfont/s_29.bmp",
                                      "images/Courier.dfont/S_55.bmp",  "images/Courier.dfont/t_30.bmp",
                                       "images/Courier.dfont/T_56.bmp",  "images/Courier.dfont/u_31.bmp",
                                        "images/Courier.dfont/U_57.bmp",  "images/Courier.dfont/v_32.bmp",
                                         "images/Courier.dfont/V_58.bmp",  "images/Courier.dfont/w_33.bmp",
                                         "images/Courier.dfont/W_59.bmp", "images/Courier.dfont/x_34.bmp",
                                         "images/Courier.dfont/X_60.bmp",  "images/Courier.dfont/y_35.bmp",
                                           "images/Courier.dfont/Y_61.bmp",  "images/Courier.dfont/z_36.bmp",
                                            "images/Courier.dfont/Z_62.bmp",  "images/Geneva.dfont/0_1.bmp",
                                            "images/Geneva.dfont/1_2.bmp", "images/Geneva.dfont/2_3.bmp",
                                             "images/Geneva.dfont/3_4.bmp", "images/Geneva.dfont/4_5.bmp",
                                             "images/Geneva.dfont/5_6.bmp", "images/Geneva.dfont/6_7.bmp",
                                              "images/Geneva.dfont/7_8.bmp", "images/Geneva.dfont/8_9.bmp",
                                               "images/Geneva.dfont/9_10.bmp",  "images/Geneva.dfont/a_11.bmp",
                                         "images/Geneva.dfont/A_37.bmp", "images/Geneva.dfont/b_12.bmp",
                                        "images/Geneva.dfont/B_38.bmp", "images/Geneva.dfont/c_13.bmp",
                                       "images/Geneva.dfont/C_39.bmp", "images/Geneva.dfont/d_14.bmp",
                                     "images/Geneva.dfont/D_40.bmp", "images/Geneva.dfont/e_15.bmp",
                                      "images/Geneva.dfont/E_41.bmp", "images/Geneva.dfont/f_16.bmp",
                                       "images/Geneva.dfont/F_42.bmp", "images/Geneva.dfont/g_17.bmp",
                                        "images/Geneva.dfont/G_43.bmp", "images/Geneva.dfont/h_18.bmp",
                                         "images/Geneva.dfont/H_44.bmp",  "images/Geneva.dfont/i_19.bmp",
                                           "images/Geneva.dfont/I_45.bmp", "images/Geneva.dfont/j_20.bmp",
                                            "images/Geneva.dfont/J_46.bmp", "images/Geneva.dfont/k_21.bmp",
                                             "images/Geneva.dfont/K_47.bmp", "images/Geneva.dfont/l_22.bmp",
                                             "images/Geneva.dfont/L_48.bmp",  "images/Geneva.dfont/m_23.bmp",
                                              "images/Geneva.dfont/M_49.bmp",  "images/Geneva.dfont/n_24.bmp",
                                          "images/Geneva.dfont/N_50.bmp",  "images/Geneva.dfont/o_25.bmp",
                                           "images/Geneva.dfont/O_51.bmp",  "images/Geneva.dfont/p_26.bmp",
                                            "images/Geneva.dfont/P_52.bmp",  "images/Geneva.dfont/q_27.bmp",
                                             "images/Geneva.dfont/Q_53.bmp",  "images/Geneva.dfont/r_28.bmp",
                                              "images/Geneva.dfont/R_54.bmp",  "images/Geneva.dfont/s_29.bmp",
                                                "images/Geneva.dfont/S_55.bmp",  "images/Geneva.dfont/t_30.bmp",
                                       "images/Geneva.dfont/T_56.bmp",  "images/Geneva.dfont/u_31.bmp",
                                       "images/Geneva.dfont/U_57.bmp",  "images/Geneva.dfont/v_32.bmp",
                                         "images/Geneva.dfont/V_58.bmp",  "images/Geneva.dfont/w_33.bmp",
                                         "images/Geneva.dfont/W_59.bmp", "images/Geneva.dfont/x_34.bmp",
                                         "images/Geneva.dfont/X_60.bmp",  "images/Geneva.dfont/y_35.bmp",
                                         "images/Geneva.dfont/Y_61.bmp",  "images/Geneva.dfont/z_36.bmp",
                                         "images/Geneva.dfont/Z_62.bmp",  "images/Helvetica.ttc/0_1.bmp",
                                         "images/Helvetica.ttc/1_2.bmp", "images/Helvetica.ttc/2_3.bmp",
                                         "images/Helvetica.ttc/3_4.bmp", "images/Helvetica.ttc/4_5.bmp",
                                         "images/Helvetica.ttc/5_6.bmp", "images/Helvetica.ttc/6_7.bmp",
                                         "images/Helvetica.ttc/7_8.bmp", "images/Helvetica.ttc/8_9.bmp",
                                         "images/Helvetica.ttc/9_10.bmp",  "images/Helvetica.ttc/a_11.bmp",
                                          "images/Helvetica.ttc/A_37.bmp", "images/Helvetica.ttc/b_12.bmp",
                                           "images/Helvetica.ttc/B_38.bmp", "images/Helvetica.ttc/c_13.bmp",
                                            "images/Helvetica.ttc/C_39.bmp", "images/Helvetica.ttc/d_14.bmp",
                                             "images/Helvetica.ttc/D_40.bmp", "images/Helvetica.ttc/e_15.bmp",
                                              "images/Helvetica.ttc/E_41.bmp", "images/Helvetica.ttc/f_16.bmp",
                                              "images/Helvetica.ttc/F_42.bmp", "images/Helvetica.ttc/g_17.bmp",
                                              "images/Helvetica.ttc/G_43.bmp", "images/Helvetica.ttc/h_18.bmp",
                                              "images/Helvetica.ttc/H_44.bmp",  "images/Helvetica.ttc/i_19.bmp",
                                                "images/Helvetica.ttc/I_45.bmp", "images/Helvetica.ttc/j_20.bmp",
                                                 "images/Helvetica.ttc/J_46.bmp", "images/Helvetica.ttc/k_21.bmp",
                                                  "images/Helvetica.ttc/K_47.bmp", "images/Helvetica.ttc/l_22.bmp",
                                                  "images/Helvetica.ttc/L_48.bmp",  "images/Helvetica.ttc/m_23.bmp",
                                                    "images/Helvetica.ttc/M_49.bmp",  "images/Helvetica.ttc/n_24.bmp",
                                                      "images/Helvetica.ttc/N_50.bmp",  "images/Helvetica.ttc/o_25.bmp",
                                                        "images/Helvetica.ttc/O_51.bmp",  "images/Helvetica.ttc/p_26.bmp",
                                                         "images/Helvetica.ttc/P_52.bmp",  "images/Helvetica.ttc/q_27.bmp",
                                                          "images/Helvetica.ttc/Q_53.bmp",  "images/Helvetica.ttc/r_28.bmp",
                                                            "images/Helvetica.ttc/R_54.bmp",  "images/Helvetica.ttc/s_29.bmp",
                                                              "images/Helvetica.ttc/S_55.bmp",  "images/Helvetica.ttc/t_30.bmp",
                                                                "images/Helvetica.ttc/T_56.bmp",  "images/Helvetica.ttc/u_31.bmp",
                                                                  "images/Helvetica.ttc/U_57.bmp",  "images/Helvetica.ttc/v_32.bmp",
                                                                    "images/Helvetica.ttc/V_58.bmp",  "images/Helvetica.ttc/w_33.bmp",
                                                               "images/Helvetica.ttc/W_59.bmp", "images/Helvetica.ttc/x_34.bmp",
                                                                "images/Helvetica.ttc/X_60.bmp",  "images/Helvetica.ttc/y_35.bmp",
                                                                "images/Helvetica.ttc/Y_61.bmp",  "images/Helvetica.ttc/z_36.bmp",
                                                                "images/Helvetica.ttc/Z_62.bmp",  "images/LucidaGrande.ttc/0_1.bmp",
                                                                "images/LucidaGrande.ttc/1_2.bmp", "images/LucidaGrande.ttc/2_3.bmp",
                                                                 "images/LucidaGrande.ttc/3_4.bmp", "images/LucidaGrande.ttc/4_5.bmp",
                                                                  "images/LucidaGrande.ttc/5_6.bmp", "images/LucidaGrande.ttc/6_7.bmp",
                                                                   "images/LucidaGrande.ttc/7_8.bmp", "images/LucidaGrande.ttc/8_9.bmp",
                                                                    "images/LucidaGrande.ttc/9_10.bmp",  "images/LucidaGrande.ttc/a_11.bmp",
                                                                     "images/LucidaGrande.ttc/A_37.bmp", "images/LucidaGrande.ttc/b_12.bmp",
                                                                       "images/LucidaGrande.ttc/B_38.bmp", "images/LucidaGrande.ttc/c_13.bmp",
                                                                        "images/LucidaGrande.ttc/C_39.bmp", "images/LucidaGrande.ttc/d_14.bmp",
                                                                         "images/LucidaGrande.ttc/D_40.bmp", "images/LucidaGrande.ttc/e_15.bmp",
                                                                         "images/LucidaGrande.ttc/E_41.bmp", "images/LucidaGrande.ttc/f_16.bmp",
                                                                          "images/LucidaGrande.ttc/F_42.bmp", "images/LucidaGrande.ttc/g_17.bmp",
                                                                           "images/LucidaGrande.ttc/G_43.bmp", "images/LucidaGrande.ttc/h_18.bmp",
                                                                            "images/LucidaGrande.ttc/H_44.bmp",  "images/LucidaGrande.ttc/i_19.bmp",
                                                                              "images/LucidaGrande.ttc/I_45.bmp", "images/LucidaGrande.ttc/j_20.bmp",
                                                                               "images/LucidaGrande.ttc/J_46.bmp", "images/LucidaGrande.ttc/k_21.bmp",
                                                                                "images/LucidaGrande.ttc/K_47.bmp", "images/LucidaGrande.ttc/l_22.bmp",
                                                                             "images/LucidaGrande.ttc/L_48.bmp",  "images/LucidaGrande.ttc/m_23.bmp",
                                                                              "images/LucidaGrande.ttc/M_49.bmp",  "images/LucidaGrande.ttc/n_24.bmp",
                                                                               "images/LucidaGrande.ttc/N_50.bmp",  "images/LucidaGrande.ttc/o_25.bmp",
                                                                                 "images/LucidaGrande.ttc/O_51.bmp",  "images/LucidaGrande.ttc/p_26.bmp",
                                                                              "images/LucidaGrande.ttc/P_52.bmp",  "images/LucidaGrande.ttc/q_27.bmp",
                                                                               "images/LucidaGrande.ttc/Q_53.bmp",  "images/LucidaGrande.ttc/r_28.bmp",
                                                                                "images/LucidaGrande.ttc/R_54.bmp",  "images/LucidaGrande.ttc/s_29.bmp",
                                                                                 "images/LucidaGrande.ttc/S_55.bmp",  "images/LucidaGrande.ttc/t_30.bmp",
                                                                            "images/LucidaGrande.ttc/T_56.bmp",  "images/LucidaGrande.ttc/u_31.bmp",
                                                                             "images/LucidaGrande.ttc/U_57.bmp",  "images/LucidaGrande.ttc/v_32.bmp",
                                                                               "images/LucidaGrande.ttc/V_58.bmp",  "images/LucidaGrande.ttc/w_33.bmp",
                                                                                 "images/LucidaGrande.ttc/W_59.bmp", "images/LucidaGrande.ttc/x_34.bmp",
                                                                                 "images/LucidaGrande.ttc/X_60.bmp",  "images/LucidaGrande.ttc/y_35.bmp",
                                                                                 "images/LucidaGrande.ttc/Y_61.bmp",  "images/LucidaGrande.ttc/z_36.bmp",
                                                                                 "images/LucidaGrande.ttc/Z_62.bmp",  "images/Times.ttc/0_1.bmp",
                                                                                 "images/Times.ttc/1_2.bmp", "images/Times.ttc/2_3.bmp",
                                                                                 "images/Times.ttc/3_4.bmp", "images/Times.ttc/4_5.bmp",
                                                                                 "images/Times.ttc/5_6.bmp", "images/Times.ttc/6_7.bmp",
                                                                                 "images/Times.ttc/7_8.bmp", "images/Times.ttc/8_9.bmp",
                                                                                 "images/Times.ttc/9_10.bmp",  "images/Times.ttc/a_11.bmp",
                                                                                 "images/Times.ttc/A_37.bmp", "images/Times.ttc/b_12.bmp",
                                                                                 "images/Times.ttc/B_38.bmp", "images/Times.ttc/c_13.bmp",
                                                                                 "images/Times.ttc/C_39.bmp", "images/Times.ttc/d_14.bmp",
                                                                                 "images/Times.ttc/D_40.bmp", "images/Times.ttc/e_15.bmp",
                                                                                 "images/Times.ttc/E_41.bmp", "images/Times.ttc/f_16.bmp",
                                                                                 "images/Times.ttc/F_42.bmp", "images/Times.ttc/g_17.bmp",
                                                                                 "images/Times.ttc/G_43.bmp", "images/Times.ttc/h_18.bmp",
                                                                                 "images/Times.ttc/H_44.bmp",  "images/Times.ttc/i_19.bmp",
                                                                                 "images/Times.ttc/I_45.bmp", "images/Times.ttc/j_20.bmp",
                                                                                 "images/Times.ttc/J_46.bmp", "images/Times.ttc/k_21.bmp",
                                                                                 "images/Times.ttc/K_47.bmp", "images/Times.ttc/l_22.bmp",
                                                                                 "images/Times.ttc/L_48.bmp",  "images/Times.ttc/m_23.bmp",
                                                                                 "images/Times.ttc/M_49.bmp",  "images/Times.ttc/n_24.bmp",
                                                                                 "images/Times.ttc/N_50.bmp",  "images/Times.ttc/o_25.bmp",
                                                                                  "images/Times.ttc/O_51.bmp",  "images/Times.ttc/p_26.bmp",
                                                                                    "images/Times.ttc/P_52.bmp",  "images/Times.ttc/q_27.bmp",
                                                                                      "images/Times.ttc/Q_53.bmp",  "images/Times.ttc/r_28.bmp",
                                                                                        "images/Times.ttc/R_54.bmp",  "images/Times.ttc/s_29.bmp",
                                                                                          "images/Times.ttc/S_55.bmp",  "images/Times.ttc/t_30.bmp",
                                                                                           "images/Times.ttc/T_56.bmp",  "images/Times.ttc/u_31.bmp",
                                                                                            "images/Times.ttc/U_57.bmp",  "images/Times.ttc/v_32.bmp",
                                                                                              "images/Times.ttc/V_58.bmp",  "images/Times.ttc/w_33.bmp",
                                                                                                "images/Times.ttc/W_59.bmp", "images/Times.ttc/x_34.bmp",
                                                                                                "images/Times.ttc/X_60.bmp",  "images/Times.ttc/y_35.bmp",
                                                                                                 "images/Times.ttc/Y_61.bmp",  "images/Times.ttc/z_36.bmp",
                                                                                                 "images/Times.ttc/Z_62.bmp"};


    int Llabels[]={48,49,50,51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,101,69, 102, 70, 103,
      71, 104, 72, 105, 73, 106, 74, 107, 75, 108, 76, 109, 77, 110, 78, 111, 79, 112, 80, 113, 81,
      114, 82, 115, 83, 116, 84, 117, 85, 118, 86, 119, 87, 120, 88, 121, 89, 122, 90, 48,49,50,51,52,53,
      54,55,56,57,97,65,98,66,99,67,100,68,101,69, 102, 70, 103, 71, 104, 72, 105, 73, 106, 74, 107, 75,
      108, 76, 109, 77, 110, 78, 111, 79, 112, 80, 113, 81, 114, 82, 115, 83, 116, 84, 117, 85, 118, 86,
      119, 87, 120, 88, 121, 89, 122, 90,48,49,50,51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,101,69,
      102, 70, 103, 71, 104, 72, 105, 73, 106, 74, 107, 75, 108, 76, 109, 77, 110, 78, 111, 79, 112, 80,
      113, 81, 114, 82, 115, 83, 116, 84, 117, 85, 118, 86, 119, 87, 120, 88, 121, 89, 122, 90, 48,49,50,
      51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,101,69, 102, 70, 103, 71, 104, 72, 105, 73, 106, 74,
       107, 75, 108, 76, 109, 77, 110, 78, 111, 79, 112, 80, 113, 81, 114, 82, 115, 83, 116, 84, 117, 85,
        118, 86, 119, 87, 120, 88, 121, 89, 122, 90,48,49,50,51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,
        101,69, 102, 70, 103, 71, 104, 72, 105, 73, 106, 74, 107, 75, 108, 76, 109, 77, 110, 78, 111, 79, 112,
         80, 113, 81, 114, 82, 115, 83, 116, 84, 117, 85, 118, 86, 119, 87, 120, 88, 121, 89, 122, 90, 48,49,50,
         51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,101,69, 102, 70, 103, 71, 104, 72, 105, 73, 106, 74, 107,
          75, 108, 76, 109, 77, 110, 78, 111, 79, 112, 80, 113, 81, 114, 82, 115, 83, 116, 84, 117, 85, 118, 86,
           119, 87, 120, 88, 121, 89, 122, 90, 48,49,50,51,52,53,54,55,56,57,97,65,98,66,99,67,100,68,101,69, 102,
        70, 103, 71, 104, 72, 105, 73, 106, 74, 107, 75, 108, 76, 109, 77, 110, 78, 111, 79, 112, 80, 113, 81, 114,
         82, 115, 83, 116, 84, 117, 85, 118, 86, 119, 87, 120, 88, 121, 89, 122, 90};

    int random= RANDOM_RANGE(441);
    struct sendback res;
    //res.path=Limages[random];
    strcpy(res.path, Limages[random]);
    res.ASCII=Llabels[random];
    printf("path is %s and ASCII is %d \n",res.path,res.ASCII);
    return res;
}



//____________________________________ Back Propagation _______________________________
double CrossEntropy(struct CL_out *clout, int BinIndicaor)
{
    struct CL_out *IndexOut=NULL;
    IndexOut=clout;

    struct Neuron *outN=NULL;
    outN=IndexOut->n;

    return -(log(exp((outN[BinIndicaor].input * outN[BinIndicaor].weight) + outN[BinIndicaor].bias)));

}

//Chain Rule derivation for output layers
double SoftLayerBack(struct CL_out *clout, int BinIndicaor, int i)
{
  struct CL_out *IndexOut=NULL;
  IndexOut=clout;

  struct Neuron *outN=NULL;
  outN=IndexOut->n;

  if(BinIndicaor==i)
  {
    return -1/(exp((outN[BinIndicaor].input * outN[BinIndicaor].weight) + outN[BinIndicaor].bias));
  }
  else
  {
    return 0;
  }

}

// Backpropagation for the output layer
void BackforOutput(struct CL_out *clout, int BinIndicaor)
{
  struct CL_out *IndexOut=NULL;
  IndexOut=clout;

  struct Neuron *outN=NULL;
  outN=IndexOut->n;

  int sum=0;
  for (int i=0;i<(NB_Char);i++)
  {

      sum=sum+exp((outN[i].input * outN[i].weight) + outN[i].bias);
  }

  for(int i=0; i<NB_Char; i++)
  {
    double rout=0;
    if (i==BinIndicaor) {
      rout= exp((outN[i].input * outN[i].weight) + outN[i].bias)*(sum-exp((outN[i].input * outN[i].weight) + outN[i].bias))/(sum*sum);
    }
    else
    {
      rout= -exp((outN[i].input * outN[i].weight) + outN[i].bias)*exp((outN[BinIndicaor].input * outN[BinIndicaor].weight) + outN[BinIndicaor].bias/(sum*sum));
    }

    outN[i].input=SoftLayerBack(clout, BinIndicaor, i)*rout*outN[i].weight;
    outN[i].weight=SoftLayerBack(clout, BinIndicaor, i)*rout*outN[i].input;
    outN[i].bias=SoftLayerBack(clout, BinIndicaor, i)*rout;

  }

  for(int i=0; i<NB_Char; i++)
  {
    printf("output n°%d is input=%f and weight=%f and bias=%f \n",i,outN[i].input, outN[i].weight,outN[i].bias  );

  }


}

void GradientsFromPoolingLast(struct PoolC2 *pool2, struct ALLFM2 *feat2)
{
  struct ALLFM2 *currFeatureMap2=NULL;
  currFeatureMap2=feat2;

  struct PoolC2 *currPool=NULL;
  currPool= pool2;

  for(int i=0;i<NB_FILTERS1*NB_FILTERS2;i++)
  {
      double *indexConv2= NULL;
      indexConv2=(currFeatureMap2->m->matrix);

      double *indexPool2=NULL;
      indexPool2=(currPool->m->matrix);

      int i4pool=0;
       for(int k=0; k<DIM_C2; k+=2)
      {
          for(int l=0;l<DIM_C2;l+=2)
          {
            double maxi=  indexPool2[i4pool];

            if(indexConv2[k*DIM_C2+l]!=maxi)
            {
              indexConv2[k*DIM_C2+l]=0;
            }
            if(indexConv2[k*DIM_C2+(l+1)]!=maxi)
            {
              indexConv2[k*DIM_C2+(l+1)]=0;
            }
            if(indexConv2[(k+1)*DIM_C2+l]!=maxi)
            {
              indexConv2[(k+1)*DIM_C2+l]=0;
            }
            if(indexConv2[k*DIM_C2+(l+1)]!=maxi)
            {
              indexConv2[k*DIM_C2+(l+1)]=0;
            }

            i4pool+=1;

            }
      }
          currFeatureMap2=currFeatureMap2->next;
          currPool=currPool->next;
  }


}

void BackForFiltersLast(struct ALLFilters2 *filers2, struct ALLFM2 *feat2,struct PoolC1 *pool1)
{
  struct ALLFM2 *currFeatureMap2=NULL;
  currFeatureMap2=feat2;

  struct ALLFilters2 *currFilter2=NULL;
  currFilter2= filers2;

  struct PoolC1 *currPool=NULL;
  currPool= pool1;

  for(int n=0; n<NB_FILTERS1; n++)
  {
    double *indexPool2=NULL;
    indexPool2=(currPool->m->matrix);

    currFilter2= filers2;

    for(int nb=0;nb<NB_FILTERS2;nb++)
    {
      double *indexConv2= NULL;
      indexConv2=(currFeatureMap2->m->matrix);

      double *indexFilter2=NULL;
      //PB here
      indexFilter2=(currFilter2->m->matrix);

      for(int y=0; y<DIM_FILTER; y++)
     {
         for(int x=0; x<DIM_FILTER;x++)
         {
              //Find Gradient
              double gradient=0;
              for (int j = 0; j < DIM_C2; j++) {
                for (int i = 0; i < DIM_C2; i++) {

                      gradient+=indexConv2[j*DIM_C2+i]*indexPool2[(j+y)*DIM_POOL1+(i+x)];
                    }

                  }

                  indexFilter2[y*DIM_FILTER+x]=gradient;

         }
       }
       currFeatureMap2=currFeatureMap2->next;
       currFilter2=currFilter2->next;
    }
    currPool=currPool->next;
  }


}

// Gradient from Max Pooling
void GradientsFromPooling(struct PoolC1 *pool1, struct ALLFM1 *feat1)
{
  struct ALLFM1 *currFeatureMap=NULL;
  currFeatureMap=feat1;

  struct PoolC1 *currPool=NULL;
  currPool= pool1;

  for(int i=0;i<NB_FILTERS1;i++)
  {
      double *indexConv= NULL;
      indexConv=(currFeatureMap->m->matrix);

      double *indexPool=NULL;
      indexPool=(currPool->m->matrix);

      int i4pool=0;
       for(int k=0; k<DIM_C1; k+=2)
      {
          for(int l=0;l<DIM_C1;l+=2)
          {

            double maxi=  indexPool[i4pool];

            if(indexConv[k*DIM_C1+l]!=maxi)
            {
              indexConv[k*DIM_C1+l]=0;
            }
            if(indexConv[k*DIM_C1+(l+1)]!=maxi)
            {
              indexConv[k*DIM_C1+(l+1)]=0;
            }
            if(indexConv[(k+1)*DIM_C1+l]!=maxi)
            {
              indexConv[(k+1)*DIM_C1+l]=0;
            }
            if(indexConv[k*DIM_C1+(l+1)]!=maxi)
            {
              indexConv[k*DIM_C1+(l+1)]=0;
            }

            i4pool+=1;

            }
      }
          currFeatureMap=currFeatureMap->next;
          currPool=currPool->next;
  }


}
//Step 5 Backprop for Conv
void BackForFilters(struct ALLFilters1 *filter1, struct ALLFM1 *feat1, Matrix input)
{

  struct ALLFM1 *currFeatureMap=NULL;
  currFeatureMap=feat1;

  struct ALLFilters1 *currFilter=NULL;
  currFilter= filter1;

  for(int nb=0;nb<NB_FILTERS1;nb++)
  {
    double *indexConv1= NULL;
    indexConv1=(currFeatureMap->m->matrix);

    double *indexFilter1=NULL;
    indexFilter1=(currFilter->m->matrix);

    for(int y=0; y<DIM_FILTER; y++)
   {
       for(int x=0; x<DIM_FILTER;x++)
       {
         //Find Gradient
            double gradient=0;
            for (int j = 0; j < DIM_C1; j++) {
              for (int i = 0; i < DIM_C1; i++) {

                    gradient+=indexConv1[j*DIM_C1+i]*input.matrix[(j+y)*DIM_INPUT+(i+x)];
                  }

                }

                indexFilter1[y*DIM_FILTER+x]=gradient;
       }
     }
     currFeatureMap=currFeatureMap->next;
     currFilter=currFilter->next;

  }

}
