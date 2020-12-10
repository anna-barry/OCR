#include "rebuilt.h"

// char *mycat(char *str1, char *str2){
//   size_t size1 = strlen(str1);
//   size_t size = size1 + strlen(str2) + 1;
//
//   char *str = realloc(str1, size * sizeof(char));
//   if (str == NULL) {
//     errx(1, "Not enough memory!");
//
//   char *p = str + size1;
//   while (*str2 != 0)
//     *(p++) = *(str2++);
//
//   *p = 0;
//
//   return str;
// }

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
  char *temp;
  if (tree->key){
    //printf("0,5\n");
    if (tree->key==-4){//racine
      printf("racine\n");
      Tree *child = tree->child;
      while (child!=NULL) {
        // text = textBuider(child, text);
        // child = child->sibling;
        char *temp = textBuider(child, text);
        char *newtext = malloc(strlen (text) + strlen(temp)+1);
        strcpy(newtext, text);
        strcat(newtext, temp);
        text = malloc(strlen (newtext));
        text = newtext;
        child = child->sibling;

      }
    }
    if (tree->key==-3||tree->key==-2){//paragra or line \n
      printf("paragraph ou ligne\n");
      char *temp = malloc(strlen(text)+2);
      strcpy(temp,text);
      strcat(temp,"\n"); //gros problemes need to be resolved.
      Tree *child = tree->child;
      while (child!=NULL) {
        char *text = textBuider(child, temp);
        char *newtext = malloc(strlen (temp) + strlen(text)+1);
        strcpy(newtext, temp);
        strcat(newtext, text);
        temp = malloc(strlen (newtext));
        temp = newtext;
        child = child->sibling;
      }
    }
    if (tree->key==-1){//word " "
      printf("mots\n");
      temp = malloc(strlen(text)+1);
      strcpy(temp,text);
      strcat(temp," ");
      Tree *child = tree->child;
      while (child!=NULL) {
        text = textBuider(child, temp);
        child = child->sibling;
      }
    }
    if (tree->key>0&&tree->key<127){//char ascii number
      printf("lettre\n");
      //text = strcat(text, "a"/*str(tree.key)*/);
      // Tree child = *tree.child;
      // while (child.key) {
      //   printf("good question bro !\n");
      //   text = textBuider(child, text);
      //   child = *child.sibling;
      // }
    }
  }
  //printf("c la que ca coice\n");
  return text;
}

// int mystrlen(char *str)
// {
//     int n = 0;
// 	while (str[n] != '\0') n++;
// 	return n;
// }
//
// char *mystrcat(char *str, char elm)
// {
//     int n = mystrlen(str)+2;
// 	char *concat = malloc(n * sizeof(char));
//     for (int i = 0 ; i < n-2 ; i++) concat[i] = str[i];
// 	concat[n-2] = elm;
// 	concat[n-1] = '\0';
//     return concat;
// }
//
//
// char *write(Tree *T, char *text)	// Go through the tree to write the text
// {
// 	if (T->key >= 0)	// T.key >= 0 mean that the node T represent a char (T.key is an ascii)
// 	{
// 		text = mystrcat(text, T->key);
// 	}
//
// 	else if (T->key == -1)	// T.key == -1 mean that the node T represent a word
// 	{
// 		Tree *tree = T->child;
//
// 		if (tree != NULL)
// 		{
// 			text = write(tree, text);
//
// 			while (tree->sibling != NULL)
// 			{
// 				tree = tree->sibling;
// 				text = write(tree, text);
// 			}
//
// 			text = mystrcat(text, ' ');
// 		}
// 	}
//
// 	else if (T->key == -2)	// T.key == -2 mean that the node T represent a line
// 	{
// 		Tree *tree = T->child;
//
// 		if (tree != NULL)
// 		{
// 			text = write(tree, text);
//
// 			while (tree->sibling != NULL)
// 			{
// 				tree = tree->sibling;
// 				text = write(tree, text);
// 			}
//
//
// 			text = mystrcat(text, '\n');
// 		}
// 	}
//
// 	else if (T->key == -3)	// T.key == -1 mean that the node T represent a paragraph
// 	{
// 		Tree *tree = T->child;
//
// 		if (tree != NULL)
// 		{
// 			text = write(tree, text);
//
// 			while (tree->sibling != NULL)
// 			{
// 				tree = tree->sibling;
// 				text = write(tree, text);
// 			}
//
// 			text = mystrcat(text, '\n');
// 			text = mystrcat(text, '\n');
// 		}
// 	}
//
// 	else if (T->key == -4)	// T.key == -4 mean that the node T is the root of the tree
// 	{
// 		Tree *tree = T->child;
//
// 		if (tree != NULL)
// 		{
// 			text = write(tree, text);
//
// 			while (tree->sibling != NULL)
// 			{
// 				tree = tree->sibling;
// 				text = write(tree, text);
// 			}
// 		}
// 	}
//
// 	free(T);
// 	return text;
// }
