#include <stdlib.h>
#include <stdio.h>
#include "minifunc.h"

double myabs(double x){
  x = x < 0 ? -x : x;
  return x;
}

double myintpart(double x){

  double i = 0;

  while (!(i <= x && i+1>=x)){

    i += 1 ;
  }

  return i;
}
