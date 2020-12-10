#include "premierepage.h"
#include "pageOCR.h"
#include "pageReWrite.h"
#include "pageWrite.h"
#include "document.h"
#include "error.h"
#include "callback.h"
#include <stdlib.h>
#include <gtk/gtk.h>


void cb_openpage2 (GtkWidget *p_widget, gpointer user_data)
{


  // start the new page = menu ----------------------------------------------------------------------------------------------------------------------------------------------------------------

  //create the widget object 
  
  GtkWidget *d_window = NULL;
  GtkWidget *d_main_box = NULL;
  GtkWidget *d_button_box = NULL;
  GtkWidget *d_text_view = NULL;
  GtkWidget *Texte = NULL;
  GtkWidget *Label = NULL;

  // create the new page 
  d_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (d_window));
  gtk_window_maximize (GTK_WINDOW (d_window));
  gtk_window_set_title (GTK_WINDOW (d_window), "MENU");
  g_signal_connect (G_OBJECT (d_window), "destroy", G_CALLBACK (cb_quit), NULL);

  // Creation big box 
  d_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (d_window), d_main_box);

  Texte = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000000\" size=\"xx-large\"><b>MENU</b></span>\n" , -1, NULL, NULL, NULL);

  //Make the texte label and put it on the window
  
  Label = gtk_label_new(Texte); // texte to label 
    
  g_free(Texte); //free the memory

  gtk_label_set_use_markup(GTK_LABEL(Label), TRUE);

  gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

  gtk_container_add(GTK_CONTAINER(d_main_box), Label); 

  
  //Create the button box
  
  d_button_box = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (d_main_box), d_button_box, FALSE, FALSE, 0);

  
  //create the open button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("MODIFYING");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_openpageReWrite), d_text_view);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the OCR button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("MAKE OCR");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_openpageOCR), d_text_view);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the new page button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("NEW PAGE");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_openpageWrite), NULL);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }


  //create the quit button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("QUIT");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //display new window
  gtk_widget_show_all (d_window);


  // Unused Parametres 
  (void)p_widget;
  (void)user_data;
}
