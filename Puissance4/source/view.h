/**
 * @file view.h
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief Header of the file containing all the functions forming the View
 *  of a Connect 4
 * 
 * @date 06-05-22
 * 
 */

#ifndef ___VIEW___
#define ___VIEW___

#include <gtk/gtk.h>

#include "model.h"

/**
 * @brief Declaration of the opaque type View
 *
 */
typedef struct view_t View;


/**
 * @brief Creates a pointer on the View (structure)
 * 
 * @param mp pointer on the Model
 * 
 * @pre mp != NULL
 * @post returns the address of the view object,
 *  NULL if something went wrong. 
 */
View* create_view(Model* mp);

/**
 * @brief Creates all the boxes (except the one that contains the buttons)
 * and adds them in the window
 * 
 * @param vp pointer on the view.
 * @param pWindow pointer on the window.
 * @param pMenu pointer on the menu.
 * @param pHBoxBoutons pointer on the box containing the game buttons
 * 
 * @pre vp != NULL, pWindow != NULL
 * @post The boxes are created and added inside of the window
 */
void create_boxes(View *vp, GtkWidget *pWindow, GtkWidget *pMenu,
 GtkWidget *pHBoxBoutons);

/**
 * @brief Loads the images of the token in the View
 * 
 * @param vp pointer on the view.
 * 
 * @pre vp != NULL
 * @post the images of tokens are loaded in the view (if the files exist).
 * 
 * @return int -1 if the images couldn't be loaded,
 *         int 0 if the images are loaded.
 */
int load_images_token(View *vp);

/**
 * @brief frees a pointer on the view
 * 
 * @param vp pointer on the View.
 * 
 * @pre /
 * @post the pointer is freed.
 */
void free_view(View *vp);

/**
 * @brief Creates and sets directly a table in a View pointer
 * to store the visual grid in
 *
 * @param vp pointer on the View
 *
 * @pre vp != NULL
 * @post a table is created and saved in the View to store the images.
 */
void initialise_table(View *vp);

/**
 * @brief Destroys the previous and creates a brand new one to store the
 * images of the tokes
 * 
 * @param vp pointer on the view
 * 
 * @pre vp != NULL
 * @post The table is refreshed
 */
void clean_table(View *vp);

/**
 * @brief Initialises the grid of the game (images)
 * 
 * @param vp pointer on the View
 *
 * @pre vp != NULL
 * @post The images that create the visual part of the grid are initialised
 * or changed to the other mode selected.
 */
void initialise_images(View *vp);

/**
 * @brief Updates an image on the grid
 *
 * @remark The images for the Breakfast mode work differently than the ones
 * for the Classic Mode. Indeed, the Classic Mode allows one image to be
 * changed directly in the table, whereas the Breafast Mode needs the entire
 * table to be refreshed in order to display the images properly. Therefore,
 * we kept the main idea we had for this function (made for the Classic Mode),
 * but the arguments aren't necessary for the Breakfast Mode (except View *vp).
 *
 * @param vp pointer on the View
 * @param posL index of the line we want to update the image in
 * @param posC index of the column wewant to update the image in
 * @param colour colour that will take the image selected in the grid 
 *
 * @pre vp != NULL
 * @post The images in the grid are updated
 */
void update_image(View *vp, unsigned posL, unsigned posC, Colour colour);

/**
 * @brief Creates the initial labels
 * 
 * @param vp pointer on the view.
 * 
 * @pre vp != NULL
 * @post the initial labels are created.
 */
void create_labels(View *vp);

/**
 * @brief Updates the score label
 * 
 * @param vp pointer on the View.
 * 
 * @pre vp != NULL
 * @post the score label is updated.
 */
void update_score_label(View *vp);

/**
 * @brief Updates the result label
 * 
 * @param vp pointer on the View.
 * @param result the result of the game. 
 * 
 * @pre vp != NULL
 * @post the result label is updated.
 */
void show_result_label(View *vp, Result result);

/**
 * @brief Updates the welcome label
 * 
 * @param vp pointer on the View.
 * 
 * @pre vp != NULL
 * @post the welcome label is updated.
 */
void show_welcome_label(View *vp);

//------------ function for the mode --------------

/**
 * @brief Toasts the images for the Breakfast Mode (optionnal)
 * 
 * @param vp pointer on the view
 * 
 * @pre vp != NULL
 * @post The images are toasted and loaded in the View
 */
void prepare_toasts(View *vp);

#endif //___VIEW___
