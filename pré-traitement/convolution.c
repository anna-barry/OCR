//_________________Convolution___________________
//__________________enlever_les_taches___________

//________________include________________________

#include <stdio.h>
#include <stdlib.h>
#iclude "../Tools/matrix.h"


//_______retirer_taches___________________________
//methode_médiane

Matrix smooth(Matrix M)
{
    int width=M.width;
    int height=M.height;
    int array[9];
    
    
    //variables a definir: di pour diagonale, h pour haut,b pour bas, g pour gauche, d pour droit
    int center=0
    int dihg=0;
    int g=0;
    int dibg=0;
    int h=0;
    int b=0;
    int dihd=0;
    int d=0;
    int dibd=0;
    
    int compteur=0;
    
    for (int x=0; w<width; i++)
    {
        compteur =0;
        for (int y=0; y<height; y++)
        {
            center= m.Matrix[x+y*width];
            array[1]=center;
            //assimilation des valeurs pour chaque pixel
            
            if (x!=0)
            {
                g= m.Matrix[(x-1)+y*width];
                array[0]=g;
                compteur ++;
            }
            if (x!=width-1)
            {
                d= m.Matrix[(x+1)+y*width];
                compteur ++;
                array[2]=d;
            }
            if (y!=0)
            {
                h=m.Matrix[x+(y-1)*width];
                compteur ++;
                array[3]=h;
            }
            if (y!=height-1)
            {
                b=m.Matrix[x+(y+1)*width];
                compteur ++;
                array[4]=b;
            }
            if (x!=0 && y!=0)
            {
                dihg= m.Matrix[(x-1)+(y-1)*width];
                compteur ++;
                array[5]=dihg;
            }
            if( x!=width-1 && y!=height-1)
            {
                dibd= m.Matrix[(x+1)+(y+1)*width];
                compteur ++;
                array[6]=dibd;
            }
            if (x!=0 && y!=height-1)
            {
                dibg= m.Matrix[(x-1)+(y+1)*width];
                compteur ++;
                array[7]=dibg;
            }
            if (x!=widht-1 && y!=0)
            {
                dihd= m.Matrix[(x+1)+(y-1)*width];
                compteur ++;
                array[8]=dihd;
            }
            
            array_select_sort(array,9);
            
            int mid= array[4]; //(9-compteur+9)/2???
            
            m.Matrix[x+y*width]=mid;
            
        }
    }
    
    return Matrix;
}

void array_select_sort(int array[], size_t len)
{
    for (size_t i=0; i<len; i++)
    {
        size_t pos=i;
        for (size_t j=i; j<len; j++)
        {
            if(array[pos] > array[j])
            pos=j;
        }
        if(pos != i)
        {
            array_swap(array,i,pos);
        }
    }
}



Matrix contrast(Matrix M)
{
    
}
