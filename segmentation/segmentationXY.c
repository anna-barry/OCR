//_____________________XY-cut_________________________________//


//_____________________include________________________________//
#include "../Tools/matrix.h"
#include "../Tools/tree.h"
#include "rlsa.h"
#include <stdio.h>
#include <stdlib.h>

//________________debut_des_fonctions_________________________//
//redimensionner matrice


//parcours de ligne ou de mots et pour decoupage vertical//
Matric vertical(Matrix M)
{
    //Dectecter les zones d'espaces
    //principe:
    //si un pixel noir est present: ce n'est pas une séparation donc
    //la colonne devient noir
    
    for (int x=0; x<w_size ;x++)
    {
        y=0;
        while (y<h_size && M.matrix[y*w_size + x]=!1)
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


tree _trycut(Matrix M, bool line, Tree *T)
{
    //copie de la matrice pour recupérer la matrice d'origine quand necessaire
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
    int x=0;        //valeur du départ coordoné départ du mot/ de la lettre
    
    //booléens pour se repérer dans les fonctions
    int begin=0; //1 si le mot est en cours de traitement
    int end=0;   //1 si on est au dernier pixel de la ligne
    
    Matrix createseg;
    
    //_______DECOUPAGE LIGNE______________________________________________
    if (line)
    {
        int nbspace=-1;  //compte le nombre de suite de pixels blancs
                        //commence a -1 car compte automatiquement au premier pixel
        
        int totalspace=0;
        //compte le nombre des pixel blancs par zone de séparation
        
        /*_______Detecter des espaces & moyenne des espaces_____________*/
        for (int c; c<w_size; c++)
        {
            
            if (M.matrix[j] == 0)
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
        //moyenne des espaces entre les mots/caractères
        
        //on reinitialise les variables
        totalspace=0;
        previous=0;
        
        for (int ix=0; ix<w_size; ix++)
        {
            if (ix+1=w_size)
            {
                end=1;
            }
            
            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //premiere condition validée mais mots pas démarré
                {
                    begin=1; //le mot demarre
                    x=xi; //on note: image commence a xi
                }
                else
                {
                    
                    if (totalspace>average || end == 1 )
                    {
                        //petite matrice du mot repéré
                        createseg=cutMatrix(reel,x,ix-totalspace,h_size);
                        
                        Tree *Child = newTree(-1);
                        AddChild(T, Child);
                        _trycut(createseg,false,Child);
                        
                        free_Matrix(createseg);
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
        int letter=0;//la valeur de la lettre en ascii
        for (int ix=0; ix<w_size; ix++)
        {
            
            if (ix+1=w_size)
            {
                end=1;
            }
            
            if (M.matrix[w_size]==1 || end==1)
            {
                if (begin == 0 && end == 0) //premiere condition validée donc la lettre demarre
                {
                    begin=1;
                    x=xi; //on dit que le mot commence au coordonées xi
                    //xlen=1;
                }
                else
                {
                //xlen+= totalspace;
                
                    if ( begin==1 && end == 1 )
                    {
                        
                        //petite matrice du caractère repéré
                        createseg=cutMatrix(reel,x,ix-totalspace,h_size);
                        
                        //TO DO
                        //createseg=redimensionner(createseg)
                        
                        //pour____SOUTENANCES______2
                        //mettre fonction qui converti l'image en caractère
                        //letter=convert(createseg);
    
                        //pour le moment on fait ca mais inutile,
                        //il faudra renvoyer le code ascii de chaque caractère
                        letter=0;
                    
                        Tree *Child = newTree(0);
                        AddChild(T, letter)
                    
                        free_Matrix(createseg);
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
    
    free_Matrix(reel);
        
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
}

//fonction qui lie le RLSA au XY-Cut

    //créer la matrice
*/
