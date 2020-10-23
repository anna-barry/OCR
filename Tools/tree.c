#include "tree.h"
#include <stdio.h>
#include <stdlib.h>stdio

Tree *newTree(int Key)
{
    Tree *T = malloc(sizeof(Tree));
    T->key=Key;
    T->sibling=NULL;
    T->child=NULL;
    
    return T;
}

void AddSibling(Tree *T, Tree *Sibling)
{
    while(T->sibling)
    {
        T=T->sibling;
    }
}

void AddChild(Tree *T, Tree *Child)
{
    if (T->child)
    {
        AddSibling(T->child,Child);
    }
    else
    {
        T->child=Child;
    }
}
