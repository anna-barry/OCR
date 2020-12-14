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
    // if (!(T->child))
    // {
        T->child= malloc (sizeof(Tree));
        T->child= Child;
    // }
    // else
    // {
    //     AddSibling(T->child,Child);
    // }
}

void dfs_printer(Tree *tree)
{
  /*
   * General description:
    Function that takes a tree in parameter and print the tree in the Terminal

    Parameters:
    - Tree *tree: pointer of the tree to print

    dates/authors :
    12/12
    geoffroy du mesnil du buisson

  */
  //printf("on rentre\n");
    if (tree->key)
    {
        printf("tree key = %i\n", tree->key);
        Tree *thesibling = tree->sibling;
        printf("the sibling of %i is %i\n", tree->key, thesibling->key);
        if (tree->child){
          Tree *child = tree->child;
          printf("the child of %i is %i\n", tree->key, child->key);
          while (child->key)
          {
              dfs_printer(child);
              Tree *curentNode = child;
              if(child->sibling)
              {
                child = child->sibling;
                //printf("marine?\n");
                printf("the sibling of %i is %i\n", curentNode->key, child->key);
                //printf("geoffroy?\n");
              }
          }
          //printf("ok?\n");
        }
    }
    else{
      printf("pas de sibling\n");
    }
}

void rec_createAtree(Tree *tree, int arr[], int i, int size)
{
  /*
   * General description:
    Function that takes an array and recurcively create a tree

    Parameters:
    - Tree *tree: pointer of the tree to create
    - int arr[]: the array that contain every value of the tree
    - int i: the index in the list
    - int size : the size of the list


    dates/authors :
    12/12
    geoffroy du mesnil du buisson

  */
    Tree *theChild = newTree(arr[i]);
    while (i<size) {
    AddChild(tree, theChild);
    i++;
    rec_createAtree(theChild, arr, i, size);
  }
}

Tree *createAtree(int arr[], int size){
  /*
   * General description:
    Function that takes an array and recurcively create a tree 

    Parameters:
    - int arr[]: the array that contain every value of the tree
    - int size : the size of the list

    dates/authors :
    12/12
    geoffroy du mesnil du buisson

  */
  Tree *theTree = newTree(-4);
  rec_createAtree(theTree,arr,0, size);
  return theTree;
}
