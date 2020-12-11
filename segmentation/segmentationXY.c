//_____________________XY-cut_________________________________//

//_____________________include________________________________//
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "../pré-traitement/binarisation/binarisation.h"
#include "rlsa.h"
#include "resizeMatrix.h"
#include <stdio.h>
#include <stdlib.h>


////____________FROM RLSA TO XY-CUT______________________________

    
// THE IDEA:

    //cut 1 matrix into several small matrices
    //put each matrix on the tree on the level were it belongs
    /*      -3 : paragraph
            -2 : lines
            -1 : words
             0 : letters    */
 

//recursively calling a new cutting process to add each step into the tree

//erase then cause useless for the OCR

///________________________CUTTING WORDS AND LINES____________________
///__________________________XY-CUT_____________________________________

//column reading to cut in vertical//
Matrix vertical(Matrix M)
{
    
/*
description :
-on this function we recon that noises and spots were treated
-traces a black column if 1 pixel is in the column
-goes along each colum, it will help to detect easily

parameters :

Matric M: the matrix of the picture

dates/authors :
17/10
marine thunet

    */
    
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
        while ((y<h_size) && (M.matrix[y*w_size + x]==0))
        {
            y++;
        }
        if (y<h_size)
        {
            while (y>=0)
            {
                M.matrix[y*w_size + x]=1;
                y--;
            }
        }
    }
    if (h_size>0)
    {
        matToImg(M,"waaf");
    }
    return M;
}


