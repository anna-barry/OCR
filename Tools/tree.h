#ifndef TREE_H
#define TREE_H

typedef struct Tree
{
    int key;
    struct Tree *child;
    struct Tree *sibling;

} Tree;

Tree *newTree(int key);
void AddSibling(Tree *T, Tree *Sibling);
void AddChild(Tree *T, Tree *Child);
void print_tree(Tree *T);
void freeTree(Tree *T);

#endif
