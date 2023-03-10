/**
 * @file interface.h
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief Header of the file containing all the functions forming the interface
 *  of a Connect 4
 * 
 * @date 06-05-22
 * 
 */

#ifndef ___INTERFACE___
#define ___INTERFACE___

#include "controller.h"

/**
 * @brief Destroys the window
 * 
 * @param pWindow the window that will be destroyed
 * 
 * @pre pWindow != NULL
 * @post the window is dstroyed
 */
void destroy_window(GtkWidget *pWindow, gpointer data);


/**
 * @brief Creates a window
 * 
 * @param length the length of the window
 * @param width the width of the window
 * @param title the title of the window
 * 
 * @pre length > 0, width > 0, title != NULL
 * @post a window is created
 */
GtkWidget *create_window(unsigned int length, unsigned int width, gchar *title);

/**
 * @brief Creates an icon for the the programme
 * 
 * @param pWindow the window of the programme
 * 
 * @pre pWindow != NULL
 * @post an icon is created for the programme
 */
void create_icon(GtkWidget *pWindow);

/**
 * @brief Creates a pop-up window for the about
 * 
 * @param pWindow the widget in cause
 * @param data the window pointer
 * 
 * @pre data != NULL
 * @post the pop-up window for the about is created
 */
void create_pop_up_about(GtkWidget *pWindow, gpointer data);

/**
 * @brief Creates the pop-up window for the top 10 best players
 * 
 * @param pWindow the widget in cause
 * @param data the pointer on Arguments
 * 
 * @pre data != NULL
 * @post the pop-up window for the top 10 best players is created
 */
void create_pop_up_top10(GtkWidget *pWindow, gpointer data);

/**
 * @brief Creates a pop-up window for the mode
 * 
 * @param pWindow the widget in cause
 * @param data the pointer on Arguments
 * 
 * @pre data != NULL
 * @post the pop-up window for that allows to choose a mode is created
 */
void create_pop_up_mode(GtkWidget *pWindow, gpointer data);

/**
 * @brief Creates the pop-up window for when we want to restart the game
 * 
 * @param pWindow the widget in cause
 * @param data the pointer on Arguments
 * 
 * @pre data != NULL
 * @post the pop-up window for when we restart the game is created
 */
void create_pop_up_restart(GtkWidget *pWindow, gpointer data);

/**
 * @brief Create a menu bar
 * 
 * @param pWindow the window on which the menu bar will be created.
 * 
 * @pre pWindow != NULL
 * @post a menu bar is created on the window.
 */
GtkWidget *create_menu(GtkWidget *pWindow, Arguments **arg);

#endif //___INTERFACE___
