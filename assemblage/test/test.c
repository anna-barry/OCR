#include <stdio.h>
#include "../assemblage.h"

int main()
{
  char text[25] = "coucou bande de nouilles " ; 
  
  textToFile(text, "new"); 

  return 0; 
}
