#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "document.h"

// by marie maturana

// main of the interface with makefile
// creation of the first window - introduction

docs_t docs = {NULL, NULL}; //informations of the document use after for open

int main (int argc, char **argv)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;
  GtkWidget *button_box = NULL;
  GtkWidget *text_view = NULL;
  GtkWidget* Label = NULL;
  gchar* Text = NULL;  

  // Initialization of gtk
  gtk_init (&argc, &argv);

  // Create the first window 
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (window));
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "INTERFACE");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  
  //Create the main container to have lots widgets
  // USE BOX
  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);
 
      

  //create the title
  Text = g_locale_to_utf8("<span face=\"Times New Roman\" foreground=\"#7A81FF\" size=\"xx-large\" style=\"italic\"><b>Optical Character Recognition</b></span>\n <span face=\"Verdana\" foreground=\"#000000\" size=\"large\">By Anna Barry, Goeffroy Du Mesnil Du Buisson, Marie Maturana, Marine Thunet</span>\n", -1, NULL, NULL, NULL);  //text avec policy
  Label = gtk_label_new(Text); //text become label
    g_free(Text);
    gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); 
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); 
    gtk_container_add(GTK_CONTAINER(main_box), Label);  
  
    //insert image for the presentation
  {
    GtkWidget *imageP = NULL;
    imageP = gtk_image_new_from_file("images/intro.png");
    gtk_box_pack_start (GTK_BOX (main_box), imageP, FALSE, FALSE, 0);
  }
  
  //create the button box
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (main_box), button_box, FALSE, FALSE, 0);
      
    //create information button
    {
      GtkWidget *button = NULL;
      GtkWidget *image = NULL; 
      button = gtk_button_new(); //create button
      image = gtk_image_new_from_file("images/bouton2.png"); //open image
      gtk_container_add(GTK_CONTAINER(button), image); //add image to the button
      g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), text_view); // add an action 
      gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0); // add button to box button
    }

    //create the start button
    {
      GtkWidget *button = NULL;
      GtkWidget *image = NULL; 
      button = gtk_button_new();
      image = gtk_image_new_from_file("images/bouton1.png");
      gtk_container_add(GTK_CONTAINER(button), image); 
      g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_openpage2), text_view);
      gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
      
    }

    //create the quit button 
    {
      GtkWidget *button = NULL;
      GtkWidget *image = NULL; 
      button = gtk_button_new();
      image = gtk_image_new_from_file("images/bouton.png");
      gtk_container_add(GTK_CONTAINER(button), image); 
      g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), NULL);
      gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
      
    }
  
  
    gtk_widget_show_all (window); //show window
    gtk_main (); //make main
    return EXIT_SUCCESS; //like 0
}
