
/**
 * @file interface.c
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief File implementing all the functions forming the interface
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

#include "interface.h"
#include "controller.h"
#include "model.h"
#include "view.h"

void destroy_window(GtkWidget *pWindow, gpointer data){
   assert(pWindow != NULL);

   gtk_main_quit();
}

GtkWidget *create_window(unsigned int length, unsigned int width, gchar *title){
   assert( length > 0 && width > 0 && title != NULL);

   //initialise the window
   GtkWidget *pWindow;
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pWindow), title);
   gtk_window_set_default_size(GTK_WINDOW(pWindow), length, width);
   gtk_window_set_resizable(GTK_WINDOW(pWindow), FALSE);
   
   //will allow to destroy the window
   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(destroy_window), NULL);

   return pWindow;
}

void create_icon(GtkWidget *pWindow){
   assert (pWindow != NULL);

   GdkPixbuf *icon = gdk_pixbuf_new_from_file("./source/icon.png", NULL);
   gtk_window_set_icon(GTK_WINDOW(pWindow), icon);

}

void create_pop_up_about(GtkWidget *pWindow, gpointer data){
   assert(data != NULL);
   //information on the creators
   gchar *message = "Puissance 4 \n \n Devs: Alyssia Kayembe et Jiaxiang Yao \n cours: INFO0030";

   //create the pop-up window for "À propos"
   GtkWidget *pPopUp;
   pPopUp = gtk_message_dialog_new(GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, message, NULL);
   gtk_window_set_title(GTK_WINDOW(pPopUp), "À propos");

   //run the pop-up window
   gtk_dialog_run(GTK_DIALOG(pPopUp));
   gtk_widget_destroy (pPopUp);
}

void create_pop_up_top10(GtkWidget *pWindow, gpointer data){
   assert(data != NULL);

   Arguments *arg = (Arguments *)data;
   Model *mp = get_model(arg->cp);

   //create the pop-up window for the top 10 players
   GtkWidget *pPopUp;
   pPopUp = gtk_message_dialog_new(GTK_WINDOW(arg->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, NULL);
   gtk_window_set_title(GTK_WINDOW(pPopUp), "TOP 10");
   gtk_widget_set_size_request(pPopUp, 450, 450);

   //get the message area of the pop-up window
   GtkWidget *textArea;
   textArea = gtk_message_dialog_get_message_area (GTK_MESSAGE_DIALOG(pPopUp));

   //boxes in which the top 10 best players are put
   GtkWidget *pVBox;
   pVBox = gtk_vbox_new(TRUE, 0);

   //description label
   GtkWidget *labelTitle = gtk_label_new("Meilleurs scores:");

   GtkWidget *pHBoxTitle;
   pHBoxTitle =  gtk_hbox_new(TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pHBoxTitle), labelTitle, TRUE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(pVBox), pHBoxTitle, TRUE, FALSE, 0);

   GtkWidget *labels[10]; //one label for each player
   char playerInfo[1000]; //information of the player
   GtkWidget *pHBox[10];
   int stop = 0;

   for(unsigned int i = 0; i < 10 && !stop; ++i){
      //it is impossible for a player to have a score of 0
      if(!get_prev_player_score(mp, i)){
         stop = 1;
      }
      else{
         sprintf(playerInfo, "%d. %s  %u", i+1, get_prev_player_name(mp, i), get_prev_player_score(mp, i));
         labels[i] = gtk_label_new(playerInfo);
         pHBox[i] = gtk_hbox_new(TRUE, 0);
         gtk_box_pack_start(GTK_BOX(pHBox[i]), labels[i], TRUE, FALSE, 0);
         gtk_box_pack_start(GTK_BOX(pVBox), pHBox[i], TRUE, FALSE, 0);
      }
   }

   //add the boxes to the message area
   gtk_container_add(GTK_CONTAINER(textArea), pVBox);

   //show the top 10 payers
   gtk_widget_show_all (textArea);

   //run the pop-up window
   gtk_dialog_run(GTK_DIALOG(pPopUp));
   gtk_widget_destroy (pPopUp);
}

void create_pop_up_restart(GtkWidget *pWindow, gpointer data){
   assert(data != NULL);
   
   Arguments *arg = (Arguments *)data;

   //create the pop-up window for "Recommencer"
   GtkWidget *pPopUp;
   gchar *message = "Veuillez choisir la couleur du jeton";
   pPopUp = gtk_message_dialog_new(GTK_WINDOW(arg->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_NONE, message, NULL);
   gtk_window_set_title(GTK_WINDOW(pPopUp), "Recommencer?");
   gtk_dialog_add_buttons (GTK_DIALOG(pPopUp), "Rouge", red, "Jaune", yellow, NULL);

   //run the pop-up window
   gint response = gtk_dialog_run(GTK_DIALOG(pPopUp));
   switch(response){
      case red:
         reinitialise_game(arg, red);
         break;
      case yellow:
         reinitialise_game(arg, yellow);
         break;
      default:
         break;
   }
   gtk_widget_destroy (pPopUp);
}

void create_pop_up_mode(GtkWidget *pWindow, gpointer data){
   assert(data != NULL);
   
   Arguments *arg = (Arguments *)data;
   Model *mp = get_model(arg->cp);
   View *vp = get_view(arg->cp);

   GtkWidget *pPopUp;
   gchar *message = "Veuillez choisir un mode de jeu";
   pPopUp = gtk_message_dialog_new(GTK_WINDOW(arg->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_NONE, message, NULL);
   gtk_window_set_title(GTK_WINDOW(pPopUp), "Mode?");
   gtk_dialog_add_buttons (GTK_DIALOG(pPopUp), "Classique", 1, "Petit déjeuner", 2, NULL);

   gint response = gtk_dialog_run(GTK_DIALOG(pPopUp));

   switch(response){
      case 1:
         if(is_breakfast(mp)){
         change_breakfast(mp);
         initialise_images(vp);
         }
         //Else it is already set on the Classic Mode
         break;

      case 2:
         if(!is_breakfast(mp)){
         change_breakfast(mp);
         initialise_images(vp);
         }
         //Else it is already set on the Breakfast Mode
         break;

      default:
         break;
   }

   gtk_widget_destroy (pPopUp);
}

GtkWidget *create_menu(GtkWidget *pWindow, Arguments **arg){
   assert(pWindow != NULL);

   //accelerator
   GtkAccelGroup *accelerator = NULL;
   accelerator = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(pWindow), accelerator);

   //menu bar
   GtkWidget *menuBar = gtk_menu_bar_new();

   //menu "Partie"
   GtkWidget *menuGame = gtk_menu_new();

   //create items for menu "Partie"
   GtkWidget *itemGame = gtk_menu_item_new_with_mnemonic("_Partie");
   GtkWidget *itemReplay = gtk_menu_item_new_with_mnemonic("_Redemarrer une partie");
   GtkWidget *itemTop10 = gtk_menu_item_new_with_mnemonic("_TOP 10");
   GtkWidget *itemMode = gtk_menu_item_new_with_mnemonic("_Changer le mode du jeu");
   GtkWidget *itemSeparator = gtk_separator_menu_item_new();
   GtkWidget *itemQuit = gtk_menu_item_new_with_label("Quitter");

   gtk_widget_add_accelerator(itemQuit, "activate", accelerator, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
   gtk_widget_add_accelerator(itemReplay, "activate", accelerator, GDK_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
   gtk_widget_add_accelerator(itemTop10, "activate", accelerator, GDK_t, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
   gtk_widget_add_accelerator(itemMode, "activate", accelerator, GDK_m, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   //attach items to "Partie"
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(itemGame), menuGame);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemReplay);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemTop10);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemMode);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemSeparator);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuGame), itemQuit);

   //menu "Help"
   GtkWidget *menuHelp = gtk_menu_new();

   //create items for menu "Aide"
   GtkWidget *itemHelp = gtk_menu_item_new_with_mnemonic("_Aide");
   GtkWidget *itemAbout = gtk_menu_item_new_with_label("A propos");

   gtk_widget_add_accelerator(itemAbout, "activate", accelerator, GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

   //attach items to "Aide"
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(itemHelp), menuHelp);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuHelp), itemAbout);

   //attach "Partie" and "Aide" to the menu bar
   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), itemGame);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), itemHelp);

   g_signal_connect(G_OBJECT(itemQuit), "activate", G_CALLBACK(destroy_window), NULL);
   g_signal_connect(G_OBJECT(itemAbout), "activate", G_CALLBACK(create_pop_up_about), pWindow);
   g_signal_connect(G_OBJECT(itemTop10), "activate", G_CALLBACK(create_pop_up_top10), arg[0]);
   g_signal_connect(G_OBJECT(itemMode), "activate", G_CALLBACK(create_pop_up_mode), arg[0]);
   g_signal_connect(G_OBJECT(itemReplay), "activate", G_CALLBACK(create_pop_up_restart), arg[0]);
   return menuBar;
}
