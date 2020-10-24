//_____________________XY-cut_________________________________//


//_____________________include________________________________//
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "rlsa.h"
#include "resizeMatrix.h"
#include <stdio.h>
#include <stdlib.h>

//________________begining_________________________//

//the fonction that begins the others
Tree *beginSeg(Matrix M)
{
    Tree *txt = new_Tree(-4);
    segmentation(M);
    return txt;
}



////____________FROM RLSA TO XY-CUT______________________________

/*Tree segmentation(Matrix M)
{
    int widht= M.width;
    int lenght= M.length;
    Matrix og= copyMatrix(M);
    Tree T= newTree(-3);
    M = rsla(M);
    int started=0;      //if started
    int previouspix=0;
    int xbeg=0;
    int xend=0;
    int yend=0;
    int ybeg=0
    int x=0;
    int y=0;
    while (x<length && y<widht)
    {
        if  (started==0 && M.matrix[y*length+x]==1)
        {
            started=1;
            xbeg=x;
            ybeg=y;
        }
        if (started==1 && M.matrix[y*lenght+x]==0 && xend==0)
        {
            xend=x;
            y++;
            x--;
        }
    }
 }*/
    
// THE IDEA:

    //cut 1 matrix into several small matrices
    //put each matrix on the tree on the level were it belongs
    /*      -3 : paragraph
            -2 : lines
            -1 : words
             0 : letters    */
 

//recursively calling a new cutting process to add each step into the tree

//__________________CUTTING HORIZONTAL BLANKS______________________________

//2nd major function
//fonction linking rsla to xy-cut
void segmentation(Matrix M)
{
    int widht= M.width;
    int lenght= M.height;
    int horizontal=1;
    Matrix og= copyMatrix(M);
    Tree *T= newTree(-3);
    M = rlsa(M,10,10);

    int xbeg=0;

    horizontalcut(T,M,og,1,1,0);

    return T;
}

void horizontalcut(Tree *T,Matrix M,Matrix og,int horizontal,int vertical,int line)
{
    int width= M.width;
    int lenght= M.height;
    int y=0;
    int x=0;
    int started=0;
    int ybeg=0;
    Matrix tocut;
    Matrix og1;
    Matrix og2;
    Matrix rest;
    
    if (horizontal==2 && vertical==2 && line==1)
    {
        Tree *Child = newTree(-2);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }
    
    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og,4,4),og,1,1,1);
    }
    
    while(y<lenght)
        {
            x=0;
            while(x<width && M.matrix[y*lenght+x]==0)
            {
                x++;
            }
            if (y==lenght && x==width && started==0)
            {
                horizontal=2;
            }
            if (x==width && started==1)
            {
                if (y!=lenght)
                {
                    rest=cutMatrix(M,0,y,width,lenght-y);
                    og1=cutMatrix(og,0,y,width,lenght-y);
                    horizontalcut(T,rest,og1,1,vertical,line);
                }
                if (line==0)
                {
                tocut=cutMatrix(M,0,ybeg,width,y-ybeg);
                og2=cutMatrix(og,0,ybeg,width,y-ybeg);
                verticalcut(T,tocut,og2,1,vertical,0);
                y=lenght;
                }
                if (line==1)
                {
                og2=cutMatrix(og,0,ybeg,width,lenght-y);
                Tree *Child = newTree(-2);
                AddChild(T, Child);
                _trycut(og,1,Child);
                }
            }
            else if( started==0 && x<width && M.matrix[y*lenght+x]==1)
            {
                ybeg=y;
                x=0;
                started=1;
            }
            else if (x<width && M.matrix[y*lenght+x]==1)
            {
                x=0;
            }
            y++;
        }
}

//__________________CUTTING VERTICAL BLANKS______________________________

void verticalcut(Tree T,Matrix M,Matrix og,int horizontal,int vertical, int line)
{
    int width= M.width;
    int lenght= M.height;
    int y=0;
    int x=0;
    int started=0;
    int xbeg=0;
    Matrix tocut;
    Matrix og1;
    Matrix og2;
    Matrix rest;
    
    if (horizontal==2 && vertical==2 && line==1)
    {
        Tree *Child = newTree(-2);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }
    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og,4,4),og,1,1,1);
    }

    
    while(x<width)
        {
            y=0;
            while(y<lenght && M.matrix[y*lenght+x]==0)
            {
                y++;
            }
            if (y==lenght && x==width && started==0)
            {
                vertical=2;
            }
            if (y==lenght && started==1)
            {
                
                if (x!=width)
                {
                    rest=cutMatrix(M,xbeg,0,width-x,lenght);
                    og1=cutMatrix(og,xbeg,0,width-x,lenght);
                    horizontalcut(T,rest,og1,horizontal,vertical,line);
                }
                tocut=cutMatrix(M,x,0,x-xbeg,lenght);
                og2=cutMatrix(og,x,0,x-xbeg,lenght);
                verticalcut(T,tocut,horizontal,vertical,line);
                x=width;
            }
            else if( started==0 && y<lenght && M.matrix[y*lenght+x]==1)
            {
                xbeg=x;
                y=0;
                started=1;
            }
            else if (y<lenght && M.matrix[y*lenght+x]==1)
            {
                y=0;
            }
            x++;
            
        }
        //return T;
}



