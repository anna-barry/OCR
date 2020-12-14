#include "rebuilt.h"

char* mycat(char *s1, char *s2){
  /*
  description :
  CONCATAIN TWO STRINGS WITH ALOCATION MEMORY

  parameters :
  char *s1 : the original string
  char *s2 : the string that will be concatain to the string *s1.

  dates/authors :
  04/12
  geoffroy du mesnil du buisson

  */
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

char* char2string(char c){
  /*
  description :
  PARSE A CHAR INTO A STING

  parameters :
  char c : the char will be transform into a string

  dates/authors :
  04/12
  geoffroy du mesnil du buisson

  */
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
    //printf("1\n");
    if (tree->key==-4){//racine
      if (tree->child) {
        Tree *child = tree->child;
        while (child->key) {
          text = mycat("",textBuider(child, text));
          if (child->sibling) {
            child = child->sibling;
          }
        }
      }
    }
    if (tree->key==-3||tree->key==-2){//paragra or line "\n"
      if (tree->child) {
        Tree *child = tree->child;
        while (child->key) {
          text = mycat("",textBuider(child, text));
          if (child->sibling) {
            child = child->sibling;
          }
        }
      }
      text = mycat(text,"\n");
    }
    if (tree->key==-1){//word " "
      if (tree->child) {
        Tree *child = tree->child;
        while (child->key) {
          text = mycat("",textBuider(child, text));
          if (child->sibling) {
            child = child->sibling;
          }
        }
      }
      text = mycat(text," ");
    }
    if (tree->key>0&&tree->key<=127){//char ascii number
      text = mycat(text,char2string((char)tree->key));
    }
    else {//in case the value in the tree key is corupt
      text = mycat(text,"/!\\");
    }
  }
  return text;
}
