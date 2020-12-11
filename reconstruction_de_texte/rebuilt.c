#include "rebuilt.h"

char* mycat(char *s1, char *s2){
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

char* char2string(char c){
  char *str=malloc(2*sizeof(char));
  if(str==NULL)
    return NULL;
  str[0]=c;
  str[1]='\0';
  return str;
}

char *textBuider(Tree *tree, char *text){
  /*
  description :
  CREATE A STRING THAT CONTAIN THE TEXT

  parameters :
  Tree tree : the tree that we want to print with classic dfs.
  char *text the string that will contain the text.

  dates/authors :
  04/12
  geoffroy du mesnil du buisson

  */
  if (tree->key){
    printf("1\n");
    if (tree->key==-4){//racine
      printf("roof\n");
      Tree *child = tree->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        //mycat("",textBuider(child, text));
        child = child->sibling;
      }
      printf("racine\n");
    }
    if (tree->key==-3||tree->key==-2){//paragra or line "\n"
    printf("para\n");
      Tree *child = tree->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        //mycat("",textBuider(child, text));
        child = child->sibling;
      }
       printf("paragraph ou ligne\n");
      //text = mycat(text,"\n");
    }
    if (tree->key==-1){//word " "
    printf("word\n");
      Tree *child = tree->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        //mycat("",textBuider(child, text));
        child = child->sibling;
      }
      printf("mots\n");
      //text = mycat(text," ");
    }
    if (tree->key>0&&tree->key<127){//char ascii number
      printf("lettre\n");
      //text = mycat(text,char2string((char)tree->key));
    }
    else {
      printf("Mauvaise valeur dans la clef de l'arbre\n");
    }
  }
  else {
    printf("il n'y a pas de clef\n");
  }
  return text;
}
