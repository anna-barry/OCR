//_____________________XY-cut_________________________________//


//_____________________include________________________________//
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "rlsa.h"
#include "resizeMatrix.h"
#include <stdio.h>
#include <stdlib.h>

//________________begining_________________________//


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


Tree _trycut(Matrix M, int line, Tree *T)
{
    //copying the og matrix
    Matrix reel = copyMatrix(M);

    int y = 0;
    int h_size = M.height;
    int w_size = M.width;
    
    
    //___________________________TO DO_____________________________________//
    //il faudrait aussi affiner les lignes au maximum: parcours horizontal//
    //améliorer la technique: histogrammes si restes de taches, grains...//
    
    //on a soit des lignes soit des mots, donc parcours vertical
    //on part du principe qu'il n'y a plus de taches ou de grain
    
    M=vertical(M);
    
    //matrice de blocs noirs obtenus
    //il faut choisir si l'on souhaite decouper des mots ou des lignes
    //le decoupage n'est pas le même
    
/*_____________INITIALISATION VARIABLES COMMUNES________________*/
    
    int previous=0; //valeur du pixel precedent
    
    int x=0;
    //valeur du départ coordoné départ du mot/ de la lettre
    
    //booléens pour se repérer dans les fonctions
    int begin=0; //1 si le mot est en cours de traitement
    int end=0;   //1 si on est au dernier pixel de la ligne
    
    Matrix createseg;
    
    int totalspace=0;//number of white pixel/separation
    
    //_______LINEAR CUT______________________________________________
    if (line==1)
    {
        int nbspace=-1;  //compte le nombre de suite de pixels blancs
                        //commence a -1 car compte automatiquement au premier pixel
        
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
    //____________________DECOUPAGES_MOTS____________________________________
    
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
                //le nmb d'espace augmente
                totalspace++;
            }
        }
    }
    
    freeMatrix(reel);
        
}

      //fonction qui trace des lignes verticales
     //detecte les espaces des séparation de caractères/moyenne
    //des espaces

    //fonction qui forme des mots
        //fonction qui ajoute dans un arbre a bon endroit et qui appelle une nouvelle fonction

    //fonction qui forme des caractères
        //redimensionne l'image
        //ajoute chaque caractère en bout d'arbre.//appel de réseau de neuronnes

    //fonction qui créé

/*Tree segmentation(Matrix M)
{
    int widht= M.width;
    int lenght= M.length;
    Matrix og= copyMatrix(M);
    Tree T= newTree(-3);
    //ibtiti
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
    
    //découper la matrice en plusieurs sous matrices
    //placer plusieurs matrices en racine de l'abre
    //rapeller la fonction en enfant de l'arbre pour ajouter les paragraphes, lignes....
}*/

//fonction qui lie le RLSA au XY-Cut

Tree horizontalcut(Tree T,Matrix M,Matrix og,int horizontal,int vertical,int line)
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
    
    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }

    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og),og,1,1,1);
    }

    
    while(y<lenght)
        {
            x=0;
            while(x<width && M.matrix[y*lenght+x]==0)
            {
                x++;
            }
            if (x==width && started==1)
            {
                tocut=cutMatrix(M,xbeg,0,x-xbeg,width);
                og2==cutMatrix(og,xbeg,0,x-xbeg,width);
                if (y=!lenght)
                {
                    rest=cutMatrix(M,x,0,w_size-x,width);
                    og1=cutMatrix(og,x,0,w_size-x,width);
                    horizontal(T,rest,og1,1,vertical);
                }
                vertical(T,tocut,og2,2,vertical);
                y=lenght;
            }
            else if( started==0 && x<width && M.matrix[y*lenght+x]==1)
            {
                xbeg=x;
                x=0
                started=1;
            }
            else if (x<width && M.matrix[y*lenght+x]==1)
            {
                x=0;
            }
            y++;
        }
}

Tree verticalcut(Tree T,Matrix M,Matrix og,int horizontal,int vertical, int line)
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
    
    if (horizontal==2 && vertical==2 && line=1)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        _trycut(og,1,Child);
    }
    if (horizontal==2 && vertical==2)
    {
        Tree *Child = newTree(-3);
        AddChild(T, Child);
        horizontalcut(Child,rlsa(og),og,1,1,1);
    }

    
    while(x<width)
        {
            y=0;
            while(y<lenght && M.matrix[y*lenght+x]==0)
            {
                y++;
            }
            if (y==lenght && started==1)
            {
                tocut=cutMatrix(M,0,ybeg,width,y-ybeg);
                og2=cutMatrix(og,0,ybeg,width,y-ybeg);
                if (x=!width)
                {
                    rest=cutMatrix(M,0,y,width,height-y);
                    og1=cutMatrix(og,0,y,width,height-y);
                    horizontal(T,rest,horizontal,vertical);
                }
                vertical(T,tocut,horizontal,2);
                x=width
            }
            else if( started==0 && y<length && M.matrix[y*lenght+x]==1)
            {
                ybeg=y;
                y=0
                started=1;
            }
            else if (y<length && M.matrix[y*lenght+x]==1)
            {
                y=0;
            }
            x++;
            
        }
    
    return T;
}

    //créer la matrice
Tree segmentation(Matrix M)
{
    int widht= M.width;
    int lenght= M.length;
    int horizontal=1;
    Matrix og= copyMatrix(M);
    Tree T= newTree(-3);
    //ibtiti
    M = rsla(M,5,2);
    int y=0;
    int x=0;
    
    int xbeg=0;
    
    T=horizontalcut(T,M,og,1,1);
    
    }
    
}
