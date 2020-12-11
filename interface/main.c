#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "document.h"

docs_t docs = {NULL, NULL};

int main (int argc, char **argv)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_button_box = NULL;
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

  
  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
 
      

  //create the texte

  Texte = g_locale_to_utf8("<span face=\"Times New Roman\" foreground=\"#7A81FF\" size=\"xx-large\" style=\"italic\"><b>Optical Character Recognition</b></span>\n <span face=\"Verdana\" foreground=\"#000000\" size=\"large\">By Anna Barry, Goeffroy Du Mesnil Du Buisson, Marie Maturana, Marine Thunet</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
    Label=gtk_label_new(Texte); // Application de la convertion à notre label
    
    g_free(Texte); // Libération de la mémoire

    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango

    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte

    gtk_container_add(GTK_CONTAINER(p_main_box), Label);  // On ajoute le label a l'interieur de 'Fenetre'
  
    //insert image
  {
    GtkWidget *d_image = NULL;
    d_image = gtk_image_new_from_file("images/intro.png");
    gtk_box_pack_start (GTK_BOX (p_main_box), d_image, FALSE, FALSE, 0);
  }
  
  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);
      
    //create the start button
    {
      GtkWidget *p_button = NULL;
      GtkWidget *image = NULL; 
      p_button = gtk_button_new();
      image = gtk_image_new_from_file("images/bouton2.png");
      gtk_container_add(GTK_CONTAINER(p_button), image); 
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), p_text_view);
     gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    //create the start button
    {
      GtkWidget *p_button = NULL;
      GtkWidget *image = NULL; 
      p_button = gtk_button_new();
      image = gtk_image_new_from_file("images/bouton1.png");
      gtk_container_add(GTK_CONTAINER(p_button), image); 
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
      gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
      
    }

    /* Creation du bouton "Quitter" */
    {
      GtkWidget *p_button = NULL;
      GtkWidget *image = NULL; 
      p_button = gtk_button_new();
      image = gtk_image_new_from_file("images/bouton.png");
      gtk_container_add(GTK_CONTAINER(p_button), image); 
      g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
      gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
      
    }
  
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
