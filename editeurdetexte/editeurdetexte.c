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
  GtkWidget *p_button_box = NULL;
  GtkWidget *p_text_view = NULL;
  GtkWidget* Label = NULL;
  gchar* Texte = NULL;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);

  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (p_window));
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "INTERFACE");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  Texte = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#000000\" size=\"xx-large\"><b>Optical Character Recognition</b></span>\n <span face=\"Verdana\" foreground=\"#808080\" size=\"large\">By Anna Barry, Goeffroy Du Mesnil Du Buisson, Marie Maturana, Marine Thunet</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
    Label=gtk_label_new(Texte); // Application de la convertion à notre label
    
    g_free(Texte); // Libération de la mémoire

    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango

    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte

    gtk_container_add(GTK_CONTAINER(p_main_box), Label);  // On ajoute le label a l'interieur de 'Fenetre'

 
  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);

  /* Creation du bouton "Ouvrir" */
  {
    GtkWidget *p_button = NULL;

    p_button = gtk_button_new_with_label("OPEN");
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Quitter" */
  {
    GtkWidget *p_button = NULL;

    p_button = gtk_button_new_with_label("QUIT");
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