void _trycut(Matrix M, int line, Tree *T)
{
    /*
    description :

    -the function cuts vertical lines
    -adds each segmente to the tree
        -if word then level -1
        -if char then level 0

    parameters :

    Matric M: the matrix of the picture
    int line: boolean teeling us if we are cutting a line or a word
    Tree *T: the pointer to the tree that is building

    dates/authors :
    15/10
    marine thunet

    */
    //copying the og matrix
    if (M.width<=0 || M.height<=0)
    {
        return;
    }
    Matrix reel = copyMatrix(M);
    //int y = 0;
    int h_size = M.height;
    int w_size = M.width;
    

    //___________________________TO DO_____________________________________//
    //we should get the lines as thin as possible: horizontal path//
    //get the technique better: histogrammes if spots and grains left...//
    
    //either lines or word, so vertical exam
    //for now we assume their isn't any defaults left
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
        M=vertical(M);
        int nbspace=-1;  //number of white pixel suite
                        //begins at -1 because it counts one more
        
        int trans=0;
        int max=0;
        /*_______Detect spaces &  average of spaces_____________*/
        for (int c=0; c<w_size; c++)
        {
            if (M.matrix[c] == 0)
            {
                totalspace++;
                trans++;
            }
            else
            {
                if (previous==0)
                {
                    nbspace++;
                    if (trans>max)
                    {
                        max=trans;
                    }
                    trans=0;
                }
            }
            previous=M.matrix[c];
        }
        //debug
        if (nbspace<=0)
        {
            return;
        }
        int average= ((totalspace/nbspace)+max)/2;
        //average space between word and char
        //reinitialisation
        totalspace=0;
        previous=0;
        //printf("ODHHHHHHHHHHHHHHHHH");

        for(int ix=0; ix<w_size; ix++)
        {

            if (ix+1==w_size)
            {
                end=1;
            }

            if (M.matrix[ix]==1 || end==1)
            {
                if (begin == 0 && end == 0) //word starts
                {
                    begin=1;
                    x=ix; //word begins at x=xi here y doesn't matter
                }
                else
                {
                    if (begin == 1 && (totalspace>=average || end == 1 ))
                    {

                        //matrix of the word that was found
                        createseg=cutMatrix(reel,0,x,h_size,ix-x);
                        //print_Matrix(createseg);
                        if (h_size>0)
                        {
                            matToImg(createseg,"testAgtgYU");
                        }

                        Tree *Child = newTree(0);
                        AddChild(T, Child);
                        _trycut(createseg,0,Child);
                        
                        free(Child);
                        freeMatrix(createseg);
                        
                        x=0;
                        begin=0;
                        //Tree *S= newTree(-1);
                        //AddSibling(T,S);
                        //T = S;
                        //free(S);
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
        
        M=vertical(M);
        //int letter=0;//the code og the letter to put in the tree then
        for (int ix=0; ix<w_size; ix++)
        {
            if ((M.matrix[ix]==0 && begin==1))
            {

                end=1;
            }
            
            if (M.matrix[ix]==1 || end==1)
            {
                if (begin == 0 && end == 0) //the letter starts
                {
                    begin=1;
                    x=ix; //the letter starts at the xy: x=xi
                    //xlen=1;
                }
                else
                {
                    printf("last\n");
                //xlen+= totalspace;
                    if ( begin==1 && end == 1 )
                    {
                        printf("last letters\n");
                        //creating a matrix for the caracter that was found
                        createseg=cutMatrix(reel,0,ix,h_size,ix-x);
                        //createseg=resizeMatrix(createseg,16);
                        //for the test
                        if (h_size>0)
                        {
                        matToImg(createseg,"testOUUO111OOU");
                        }
                        //____FINAL___________
                        //intergrate the fonction when the
                        //neural network is created
                        //for now that is how it works but useless,
                        //we'll have to send the ascii code of the char
                        //letter=ascii code;
                        T->key=97;
                        /*
                        Tree *Child = newTree(97);
                        AddChild(T, Child);*/ //will be the value of the char
                        
                        //reinitialisation
                        freeMatrix(createseg);
                        //Tree *S= newTree(0);
                        //AddSibling(T,S);
                        //free(T);
                        //T = S;
                        //free(S);
                        x=ix;
                        begin=0;
                        end=0;
                    }
                }
            }
        
        }
    }
    
    //freeMatrix(createseg);
    freeMatrix(reel);
    return;
}


//__________________CUTTING HORIZONTAL BLANKS______________________________
void verticalcut(Tree *T,Matrix M,Matrix og, int line, int cutted);

void horizontalcut(Tree *T,Matrix M,Matrix og,int line, int cutted)
{
    /*
    description :

    -cuts first horizontal block founded
    -treats the block founded
    -the rest of the block is treated horizontally

    parameters :

    Tree *T : the pointer to the tree that is building
    Matric M : the matrix of the picture
    int cutted: 1 if wasn't cuted last trial, 0 otherwise
    int line : boolean teeling us if we are cutting a line (1) or a word (0)

    dates/authors :
    24/10
    marine thunet

    */
    if (M.width<=0 || M.height<=0)
    {
        return;
    }
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
    
    while(y<lenght)
        {
            x=0;
            //parcours ligne tant que pas de pixel noir
            while(x<width && M.matrix[y*width+x]==0)
            {
                x++;
            }
            
            if (y==lenght-1 && ybeg==0 && started==1)
            {
                cutted++;
                if (line==1)
                {
                    Tree *Child = newTree(-1);
                    AddChild(T, Child);
                    _trycut(og,1,Child);
                    //freeMatrix(og);
                }
                else
                {
                    if (cutted>=2)
                    {
                        //matToImg(og,"testAC");
                        Tree *Child = newTree(-2);
                        AddChild(T, Child);
                        Matrix s = rlsa(og,250,40);
                        Matrix m = rlsa(s,400,200);
                        horizontalcut(Child,m,og,1,0);
                        
                        //free(Child);
                        freeMatrix(m);
                        freeMatrix(s);
                    }
                
                    else
                    {
                        verticalcut(T,M,og,0,1);
                    }
                }
                return;
                
            }
            //si on n'a pas deja commencé, mais que l'on trouve un pixel noir
            else if (started==0 && x<width && M.matrix[y*width+x]==1)
            {
                printf("3\n");
                ybeg=y;
                x=0;
                started=1;
            }
            //si on a deja comméncé et qu'on trouve un pixel noir
            else if (x<width && M.matrix[y*width+x]==1)
            {
                //printf("2\n");
                x=0;
            }
            //si on a parcouru une ligne blanche sans pixel noir et que l'on avait avant
            else if ((x==width || y==lenght-1) && started==1 && y>0)
            {
                printf("enter??\n");
                //ensuite on va traiter le paragraphe deja découpé
                //si on etait a l'étape de découpe de paragraphes
                if (line==0)
                {
                    tocut=cutMatrix(M,ybeg,0,y-ybeg,width);
                    og2=cutMatrix(og,ybeg,0,y-ybeg,width);
                    //matToImg(og2,"OMGSTE\n");
                    verticalcut(T,tocut,og2,0,0);
                    freeMatrix(tocut);
                    freeMatrix(og2);
                }
                //si on etait à l'étape de decoupe des lignes
                if (line==1)
                {
                    printf("tacaptax\n");
                    og2=cutMatrix(og,ybeg,0,y-ybeg,width);
                    //printf("ici??ouou\n");
                    //matToImg(og,"ARCHE");
                    matToImg(og2,"OMGSTPCAMARCHE");
                    Tree *Child = newTree(-2);
                    AddChild(T, Child);
                    _trycut(og2,1,Child);
                    free(Child);

                    freeMatrix(og2);
                }
                
                //si pas a la fin de la matrice, on continue horizontale pour le reste
                if (y!=lenght)
                {
                        rest=cutMatrix(M,y,0,lenght-y,width);
                        og1=cutMatrix(og,y,0,lenght-y,width);
                        //rest so new sibling;
                        Tree *S = newTree(-3);
                        if (line==1)
                        {
                            S = newTree(-2);
                        }
                        AddSibling(T,S);
                        horizontalcut(S,rest,og1,line,0);
                        horizontalcut(S,rest,og1,line,0);
                        free(S);
                        freeMatrix(rest);
                        freeMatrix(og1);
                    //matToImg(og1,"MARCHE\n");
                }
                return;
            }
            //si ligne blanche on passe à l'autre
            y++;
        }
}


//__________________CUTTING VERTICAL BLANKS______________________________

void verticalcut(Tree *T,Matrix M,Matrix og, int line, int cutted)
{
    /*
    description :

    -cuts first vertical block founded
    -treats the block founed
    -the rest of the block is treated vertically

    parameters :

    Tree *T : the pointer to the tree that is building
    Matric M : the matrix of the picture
    int horizontal : 2 if horizonral cuts can go further
    int vertical : 2 if vertical cuts can no go further
    int line : boolean teeling us if we are cutting a line or a word

    dates/authors :
    24/10
    marine thunet

    */
    
    if (M.width<=0 || M.height<=0)
    {
        return ;
    }
    matToImg(og,"verticalempty");
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
    

    
    while(x<width)
        {
            y=0;
            while(y<lenght && M.matrix[y*width+x]==0)
            {
                y++;
            }
            
            if (x==width-1 && xbeg==0 && started==1)
            {
                if (cutted>=1)
                {
                    /*printf("test2\n");
                matToImg(og,"testA");*/
                Tree *Child = newTree(-3);
                AddChild(T, Child);
                Matrix s = rlsa(og,250,40);
                Matrix m = rlsa(s,400,200);
                matToImg(m,"testA000");
                horizontalcut(Child,m,og,1,0);
                free(Child);
                freeMatrix(s);
                freeMatrix(m);
                }
                else
                {
                    horizontalcut(T,M,og,line,1);
                }
                return;
            }
            
            else if( started==0 && y<lenght && M.matrix[y*width+x]==1)
            {
                xbeg=x;
                y=0;
                started=1;
            }
            else if (y<lenght && M.matrix[y*width+x]==1)
            {
                y=0;
            }
            
            else if (y==lenght && started==1)
            {
                tocut=cutMatrix(M,0,xbeg,lenght,x-xbeg);
                og2=cutMatrix(og,0,xbeg,lenght,x-xbeg);
                matToImg(og2,"testA012");
                horizontalcut(T,tocut,og2,line,0);
                freeMatrix(tocut);
                freeMatrix(og2);
                
                if (x<width)
                {
                    rest=cutMatrix(M,0,x,lenght,width-x);
                    og1=cutMatrix(og,0,x,lenght,width-x);
                    //new paragraph, new sibling
                    Tree *Sibling = newTree(-3);
                    AddSibling(T,Sibling);
                    verticalcut(Sibling,rest,og1,line,0);
                    
                    free(Sibling);
                    freeMatrix(rest);
                    freeMatrix(og1);
                }

                return;
            }
            x++;
            
        }
    
}


//________________begining_________________________//


Tree *beginSeg(Matrix M)
{
    /*
    description :

    -fonction to help begin the others
    -starting the segmentation

    parameters :

    Matric M: the matrix of the picture

    dates/authors :
    24/10
    marine thunet

    */
    //printf("begin");
    Tree *txt = newTree(-3);
    Matrix p = rlsa(M,250,1200);
    Matrix q = rlsa(p,400,1300);
    horizontalcut(txt,q,M,0,0);
    freeMatrix(p);
    freeMatrix(q);
    
    return txt;

}
