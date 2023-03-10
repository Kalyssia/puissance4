/**
 * @file view.c
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief File implementing all the functions forming the View
 *  of a Connect 4
 * 
 * @date 06-05-22
 * 
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "model.h"
#include "view.h"

#define IMAGES_NUMBER 3
#define RESULT_NUMBER 3

/**
 * @brief Implementation of View for a Connect 4 program
 */
struct view_t{
   Model *mp;
   GtkWidget *table;
   GdkPixbuf *pixBClassic[IMAGES_NUMBER];
   GdkPixbuf *pixBToasts[IMAGES_NUMBER];
   GtkWidget *pHBoxGrid;
   GtkWidget *pLabelScore;
   GtkWidget *pLabelMessage;
};

View* create_view(Model* mp){
   assert(mp != NULL);

   //Creation of the view
   View* vp = malloc(sizeof(View));
   if(vp == NULL){
      return NULL;
   }

   //Association with the model
   vp->mp = mp;

   //Loading the images of the classic tokens
   if(load_images_token(vp) == -1){
      free(vp);
      return NULL;
   }
   //Prepares the images if the player wants to play to the Breakfast mode
   prepare_toasts(vp);

   return vp;
}

void create_boxes(View *vp, GtkWidget *pWindow, GtkWidget *pMenu,
 GtkWidget *pHBoxBoutons){
   assert(vp != NULL && pWindow != NULL);

   vp->pHBoxGrid = gtk_hbox_new(FALSE, 0);
   create_labels(vp);

   //Creation of the boxes
   GtkWidget *pVBox = gtk_vbox_new(FALSE, 0); //Main box
   GtkWidget *pHBoxLabel = gtk_hbox_new(FALSE, 0);

   //creation of the box that will contain the table
   vp->pHBoxGrid = gtk_hbox_new(FALSE, 0);
   initialise_table(vp);

   gtk_box_pack_start(GTK_BOX(pVBox), pMenu, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pHBoxLabel), vp->pLabelMessage, TRUE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pHBoxLabel), vp->pLabelScore, FALSE, FALSE, 10);
   gtk_box_pack_start(GTK_BOX(pVBox), pHBoxLabel, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(vp->pHBoxGrid), vp->table, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), vp->pHBoxGrid, FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), pHBoxBoutons, FALSE, FALSE, 0);

   gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
   initialise_images(vp);
}

int load_images_token(View *vp){
   assert(vp != NULL);

   //Storing the images
   GdkPixbuf *pbTemp[IMAGES_NUMBER];

   pbTemp[none] = gdk_pixbuf_new_from_file("./source/pions/bleu.gif", NULL);
   pbTemp[yellow] = gdk_pixbuf_new_from_file("./source/pions/jaune.gif", NULL);
   pbTemp[red] = gdk_pixbuf_new_from_file("./source/pions/rouge.gif", NULL);

   if(pbTemp[none] == NULL || pbTemp[yellow] == NULL || pbTemp[red] == NULL){ 
      printf("Erreur lors du chargement des images (pions).\n");
      return -1;
   }

   //Dimensionning the images
   const int SIZE = 75;
   vp->pixBClassic[none] = gdk_pixbuf_scale_simple(pbTemp[none], SIZE, SIZE,
    GDK_INTERP_NEAREST);
   vp->pixBClassic[yellow] = gdk_pixbuf_scale_simple(pbTemp[yellow], SIZE, SIZE,
    GDK_INTERP_NEAREST);
   vp->pixBClassic[red] = gdk_pixbuf_scale_simple(pbTemp[red], SIZE, SIZE,
    GDK_INTERP_NEAREST);

   return 0;
}

void free_view(View *vp){
   if(vp != NULL)
      free(vp);
}

void initialise_table(View *vp){
   assert(vp != NULL);

   unsigned nbLines = get_nbLines(vp->mp);
   unsigned nbColumns = get_nbColumns(vp->mp);
   vp->table = gtk_table_new(nbLines, nbColumns, FALSE);
}

void clean_table(View *vp){
   assert(vp != NULL);

   //We detroy the previous table (or the images won't change)
   gtk_widget_destroy(vp->table);
   //We create another one
   initialise_table(vp);

   //We get the box that contains the grid and place the new table in it
   gtk_box_pack_start(GTK_BOX(vp->pHBoxGrid), vp->table, FALSE, FALSE, 0);
}

