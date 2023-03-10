/**
 * @file main.c
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief main file of a Connect 4 program
 * 
 * @date 06-05-22
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

#include "model.h"
#include "view.h"
#include "controller.h"
#include "interface.h"

int main(int argc, char *argv[]){

   char *optstring = ":n:l:c:f:Hp:";
   int option = 0;
   int status = 0;

   char *filename;
   int fileCheck = 0;

   char *name;
   int nameCheck = 0;

   int colour = 0;

   unsigned int nbLines = 6, nbColumns = 7;

   while(((option = getopt(argc, argv, optstring)) != EOF) && status != -1){
      switch(option){
         //Mendatory option
         case 'f':
            filename = optarg;
            if(check_extension(filename, "txt")){
               fileCheck = 1;
            }
            else{
               printf("Extension du fichier incorrecte.\n");
            }
            break;

         //Optional options
         case 'n':
            name = optarg;
            nameCheck = 1;
            break;

         case 'l':
            nbLines = atoi(optarg);
            if(nbLines > 100){
               printf("nombre de lignes choisi trop grand.\n");
               return EXIT_FAILURE;
            }
            break;

         case 'c':
            nbColumns = atoi(optarg);
            if(nbColumns > 100){
               printf("nombre de colonnes choisi trop grand.\n");
               return EXIT_FAILURE;
            }
            break;

         case 'p':
            if(!strcmp(optarg, "rouge")){
               colour = red;
            }
            else if(!strcmp(optarg, "jaune")){
               colour = yellow;
            }
            break;

         case 'H':
            printf("AIDE OPTIONS:\n");
            printf("-f <nom du fichier>: pour afficher les meilleurs scores (requis).\n");
            printf("-n <nom du joueur>: permet d'enregistrer le nom du joueur (optionnel).\n");
            printf("-l <nombre de lignes>: nombre de lignes du plateau (optionnel).\n");
            printf("-c <nombre de colonnes>: nombre de colonnes du plateau (optionnel).\n");
            printf("-j <rouge ou jaune>: couleur du joueur (optionnel).\n");
            return EXIT_SUCCESS;
            break;

         //Cases when issues occure with the options
         case '?':
            printf("Option inconnue: %c\n", optopt);
            status = -1;
            break;

         case ':':
            printf("Argument manquant: %c\n", optopt);
            status = -1;
            break;

         default:
            printf("Une erreur inconnue s'est produite\n");
            status = -1;
            break;
      }
   }

   if(status == -1){
      printf("Une erreur au niveau des options est survenue!\n");
      return EXIT_FAILURE;
   }

   if(!fileCheck){
      printf("Le fichier contenant les meilleurs scores n'a pas été ajouté!\n");
      return EXIT_FAILURE;
   }

   if(nbLines < 6 || nbColumns < 7){
      printf("Les sizes choisies sont trop petites.\n");
      return EXIT_FAILURE;
   }

   if(nameCheck){
      printf("Bienvenue, %s! Bonne chance..\n", name);
   }

   // End of the options and checks -----

   //Creation of the MVC -----
      //MODEL
   Model *mp = create_model(nbLines, nbColumns);
   if(mp == NULL){
      return EXIT_FAILURE;
   }

      //VIEW
   View *vp = create_view(mp);
   if(vp == NULL){
      free_model(mp);
      return EXIT_FAILURE;
   }
      //CONTROLLER
   Controller *cp = create_controller(mp, vp);
   if(cp == NULL){
      //the order of the frees matters
      free_view(vp);
      free_model(mp);
      return EXIT_FAILURE;
   }

   //End of the creation -----

   //Saving the options in those new variables
   if(nameCheck){
      set_name(mp, name);
   }
   initialise_game_model(mp, colour);
   set_highscores_file(mp, filename);
   load_highscores(mp);

   //initialisation of the GTK environment
   gtk_init(&argc, &argv);

   //creation of the main window
   GtkWidget *pWindow = create_window(350, 300, "Puissance 4");

   //creation of the icon
   create_icon(pWindow);

   //Array of arguments
   Arguments **arg = create_arg_array(nbColumns, pWindow);
   if(arg == NULL){
      free_view(vp);
      free_model(mp);
      free_controller(cp);
      return EXIT_FAILURE;
   }

   //Creation the labels
   create_labels(vp);

   //Creation of the buttons and the menu
   GtkWidget *pMenu = create_menu(pWindow, arg);

   connect_buttons(cp, arg);


   //Creation of the box containing the buttons
   GtkWidget *pHBoxBoutons = create_box_buttons(cp);
   //Creation of the boxes and the visual interface
   create_boxes(vp, pWindow, pMenu, pHBoxBoutons);

   //Display
   gtk_widget_show_all(pWindow);

   gtk_main();

   //We free all the pointers we created dynamically
   free_arguments_array(arg, nbColumns);
   free_view(vp);
   free_model(mp);
   free_controller(cp);

   return EXIT_SUCCESS;
}
