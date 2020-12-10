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

//___________________________________________________________________________
//
////1) Model initialization
//TRAINING MODEL

struct TM
{
   Matrix *M;
   int result;
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

    for(int i=0;i<NB_FILTERS1;i++)
    {
        double *indexConv= NULL;
        indexConv=(cfm1->m->matrix);

        for(int y=0; y<DIM_C1; y++)
         {
            for(int x=0; x<DIM_C1;x++)
            {
                indexConv[y*DIM_C1+x]=max(0, indexConv[y*DIM_C1+x]);
             }
         }
        cfm1=cfm1->next;
    }
}
//_____________________________________________________________________________________


// 4) Pooling after C1's activation
void Pool1(struct ALLFM1 *cfm1,struct PoolC1 *pc1)
{

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

         for(int k=0; k<DIM_C1; k+=2)
        {
            for(int l=0;l<DIM_C1;l+=2)
            {

            double maxi=max(indexConv[k*DIM_C1+l],indexConv[k*DIM_C1+l+1]);
            maxi=max(maxi,max(indexConv[k*DIM_C1+l+1],indexConv[k+1*DIM_C1+l+1]));

            maxi=max(maxi,(max(indexConv[k+1*DIM_C1+l+1],indexConv[k+1*DIM_C1+l])));

            maxi=max(maxi,(max(indexConv[k*DIM_C1+l],indexConv[k+1*DIM_C1+l])));

            if(k==0 && l==0)
            {
                (indexPool[k*DIM_POOL1+l])=maxi;
                }
            else
            {
                if(k==0)
                {
                    indexPool[k*DIM_POOL1+(l-1)]=maxi;
                }
                else
                {
                if(l==0)
                {
                    indexPool[(k-1)*DIM_POOL1+l]=maxi;
                }
                else
                {
                    (indexPool[(k-1)*DIM_POOL1+(l-1)])=maxi;
                }
                }
            }
            }
            }

            currFeatureMap=currFeatureMap->next;
            currPool=currPool->next;
    }

    /*
    for(int j=0; j< NB_FILTERS1; j++)
    {

        for(int k=0; k<DIM_C1; k+=2)
    {
        for(int l=0;l<DIM_C1;l+=2)
        {

            double maxi=max(cfm1->fm1[j].matrix[k*DIM_C1+l],cfm1->fm1[j].matrix[k*DIM_C1+l+1]);
            maxi=max(maxi,max(cfm1->fm1[j].matrix[k*DIM_C1+l+1],cfm1->fm1[j].matrix[k+1*DIM_C1+l+1]));

            maxi=max(maxi,(max(cfm1->fm1[j].matrix[k+1*DIM_C1+l+1],cfm1->fm1[j].matrix[k+1*DIM_C1+l])));

            maxi=max(maxi,(max(cfm1->fm1[j].matrix[k*DIM_C1+l],cfm1->fm1[j].matrix[k+1*DIM_C1+l])));

            if(k==0 && l==0)
            {
            pc1->pool1[j].matrix[k*DIM_POOL1+l]=maxi;
                }
            else
            {
                if(k==0)
                {
                    pc1->pool1[j].matrix[k*DIM_POOL1+(l-1)]=maxi;
                }
                else
                {
                if(l==0)
                {
                    pc1->pool1[j].matrix[(k-1)*DIM_POOL1+l]=maxi;
                }
                else
                {
                    pc1->pool1[j].matrix[(k-1)*DIM_POOL1+(l-1)]=maxi;
                }
                }
            }
        }
    }
    }*/
}

//_____________________________________________________________________________________
// FOR C2 _____________________________________________________________________________


//______ Function for Convolution C2  _____________________________________________________
void ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1,struct ALLFM2 *cfm2)
{
    /*
    for(int i0=0; i0<NB_FILTERS1;i0++)
    {
    for(int i=0; i<NB_FILTERS2; i++)
    {
        for(int i2=0; i2<DIM_FILTER; i2++)
        {
        for(int k=0; k<DIM_POOL1;k++)
        {
            for(int l=0; l<DIM_POOL1; l++)
            {
                cfm2->fm2[i].matrix[k*DIM_C2+l]= pc1->pool1[i0].matrix[k*DIM_POOL1+l]* (A2->Mall2[i2].matrix[k*DIM_FILTER+l]);

            }
        }
        }
    }
    }*/
    
    struct ALLFilters2 *currfilter =NULL;
    currfilter=A2;

    struct ALLFM2 *currFeatureMap=NULL;
    currFeatureMap=cfm2;

    struct PoolC1 *currPool=NULL;
    currPool=pc1;

    for(int i=0; i<NB_FILTERS2; i++)
    {
        double *cfilter =NULL;
        cfilter=currfilter->m->matrix;

        double *cfeatureM=NULL;
        cfeatureM=currFeatureMap->m->matrix;

        double *cpool=NULL;
        cpool=currPool->m->matrix;

        for(int k=0; k<DIM_POOL1;k++)
        {
            for(int l=0; l<DIM_POOL1; l++)
            {
                cfeatureM[k*DIM_C2+l]= cpool[k*DIM_POOL1+l]* (cfilter[k*DIM_FILTER+l]);

            }
        }
        currfilter=currfilter->next;
        currFeatureMap=currFeatureMap->next;
        
        if (i%2==0)
        {
            currPool=currPool->next;
        }
    }

}

//_____________________________________________________________________________________

