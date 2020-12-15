//_____________________XY-cut_________________________________//

//_____________________include________________________________//
#include "../../Tools/matrix.h"
#include "../../Tools/tree.h"
#include "../../pré-traitement/binarisation/binarisation.h"
#include "../rlsa.h"
#include "../resizeMatrix.h"
#include "../../réseau_de_neurones/CNN/RecogniseASCII.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../réseau_de_neurones/CNN/LeNet.h"
#include <math.h>

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
void textToFile(char text[], char *str, int i)
{
    /*
     Authors: Marie Maturana and Marine Thunet
     text: the text to add
     str: the title of the file were to add the text
     i: represent a bool 1 if it is the begining of the file*/
  FILE* fichier = NULL;
  fichier = fopen(str, "a");

    if (fichier == NULL || i==1)
    {
        fclose(fichier);
        fichier = fopen(str, "w");
        fputs(text, fichier);
    }
    else
    {
        fputs(text,fichier);
    }
    fclose(fichier);
}

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
    return M;
}

void _trycut(Matrix M, int line, char *name)
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
        return ;
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
            if (c+1==w_size)
            {
                totalspace=totalspace-trans;
                trans=0;
            }
            if (M.matrix[c] == 0 && begin==1)
            {
                totalspace++;
                trans++;
            }
            else
            {
                if (M.matrix[c]==1 && begin==0)
                {
                    begin=1;
                }
                if (begin==1)
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
            }
            previous=M.matrix[c];
        }
        
        begin=0;
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
                    if (begin == 1 && (totalspace>average || end == 1 ))
                    {

                        //matrix of the word that was found
                        createseg=cutMatrix(reel,0,x,h_size,ix-x);
                        
                        textToFile(" ",name,0);
                        matToImg(createseg,"last_word");

                        //Tree *Child = newTree(0);
                        //AddChild(T, Child);
                        _trycut(createseg,0,name);
                        
                        
                        freeMatrix(createseg);
                        x=0;
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
        //int a;
        M=vertical(M);
                //int letter=0;//the code og the letter to put in the tree then
        for (int ix=0; ix<w_size; ix++)
        {
            if (ix+1==w_size || (M.matrix[ix]==0 && begin==1))
            {
                end=1;
            }
            
            if (M.matrix[ix]==1 || end==1)
            {
                if (begin == 0 && end == 0) //the letter starts
                {
                    begin=1;
                    x=ix; //the letter starts at the xy: x=xi
                }
                else
                {
                //xlen+= totalspace;
                    if ( begin==1 && end == 1 )
                    {
                        //creating a matrix for the caracter that was found
                        createseg=cutMatrix(reel,0,x,h_size,ix-x+1);
                        createseg=resizeMatrix(createseg,32);
                        
                        //a=getASCII(createseg);
                        /*switch(a)
                           {
                               case 48: textToFile("0",name,0);break;
                               case 49 : textToFile("1",name,0); break;
                               case 50 : textToFile("2",name,0); break;
                               case 51: textToFile("3",name,0);break;
                               case 52 : textToFile("4",name,0); break;
                               case 53 : textToFile("5",name,0); break;
                               case 54: textToFile("6",name,0);break;
                               case 55 : textToFile("7",name,0); break;
                               case 56 : textToFile("8",name,0); break;
                               case 57 :textToFile("9",name,0);break;
                                   
                               case 65: textToFile("A",name,0);break;
                               case 66 : textToFile("B",name,0); break;
                               case 67 : textToFile("C",name,0); break;
                               case 68: textToFile("D",name,0);break;
                               case 69 : textToFile("E",name,0); break;
                               case 70 : textToFile("F",name,0); break;
                               case 71: textToFile("G",name,0);break;
                               case 72 : textToFile("H",name,0); break;
                               case 73 : textToFile("I",name,0); break;
                               case 74 :textToFile("J",name,0);break;
                               case 75 :textToFile("K",name,0);break;
                               case 76 :textToFile("L",name,0);break;
                               case 77: textToFile("M",name,0);break;
                               case 78 : textToFile("N",name,0); break;
                               case 79 : textToFile("O",name,0); break;
                               case 80: textToFile("P",name,0);break;
                               case 81 : textToFile("Q",name,0); break;
                               case 82 : textToFile("R",name,0); break;
                               case 83: textToFile("S",name,0);break;
                               case 84 : textToFile("T",name,0); break;
                               case 85 : textToFile("U",name,0); break;
                               case 86 :textToFile("V",name,0);break;
                               case 87: textToFile("W",name,0);break;
                               case 88 : textToFile("X",name,0); break;
                               case 89 : textToFile("Y",name,0); break;
                               case 90: textToFile("Z",name,0);break;
                                   
                               case 97 : textToFile("a",name,0); break;
                               case 98 : textToFile("b",name,0); break;
                               case 99: textToFile("c",name,0);break;
                               case 100 : textToFile("d",name,0); break;
                               case 101 : textToFile("e",name,0); break;
                               case 102 :textToFile("f",name,0);break;
                               case 103: textToFile("g",name,0);break;
                               case 104 : textToFile("h",name,0); break;
                               case 105: textToFile("i",name,0); break;
                               case 106: textToFile("j",name,0);break;
                               case 107: textToFile("k",name,0); break;
                               case 108: textToFile("l",name,0); break;
                               case 109: textToFile("m",name,0);break;
                               case 110: textToFile("n",name,0); break;
                               case 111: textToFile("o",name,0); break;
                               case 112:textToFile("p",name,0);break;
                               case 113: textToFile("q",name,0);break;
                               case 114: textToFile("r",name,0); break;
                               case 115: textToFile("s",name,0); break;
                               case 116: textToFile("t",name,0);break;
                               case 117: textToFile("u",name,0); break;
                               case 118: textToFile("v",name,0); break;
                               case 119: textToFile("w",name,0);break;
                               case 120: textToFile("x",name,0); break;
                               case 121: textToFile("y",name,0); break;
                               case 122:textToFile("z",name,0);break;
                               default :textToFile("?",name,0);break;
                           }*/
                        //char *c= (char*)a;
                        //char new= [char]a;
                        //textToFile(c,name);
                        
                        
                        //for the test, nerual netork not added to see how fast goes the segmentation
                        textToFile("a",name,0);
                        matToImg(createseg,"last_letter");
                        x=ix;
                        freeMatrix(createseg);
                        begin=0;
                        end=0;
                    }
                }
            }
        
        }
    }
    
    freeMatrix(reel);
    return;
}


