/**
 * @file controller.h
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief Header of the file containing all the functions forming the Controller
 *  of a Connect 4
 * 
 * @date 06-05-22
 */

#ifndef ___CONTROLLER___
#define ___CONTROLLER___

#include <gtk/gtk.h>

#include "model.h"
#include "view.h"

/**
 * @brief Declaration of the Controller (opaque type)
 */
typedef struct controller_t Controller;

/**
 * @brief A structure to store multiples arguments for the callbacks
 * 
 */
typedef struct arguments_t{
   int index;
   Controller *cp;
   GtkWidget *pWindow;
}Arguments;

/**
 * @brief Creates a pointer on the controller
 * 
 * @param mp pointer on the Model.
 * @param vp pointer on the View.
 * 
 * @pre mp != NULL, vp != NULL
 * @post returns the pointer on the controller,
 *         NULL if an issue occured during its creation.
 */
Controller* create_controller(Model* mp, View* vp);

/**
 * @brief Frees a controller pointer created dynamically
 * 
 * @param cp the pointer on the controller
 * 
 * @pre /
 * @post the pointer is freed
 */
void free_controller(Controller* cp);

/**
 * @brief Callback function that reacts according to the button clicked by
 *  the player and responds to their move
 * 
 * @param pButton button connected to the callback function.
 * @param data data containing the index of the button and the controller.
 * 
 * @pre data != NULL
 * @post reacts to the player's move and continues or ends the game.
 */
void click_button_game(GtkWidget *pButton, gpointer data);

/**
 * @brief Reinitialises the game
 * 
 * @param arg array of pointers on arguments (to get the window and controller).
 * @param choice colour of the token chosen by the player.
 * 
 * @pre arg != NULL
 * @post the game is reinitalised.
 */
void reinitialise_game(Arguments *arg, Colour choice);

// ------------ Functions for GTK ----------------

/**
 * @brief Connects the buttons to the callback function associated
 * 
 * @param cp pointer on the controller
 * @param arg array of pointers on arguments that will allow the connection.
 * 
 * @pre cp != NULL, arg != NULL
 * @post the game buttons are connected to the game callback function.
 */
void connect_buttons(Controller* cp, Arguments **arg);

/**
 * @brief Desactivates all the game buttons
 * 
 * @param cp pointer on the controller.
 * 
 * @pre cp != NULL
 * @post all the buttons are desactivated.
 */
void desactivate_all_buttons(Controller* cp);

/**
 * @brief Activates all the game buttons
 * 
 * @param cp pointer on the controller.
 * 
 * @pre cp != NULL
 * @post all the buttons are (re)activated.
 */
void activate_all_buttons(Controller* cp);

/**
 * @brief Places all the game buttons inside a horizontal box
 * 
 * @param cp pointer on the controller.
 * 
 * @pre cp != NULL
 * @post All the buttons are placed inside a horizontal box.
 */
GtkWidget *create_box_buttons(Controller* cp);

/**
 * @brief Creates an array of pointers on Argument
 * 
 * @param length the length wanted for the array 
 * 
 * @pre length > 0
 * @post returns the address of the array if the creation went well,
 *       NULL otherwise.
 * 
 * @return Arguments** 
 */
Arguments **create_arg_array(int length, GtkWidget *pWindow);

/**
 * @brief Frees an array of pointers on Argument
 * 
 * @param arg address of the array.
 * @param length size of the array.
 * 
 * @pre /
 * @post The array is freed properly.
 */
void free_arguments_array(Arguments **arg, int length);

/**
 * @brief Checks the extension of a file
 * 
 * @param filename the name of the file to be checked
 * @param extension the correct extension of the file
 * 
 * @pre filename != NULL, extension != NULL
 * @post the file extension is checked.
 * 
 * @return int 1 if the extension of the file is the one expected,
 *         int 0 if the extension isn't the same one as the file extension.
 */
int check_extension(char* filename, char* extension);

//------------ getters functions ------------------

/**
 * @brief Gets the pointer on the view
 * 
 * @param cp pointer on the controller.
 * 
 * @pre cp != NULL
 * @post returns the pointer on the view.
 */
View *get_view(Controller *cp);

/**
 * @brief Gets the pointer on the model
 * 
 * @param cp pointer on the controller.
 * 
 * @pre cp != NULL
 * @post returns the pointer on the model.
 */
Model *get_model(Controller *cp);

#endif //___CONTROLLER___
