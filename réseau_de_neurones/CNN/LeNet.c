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
        currFeatureMap=currFeatureMap->next;
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

            currFeatureMap=currFeatureMap->next;
            currPool=currPool->next;
    }

}

//_____________________________________________________________________________________
// FOR C2 _____________________________________________________________________________


//______ Function for Convolution C2  _____________________________________________________
void ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1,struct ALLFM2 *cfm2)
{

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
        currFeatureMap=currFeatureMap->next;
        currPool=currPool->next;
        
    }

}

//____________________________________________________________________________________
// 8) Flattern Layer + First Fully Connected Layer
struct FL *init_fl(size_t n)
{   
    struct FL *new;
    new= malloc (sizeof(struct FL));
    struct Neuron *newN; 
    newN = calloc(n,sizeof(double)); 
    for(int i=0;i<(int)n;i++)
    {
        double random1=RAND_DOUBLE;
        double random2=RAND_DOUBLE;
        newN[i].input=0;
        newN[i].weight=random1;
        newN[i].bias=random2;
    }
    new->n = newN;
    
    return new;
   
}
void FlatternLayer(struct PoolC2 *pc2,struct FL *res)
{
    
    struct PoolC2 *currPool = NULL;
    currPool = pc2;
    
    struct Neuron *CurNeu=NULL;
    CurNeu= res->n;

    for (int i = 0; i < NB_FILTERS2 * NB_FILTERS1 ; i++)
    { 
        double *indexPool= NULL;
        indexPool=(currPool->m->matrix);

        for(int j=0; j< DIM_POOL2; j++)
        {
            for(int k=0; k< DIM_POOL2;k++ )
            {
                CurNeu[i].input= indexPool[j*DIM_POOL2+k];
               // printf("Current input %f \n",CurNeu[i].input);
                
            }
        }
        currPool=currPool->next;
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
        double drop=RAND_DOUBLE;
        if(drop>0.3)
        {
            res+=(CurNeu[i].input*CurNeu[i].weight) + CurNeu[i].bias;
        }
    }

    return res;
}
//Init Fully Connected Layer
struct CL_out *init_out(size_t n)
{  

    struct CL_out *new;
    new= malloc (sizeof(struct FL));
    struct Neuron *newN;
    newN = calloc(n,sizeof(double));
    for(int i=0;i<(int)n;i++)
    {   
        double random1=RAND_DOUBLE;
        double random2=RAND_DOUBLE;
        newN[i].input=0;
        newN[i].weight=random1;
        newN[i].bias=random2;
    }
    new->n = newN;

    return new;
}


void FullyConnectedLayer1(struct FL *flatterned, struct Neuron *CurNeu)
{
    for(int i=0; i<NB_Char;i++)
    {
        double getres=GetInputFromFC(flatterned);
        CurNeu[i].input= getres;
    }
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
    double sum= 0;
    
    struct CL_out *IndexOut=NULL;
    IndexOut=outin;


    for (int i=0;i<(NB_Char);i++)
    {
        struct Neuron *outN=NULL;
        outN=IndexOut->n;

        sum=sum+exp((outN[i].input * outN[i].weight) + outN[i].bias);
    }

    struct Neuron *outN2=NULL;
    outN2=IndexOut->n;

    double maxiO=exp((outN2[0].input*outN2[0].weight)+outN2[0].bias)/sum;
    double maxA=0;
    double maxW=outN2[0].weight;
    double maxB=outN2[0].bias;
    for(int i=1; i<NB_Char; i++)
    {
        double curexp=exp((outN2[i].input*outN2[i].weight)+outN2[i].bias)/sum;
        if (curexp>maxiO)
        {
            maxiO=curexp;
            maxA=i;
            maxW=outN2[i].weight;
            maxB=outN2[i].bias;
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
    struct resultsfromoutput res={maxA,maxiO,maxW,maxB};
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
