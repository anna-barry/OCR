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
 */


// Include section
 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>
 #include "../../Tools/matrix.h"

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
#define NB_FILTERS2 12
#define DIM_C2 10
#define DIM_POOL2 5
#define NB_Char 93

//__________________________________________________________________________________
//
//                                      Main
//
//__________________________________________________________________________________

// Filters for C1
struct ALLFilters1{
    Matrix[NB_FILTERS1] Mall;

    for(int i=0; i<NB_FILTERS1;i++)
    {
        Mall[i].height=DIM_FILTER;
        Mall[i].width=DIM_FILTER;
    }
};

//Feature Maps for C1
struct ALLFM1{
    Matrix[NB_FILTERS1] fm1;

    for(int i=0; i<NB_FILTERS1;i++)
    {
        fm1[i].height=DIM_C1;
        fm1[i].width=DIM_C1;
    }

};

//New Matrixes for Pooling for C1
struct PoolC1{
    Matrix[NB_FILTERS1] pool1;

    for(int i=0; i<NB_FILTERS1;i++)
    {
        pool1[i].height=DIM_POOL1;
        pool1[i].width=DIM_POOL1;
    }
};

//Filters for C2
struct ALLFilters2{
    Matrix[NB_FILTERS2] Mall2;

    for(int i=0; i<NB_FILTERS2;i++)
    {
        Mall2[i].height=DIM_FILTER;
        Mall2[i].width=DIM_FILTER;
    }
};

//Feature Maps for C2
struct ALLFM2{
  Matrix[NB_FILTERS2] fm2; 

  for(int i=0; i<NB_FILTERS2;i++)
    {
        fm2[i].height=DIM_C2;
        fm2[i].width=DIM_C2;
    }
};

//New Matrixes for Pooling for C2
struct PoolC2{
    Matrix[NB_FILTERS2] pool2;

    for(int i=0; i<NB_FILTERS2;i++)
    {
        pool2[i].height=DIM_POOL2;
        pool2[i].width=DIM_POOL2;
    }
};

// Neuron Structure
struct Neuron1{
        double input;
        double weight;
        double bias;
};

//Flatterning Layer with neuron implementation -> Fully connected layer
struct FL{
    struct Neuron[DIM_POOL2*DIM_POOL2*NB_FILTERS2] flayer;
};


//Fully Connected Layer for output
struct CL_out{
    struct Neuron[NB_Char] outP;
};


//______ Function for filters C1 _________________________________________________________

// "They’re usually randomly initialised and then learned over the course of training."
struct ALLFilters1 * getFilter1()
{
    struct ALLFilters1 *A1;
    A1=(struct ALLFilters1 *) malloc (NB_FILTERS1*DIM_FILTER*DIM_FILTER*sizeof(double));
    
    for (int i=0; i<DIM_C1; i++)
    {
        for(int y=0; y<DIM_FILTER; y++)
        {
            for(int x=0; x<DIM_FILTER;x++)
            {
               A1-> Matrix[i].matrix[y*DIM_FILTER+x]=RAND_DOUBLE;
            }
        }
    }
    return A1;
}

//________________________________________________________________________________________

//m.matrix[i*m.width+j]
//j width

//______ Function for Convolution C1 _____________________________________________________
struct ALLFM1 *ConvolutionLayer1(struct ALlfilters1 *A1, Matrix input)
{
    struct ALLFM1 *fm1;
    fm1=(struct ALLFM1 *) malloc (NB_FILTERS1*DIM_C1*DIM_C1*sizeof(double));

    for(int i=0; i<NB_FILTERS1; i++)
    {
        for(int i2=0; i2<DIM_FILTER; i2++)
        {
        for(int k=0; k<DIM_INPUT;k++)
        {
            for(int l=0; l<DIM_INPUT; l++)
            {
                fm1->Matrix[i].matrix[k*DIM_C1+l]= input[k*DIM_INPUT+l]* (A1->Matrix[i2].matrix[k*DIM_FILTER+l]);

            }
        }
        }
    }
    return fm1;
}

//_____________________________________________________________________________________

// 3) Relu activation after C1 ________________________________________________________
void ReluActiv1(struct ALLFM1 *fm1)
{
    for(int i=0;i<NB_FILTERS1; i++)
    {
        for(int y=0; y<DIM_C1; y++)
        {
            for(int x=0; x<DIM_C1;x++)
            {
                fm1->Matrix[i].matrix[y*DIM_C1+x]=max(0,  fm1->Matrix[i].matrix[y*DIM_C1+x]);
            }
        }
    }
}
//_____________________________________________________________________________________


