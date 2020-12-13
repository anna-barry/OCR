#include "callback.h"
#include "document.h"
#include "string.h"
#include "error.h"

// by marie maturana

//all my callback functions for this functions and for funtions in main.c
// like save or open and different pages

#define DEFAULT_FILE "texteOCR"


//---------------------------------------------------------OPEN IMAGE-------------------------------------------------------------------------

// funtion for open image

void on_open_image (GtkWidget* widget, gpointer user_data)
{
  GtkWidget *image = GTK_WIDGET (user_data);
  GtkWidget *toplevel = gtk_widget_get_toplevel (image);
  GtkFileFilter *filter = gtk_file_filter_new ();
  GtkWidget *dialog = gtk_file_chooser_dialog_new (("Open image"),
						   GTK_WINDOW (toplevel),
						   GTK_FILE_CHOOSER_ACTION_OPEN,
						   GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
						   GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						   NULL); //choose file manually from a dialog box

  gtk_file_filter_add_pixbuf_formats (filter);
  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
			       filter);

  switch (gtk_dialog_run (GTK_DIALOG (dialog)))
    {
    case GTK_RESPONSE_ACCEPT:
      {
	gchar *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	char *extention = ".bmp";
	char *extentionn = ".BMP";
	unsigned long j = 0;
	unsigned res = 0;
	//compare if is a .bmp or .BMP
	for(unsigned long i = strlen(filename)-4; i < strlen(filename); i++)
	  {
	    if((extention[j] == filename[i])||(extentionn[j] == filename[i]))
	      res += 1;
	    j++;
	  }
	if(res == 4)
	  {
	    GdkPixbuf *pixbuf; 
	    pixbuf = gdk_pixbuf_new_from_file (filename , NULL);
			
			  
	    GdkPixbuf *pixbuf_mini = NULL; 
  
	    pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf, 
						   gdk_pixbuf_get_width (pixbuf) /2  , 
						   gdk_pixbuf_get_height (pixbuf) /2 , 
						   GDK_INTERP_NEAREST); 
  
	    gtk_image_set_from_pixbuf(GTK_IMAGE (image),pixbuf_mini);
			  
	     
		     
	  }
	else
	  {
	    cd_Errorpage(widget, user_data); //error page
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

void cb_openOCR (GtkWidget *widget, gpointer user_data)
{
  open_file_ocr (DEFAULT_FILE, GTK_TEXT_VIEW (user_data));  //use the file from ocr
  (void)widget;
}

static void open_file_ocr (const gchar *file_name, GtkTextView *text_view)
{
  g_return_if_fail (file_name && text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      // Copy contents in the text_viewer
      gchar *utf8 = NULL;
      GtkTextIter iter;
      GtkTextBuffer *text_buffer = NULL;

      text_buffer = gtk_text_view_get_buffer (text_view);
      gtk_text_buffer_get_iter_at_line (text_buffer, &iter, 0);
      utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
      g_free (contents), contents = NULL;
      gtk_text_buffer_insert (text_buffer, &iter, utf8, -1);
      g_free (utf8), utf8 = NULL;
    }
    else
    {
      print_warning ("Can't open the file %s\n", file_name); //error
    }
  }
}


//-----------------------------------------------------------OPEN FILE------------------------------------------------------------------------

static void open_file (const gchar *, GtkTextView *);

void cb_open (GtkWidget *widget, gpointer user_data)
{
  GtkWidget *dialog = NULL;
  dialog = gtk_file_chooser_dialog_new ("Open file", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    open_file (file_name, GTK_TEXT_VIEW (user_data)); //open the file choosen in the dialog box
    g_free (file_name), file_name = NULL;
  }
  gtk_widget_destroy (dialog);

}
//-----------------------------------------------------NEW FILE-------------------------------------------------------------------------------

//create a new file and write in 

void cb_new (GtkWidget *widget, gpointer user_data)
{
  
  docs.actif = g_malloc (sizeof (*docs.actif)); //create new doc
  docs.actif->chemin = NULL; //path is null because file don't exist
  docs.actif->text_view = GTK_TEXT_VIEW (user_data); 
  docs.actif->sauve = TRUE; //not modifie
  gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->text_view), TRUE);
}

//-----------------------------------------------------SAVE FILE-------------------------------------------------------------------------------