// 3) Relu activation after C2 ________________________________________________________
void ReluActiv2(struct ALLFM2 *cfm2)
{
    /*
    for(int i=0;i<NB_FILTERS2; i++)
    {
        for(int y=0; y<DIM_C2; y++)
        {
            for(int x=0; x<DIM_C2;x++)
            {
                cfm2->fm2[i].matrix[y*DIM_C2+x]=max(0,  cfm2->fm2[i].matrix[y*DIM_C2+x]);
            }
        }
    }*/
    for(int i=0;i<NB_FILTERS2;i++)
    {
        double *indexConv= NULL;
        indexConv=(cfm2->m->matrix);

        for(int y=0; y<DIM_C2; y++)
         {
            for(int x=0; x<DIM_C2;x++)
            {
                indexConv[y*DIM_C2+x]=max(0, indexConv[y*DIM_C2+x]);
             }
         }
        cfm2=cfm2->next;
    }

}
//_____________________________________________________________________________________

// 4) Pooling after C2's activation
void Pool2(struct ALLFM2 *cfm2,struct PoolC2 *pc2)
{
    /*for(int j=0; j< NB_FILTERS2; j++)
    {

        for(int k=0; k<DIM_C2; k+=2)
    {
        for(int l=0;l<DIM_C2;l+=2)
        {

            double maxi=max(cfm2->fm2[j].matrix[k*DIM_C2+l],cfm2->fm2[j].matrix[k*DIM_C2+(l+1)]);
            maxi=max(maxi,max(cfm2->fm2[j].matrix[k*DIM_C2+(l+1)],cfm2->fm2[j].matrix[k+1*DIM_C2+(l+1)]));

            maxi=max(maxi,(max(cfm2->fm2[j].matrix[(k+1)*DIM_C2+(l+1)],cfm2->fm2[j].matrix[(k+1)*DIM_C2+l])));

            maxi=max(maxi,(max(cfm2->fm2[j].matrix[k*DIM_C2+l],cfm2->fm2[j].matrix[(k+1)*DIM_C2+l])));

            if(k==0 && l==0)
            {
                pc2->pool2[j].matrix[k*DIM_POOL2+l]=maxi;
                }
            else
            {
                if(k==0)
                { pc2->pool2[j].matrix[k*DIM_POOL2+(l-1)]=maxi;}
                else
                {   if(l==0){
                    pc2->pool2[j].matrix[(k-1)*DIM_POOL2+l]=maxi;
                            }
                    else
                            {
                    pc2->pool2[j].matrix[(k-1)*DIM_POOL2+(l-1)]=maxi;
                            }
                }
            }
        }
    }
}*/
} //last

//____________________________________________________________________________________
// 8) Flattern Layer + First Fully Connected Layer

void FlatternLayer(struct PoolC2 *pc2,struct FL *res)
{
    /*
    int count=0;
    for(int i=0; i<NB_FILTERS2; i++)
    {
        for(int j=0; j<DIM_POOL2; j++)
        {

            for(int k=0; k<DIM_POOL2;k++ )
        {
            res->flayer[count].input= pc2->pool2[i].matrix[j*DIM_POOL2+k];

            count+=1;
        }
    }
    }*/
}

//____________________________________________________________________________________
//9) Fully Connected Layer

double GetInputFromFC(struct FL *flatterned)
{
    double res=0;
    /*for(int i=0; i<NB_FILTERS2*DIM_POOL2*DIM_POOL2; i++)
    {
        //Dropout -> not all features are seen for better performance
        double drop=RAND_DOUBLE;
        if(drop>0.3)
        {
            res+=(flatterned->flayer[i].input*flatterned->flayer[i].weight) + flatterned->flayer[i].bias;
        }
    }*/

    return res;
}


void FullyConnectedLayer1(struct FL *flatterned, struct CL_out *outin)
{
    /*for(int i=0; i<NB_Char;i++)
    {
        double getres=GetInputFromFC(flatterned);
        outin->outP[i].input= getres;
    }*/
}

//10) Get output with softmax -> OutPut Layer
struct resultsfromoutput{
    double ASCII;
    double output;
    double weight;
    double bias;
};
struct resultsfromoutput GetOutPut(struct CL_out *outin)
{
    /*double sum= 0;
    for (int i=0;i<(NB_Char);i++)
    {
        sum=sum+exp((outin->outP[i].input*outin->outP[i].weight)+outin->outP[i].bias);
    }

    double maxiO=exp((outin->outP[0].input*outin->outP[0].weight)+outin->outP[0].bias)/sum;
    double maxA=0;
    double maxW=outin->outP[0].weight;
    double maxB=outin->outP[0].bias;
    for(int i=1; i<NB_Char; i++)
    {
        double curexp=exp((outin->outP[i].input*outin->outP[i].weight)+outin->outP[i].bias)/sum;
        if (curexp>maxiO)
        {
            maxiO=curexp;
            maxA=i;
            maxW=outin->outP[i].weight;
            maxB=outin->outP[i].bias;
        }
    }

    // Digits
    if (maxA<10)
    {
        maxA+=48;
    }
    else
    {
        //Lower letters
      //  if(maxA<35)
      //  {
            maxA+=97;
        }
        else
        {
            //Capital letters
            maxA+=65;
        }
    }
    struct resultsfromoutput res={maxiO,maxA,maxW,maxB};*/
    struct resultsfromoutput res={0,0,0,0};
    return res;
}

