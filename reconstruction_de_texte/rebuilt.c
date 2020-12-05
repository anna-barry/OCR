#include "rebuiult.h"


char *textBuider(Tree tree, char *text){
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
    if (tree->key==-4){//racine
      Tree child = T->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        child = T->child;
      }
    }
    if (tree->key==-3||tree->key==-2){//paragra or line \n
      text = strcat(text, "\n");
      Tree child = T->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        child = T->child;
      }
    }
    if (tree->key==-1){//word " "
      text = strcat(text, " ");
      Tree child = T->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        child = T->child;
      }
    }
    if (tree->key>0&&tree->key<127){//char ascii number
      text = strcat(text, str(tree->key));
      Tree child = T->child;
      while (child!=NULL) {
        text = textBuider(child, text);
        child = T->child;
      }
    }
  }
  free(tree);
  return text;
}
