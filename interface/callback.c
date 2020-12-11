#include "callback.h"
#include "document.h"
#include "error.h"

#define DEFAULT_FILE "texteOCR"

//---------------------------------------------------------OPEN IMAGE-------------------------------------------------------------------------

static void on_open_image (GtkButton* button, gpointer user_data)
{
	GtkWidget *image = GTK_WIDGET (user_data);
	GtkWidget *toplevel = gtk_widget_get_toplevel (image);
	GtkFileFilter *filter = gtk_file_filter_new ();
	GtkWidget *dialog = gtk_file_chooser_dialog_new (("Open image"),
	                                                 GTK_WINDOW (toplevel),
	                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                 NULL);

	gtk_file_filter_add_pixbuf_formats (filter);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
	                             filter);

	switch (gtk_dialog_run (GTK_DIALOG (dialog)))
	  {
	  case GTK_RESPONSE_ACCEPT:
	    {
	      gchar *filename =gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	      gchar *extention = ".bmp";
	      gchar *extentionn = ".BMP";
	      size_t j = 0;
	      size_t b = 0;
	      for(size_t i = strlen(filename)-4; i < strlen(filename); i++)
		{
		  if((extention[j] != filename[i])||(extentionn[j] != filename[i]))
		    b += 1;
		  j++;
		}
	      if(b  != 4)
		{
		  gtk_image_set_from_file (GTK_IMAGE (image), filename);
		}
			
	      break;
	    }
	  default:
	    break;
	  }
	gtk_widget_destroy (dialog);
}



//-------------------------------------------------------OPEN OCR FILE------------------------------------------------------------------------


static void open_file_ocr (const gchar *, GtkTextView *);

void cb_openOCR (GtkWidget *p_widget, gpointer user_data)
{
  open_file_ocr (DEFAULT_FILE, GTK_TEXT_VIEW (user_data));
  (void)p_widget;
}

static void open_file_ocr (const gchar *file_name, GtkTextView *p_text_view)
{
  g_return_if_fail (file_name && p_text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      /* Copie de contents dans le GtkTextView */
      gchar *utf8 = NULL;
      GtkTextIter iter;
      GtkTextBuffer *p_text_buffer = NULL;

      p_text_buffer = gtk_text_view_get_buffer (p_text_view);
      gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
      utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
      g_free (contents), contents = NULL;
      gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
      g_free (utf8), utf8 = NULL;
    }
    else
    {
    	print_warning ("Impossible d'ouvrir le fichier %s\n", file_name);
    }
  }
}


//-----------------------------------------------------------OPEN FILE------------------------------------------------------------------------

static void open_file (const gchar *, GtkTextView *);

void cb_open (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *p_dialog = NULL;
  p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    open_file (file_name, GTK_TEXT_VIEW (user_data));
    g_free (file_name), file_name = NULL;
  }
  gtk_widget_destroy (p_dialog);

}
//-----------------------------------------------------NEW FILE-------------------------------------------------------------------------------

void cb_new (GtkWidget *p_widget, gpointer user_data)
{
  /* Pour l'instant il faut allouer la memoire, par la suite on modifiera
     simplement le pointeur */
  docs.actif = g_malloc (sizeof (*docs.actif));
  docs.actif->chemin = NULL;
  /* Pour l'instant, on se contente de stocker le seul GtkTextView qui existe,
    par la suite, il faudra en creer un nouveau ! */
  docs.actif->p_text_view = GTK_TEXT_VIEW (user_data);
  /* Le document vient d'etre cree, il n'est donc pas modifie */
  docs.actif->sauve = TRUE;
  gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->p_text_view), TRUE);
}

//-----------------------------------------------------SAVE FILE-------------------------------------------------------------------------------

void cb_save (GtkWidget *p_widget, gpointer user_data)
{
  if (docs.actif)
  {
    if (!docs.actif->sauve)
    {
      /* Le fichier n'a pas encore ete enregistre */
      if (!docs.actif->chemin)
      {
        GtkWidget *p_dialog = NULL;

        p_dialog = gtk_file_chooser_dialog_new ("Sauvegarder le fichier", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
        {
          docs.actif->chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
        }
        gtk_widget_destroy (p_dialog);
      }
      /* Soit le fichier a deja ete enregistre, soit l'utilisateur vient de nous
         fournir son nouvel emplacement, on peut donc l'enregistrer */
      if (docs.actif->chemin)
      {
        FILE *fichier = NULL;

        fichier = fopen (docs.actif->chemin, "w");
        if (fichier)
        {
          gchar *contents = NULL;
          gchar *locale = NULL;
          GtkTextIter start;
          GtkTextIter end;
          GtkTextBuffer *p_text_buffer = NULL;

          p_text_buffer = gtk_text_view_get_buffer (docs.actif->p_text_view);
          gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
          contents = gtk_text_buffer_get_text (p_text_buffer, &start, &end, FALSE);
          locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
          g_free (contents), contents = NULL;
          fprintf (fichier, "%s", locale);
          g_free (locale), locale = NULL;
          fclose (fichier), fichier = NULL;
          docs.actif->sauve = TRUE;
        }
        else
        {
          print_warning ("Impossible de sauvegarder le fichier %s", docs.actif->chemin);
        }
      }
    }
  }
  else
  {
    print_warning ("Aucun document ouvert");
  }

}

//-----------------------------------------------------------------SAVE AS------------------------------------------------------------------------------

void cb_saveas (GtkWidget *p_widget, gpointer user_data)
{
  if (docs.actif)
  {
    document_t tmp = *docs.actif;

    docs.actif->chemin = NULL;
    docs.actif->sauve = FALSE;
    cb_save (p_widget, user_data);
    if (!docs.actif->sauve)
    {
      (*docs.actif) = tmp;
    }
  }
  else
  {
    print_warning ("Aucun document ouvert");
  }
}


//-------------------------------------------------------------QUIT-----------------------------------------------------------------------------------

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();

}
//-----------------------------------------------------------MODIFY----------------------------------------------------------------------------------