///________________________CUTTING WORDS AND LINES____________________
///__________________________XY-CUT_____________________________________

//column reding to cut in vertical//
Matrix vertical(Matrix M)
{
    int h_size = M.height;
    int w_size = M.width;
    int y=0;
    //Detect zone spaces
    //principle
    //if there is a black pixel-> it is a separation
    //the column becomes black
    
    for (int x=0; x<w_size ;x++)
    {
        y=0;
        while ((y<h_size) && (M.matrix[y*w_size + x]=!1))
        {
            y++;
        }
        if (y!=h_size)
        {
            for (int i; i<h_size; i++)
            {
                M.matrix[i*w_size + x]=1;
            }
        }
    }
    return M;
}


void _trycut(Matrix M, int line, Tree *T)
{
    //copying the og matrix
    Matrix reel = copyMatrix(M);

    int y = 0;
    int h_size = M.height;
    int w_size = M.width;
    

    //___________________________TO DO_____________________________________//
    //we should get the lines as thin as possible: horzontal path//
    //get the technique better: histogrammes if spots and grains left...//
    
    //either lines or word, so vertical exam
    //for now we assume their isn't any defaults left
    
    M=vertical(M);
    //black blocks matrix
    //now choose if it's cuting line or words
    //it's not made the same way
    
/*_____________INITIALISATION VARIABLES COMMUNES________________*/
    
    int previous=0; //previous pixel value
    
    int x=0;
    //first value of the x of  the element
    
    //booléens pour se repérer dans les fonctions
    int begin=0; //1 if the word has started
    int end=0;   //1 if it is the last pixel of the line
    
    Matrix createseg;
    
    int totalspace=0;//number of white pixel/separation
    
    //_______LINEAR CUT______________________________________________
    if (line==1)
    {
        int nbspace=-1;  //number of white pixel suite
                        //begins at -1 because it counts one more
        
        /*_______Detect spaces &  average of spaces_____________*/
        for (int c; c<w_size; c++)
        {
            
            if (M.matrix[c] == 0)
            {
                totalspace++;
            }
            else
            {
                if (previous==0)
                {
                    nbspace++;
                }
                previous=1;
            }
        }
        
        int average= totalspace/nbspace;
        //average space between word and char
        
        //reinitialisation
        totalspace=0;
        previous=0;
        
        for (int ix=0; ix<w_size; ix++)
        {
            if (ix+1==w_size)
            {
                end=1;
            }
            
            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //word starts
                {
                    begin=1;
                    x=ix; //word begins at x=xi here y doesn't matter
                }
                else
                {
                    
                    if (totalspace>average || end == 1 )
                    {
                        //matrix of the word that was found
                        createseg=cutMatrix(reel,x,0,ix-totalspace,h_size);
                        
                        Tree *Child = newTree(-1);
                        AddChild(T, Child);
                        _trycut(createseg,0,Child);
                        
                        freeMatrix(createseg);
                        begin=0;
                    }
                }
                totalspace=0;
            }
            else
            {
                totalspace++;
                
            }
        }
        
    }
    //____________________WORD_CUTTING____________________________________
    
    else
    {
        int letter=0;//the code og the letter to put in the tree then
        for (int ix=0; ix<w_size; ix++)
        {
            
            if (ix+1==w_size)
            {
                end=1;
            }
            
            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //the letter starts
                {
                    begin=1;
                    x=ix; //the letter starts at the xy: x=xi
                    //xlen=1;
                }
                else
                {
                //xlen+= totalspace;
                
                    if ( begin==1 && end == 1 )
                    {
                        
                        //creating a matrix for the caracter that was found
                        createseg=cutMatrix(reel,x,0,ix-totalspace,h_size);
                        
                        createseg=resizeMatrix(createseg,30);
                        
                        //____FINAL___________
                        //intergrate the fonction when the
                        //neural network is created
    
                        //for now that is how it works but useless,
                        //we'll have to send the ascii code of the char
                        //letter=ascii code;
                    
                        Tree *Child = newTree(0);
                        AddChild(T, 0); //will be the value of the char
                        
                        //reinitialisation
                        freeMatrix(createseg);
                        begin=0;
                    }
                }
                totalspace=0;
            }
        
        else
            {
                //number of space adds up
                totalspace++;
            }
        }
    }
    
    freeMatrix(reel);
    //return *T;
}