// 4) Pooling after C1's activation
struct PoolC1 * Pool1(struct ALLFM1 *fm1)
{
    struct PoolC1 *pc1;
    pc1=(struct PoolC1 *) malloc (NB_FILTERS1*DIM_POOL1*DIM_POOL1*sizeof(double));

    for(int j=0; j< NB_FILTERS1; j++)
    {

        for(int k=0; k<DIM_C1; k+=2)
    {
        for(int l=0;l<DIM_C1;l+=2)
        {

            double maxi=max(fm1->Matrix[j].matrix[k*DIM_C1+l],fm1->Matrix[j].matrix[k*DIM_C1+l+1]);
            maxi=max(maxi,max(fm1->Matrix[j].matrix[k*DIM_C1+l+1],fm1->Matrix[j].matrix[k+1*DIM_C1+l+1]));

            maxi=max(maxi,(max(fm1->Matrix[j].matrix[k+1*DIM_C1+l+1],fm1->Matrix[j].matrix[k+1*DIM_C1+l])));

            maxi=max(maxi,(max(fm1->Matrix[j].matrix[k*DIM_C1+l],fm1->Matrix[j].matrix[k+1*DIM_C1+l])));

            if(k==0 && l==0)
            {
            pc1->Matrix[j].matrix[k*DIM_POOL1+l]=maxi;
                }
            else
            {
                if(k==0)
                {
                    pc1->Matrix[j].matrix[k*DIM_POOL1+(l-1)]=maxi;
                }
                else
                {
                if(l==0)
                {
                    pc1->Matrix[j].matrix[(k-1)*DIM_POOL1+l]=maxi;
                }
                else
                {
                    pc1->Matrix[j].matrix[(k-1)*DIM_POOL1+(l-1)]=maxi;
                }
                }
            }
        }
    }
    }
    return pc1;
}

//_____________________________________________________________________________________
// FOR C2 _____________________________________________________________________________
//______ Function for filters C2  ______________________________________________________

struct ALLFilters2 getFilter2()
{   
    struct ALLFilters2 *A2;
    A2=(struct ALLFilters2 *) malloc (NB_FILTERS2*DIM_FILTER*DIM_FILTER*sizeof(double));
    
    for (int i=0; i<DIM_C2; i++)
    {   
        for(int y=0; y<DIM_FILTER; y++)
        {   
            for(int x=0; x<DIM_FILTER;x++)
            {  
               A2-> Matrix[i].matrix[y*DIM_FILTER+x]=RAND_DOUBLE;
            }
        }
    }

    return A2;

}

//_____________________________________________________________________________________

//______ Function for Convolution C2  _____________________________________________________
struct ALLFM2 * ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1)
{
    struct ALLFM2 *fm2;
    fm2=(struct ALLFM2 *) malloc (NB_FILTERS2*DIM_POOL1*DIM_POOL1*sizeof(double));

    for(int i=0; i<NB_FILTERS2; i++)
    {
        for(int i2=0; i2<DIM_FILTER; i2++)
        {
        for(int k=0; k<DIM_POOL1;k++)
        {
            for(int l=0; l<DIM_POOL1; l++)
            {
                fm2->Matrix[i].matrix[k*DIM_C2+l]= input[k*DIM_POOL1+l]* (A2->Matrix[i2].matrix[k*DIM_FILTER+l]);

            }
        }
        }
    }

    return fm2;
}

//_____________________________________________________________________________________

// 3) Relu activation after C2 ________________________________________________________
void ReluActiv2(struct ALLFM2 *fm2)
{
    for(int i=0;i<NB_FILTERS2; i++)
    {
        for(int y=0; y<DIM_C2; y++)
        {
            for(int x=0; x<DIM_C2;x++)
            {
                fm2->Matrix[i].matrix[y*DIM_C2+x]=max(0,  fm1->Matrix[i].matrix[y*DIM_C2+x]);
            }
        }
    }
}
//_____________________________________________________________________________________

// 4) Pooling after C2's activation
struct PoolC2 * Pool2(struct ALLFM2 *fm2)
{
    struct PoolC2 *pc2;
    pc2=(struct PoolC2 *) malloc (NB_FILTERS2*DIM_POOL2*DIM_POOL2*sizeof(double));

