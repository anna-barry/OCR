#include "pageReWrite.h"
#include "document.h"
#include "callback.h"
#include "premierepage.h"
#include <stdlib.h>
#include <gtk/gtk.h>


void cb_openpageReWrite (GtkWidget *p_widget, gpointer user_data)
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
  gtk_window_set_title (GTK_WINDOW (d_window), "MODIFIED A DOCUMENT");
  g_signal_connect (G_OBJECT (d_window), "destroy", G_CALLBACK (cb_quit), NULL);

  // Creation big box 
  d_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (d_window), d_main_box);

  // create the texte zone
  {
    GtkTextBuffer *d_text_buffer = NULL;

    d_text_view = gtk_text_view_new ();
    d_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (d_text_view));
    g_signal_connect (G_OBJECT (d_text_buffer), "changed", G_CALLBACK (cb_modifie), NULL);
    gtk_box_pack_start (GTK_BOX (d_main_box), d_text_view, TRUE, TRUE, 0);
  }
  
  //Create the button box
  
  d_button_box = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (d_main_box), d_button_box, FALSE, FALSE, 0);

  //create the save button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("OPEN");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_open), NULL);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the save button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("SAVE");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_save), NULL);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the save as button
  {
    GtkWidget *d_button = NULL;

    d_button = gtk_button_new_with_label("SAVE AS");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (d_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the return button
  {
    GtkWidget *d_button = NULL;

   d_button = gtk_button_new_with_label("RETURN");
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_openpage2), NULL);
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
