#ifndef LENET_H
#define LENET_H

//Include
#include <math.h>
#include <stdlib.h>
#include "../../Tools/matrix.h"
#include <err.h>

//Maths and Constants
#define RANDOM_RANGE(max) ( rand() % max )
// Returns double between 0 and 1:
#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )

#define max(a,b) (a>=b?a:b)
#define min(a,b) ((a) < (b) ? (a) : (b))

#define DIM_INPUT 32
#define DIM_C1 28
#define NB_FILTERS1 6
#define DIM_FILTER 5
#define DIM_POOL1 14
#define FILTER_WP1 2
#define NB_FILTERS2 12
#define DIM_C2 10
#define DIM_POOL2 5
#define NB_Char 35


//Struct
struct TM
{
   Matrix *M;
   int result;
 };
// Filters for C1
struct ALLFilters1{
    Matrix Mall[NB_FILTERS1];
};

//Feature Maps for C1
struct ALLFM1{
    Matrix fm1[NB_FILTERS1];

};

//New Matrixes for Pooling for C1
struct PoolC1{
    Matrix pool1[NB_FILTERS1];
};

//Filters for C2
struct ALLFilters2{
    Matrix Mall2[NB_FILTERS2];

};

//Feature Maps for C2
struct ALLFM2{
  Matrix fm2[NB_FILTERS2];

};

//New Matrixes for Pooling for C2
struct PoolC2{
    Matrix pool2[NB_FILTERS2];

};
// Neuron Structure
struct Neuron{
        double input;
        double weight;
        double bias;
};

//Flatterning Layer with neuron implementation -> Fully connected layer
struct FL{
    struct Neuron flayer[DIM_POOL2*DIM_POOL2*NB_FILTERS2];

};


//Fully Connected Layer for output
struct CL_out{
    struct Neuron outP[NB_Char];
};

struct resultsfromoutput{
    double ASCII;
    double output;
    double weight;
    double bias;
};


void getFilter1(struct ALLFilters1 *A1);
void ConvolutionLayer1(struct ALLFM1 *cfm1, struct ALLFilters1 *A1, Matrix input);
void ReluActiv1(struct ALLFM1 *cfm1);
void Pool1(struct ALLFM1 *cfm1,struct PoolC1 *pc1);
void getFilter2(struct ALLFilters2 *A2);
void ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1,struct ALLFM2 *cfm2);
void ReluActiv2(struct ALLFM2 *cfm2);
void Pool2(struct ALLFM2 *cfm2,struct PoolC2 *pc2);
void FlatternLayer(struct PoolC2 *pc2,struct FL *res);
double GetInputFromFC(struct FL *flatterned);
void FullyConnectedLayer1(struct FL *flatterned, struct CL_out *outin);
struct resultsfromoutput GetOutPut(struct CL_out *outin);




#endif


