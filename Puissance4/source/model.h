/**
 * @file model.h
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief Header of the file containing all the functions forming the Model
 *  of a Connect 4
 * 
 * @date 06-05-22
 */

#ifndef ___MODEL___
#define ___MODEL___

typedef enum{none, red, yellow}Colour;

typedef enum{lose, win, draw}Result;

typedef enum{false, true}Boolean;

typedef struct user_t User;

/**
 * \brief Declaration of the Model opaque type
 *
 */
typedef struct model_t Model;

/**
 * @brief Creates a pointer on the model
 * 
 * @param nbLines Number of lines of the grid
 * @param nbColumns Number of columns of the grid
 * 
 * @pre /
 * @post Returns the address of the pointer, NULL if something went wrong.
 * 
 * @return Model*
 */
Model *create_model(unsigned nbLines, unsigned nbColumns);

/**
 * @brief Creates dynamically the grid of the game
 * 
 * @param nbLines number of lines of the grid
 * @param nbColumns number of columns of the grid
 * 
 * @pre nbLines > 0, nbColumns > 0
 * @post returns the address of the grid,
 * or NULL if something went wrong.
 */
Colour **create_game_grid(unsigned nbLines, unsigned nbColumns);

/**
 * @brief frees a matrix created dynamically
 * 
 * @param grid the matrix
 * @param nbLines the number of lines of the matrix
 * 
 * @pre /
 * @post the matrix is freed
 */
void free_game_grid(Colour **gameGrid, unsigned nbLines);

/**
 * @brief Initialises the data to start a Connect 4 game
 * 
 * @param mp pointer on the Model.
 * @param choice colour of the player.
 * 
 * @pre mp != NULL
 * @post The data is initialised to start a game.
 */
void initialise_game_model(Model *mp, Colour choice);

/**
 * @brief Frees a model pointer properly
 * 
 * @param mp a model pointer
 * 
 * @pre /
 * @post the pointer is freed
 */
void free_model(Model *mp);

/**
 * @brief Checks all the possibilities/angles from an empty spot, for a
 * specific column or for all of them, to find consecutive tokens of a given 
 * colour according to a range given.
 * 
 * @param mp a pointer on the model.
 * @param range the range we want to check (must be 2 or 3).
 * @param colour the colour of the tokens we want to check.
 * @param specificColumn the index of the specific column we want to check (
 * a negative number if we want to check all of them).
 * 
 * @pre mp != NULL
 * @post Returns -1 if no possibility of consecutive tokens was found,
 *       returns the index of the column otherwise.
 * 
 * @return int [index of the column] if a possibility was found,
 *         int -1 if no possibility was found.
 */
int check_grid(Model *mp, int range, Colour colour, int specificColumn);

/**
 * @brief Adds a token in the grid for the player
 * 
 * @param mp a pointer on the model.
 * @param columnPosition the column chosen by the player.
 * @param result a pointer that will store the result of the move.
 * 
 * @pre mp != NULL
 * @post returns the position of the row the token has been placed in and
 * tells if the player won through the pointer Result *result.
 * 
 * @return unsigned int rowPosition
 */
unsigned add_token_player(Model *mp, unsigned columnPosition, Result *result);

/**
 * @brief Adds a token in the grid for the computer
 * 
 * @param mp pointer on the model.
 * @param columnPosition a pointer that will store the index of
 *  the column chosen by the computer.
 * @param result a pointer that will store the result of the move.
 * 
 * @pre mp != NULL
 * @post returns the position of the row the token has been placed in and
 * tells if the computer won through the pointer Result *result.
 * 
 * @return unsigned int rowPosition
 */
unsigned add_token_ai(Model *mp, unsigned *columnPosition, Result *result);

/**
 * @brief Checks if a column is completely filled
 * 
 * @param mp pointer on the model.
 * @param columnChosen column that has to be checked.
 * 
 * @pre mp != NULL
 * @post returns 1 if the column is filled,
 *       otherwise 0.
 * 
 * @return int 1 if the column is full,
 *         int 0 if there is still space.
 */
int check_height(Model *mp, unsigned columnChosen);

//------------ Setter functions ------------------

/**
 * @brief Sets the name of the player in the model
 * 
 * @param mp pointer on the model.
 * @param name name of the player.
 * 
 * @pre mp != NULL, name != NULL
 * @post the name is saved in the model.
 */
void set_name(Model *mp, char *name);

