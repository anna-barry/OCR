#ifndef H_DOCUMENT
#define H_DOCUMENT

#include <gtk/gtk.h>


//struct for use a file and have informations about it

typedef struct
{
  gchar *chemin;
  gboolean sauve;
  GtkTextView *text_view;
} document_t;

typedef struct
{
  GList *tous;
  document_t *actif;
} docs_t;

extern docs_t docs;

#endif /* not H_DOCUMENT */