void cb_modifie (GtkWidget *p_widget, gpointer user_data)
{
  if (docs.actif)
  {
    docs.actif->sauve = FALSE;
  }

}

//-------------------------------------------------OPEN FILE PART 2--------------------------------------------------------------------------------------------

static void open_file (const gchar *file_name, GtkTextView *p_text_view)
{
  g_return_if_fail (file_name && p_text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      /* Copie de contents dans le GtkTextView */
      GtkTextIter iter;
      GtkTextBuffer *p_text_buffer = NULL;

      cb_new (NULL, p_text_view);
      gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->p_text_view), TRUE);
      p_text_buffer = gtk_text_view_get_buffer (p_text_view);
      gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
      gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);
      /* Nous sommes obliges de remettre sauve a TRUE, car l'insertion du contenu
         du fichier dans le GtkTextView a appele cb_modfie */
      docs.actif->sauve = TRUE;
    }
    else
    {
        print_warning ("Impossible d'ouvrir le fichier %s\n", file_name);
    }
  }
  
}


//------------------------------------------------------------PAGE WRITE NEW DOCUMENT-------------------------------------------------------------------------------------------------------------------

void cb_pageWrite (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_button_box = NULL;
  GtkWidget *p_text_view = NULL;



  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW (p_window));
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  /* Creation de la zone de texte */
  p_text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (p_main_box), p_text_view, TRUE, TRUE, 0);

  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);

  /* Creation du bouton "Ouvrir" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOpenNew.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_new), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Sauvegarder sous" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }
  
  /* Creation du bouton "Return" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Quitter" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);

  

}

//--------------------------------------------------------------------------OPEN PAGE MODIYING A DOC-----------------------------------------------------------------------------------

void cb_pageReWrite (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_button_box = NULL;
  GtkWidget *p_text_view = NULL;



  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

  /* Creation de la zone de texte */
  p_text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (p_main_box), p_text_view, TRUE, TRUE, 0);

  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);

  /* Creation du bouton "Ouvrir" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOpen.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_open), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Sauvegarder" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSave.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_save), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Sauvegarder sous" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }
  
  /* Creation du bouton "Return" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(p_button), image);
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Quitter" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);



}

//--------------------------------------------------------------------------OPEN PAGE OCR-----------------------------------------------------------------------------------------------

void cb_pageOCR (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_button_box = NULL;
  GtkWidget *p_text_view = NULL;



  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (p_window));
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

   /* Creation de la zone d' Image */
  GtkWidget *imageF;
  imageF = gtk_image_new ();
  GtkWidget *box;
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (box), imageF, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (p_main_box), box, TRUE, TRUE, 0);

  /* Creation de la zone de texte */
  p_text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (p_main_box), p_text_view, TRUE, TRUE, 0);


  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);

  /* Creation du bouton "Ouvrir Image" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonImg.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (on_open_image), imageF);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }
  
  /* Creation du bouton "Ouvrir" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOCR.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openOCR), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Sauvegarder sous" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }
  
  /* Creation du bouton "Return" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), p_text_view);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Creation du bouton "Quitter" */
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
  }

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);

 

}

//--------------------------------------------------------------------------OPEN MENU-------------------------------------------------------------------------------------------------


void cb_openpage2 (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *p_window = NULL;
  GtkWidget *p_main_box = NULL;
  GtkWidget *p_button_box = NULL;



  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (p_window));
  gtk_window_maximize (GTK_WINDOW (p_window));
  gtk_window_set_title (GTK_WINDOW (p_window), "Editeur de texte en GTK+");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /* Creation du conteneur principal */
  p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (p_window), p_main_box);
 
  //insert image
  {
    GtkWidget *d_image = NULL;
    d_image = gtk_image_new_from_file("images/menu.png");
    gtk_box_pack_start (GTK_BOX (p_main_box), d_image, FALSE, FALSE, 0);
  }
  
  /* Creation du conteneur pour les boutons */
  p_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);
      

  //create the open button
  {
    GtkWidget *d_button = NULL;
    GtkWidget *image = NULL; 
    d_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonModif.png");
    gtk_container_add(GTK_CONTAINER(d_button), image);
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_pageReWrite), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the OCR button
  {
    GtkWidget *d_button = NULL;
    GtkWidget *image = NULL; 
    d_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonMakeOcr.png");
    gtk_container_add(GTK_CONTAINER(d_button), image);
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_pageOCR), NULL);
   gtk_box_pack_start (GTK_BOX (p_button_box), d_button, FALSE, FALSE, 0);
  }

  //create the new page button
  {
    GtkWidget *d_button = NULL;
    GtkWidget *image = NULL; 
    d_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonNew.png");
    gtk_container_add(GTK_CONTAINER(d_button), image);
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_pageWrite), NULL);
   gtk_box_pack_start (GTK_BOX (p_button_box), d_button, FALSE, FALSE, 0);
  }


  //create the quit button
  {
    GtkWidget *d_button = NULL;
    GtkWidget *image = NULL; 
    d_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQUITM.png");
    gtk_container_add(GTK_CONTAINER(d_button), image);
    g_signal_connect (G_OBJECT (d_button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (p_button_box), d_button, FALSE, FALSE, 0);
  }

  //display new window
  gtk_widget_show_all (p_window);

  
}
