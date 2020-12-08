#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "document.h"
#include "premierepage.h"

docs_t docs = {NULL, NULL};

int main (int argc, char **argv)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_table = NULL;;
  GtkWidget *p_text_view = NULL;
  GtkWidget* Label = NULL;
  gchar* Texte = NULL;  

  // Initialization of gtk
  gtk_init (&argc, &argv);

  // Create the first window 
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (p_window));
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "INTERFACE");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  
  //create the box for have numerous gtkwidget
  p_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  //create the texte

  Texte = g_locale_to_utf8("<span face=\"Times New Roman\" foreground=\"#7A81FF\" size=\"xx-large\" style=\"italic\"><b>Optical Character Recognition</b></span>\n <span face=\"Verdana\" foreground=\"#000000\" size=\"large\">By Anna Barry, Goeffroy Du Mesnil Du Buisson, Marie Maturana, Marine Thunet</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
    Label=gtk_label_new(Texte); // Application de la convertion à notre label
    
    g_free(Texte); // Libération de la mémoire

    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango

    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte

    gtk_container_add(GTK_CONTAINER(p_main_box), Label);  // On ajoute le label a l'interieur de 'Fenetre'
  
 

    //create the button box
    p_table = gtk_table_new(2, 3, FALSE);
    //gtk_table_set_col_spacing (p_table, 1, 4); 
    gtk_container_add (GTK_CONTAINER(p_main_box), p_table);
    
      
    //insert image
    {
      GtkWidget *p_image = NULL;
      p_image = gtk_image_new_from_file("intro.png");
      gtk_table_attach(GTK_TABLE(p_table), p_image,  1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 10, 10);
    }
    
    //create the start button
    {
      GtkWidget *p_button = NULL;

      p_button = gtk_button_new_with_label("INFORMATIONS");
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
      gtk_widget_set_size_request(p_button, 250, 200);
      gtk_table_attach(GTK_TABLE(p_table), p_button, 0, 1, 1, 2, GTK_EXPAND, GTK_EXPAND, 10, 10);
    }

    //create the start button
    {
      GtkWidget *p_button = NULL;

      p_button = gtk_button_new_with_label("START");
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
      gtk_widget_set_size_request(p_button, 250, 200);
      gtk_table_attach(GTK_TABLE(p_table), p_button, 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 10, 10);
    }

    /* Creation du bouton "Quitter" */
    {
      GtkWidget *p_button = NULL;

      p_button = gtk_button_new_with_label("QUIT");
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
      gtk_widget_set_size_request(p_button, 250, 200);
      gtk_table_attach(GTK_TABLE(p_table), p_button, 2, 3, 1, 2, GTK_EXPAND, GTK_EXPAND, 10, 10);
    }


  
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