    for(int j=0; j< NB_FILTERS2; j++)
    {

        for(int k=0; k<DIM_C2; k+=2)
    {
        for(int l=0;l<DIM_C2;l+=2)
        {

            double maxi=max(fm2->Matrix[j].matrix[k*DIM_C2+l],fm2->Matrix[j].matrix[k*DIM_C2+(l+1)]);
            maxi=max(maxi,max(fm2->Matrix[j].matrix[k*DIM_C2+(l+1)],fm2->Matrix[j].matrix[k+1*DIM_C2+(l+1)]));

            maxi=max(maxi,(max(fm2->Matrix[j].matrix[(k+1)*DIM_C2+(l+1)],fm2->Matrix[j].matrix[(k+1)*DIM_C2+l])));

            maxi=max(maxi,(max(fm2->Matrix[j].matrix[k*DIM_C2+l],fm2->Matrix[j].matrix[(k+1)*DIM_C2+l])));

            if(k==0 && l==0)
            {
            pc2->Matrix[j].matrix[k*DIM_POOL2+l]=maxi;
                }
            else
            {
                if(k==0)
                {
                    pc2->Matrix[j].matrix[k*DIM_POOL2+(l-1)]=maxi;
                }
                else
                {
                if(l==0)
                {
                    pc2->Matrix[j].matrix[(k-1)*DIM_POOL2+l]=maxi;
                }
                else
                {
                    pc2->Matrix[j].matrix[(k-1)*DIM_POOL2+(l-1)]=maxi;
                }
                }
            }
        }
    }

    return pc2;
}

//____________________________________________________________________________________
// 8) Flattern Layer + First Fully Connected Layer
void FlatternLayer(struct PoolC2 *pc2)
{

    //double[length] *res;
    //res=(double [length] *) malloc (DIM_POOL2*DIM_POOL2*sizeof(double));
    struct FL res*;
    res=(struct FL *) malloc (NB_FILTERS2*DIM_POOL2*DIM_POOL2*sizeof(struct Neuron));

int count=0;
for(int i=0; i<NB_FILTERS2; i++)
{
    for(int j=0; j<DIM_POOL2; j++)
    {

        for(int k=0; k<DIM_POOL2;k++ )
        {
            res->flayer[count].input= pc2->Matrix[i].matrix[j*DIM_POOL2+k];
            res->flayer[count].weights= RAND_DOUBLE;
            res->flayer[coun].bias=RAND_DOUBLE;

            count+=1;
        }
    }
}
    return res;
}

//____________________________________________________________________________________
//9) Fully Connected Layer

double GetInputFromFC(struct FL flatterned*)
{
    double res=0
    for(int i=0; i<NB_FILTERS2*DIM_POOL2*DIM_POOL2; i++)
    {
        //Dropout -> not all features are seen for better performance
        double drop=RAND_DOUBLE;
        if(drop>0.3)
        {
            res+=(flatterned->flayer[i].input*flatterned->flayer[i].weight) + flatterned->flayer[i].bias;
        }
    }

    return double;
}


void FullyConnectedLayer1(struct FL flatterned*, struct CL_out outin*)
{
    for(int i=0; i<NB_Char;i++)
    {
        outin->outP[i].input= GetInputFromFC(flatterned);
    }
}


//10) Get output with softmax

//_____________________________________________________________________________________

int main()
{
        // 1-Get Training Model

    // Forward Propagate __________________________________________________________________________

        // 2) C1 -> Convolutional Layer with 6 filters to get 6 feature maps

        // 3) Relu activation function on feature maps
        
        // 4) Pooling
        
        // 5) C2 -> Convolutional Layer with 16 filters for each feature maps to get new feature maps
        
        // 6) Relu activation function on the 96 feature maps
        
        // 7) Pooling
        
        // 8) Flattern Layer
        
        // 9) First Fully connected layer -> inputs from feature analysis make us apply weights to predict label
        
        // 10) Fully connected output layer
        
    // Backwards Propagate _______________________________________________________________________
    
    // 1) Evaluate Loss function -> Cross Entropy of first fully connected layer
    
    // 2) Derive gradients of parameters in 10
    //
    // 3) Derive gradients of parameters in Convo Layer

        
}


