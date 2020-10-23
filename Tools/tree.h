#ifndef TREE_H
#define TREE_H

Tree *newTree(int key);
void AddSibling(Tree *T, Tree *Sibling);
void AddChild(Tree *T, Tree *Child);

#endif
