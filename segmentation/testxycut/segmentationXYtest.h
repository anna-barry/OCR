#ifndef SEGMENTATIONXYTEST_H
#define SEGMENTATIONXYTEST_H

#include "../../Tools/matrix.h"
#include "../../Tools/tree.h"
#include "../../pré-traitement/binarisation/binarisation.h"

char* mycat(char *s1, char *s2);

char* char2string(char c);

void textBuider(int code, char *text);

void beginSeg(Matrix M,char *txt); 

void segmentation(Matrix M);

Matrix vertical(Matrix M);

void _trycut(Matrix M, int line, Tree *T);

void horizontalcut(Tree *T,Matrix M,Matrix og,int horizontal,int vertical,int line);

void verticalcut(Tree T,Matrix M,Matrix og,int horizontal,int vertical, int line);

#endif