/**
 * @brief Sets the file of the highscores in the model
 * 
 * @param mp the pointer on the model.
 * @param highscoresFile the name of the file.
 * 
 * @pre mp != NULL, highscoresFile != NULL
 * @post the highscoresFile is saved in the model.
 */
void set_highscores_file(Model *mp, char *highscoresFile);

//------------ getters functions ------------------

/**
 * @brief Gets the number of lines of the grid
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the number of lines of the grid.
 */
unsigned int get_nbLines(Model *mp);

/**
 * @brief Gets the number of columns of the grid
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the number of columns of the grid.
 */
unsigned int get_nbColumns(Model* mp);

/**
 * @brief Gets the current colour of the player
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the current colour of the player.
 * @return Colour (red or yellow)
 */
Colour get_player_colour(Model* mp);

/**
 * @brief Gets the current colour of the computer playing against the player
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the current colour of the AI.
 * @return Colour (red or yellow)
 */
Colour get_ai_colour(Model* mp);

/**
 * @brief Gets the current player's name (if it exists)
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the name of the current player if it exists,
 * NULL otherwise.
 * @return char* name or NULL
 */
char *get_curr_player_name(Model *mp);

/**
 * @brief Gets one of the previous players' name (if it exists)
 * 
 * @param mp pointer on the model.
 * @param rank position of the former player in the array.
 * 
 * @pre mp != NULL
 * @post returns the name of a previous player chosen, if it exists,
 * NULL otherwise.
 * @return char* name or NULL
 */
char *get_prev_player_name(Model *mp, unsigned rank);

/**
 * @brief Gets the current player's score
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the current score of the player.
 * @return unsigned score
 */
unsigned get_curr_player_score(Model *mp);

/**
 * @brief Gets one of the previous players' score
 * 
 * @param mp pointer on the model.
 * @param rank position of the former player in the array.
 * 
 * @pre mp != NULL
 * @post returns the score of the previous player chosen.
 * @return unsigned score
 */
unsigned get_prev_player_score(Model *mp, unsigned rank);

/**
 * @brief Tells if the player is present (has a name)
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the presence of the player.
 * 
 * @return Boolean true if the player has a name,
 *         Boolean false if the player doesn't have one.
 */
Boolean get_presence_player(Model *mp);

/**
 * @brief Gets the grid of the game
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the grid of the game in its current state.
 * 
 * @return Colour** game grid 
 */
Colour **get_grid(Model *mp);

//----------------FUNCTIONS HIGHSCORES RELATED -------------

/**
 * @brief Checks and update the highscores file (if needed)
 *
 * @param mp pointer on the model.
 *
 * @pre mp != NULL
 * @post The file is updated and the player added to it if they had a
 * better score and a name.
 *
 * @return int 1 the file has been updated,
 *         int 0 player doesn't have a name or there's no need to update,
 * 		   int -1 an issue while opening the file occured,
 *         int -2 an issue while writing in the file occured.
 *
 */
int update_highscores(Model *mp);

/**
 * @brief Loads the list of the best scores in the Model
 *
 * @param mp pointer on the model.
 *
 * @pre mp != NULL
 * @post The list is loaded in the Model.
 *
 * @return int -1 the file couldn't be open,
 *         int 1 the data has been saved in the Model.
 */
int load_highscores(Model *mp);

/**
 * @brief Writes in a file the best scores
 *
 * @remark the last player in the previous list won't be saved
 * and therefore lost.
 *
 * @param mp pointer on the model.
 * @param rank rank where we want to place the current player.
 *
 * @pre  mp != NULL
 * @post The current player is placed in the highscores file and the file
 * is updated.
 *
 * @return int -1 the file couldn't be open,
 *         int -2 an issue while writing in the file occured,
 *         int 1 the update has been done properly.
 */
int update_highscores_file(Model *mp, int rank);

//------------ functions for the modes -------------

/**
 * @brief Tells if the breakfast mode is activated of not.
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post returns the state of the mode "Breakfast".
 * 
 * @return Boolean true if the mode is activated,
 *         Boolean false if the mode is off.
 */
Boolean is_breakfast(Model *mp);

/**
 * @brief Switches the Breakfast Mode (on or off)
 * 
 * @param mp pointer on the model.
 * 
 * @pre mp != NULL
 * @post The value is switched to true or false according to its previous
 * value.
 */
void change_breakfast(Model *mp);

#endif //___MODEL___
