#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

Tree *newTree(int Key)
{

/*
description :

initialization of a new tree

parameters :

int Key : the key of the tree

dates/authors :
15/10
marine thunet

*/
    
    Tree *T = malloc(sizeof(Tree));
    T->key=Key;
    T->sibling=malloc(sizeof(Tree)); //previous was NULL
    T->child=malloc(sizeof(Tree));

    return T;
}

void freeTree(Tree *T){

  /*description :
  unallocate the memory that have been allocate for a tree

  parameters :
  Tree T : the matrix that we want to supress because we
  dont need it anymore

  dates/authors :
  10/12
  marine thunet*/
  
    if (!T)
    {
        return;
    }
    free(T);
    T=NULL;
}

void AddSibling(Tree *T, Tree *Sibling)
{

/*
description :

adding a new right brother

parameters :

int *T: pointer of the Tree T
Tree *Sibling: pointer of the Sibling to add

dates/authors :
15/10
marine thunet

*/
    T->sibling= malloc(sizeof(Tree));
    T->sibling = Sibling;
}

void AddChild(Tree *T, Tree *Child)
{
/*
description :

adding a new child to the tree

parameters :

int *T: pointer of the Tree T
Tree *Sibling: pointer of the Child to add

dates/authors :
15/10
marine thunet

    */
    if (!(T->child))
    {
        T->child= malloc (sizeof(Tree));
        T->child= Child;
    }
    else
    {
        AddSibling(T->child,Child);
    }
}
