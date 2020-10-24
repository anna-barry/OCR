#ifndef TREE_H
#define TREE_H

typedef struct Tree
{
    int key;
    struct Tree *Child;
    struct Tree *Sibling;
    
} Tree;

Tree *newTree(int key);
void AddSibling(Tree *T, Tree *Sibling);
void AddChild(Tree *T, Tree *Child);

#endif
