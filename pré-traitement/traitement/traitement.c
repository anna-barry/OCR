//_________________Convolution___________________
//_________________Remove_Spots___________

//________________include________________________

#include <stdio.h>
#include <stdlib.h>
#include "../../Tools/matrix.h"
#include "../../Tools/help4display.h"
#include "traitement.h"


//_______Begin___________________________

int summul(Matrix m1, Matrix m2)
{
    /*
    description :
    sum of the multiplication of two matrixes
    parameters :

    double m1[]: first matrix
    double m2[]: second matrix
     
    dates/authors :
    24/10
    marine thunet

    */
    int total=0;
    int sum=0;
    for (size_t x=0; x<3; x++)
    {
        for (size_t y=0; y<3; y++)
        {
            for (size_t i=0; i<3; i++)
            {
                sum+=m1.matrix[x*3+i]*m2.matrix[i*3+y];
            }
            total+=sum;
            sum=0;
        }
    }
    /*if (total<0)    {
        total=-total;
    }*/
    return total;
}

//TO DO NOT FINISHED
Matrix smooth(Matrix m)
{
    /*
    description :

    -taking each 8 pixel around the middle pixel
    -replacing the middle pixel by the result of the gaussian filter
    -helps to smooth

    parameters :

    Matric M: the matrix of the picture

    dates/authors :
    24/10
    marine thunet

    */
    
    int width=m.width;
    int height=m.height;
    double sum=0;
    Matrix new;
    new.height=height;
    new.width=width;
    new.matrix= malloc(width*height*sizeof(double));
    
    Matrix array;
    array.height=3;
    array.width=3;
    array.matrix = malloc (3*3*sizeof(double));
    
    Matrix mult;
    mult.height=3;
    mult.width=3;
    mult.matrix = malloc (3*3*sizeof(double));
    
    mult.matrix[0]=1;
    mult.matrix[1]=2;
    mult.matrix[2]=1;
    mult.matrix[3]=2;
    mult.matrix[4]=4;
    mult.matrix[5]=2;
    mult.matrix[6]=1;
    mult.matrix[7]=2;
    mult.matrix[8]=1;
    
    
    //variables a definir: di pour diagonale, h pour haut,b pour bas, g pour gauche, d pour droit
    for (int y=1; y<height-1; y++)
    {
        for (int x=1; x<width-1; x++)
        {
            array.matrix[4]= m.matrix[x+y*width];
            //assimilation des valeurs pour chaque pixel
            array.matrix[3]=m.matrix[(x-1)+y*width];
            
            array.matrix[5]=m.matrix[(x+1)+y*width];
            
            array.matrix[1]=m.matrix[x+(y-1)*width];
            
            array.matrix[7]=m.matrix[x+(y+1)*width];
            
            array.matrix[0]=m.matrix[(x-1)+(y-1)*width];
            
            array.matrix[8]=m.matrix[(x+1)+(y+1)*width];
            
            array.matrix[6]=m.matrix[(x-1)+(y+1)*width];
            
            array.matrix[2]=m.matrix[(x+1)+(y-1)*width];
            
            sum=summul(array,mult);

            new.matrix[x+y*width]=sum/16; //16 being the coefficent's sum
            
        }
    }
    freeMatrix(mult);
    freeMatrix(array);
    m=new;
    freeMatrix(new);
    return m;
}

int mul(Matrix m1, Matrix m2, Matrix r)
{
    int sum=0;
    for (size_t x=0; x<3; x++)
    {
        for (size_t y=0; y<3; y++)
        {
            for (size_t i=0; i<3; i++)
            {
                sum+=m1.matrix[x*3+i]*m2.matrix[i*3+y];
            }
            r.matrix[x*3+y]=sum;
            sum=0;
        }
    }
    return r.matrix[4];
}


Matrix contrast(Matrix m)
{
    /*
    description :

    giving more contrast on matrix

    parameters :

    Matrix M= matrix of an image
     
    dates/authors :
    15/11
    marine thunet

    */
    
    int width=m.width;
    int height=m.height;
    
    Matrix new2;
    new2.height=height;
    new2.width=width;
    new2.matrix= malloc(height*width*sizeof(double));
    
    Matrix new;
    new.width=3;
    new.height=3;
    new.matrix= malloc(9*sizeof(double));
    
    
    Matrix array;
    array.width=3;
    array.height=3;
    array.matrix= malloc(9*sizeof(double));
    
    Matrix mult;
    mult.width=3;
    mult.height=3;
    mult.matrix= malloc(9*sizeof(double));
    
    mult.matrix[0]=0;
    mult.matrix[1]=-1;
    mult.matrix[2]=0;
    mult.matrix[3]=-1;
    mult.matrix[4]=6;
    mult.matrix[5]=-1;
    mult.matrix[6]=0;
    mult.matrix[7]=-1;
    mult.matrix[8]=0;
    
    /*//variables a definir: di pour diagonale, h pour haut,b pour bas, g pour gauche, d pour droit
    int center=0;
    int g=0;
    int h=0;
    int b=0;
    int d=0;*/
    
    for (int y=1; y<height-1; y++)
    {
        for (int x=1; x<width-1; x++)
        {
            array.matrix[4]= m.matrix[x+y*width];
            //assimilation des valeurs pour chaque pixel
            array.matrix[3]=m.matrix[(x-1)+y*width];
            
            array.matrix[5]=m.matrix[(x+1)+y*width];
            
            array.matrix[1]=m.matrix[x+(y-1)*width];
            
            array.matrix[7]=m.matrix[x+(y+1)*width];
            
            array.matrix[0]=m.matrix[(x-1)+(y-1)*width];
            
            array.matrix[8]=m.matrix[(x+1)+(y+1)*width];
            
            array.matrix[6]=m.matrix[(x-1)+(y+1)*width];
            
            array.matrix[2]=m.matrix[(x+1)+(y-1)*width];
            
            
            
            new2.matrix[x+y*width]=mul(array,mult,new);
        }
    }
    freeMatrix(new);
    freeMatrix(mult);
    m=new2;
    freeMatrix(new2);
    return m;
}
