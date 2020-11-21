#include <stdlib.h>
#include <stdio.h>
#include "minifunc.h"

double myabs(double x){
  /*
  description :
  return the absolute value of a double

  parameters :
  double x : the value we want to be positive

  dates/authors :
  23/10
  geoffroy du mesnil du buisson

  */
  x = x < 0 ? -x : x;
  return x;
}

double myintpart(double x){

  /*
  description :
  return the integer part of a double but still a double

  parameters :
  double x : the value we want the integer part of

  dates/authors :
  23/10
  geoffroy du mesnil du buisson

  */

  double i = 0;

  while (!(i <= x && i+1>=x)){

    i += 1 ;
  }

  return i;
}
