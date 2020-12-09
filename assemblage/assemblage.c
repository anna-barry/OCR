#include <stdlib.h>
#include <stdio.h>

void textToFile(char text[], char *str)
{
  FILE* fichier = NULL;
  fichier = fopen(str, "w");

  if (fichier != NULL)
    {
        fputs(text, fichier);
        fclose(fichier);
    }
}
