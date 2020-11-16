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
    T->sibling=NULL;
    T->child=NULL;

    return T;
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
    while(T->sibling)
    {
        T=T->sibling;
    }
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
    if (T->child)
    {
        AddSibling(T->child,Child);
    }
    else
    {
        T->child=Child;
    }
}

void print_tree (Tree *T){
  /*
  description :
  print a tree

  parameters :
  Tree T : the tree that we want to print

  dates/authors :
  16/11
  geoffroy du mesnil du buisson

  */
  if (T){
    printf("%s\n", T->key);
    Tree child = T->child;
    while (child!=NULL) {
      print_tree(child);
      child = T->child;
    }
  }
  else{
    printf("the tree is empty")
  }
}


void freeTree (Tree *T){
  /*
  description :
  unallocate the memory that have been allocate for a Tree

  parameters :
  Tree T : the tree that we want to supress because we
  dont need it anymore

  dates/authors :
  16/11
  geoffroy du mesnil du buisson

  */

  free(*T);
  T->key=NULL;
  T->sibling=NULL;
  T->child=NULL;

}