//__________________CUTTING HORIZONTAL BLANKS______________________________
void verticalcut(char *name,Matrix M,Matrix og, int line, int cutted);

void horizontalcut(char *name,Matrix M,Matrix og,int line, int cutted)
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
                    matToImg(og,"last_line");
                    textToFile("\n",name,0);
                    
                    _trycut(og,1,name);
                }
                else
                {
                    if (cutted>=2)
                    {
                        
                        //Tree *Child = newTree(-2);
                        //AddChild(T, Child);
                        Matrix s = rlsa(og,250,40);
                        Matrix m = rlsa(s,400,200);
                        horizontalcut(name,m,og,1,0);
                        freeMatrix(m);
                        freeMatrix(s);
                    }
                
                    else
                    {
                        verticalcut(name,M,og,0,1);
                    }
                }
                return;
                
            }
            //si on n'a pas deja commencé, mais que l'on trouve un pixel noir
            else if (started==0 && x<width && M.matrix[y*width+x]==1)
            {
                ybeg=y;
                x=0;
                started=1;
            }
            //si on a deja comméncé et qu'on trouve un pixel noir
            else if (x<width && M.matrix[y*width+x]==1)
            {
                x=0;
            }
            //si on a parcouru une ligne blanche sans pixel noir et que l'on avait avant
            else if ((x==width || y==lenght-1) && started==1 && y>0)
            {
                //ensuite on va traiter le paragraphe deja découpé
                //si on etait a l'étape de découpe de paragraphes
                if (line==0)
                {
                    tocut=cutMatrix(M,ybeg,0,y-ybeg,width);
                    og2=cutMatrix(og,ybeg,0,y-ybeg,width);
                    
                    verticalcut(name,tocut,og2,0,0);
                    
                    freeMatrix(tocut);
                    freeMatrix(og2);
                }
                //si on etait à l'étape de decoupe des lignes
                if (line==1)
                {
                    og2=cutMatrix(og,ybeg,0,y-ybeg,width);
                    matToImg(og2,"last_line");
                    textToFile("\n",name,0);
                    
                    _trycut(og2,1,name);
                    
                    freeMatrix(og2);
                }
                
                //si pas a la fin de la matrice, on continue horizontale pour le reste
                if (y!=lenght)
                {
                        rest=cutMatrix(M,y,0,lenght-y,width);
                        og1=cutMatrix(og,y,0,lenght-y,width);
                    
                    horizontalcut(name,rest,og1,line,0);
                     //freingspace
                    freeMatrix(rest);
                    freeMatrix(og1);
                }
                return ;
            }
            //if white ligne, goes to new one
            y++;
        }
    return;
}


//__________________CUTTING VERTICAL BLANKS______________________________

void verticalcut(char *name,Matrix M,Matrix og, int line, int cutted)
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
                Matrix s = rlsa(og,250,40);
                Matrix m = rlsa(s,400,200);
                matToImg(og,"last_paragraph");
                    
                horizontalcut(name,m,og,1,0);
                    
                textToFile("\n\n",name,0);
                freeMatrix(s);
                freeMatrix(m);
                }
                else
                {
                    horizontalcut(name,M,og,line,1);
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
                horizontalcut(name,tocut,og2,line,0);
                freeMatrix(tocut);
                freeMatrix(og2);
                
                if (x<width)
                {
                    rest=cutMatrix(M,0,x,lenght,width-x);
                    og1=cutMatrix(og,0,x,lenght,width-x);
                    verticalcut(name,rest,og1,line,0);
                    textToFile("\n\n",name,0);
                    freeMatrix(rest);
                    freeMatrix(og1);
                }

                return;
            }
            x++;
            
        }
    return;
}


//________________begining_________________________//
void beginSeg(Matrix M)
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
    
    char *txt = "textOCR";
    textToFile("",txt,1);
    Matrix p = rlsa(M,250,1200);
    Matrix q = rlsa(p,400,1300);
    horizontalcut(txt,q,M,0,0);
    
    freeMatrix(p);
    freeMatrix(q);

}
