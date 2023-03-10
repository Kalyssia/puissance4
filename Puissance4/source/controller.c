/**
 * @file controller.c
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief File implementing all the functions forming the Controller
 *  of a Connect 4
 * 
 * @date 06-05-22
 */

#include <gtk/gtk.h>
#include <assert.h>
#include <time.h>

#include "model.h"
#include "view.h"
#include "controller.h"
#include "interface.h"

/**
 * @brief Implementation of the controller for the Connect 4
 */
struct controller_t{
   Model *mp;
   View *vp;
   GtkWidget **pGameButtons;
};

Controller* create_controller(Model* mp, View* vp){
   assert(mp != NULL && vp != NULL);

   Controller* cp = malloc(sizeof(Controller));
   if(cp == NULL){
      return NULL;
   }

   cp->mp = mp;
   cp->vp = vp;

   cp->pGameButtons = malloc(sizeof(GtkWidget*) * get_nbColumns(cp->mp));
   if(cp->pGameButtons == NULL){
      free(cp);
      return NULL;
   }

   return cp;
}

void free_controller(Controller* cp){
   if(cp == NULL){
      return;
   }
   free(cp->pGameButtons);
   free(cp);
}

void click_button_game(GtkWidget *pButton, gpointer data){
   Arguments *arg = (Arguments*) data;
   assert(arg->cp != NULL);

   unsigned int columnChosen = arg->index;
   Controller *cp = arg->cp;

   //This variable will tell if the player or machine won
   Result result = lose;

   //Reacting to the player's move according to their choice
   unsigned rowPosition = add_token_player(cp->mp, columnChosen, &result);
   update_image(cp->vp, rowPosition, columnChosen, get_player_colour(cp->mp));
   update_score_label(cp->vp);

   //Actions if the player wins
   if(result == win){
      desactivate_all_buttons(cp);
      update_highscores(cp->mp);
      load_highscores(cp->mp);
      show_result_label(cp->vp, win);
      return;
   }

  //It is the computer's turn to play
  //This variable will allow us to also store the column chosen by the ai
   unsigned int newColumn = 0;

   rowPosition = add_token_ai(cp->mp, &newColumn, &result);
   update_image(cp->vp, rowPosition, newColumn, get_ai_colour(cp->mp));

   //Actions if the computer wins
   if(result == win){
      desactivate_all_buttons(cp);
      show_result_label(cp->vp, lose);
      return;
   }

   unsigned int counter = 0;
   /* Checking if the pile of tokens in a column has reached the limit,
      in that case we desactivate the button associated */
   for(unsigned i = 0; i < get_nbColumns(cp->mp); ++i){
      if(check_height(cp->mp, i)){
         gtk_widget_set_sensitive(cp->pGameButtons[i], FALSE);
         counter++;
      }
   }

   //Checking if there is a draw
   if(counter == get_nbColumns(cp->mp)){
      show_result_label(cp->vp, draw);
   }

}

void reinitialise_game(Arguments *arg, Colour choice){
   assert(arg != NULL);

   GtkWidget *pWindow = arg->pWindow;
   Controller *cp = arg->cp;

   if(cp == NULL || pWindow == NULL){
      printf("Erreur lors de la réinitialisation.\n");
      return;
   }

   //Initialise the game model
   initialise_game_model(cp->mp, choice);

   //Initialise the game view
   show_welcome_label(cp->vp);
   update_score_label(cp->vp);
   initialise_images(cp->vp);

   //Reactivate all the buttons
   activate_all_buttons(cp);

   gtk_widget_show_all(pWindow);
}

// ------------ Functions for GTK ----------------

void connect_buttons(Controller* cp, Arguments **arg){
   assert(cp != NULL && arg != NULL);

   char number[7];

   for(unsigned i = 0; i < get_nbColumns(cp->mp); ++i){
      arg[i]->cp = cp;
      arg[i]->index = i;

      sprintf(number, "_%u", i + 1);
      cp->pGameButtons[i] = gtk_button_new_with_mnemonic(number);
      g_signal_connect(G_OBJECT(cp->pGameButtons[i]), "clicked", G_CALLBACK(click_button_game), arg[i]);
   }
}

void desactivate_all_buttons(Controller* cp){
   assert(cp != NULL);

   const unsigned NBCOLUMNS = get_nbColumns(cp->mp);
   for(unsigned i = 0; i < NBCOLUMNS; ++i){
      gtk_widget_set_sensitive(cp->pGameButtons[i], FALSE);
   }
}

void activate_all_buttons(Controller* cp){
   assert(cp != NULL);

   const unsigned NBCOLUMNS = get_nbColumns(cp->mp);
   for(unsigned i = 0; i < NBCOLUMNS; ++i){
      gtk_widget_set_sensitive(cp->pGameButtons[i], TRUE);
   }
}

GtkWidget *create_box_buttons(Controller* cp){
   assert(cp != NULL);

   const unsigned NBCOLUMNS = get_nbColumns(cp->mp);
   GtkWidget *pHBoxB = gtk_hbox_new(FALSE, 0);

   //We place all the buttons directly in the box
   for(unsigned i = 0; i < NBCOLUMNS; ++i){
      gtk_box_pack_start(GTK_BOX(pHBoxB), cp->pGameButtons[i], TRUE, TRUE, 0);
   }

   return pHBoxB;
}

Arguments **create_arg_array(int length, GtkWidget *pWindow){
   assert(length >= 1 && pWindow != NULL);

   Arguments **arg = malloc(length * sizeof(Arguments*));
   if(arg == NULL){
      return NULL;
   }

   int stop = 0;
   for(int i = 0; i < length && !stop; ++i){
      arg[i] = malloc(sizeof(Arguments));

      if(arg[i] == NULL){
         //we do the way back and free what was already allocated
         i--;
         while(i >= 0){
            free(arg[i]);
            arg[i] = NULL;
            i--;
         }
         stop = 1;
      }
      else{
         arg[i]->pWindow = pWindow;
      }
   }

   return arg;
}

void free_arguments_array(Arguments **arg, int length){
   if(arg == NULL){
      return;
   }

   for(int i = 0; i < length; ++i){
      if(arg[i] != NULL){
         free(arg[i]);
      }
   }
   free(arg);
}

int check_extension(char* filename, char* extension){
   assert(filename != NULL && extension != NULL);

   //fileExt will store the string starting from the last '.'
   char *fileExt = strrchr(filename, '.');
   if(fileExt == NULL){
      return 0;
   }

   int isDifferent = strcmp(extension, fileExt+1);
   if(isDifferent){
      return 0;
   }

   //the extension is the right one:
   return 1;
}

//------------ getter functions ------------------

View *get_view(Controller *cp){
   assert(cp != NULL);
   return cp->vp;
}

Model *get_model(Controller *cp){
   assert(cp != NULL);
   return cp->mp;
}