void initialise_images(View *vp){
   assert(vp != NULL);

   if(is_breakfast(vp->mp)){
      update_image(vp, 0, 0, 0);
   }
   else{
      //if we are on classic mode, we clean the table only once here
      clean_table(vp);

      const unsigned C = get_nbColumns(vp->mp);
      const unsigned L = get_nbLines(vp->mp);
      Colour **grid = get_grid(vp->mp);

      for(unsigned i = 0; i < L; ++i){
         for(unsigned j = 0; j < C; ++j){
            update_image(vp, i, j, grid[i][j]);
         }
      }
   }
}

void update_image(View *vp, unsigned posL, unsigned posC, Colour colour){
   assert(vp != NULL);

   if(colour != none && colour != yellow && colour != red){
      return;
   }

   GtkWidget *image;

   if(is_breakfast(vp->mp)){

      /*We have to clean the table entirely when we want to add toasts,
       which isn't necessary in the case of the classic tokens. */
      clean_table(vp);

      Colour **grid = get_grid(vp->mp);

      const unsigned C = get_nbColumns(vp->mp);
      const unsigned L = get_nbLines(vp->mp);

      for(unsigned i = 0; i < L; ++i){
         for(unsigned j = 0; j < C; ++j){
            GtkWidget *image = gtk_image_new_from_pixbuf(vp->pixBToasts[grid[i][j]]);
            gtk_table_attach(GTK_TABLE(vp->table), image, j, j + 1,
             i, i + 1, GTK_FILL, GTK_FILL, 0, 0);
         }
      }
   }

   /* if it the game is set on the Classic mode, we only change the box
      that is concerned in the table. */
   else{
      GtkWidget *image = gtk_image_new_from_pixbuf(vp->pixBClassic[colour]);
      gtk_table_attach(GTK_TABLE(vp->table), image, posC, posC + 1,
       posL, posL + 1, GTK_FILL, GTK_FILL, 0, 0);
   }

   gtk_widget_show_all(vp->table);
}

void create_labels(View *vp){
   assert(vp != NULL);

   //the initial label for the score
   vp->pLabelScore = gtk_label_new("Score: 0");

   //the initial label to welcome the player
   vp->pLabelMessage = gtk_label_new(" ");

   show_welcome_label(vp);
}

void update_score_label(View *vp){
   assert(vp != NULL);

   char message[100];

   sprintf(message, "Score: %u", get_curr_player_score(vp->mp));

   gtk_label_set_text(GTK_LABEL(vp->pLabelScore), message);

}

void show_result_label(View *vp, Result result){
   assert(vp != NULL);

   char message[100];

   switch(result){
      case win:
         sprintf(message, "Vous avez gagné!");
         break;

      case lose:
         sprintf(message, "Vous avez perdu...");
         break;

      case draw:
         sprintf(message, "Match nul...");
         break;
      default:
         sprintf(message, "ERREUR");
         break;
   }

   gtk_label_set_text(GTK_LABEL(vp->pLabelMessage), message);
}

void show_welcome_label(View *vp){
   assert(vp != NULL);

   char message[100];

   if(get_presence_player(vp->mp)){
      sprintf(message, "Bienvenue %s!", get_curr_player_name(vp->mp));
   }
   else{
      sprintf(message, "Bienvenue!");
   }

   gtk_label_set_text(GTK_LABEL(vp->pLabelMessage), message);

}

//------------ function for the mode --------------

void prepare_toasts(View *vp){
   assert(vp != NULL);

   GdkPixbuf *pbTemp[IMAGES_NUMBER];

   pbTemp[none] = gdk_pixbuf_new_from_file("./source/toasts/nature.jpg", NULL);
   pbTemp[yellow] = gdk_pixbuf_new_from_file("./source/toasts/orange.jpg", NULL);
   pbTemp[red] = gdk_pixbuf_new_from_file("./source/toasts/fraise.jpg", NULL);

   if(pbTemp[none] == NULL || pbTemp[yellow] == NULL || pbTemp[red] == NULL){ 
      printf("Erreur lors du chargement des images (toasts).\n");
   }

   //Dimensionning the images
   const int SIZE = 75;
   vp->pixBToasts[none] = gdk_pixbuf_scale_simple(pbTemp[none], SIZE, SIZE,
    GDK_INTERP_NEAREST);
   vp->pixBToasts[yellow] = gdk_pixbuf_scale_simple(pbTemp[yellow], SIZE, SIZE,
    GDK_INTERP_NEAREST);
   vp->pixBToasts[red] = gdk_pixbuf_scale_simple(pbTemp[red], SIZE, SIZE,
    GDK_INTERP_NEAREST);
}