void cb_save (GtkWidget *widget, gpointer user_data)
{
  if (docs.actif)
  {
    if (!docs.actif->sauve)
    {
      // file never save
      if (!docs.actif->chemin)
      {
        GtkWidget *dialog = NULL;

        dialog = gtk_file_chooser_dialog_new ("Save file", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
        {
          docs.actif->chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        }
        gtk_widget_destroy (dialog);
      }
      // file already save
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
          GtkTextBuffer *text_buffer = NULL;

          text_buffer = gtk_text_view_get_buffer (docs.actif->text_view);
          gtk_text_buffer_get_bounds (text_buffer, &start, &end);
          contents = gtk_text_buffer_get_text (text_buffer, &start, &end, FALSE);
          locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
          g_free (contents), contents = NULL;
          fprintf (fichier, "%s", locale);
          g_free (locale), locale = NULL;
          fclose (fichier), fichier = NULL;
          docs.actif->sauve = TRUE;
        }
        else
        {
          print_warning ("Can't open file %s", docs.actif->chemin);
        }
      }
    }
  }
  else
  {
    print_warning ("not file");
  }

}

//-----------------------------------------------------------------SAVE AS------------------------------------------------------------------------------

void cb_saveas (GtkWidget *widget, gpointer user_data)
{
  if (docs.actif)
  {
    document_t tmp = *docs.actif;

    docs.actif->chemin = NULL;
    docs.actif->sauve = FALSE;
    cb_save (widget, user_data);
    if (!docs.actif->sauve)
    {
      (*docs.actif) = tmp;
    }
  }
  else
  {
    print_warning ("not file open");
  }
}


//-------------------------------------------------------------QUIT-----------------------------------------------------------------------------------

void cb_quit (GtkWidget *widget, gpointer user_data)
{
  gtk_main_quit();

}
//-----------------------------------------------------------MODIFY----------------------------------------------------------------------------------

void cb_modifie (GtkWidget *widget, gpointer user_data)
{
  if (docs.actif)
  {
    docs.actif->sauve = FALSE; //say the doc was modifie 
  }

}

//-------------------------------------------------OPEN FILE PART 2--------------------------------------------------------------------------------------------

static void open_file (const gchar *file_name, GtkTextView *text_view)
{
  g_return_if_fail (file_name && text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      //copy content
      GtkTextIter iter;
      GtkTextBuffer *text_buffer = NULL;

      cb_new (NULL, text_view);
      gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->text_view), TRUE);
      text_buffer = gtk_text_view_get_buffer (text_view);
      gtk_text_buffer_get_iter_at_line (text_buffer, &iter, 0);
      gtk_text_buffer_insert (text_buffer, &iter, contents, -1);
      docs.actif->sauve = TRUE;
    }
    else
    {
        print_warning ("can't open file %s\n", file_name);
    }
  }
  
}


//------------------------------------------------------------PAGE WRITE NEW DOCUMENT-------------------------------------------------------------------------------------------------------------------

//function for open the page for write a new document

void cb_pageWrite (GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;
  GtkWidget *button_box = NULL;
  GtkWidget *text_view = NULL;

  // create window
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW (window));
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "WRITE NEW DOCUMENT");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  // box created 
  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);

  // box for the text
  text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (main_box), text_view, TRUE, TRUE, 0);

  //button box
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (main_box), button_box, FALSE, FALSE, 0);

  //"open" button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOpenNew.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_new), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // "Save as" button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }
  
  // "Return" button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_openpage2), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // "Quit" button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  //show the window
  gtk_widget_show_all (window);

  

}

//--------------------------------------------------------------------------OPEN PAGE MODIYING A DOC-----------------------------------------------------------------------------------

//function for create the page for modify documents existing

void cb_pageReWrite (GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;
  GtkWidget *button_box = NULL;
  GtkWidget *text_view = NULL;

  //create page
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "MODIYING A DOC");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  // box
  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);

  //box for the text
  text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (main_box), text_view, TRUE, TRUE, 0);

  // button box
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (main_box), button_box, FALSE, FALSE, 0);

  // open file button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOpen.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_open), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // save button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSave.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_save), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // save as button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }
  
  // return button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_openpage2), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // quit button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // show the window
  gtk_widget_show_all (window);



}

//-------------------------------------------------------------------------ERROR PAGE--------------------------------------------------------------------------------------------------

