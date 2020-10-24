/* 
 *                                               XOR NEURAL NETWORK 
 *
 *                          A neural network capable of learning the XOR function
 *                          By A.Barry
 *
 * Memory usage:
 * - 2 neuronModels for the hidden layer of neurons
 * - 1 neuronModel for the output neuron
 * - 1 training model for the current model that is trained
 *
 */


// Include section
 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>

//___________________________________________________________________________________________________________________

//1) Model initialization

// Training Model with two inputs for example 1 XOR 0 and the result(0 or 1)

struct TM
{
   double inputs[2];
   double result;
 };

// Neuron Model

struct neuronModel
{
   double inputs[2];
   double weights[2];
   double bias;
  };


// 2 inputs -> hidden layer= intermediate layer - 2 inputs -> output layer 
//So need for 2 input array per neuron


//_________________________________ Needed Maths functions ___________________

// Sigmoid and its derivative
#define SIGMOID(x)       ( 1. / (1. + exp(-x)) )
#define SIGMOID_DERIV(x) ( exp(-x)/((1+exp(-x)*(1+exp(-x)))))

// Returns int between 0 and max:
#define RANDOM_RANGE(max) ( rand() % max )
// Returns double between 0 and 1:
#define RAND_DOUBLE       ( (double)rand()/(double)RAND_MAX )



//__________________________________________________________________________________
//
//                                      Main
//
//__________________________________________________________________________________

int main()
{
  //___________________________________________________________________      
  //Step 1- Model initialization

  //__________ Print _________________
  printf("\n_________________________________________________________ \n\n Initialisation du modèle du réseau de neurones XOR \n \n_________________________________________________________\n \n");
  //__________________________________
    
    //Initializing output layer (made of 1 neuron, the output)
    
     double random4= RAND_DOUBLE;
     double random5= RAND_DOUBLE;
     double random6= RAND_DOUBLE;
     struct neuronModel *output_neuron;
     output_neuron=(struct neuronModel *) malloc (sizeof(struct neuronModel));
     output_neuron->weights[0]=random4;
     output_neuron->weights[1]=random5;
     output_neuron->bias=random6;

    // Creating intermediate layer -> array of 2 neurons
    struct neuronModel *intermediate_neurons;
    intermediate_neurons=(struct neuronModel *)  malloc(2* sizeof(struct neuronModel));
    
  // Initialize the 2 neurons by randomizing them
  for (size_t i = 0; i < 2; i++)
  {
            //intermediate_neurons[i]=(struct neuronModel *) malloc (sizeof(struct neuronModel));
            double random1= RAND_DOUBLE;
            double random2= RAND_DOUBLE;
            double random3= RAND_DOUBLE;
            (intermediate_neurons[i]).weights[0]= random1;
            (intermediate_neurons[i]).weights[1]= random2;
            (intermediate_neurons[i]).bias= random3;
  
    //________ Print_____________
    printf("Les poids initiaux du neurone n°%zu de la couche cachée: \n  poids n1=%f \n  poids n2=%f \n  son biais=%f \n______________________________________________________ \n \n",i, intermediate_neurons[i].weights[0], intermediate_neurons[i].weights[1], intermediate_neurons[i].bias);
    //___________________________
    
  }

    
  //______________________________________________________________________
  //TRAINING THE NEURAL NETWORK
 
    struct TM *t;
    t=(struct TM *) malloc (sizeof(struct TM));
    
  for (unsigned long ktests = 0; ktests < 40000000000; ktests++)
  {
      
    // Random test (for now then will put inputs)
    //
    struct TM all_xor[] = {
    {{0, 0}, 0},
    {{0, 1}, 1},
    {{1, 0}, 1},
    {{1, 1}, 0},
      };

    t = &(all_xor[RANDOM_RANGE(4)]);
    
     //_________________________________________________________________________
    // Step 2- Forward propagate 
    // Feedforward= called feedforward because information only travels forward in the network (no loops)

    for (size_t i = 0; i < 2 ; i++)
    { 
    for (size_t j = 0; j < 2 ; j++)
      {   intermediate_neurons[i].inputs[j] = t->inputs[j]; }

        double forward1=0;
         for(size_t forw1 = 0; forw1 < 2; forw1++)
         {
             forward1 += intermediate_neurons[i].inputs[forw1] * intermediate_neurons[i].weights[forw1];
         }
     forward1 += intermediate_neurons[i].bias;
     output_neuron->inputs[i] = SIGMOID(forward1);

    }

    // Get the output for Step 3- Loss function
    // Output Layer -> Output
    //struct Tuple res= forward(output_neuron);
    double output= 0;
    //output_neuron= res.b;
    
    for(size_t forw2 = 0; forw2 < 2; forw2++)
        {
        output+= output_neuron->inputs[forw2] * output_neuron->weights[forw2];
         }   
     output += output_neuron->bias;
     output = SIGMOID(output);


    //Print Loss function every 10000 000times
    if (ktests%100000000==0)
    {
        printf("Entraînement n°%lu, fonction de perte= %f \n",ktests,output);
    }
    //___________________________________________________________________________

    // Step 4- Differentiation
    
    double differentiation = SIGMOID_DERIV(output) * (t->result - output);
    if (ktests%100000000==0)
     {
         printf("Differentiation= %f \n \n",differentiation);
     }
    //___________________________________________________________________________
    //
    //Step 5- Back-propagation and Step 6- Weight update
    // See ouput weigths before back propagation using SGD
    
             for(size_t b=0;b<2;b++)
    {
        output_neuron->weights[b] += differentiation * output_neuron->inputs[b];
    }
    output_neuron->bias += differentiation;
        

    // Update hidden layer
    for (size_t i = 0; i < 2; i++)
    {   
      double errors = SIGMOID_DERIV(output_neuron->inputs[i]) * differentiation * output_neuron->weights[i];
        
      for(size_t back=0;back<2;back++)
      {
          intermediate_neurons[i].weights[back] += errors * intermediate_neurons[i].inputs[back];
      }
      intermediate_neurons[i].bias +=errors;
      
      if(ktests%100000000==0)
      {
      printf("Mise à jour du poids du neurone n°%zu de la couche cachée:  n1= %f n2=%f et biais= %f \n",i, intermediate_neurons[i].inputs[0], intermediate_neurons[i].inputs[1], intermediate_neurons[i].bias);
        }
     
    }
   //_____________________________________________________________________________ 
    //Step 7- Iterate until convergence --> for ...

    if(ktests%100000000==0)
  {printf("Poids du neurone de sortie, n°1=%f n°2=%f et biais=%f \nRésultat final: \n%d XOR %d = %d \n_______________________________________________________________________________________________ \n", output_neuron->weights[0], output_neuron->weights[1],output_neuron->bias,(int)t->inputs[0], (int)t->inputs[1], output>0.5);

  }
     
      if (ktests==40000000000)
      {
      if(output_neuron != NULL){
         free(output_neuron);
         output_neuron = NULL;
    }

   if(intermediate_neurons != NULL){
     free(intermediate_neurons);
     intermediate_neurons = NULL;
    }

     if(t != NULL){
          free(t);
         t = NULL;
     }
      }
  }
  
  return 0;
}
