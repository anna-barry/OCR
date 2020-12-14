#ifndef H_CALLBACK
#define H_CALLBACK

#include <gtk/gtk.h>
#include <stdlib.h>


void cb_open (GtkWidget *, gpointer);
void cb_openOCR (GtkWidget *, gpointer);
void cb_new (GtkWidget *p_widget, gpointer user_data);
void cb_rotate_image (GtkWidget *widget, gpointer user_data);
void cb_smooth_image (GtkWidget *widget, gpointer user_data);
void cb_contrast_image (GtkWidget *widget, gpointer user_data);
void cb_save (GtkWidget *p_widget, gpointer user_data);
void cb_saveas (GtkWidget *p_widget, gpointer user_data);
void cb_quit (GtkWidget *p_widget, gpointer user_data);
void cb_modifie (GtkWidget *p_widget, gpointer user_data);
void cb_pageWrite (GtkWidget *p_widget, gpointer user_data);
void cb_pageReWrite (GtkWidget *p_widget, gpointer user_data);
void cd_Errorpage(GtkWidget *p_widget, gpointer user_data);
void cb_pageOCR (GtkWidget *p_widget, gpointer user_data);
void cb_openpage2 (GtkWidget *p_widget, gpointer user_data);


#endif /* not H_CALLBACK */