void cd_Errorpage(GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;

  // create window
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "Error");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  // box
  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);

  //create the label for the image choosing
  GtkWidget *Label;
  
  gchar* Text = NULL;
  
  Text = g_locale_to_utf8("<span face=\"Times New Roman\" foreground=\"#7A81FF\" size=\"xx-large\" style=\"italic\"><b>ERROR = Choose a BMP image !!</b></span>\n", -1, NULL, NULL, NULL);
   
  Label=gtk_label_new(Text); // text in the label
    
  g_free(Text); 

  gtk_label_set_use_markup(GTK_LABEL(Label), TRUE);

  gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

  gtk_container_add(GTK_CONTAINER(main_box), Label); 


  // return button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_pageOCR), NULL);
    gtk_box_pack_start (GTK_BOX (main_box), button, FALSE, FALSE, 0);
  }
  
  gtk_widget_show_all (window);

  (void)widget;
  (void)user_data; 
 

}
  

//--------------------------------------------------------------------------OPEN PAGE OCR-----------------------------------------------------------------------------------------------

void cb_pageOCR (GtkWidget *p_widget, gpointer user_data)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;
  GtkWidget *button_box = NULL;
  GtkWidget *text_view = NULL;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (window));
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "Make OCR");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);

  //create the label for the image choosing
  GtkWidget *Label;
  gchar* Text = NULL; 
  Text = g_locale_to_utf8("<span face=\"Times New Roman\" foreground=\"#7A81FF\" size=\"xx-large\" style=\"italic\"><b>Choose a BMP image</b></span>\n", -1, NULL, NULL, NULL);
   
  Label=gtk_label_new(Text); 
    
  g_free(Text);

  gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); 

  gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);

  gtk_container_add(GTK_CONTAINER(main_box), Label);  

  GtkWidget *imageF;
  imageF = gtk_image_new ();
  GtkWidget *box;
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (box), imageF, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (main_box), box, TRUE, TRUE, 0);
  
 
  text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (main_box), text_view, TRUE, TRUE, 0);


  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (main_box), button_box, FALSE, FALSE, 0);

  // open image button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonImg.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (on_open_image), imageF );
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }
  
  //open button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonOCR.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_openOCR), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  // save as button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonSaveAs.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_saveas), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }
  
  // return button
  {
    GtkWidget *p_button = NULL;
    GtkWidget *image = NULL; 
    p_button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonReturn.png");
    gtk_container_add(GTK_CONTAINER(p_button), image); 
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_openpage2), text_view);
    gtk_box_pack_start (GTK_BOX (button_box), p_button, FALSE, FALSE, 0);
  }

  // quit button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQuit.png");
    gtk_container_add(GTK_CONTAINER(button), image); 
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  gtk_widget_show_all (window);

 

}

//--------------------------------------------------------------------------OPEN MENU-------------------------------------------------------------------------------------------------


void cb_openpage2 (GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window = NULL;
  GtkWidget *main_box = NULL;
  GtkWidget *button_box = NULL;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_fullscreen(GTK_WINDOW (window));
  gtk_window_maximize (GTK_WINDOW (window));
  gtk_window_set_title (GTK_WINDOW (window), "MENU");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_quit), NULL);

  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add (GTK_CONTAINER (window), main_box);
 
  //insert image
  {
    GtkWidget *f_image = NULL;
    f_image = gtk_image_new_from_file("images/menu.png");
    gtk_box_pack_start (GTK_BOX (main_box), f_image, FALSE, FALSE, 0);
  }
  
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start (GTK_BOX (main_box), button_box, FALSE, FALSE, 0);
      

  //create the open button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonModif.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_pageReWrite), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  //create the OCR button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonMakeOcr.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_pageOCR), NULL);
   gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  //create the new page button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonNew.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_pageWrite), NULL);
   gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }


  //create the quit button
  {
    GtkWidget *button = NULL;
    GtkWidget *image = NULL; 
    button = gtk_button_new();
    image = gtk_image_new_from_file("images/boutonQUITM.png");
    gtk_container_add(GTK_CONTAINER(button), image);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (cb_quit), NULL);
    gtk_box_pack_start (GTK_BOX (button_box), button, FALSE, FALSE, 0);
  }

  //display new window
  gtk_widget_show_all (window);

  
}
