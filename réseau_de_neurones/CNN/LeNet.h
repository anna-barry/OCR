#ifndef LENET_H
#define LENET_H

//Include
#include <math.h>
#include <stdlib.h>
#include "../../Tools/matrix.h"
#include <err.h>
#include <time.h>

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
#define NB_FILTERS2 10
#define DIM_C2 10
#define DIM_POOL2 5
#define NB_Char 60
#define NB_ITERATION 1

//Struct
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
    Matrix *m;
    struct PoolC1 *next;
};

//Filters for C2
struct ALLFilters2{
    Matrix *m;
    struct ALLFilters2 *next;
};

//Feature Maps for C2
struct ALLFM2{
    Matrix *m;
    struct ALLFM2 *next;
};

//New Matrixes for Pooling for C2
struct PoolC2{
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
    struct Neuron *n;
};


//Fully Connected Layer for output
struct CL_out{
    struct Neuron *n;
};

struct resultsfromoutput{
    double ASCII;
    double i;
    double output;
    double weight;
    double bias;
};

struct sendback GetRandomSet();
void getFilter1(struct ALLFilters1 *A1);

void ConvolutionLayer1(struct ALLFM1 *cfm1, struct ALLFilters1 *A1, Matrix input);

void ReluActiv1(struct ALLFM1 *cfm1);

void Pool1(struct ALLFM1 *cfm1,struct PoolC1 *pc1);

void getFilter2(struct ALLFilters2 *A2);

void ConvolutionLayer2(struct ALLFilters2 *A2, struct PoolC1 *pc1,struct ALLFM2 *cfm2);

void ReluActiv2(struct ALLFM2 *cfm2);

struct PoolC2 *init_pool(size_t n);

void Pool2(struct ALLFM2 *cfm2,struct PoolC2 *pc2);

void FlatternLayer(struct PoolC2 *pc2,struct FL *res);

double GetInputFromFC(struct FL *flatterned);

void FullyConnectedLayer1(struct FL *flatterned,  struct CL_out *outin);

struct resultsfromoutput GetOutPut(struct CL_out *outin);

struct CL_out *init_out(int n);

struct FL *init_fl(int n);

void free_Matrix(Matrix *m);

void free_FlatternedLayer(struct FL *flatterned1);

void free_OutPutLayer(struct CL_out *out);

void free_ALLFilters1(struct ALLFilters1 *p);

void free_ALLFM1(struct ALLFM1 *p);

void free_PoolC1(struct PoolC1 *p);

void free_ALLFilters2(struct ALLFilters2 *p);

void free_ALLMaps2(struct ALLFM2 *p);

void free_PoolC2(struct PoolC2 *p);

void free_Matrix2(Matrix m);
void freeMatrix1(Matrix M);

double CrossEntropy(struct CL_out *clout, int BinIndicaor);

double SoftLayerBack(struct CL_out *clout, int BinIndicaor, int i);

void BackforOutput(struct CL_out *clout, int BinIndicaor);

void GradientsFromPoolingLast(struct PoolC2 *pool2, struct ALLFM2 *feat2);

void BackForFiltersLast(struct ALLFilters2 *filers2, struct ALLFM2 *feat2,struct PoolC1 *pool1);

void GradientsFromPooling(struct PoolC1 *pool1, struct ALLFM1 *feat1);

void BackForFilters(struct ALLFilters1 *filter1, struct ALLFM1 *feat1, Matrix input);


#endif
