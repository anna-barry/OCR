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
      Tree *child = tree->child;
      while (child!=NULL) {
        text = mycat("",textBuider(child, text));
        child = child->sibling;
      }
    }
    if (tree->key==-3||tree->key==-2){//paragra or line "\n"
      Tree *child = tree->child;
      while (child!=NULL) {
        text = mycat("",textBuider(child, text));
        child = child->sibling;
      }
      text = mycat(text,"\n");
    }
    if (tree->key==-1){//word " "
      Tree *child = tree->child;
      while (child!=NULL) {
        text = mycat("",textBuider(child, text));
        child = child->sibling;
      }
      text = mycat(text," ");
    }
    if (tree->key>0&&tree->key<127){//char ascii number
      text = mycat(text,char2string((char)tree->key));
    }
    else {//in case the value in the tree key is corupt
      text = mycat(text,"/!\\");
    }
  }
  return text;
}
