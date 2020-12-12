#ifndef TREE_H
#define TREE_H

typedef struct Tree
{
    int key;
    struct Tree *child;
    struct Tree *sibling;

} Tree;

Tree *newTree(int key);
void freeTree(Tree *T);
void AddSibling(Tree *T, Tree *Sibling);
void AddChild(Tree *T, Tree *Child);
void dfs_printer(Tree *tree);
Tree *createAtree(int arr[], int size);

#endif
