/**
 * @file model.c
 * 
 * @author Alyssia Kayembe S211023 & Jiaxiang Yao S214174
 * 
 * @brief File implementing all the functions forming the Model
 *  of a Connect 4
 * 
 * @date 06-05-22
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "model.h"
#include "ai.h"

#define MAX_CHAR 50
#define NB_PLAYERS 10
/**
 * @brief Implementation of a User structure
 */
struct user_t{
   char name[MAX_CHAR];
   unsigned int score;
   Colour colour;
   Boolean present;
};
 /**
  * @brief Implementation of a Mode structure
  * 
  */
typedef struct mode_t{
   Boolean isBreakfast;
}Mode;

/**
 * @brief Implementation of the model for the Connect 4
 */
struct model_t{
   char *highscoresFile;
   Colour **gameGrid;
   int* casesLeft;
   unsigned int nbLines;
   unsigned int nbColumns;
   User player;
   User prevPlayers[NB_PLAYERS];
   Colour machineColour;
   Mode mode;
};

//_________DECLARATION OF THE STATIC FUNCTION_____________

/**
 * @brief Picks randomly a number from 0 to upperLimit (not included)
 * 
 * @param upperLimit The upper limit of the interval
 * 
 * @pre upperLimit > 0
 * @post returns a number within the interval
 */
static int random_number(int upperLimit);

//________END OF THE DECLARATION__________________________ 

Model *create_model(unsigned nbLines, unsigned nbColumns){

   Model* mp = malloc(sizeof(Model));
   if(mp == NULL){
      return NULL;
   }

   mp->gameGrid = create_game_grid(nbLines, nbColumns);
   if(mp->gameGrid == NULL){
      free(mp);
      return NULL;
   }

   mp->casesLeft = malloc(sizeof(int) * nbColumns);
   if(mp->casesLeft == NULL){
      free_game_grid(mp->gameGrid, nbLines);
      free(mp);
      return NULL;
   }

   mp->nbLines = nbLines;
   mp->nbColumns = nbColumns;
   mp->highscoresFile = NULL;
   mp->player.present = false;
   mp->mode.isBreakfast = false;

   /* we call this fonction in here in case it is not called in the main
    *  at the beginning */
   initialise_game_model(mp, 0);

   return mp;
}

Colour **create_game_grid(unsigned nbLines, unsigned nbColumns){
   assert(nbLines > 0 &&  nbColumns > 0);

   Colour **grid = malloc(sizeof(Colour *) * nbLines);
   if(grid == NULL){
      return NULL;
   }

   int stop = 0;
   for(unsigned i = 0; i < nbLines && !stop; ++i){
      grid[i] = malloc(sizeof(Colour) * nbColumns);
      if(grid[i] == NULL){
         free_game_grid(grid, nbLines);
         stop = 1;
      }
   }
   if(stop == 1){
      return NULL;
   }

   return grid;
}

void free_game_grid(Colour **gameGrid, unsigned nbLines){
   if(gameGrid == NULL){
      return;
   }
   for(unsigned i = 0; i < nbLines; ++i){
      if(gameGrid[i] != NULL){
         free(gameGrid[i]);
      }
   }
   free(gameGrid);
}

void initialise_game_model(Model *mp, Colour choice){
   assert(mp != NULL);

   mp->player.colour = none;
   mp->machineColour = none;
   mp->player.score = 0;

   //If the colour given doesn't exist, we pick one randomly
   if(choice != red && choice != yellow){
      choice = random_number(2);
   }

   switch(choice){
      case red:
         mp->player.colour = red;
         mp->machineColour = yellow;
         break;

      case yellow:
         mp->player.colour = yellow;
         mp->machineColour = red;
         break;

      default:
         //if the random number is 0, it will pick these default values
         mp->player.colour = yellow;
         mp->machineColour = red;
      break;
   }

   for(unsigned i = 0; i < mp->nbLines; ++i){
      for(unsigned j = 0; j < mp->nbColumns; ++j){
         mp->gameGrid[i][j] = none;
      }
   }

   for(unsigned i = 0; i < mp->nbColumns; ++i){
      mp->casesLeft[i] = (int)mp->nbLines - 1;
   }
}

void free_model(Model *mp){
   if(mp == NULL){
      return;
   }
   free_game_grid(mp->gameGrid, mp->nbLines);
   free(mp->casesLeft);
   free(mp);
}

int check_grid(Model* mp, int range, Colour colour, int specificColumn){
   assert(mp != NULL);

   const int NBCOLUMNS = (int)mp->nbColumns;
   const int NBLINES = (int)mp->nbLines;

   int status = -1;
   int stop = 0;
   int i = 0;
   //if the column given as argument is valid, we will only check that column
   if(specificColumn >= 0 && specificColumn < NBCOLUMNS){
      i = specificColumn;
   }

   while(i < NBCOLUMNS && status == -1 && !stop){

      //allows to check only once and stop the loop right after the check
      if(specificColumn >= 0){
         stop = 1;
      }

      //if the current column is full, we move on to the next one
      if(check_height(mp, i)){
         ++i;
      }
      else{
         //checking the tokens to the left
         status = verify_left(range, mp->gameGrid, mp->casesLeft, colour, i);

         if(status == -1){
            //checking the tokens in oblique to the top left
            status = verify_up_left(range, mp->gameGrid, mp->casesLeft, colour,
             i);
         }

         if(status == -1){
            //checking the tokens in oblique to the bottom left
            status = verify_down_left(range, mp->gameGrid, mp->casesLeft,
             colour, i, NBLINES);
         }

         if(status == -1){
            //checking the tokens to the right
            status = verify_right(range, mp->gameGrid, mp->casesLeft, colour,
             i, NBCOLUMNS);
         }

         if(status == -1){
            //checking the tokens in oblique to the top right
            status = verify_up_right(range, mp->gameGrid, mp->casesLeft,
             colour, i, NBCOLUMNS);
         }

         if(status == -1){
            //checking the tokens in oblique to the bottom right
            status = verify_down_right(range, mp->gameGrid, mp->casesLeft,
             colour, i, NBLINES, NBCOLUMNS);
         }

         if(status == -1){
            //checking the tokens underneath
            status = verify_down(range, mp->gameGrid, mp->casesLeft, colour,
             i, NBLINES);
         }

         //checking if a token is between other tokens:
         if(status == -1){
            /* will allow to check all the posibilities according to the position
             * (here the possibilities for a row) 
             */
            status = verify_within_row(range, i, mp->gameGrid, mp->casesLeft, colour,
             NBCOLUMNS);
         }

         if(status == -1){
            /* will allow to check all the posibilities according to the position
             * (here the possibilities for a diagonal with a negative slope) 
             */
            status = verify_within_diagonal_left(range, i, mp->gameGrid,
             mp->casesLeft, colour, NBLINES, NBCOLUMNS);
         }
         if(status == -1){
               /* will allow to check all the posibilities according to the position
               * (here the possibilities for a diagonal with a positive slope) 
               */
            status = verify_within_diagonal_right(range, i, mp->gameGrid,
             mp->casesLeft, colour, NBLINES, NBCOLUMNS);
         }

         ++i;
      }
   }
   return status;
}

unsigned add_token_player(Model *mp, unsigned columnPosition, Result *result){
   assert(mp != NULL);

   //Checking if the player will win the game with this move
   int status = check_grid(mp, 3, mp->player.colour, columnPosition);

   //if the status is != -1, it means the spot selected did a Connect 4 
   if(status != -1){
      *result = win;
   }

   unsigned rowPosition = (unsigned)mp->casesLeft[columnPosition];
   //The game grid will be filled according to the position of the token
   mp->gameGrid[rowPosition][columnPosition] = mp->player.colour;

   //The players score increase after placing a token
   ++mp->player.score;

   //The pile of tokens in that column increases
   --mp->casesLeft[columnPosition];

   return rowPosition;
}

unsigned add_token_ai(Model *mp, unsigned* columnPosition, Result *result){
   assert(mp != NULL);

   *result = win;
   int colTemp = 0;
   int everyColumn = -1;

   //Step 1: Check victory for the computer
   colTemp = check_grid(mp, 3, mp->machineColour, everyColumn);

   //Step 2: Prevent player from winning (if not step 1)
   if(colTemp == -1){
      *result = lose;
      colTemp = check_grid(mp, 3, mp->player.colour, everyColumn);
   }

   //Step 3: Add a third token (if not steps 1 & 2)
   if(colTemp == -1){
      *result = lose;
      colTemp = check_grid(mp, 2, mp->machineColour, everyColumn);
   }

   //Step 4: Prevent a third token to be added (if not steps 1, 2 & 3)
   if(colTemp == -1){
      *result = lose;
      colTemp = check_grid(mp, 2, mp->player.colour, everyColumn);
   }

   //Step 5: Choose a random column to add a token (last option)
   if(colTemp == -1){
      *result = lose;
      colTemp = random_number(mp->nbColumns);
      //if the column chosen is full, we take the next one that isn't
      while(mp->casesLeft[colTemp] < 0){
         colTemp = (colTemp + 1) % mp->nbColumns;
      }
   }

   //colTemp represents the column chosen by the computer now
   *columnPosition = (unsigned)colTemp;

   unsigned rowPosition = (unsigned)mp->casesLeft[*columnPosition];

   mp->gameGrid[rowPosition][*columnPosition] = mp->machineColour;
   --mp->casesLeft[*columnPosition];
   return rowPosition;
}

int check_height(Model *mp, unsigned columnChosen){
   assert(mp != NULL);

   if(columnChosen < mp->nbColumns)
      if(mp->casesLeft[columnChosen] < 0)
         return 1;

   return 0;
}

//------------ Setter functions ------------------

void set_name(Model *mp, char *name){
   assert(mp != NULL && name != NULL);
   strcpy(mp->player.name, name);
   //the player has a name and therefore exists, so we can change its status
   mp->player.present = true;
}

void set_highscores_file(Model *mp, char *highscoresFile){
   assert(mp != NULL && highscoresFile != NULL);
   mp->highscoresFile = highscoresFile;
}

//------------ getters functions ------------------

unsigned int get_nbLines(Model* mp){
   assert(mp != NULL);
   return mp->nbLines;
}

unsigned int get_nbColumns(Model* mp){
   assert(mp != NULL);
   return mp->nbColumns;
}

Colour get_player_colour(Model* mp){
   assert(mp != NULL);
   return mp->player.colour;
}

Colour get_ai_colour(Model* mp){
   assert(mp != NULL);
   return mp->machineColour;
}

char *get_curr_player_name(Model *mp){
   assert(mp != NULL);
   if(!mp->player.present){
      return NULL;
   }
   return mp->player.name;
}

char *get_prev_player_name(Model *mp, unsigned rank){
   assert(mp != NULL && rank < NB_PLAYERS);
   if(!mp->prevPlayers[rank].present){
      return NULL;
   }
   return mp->prevPlayers[rank].name;
}

unsigned get_curr_player_score(Model *mp){
   assert(mp != NULL);
   return mp->player.score;
}

unsigned get_prev_player_score(Model *mp, unsigned rank){
   assert(mp != NULL && rank < NB_PLAYERS);
   return mp->prevPlayers[rank].score;
}

Boolean get_presence_player(Model *mp){
   assert(mp != NULL);
   return mp->player.present;
}

Colour **get_grid(Model *mp){
   assert(mp != NULL);

   return mp->gameGrid;
}

// ----------- Highscore Related functions ---------

int update_highscores(Model *mp){
   assert(mp != NULL);

   /*If the player doesn't have a name, we do not add them
      in the file.*/
   if(!mp->player.present){
      return 0;
   }

   int rank = -1;

   for(int i = 0; i < NB_PLAYERS && rank < 0; ++i){
      if(mp->player.score < mp->prevPlayers[i].score || !mp->prevPlayers[i].score){
         rank = i;
      }
   }

   int status = 0;
   if(rank >= 0){
      status = update_highscores_file(mp, rank);
   }
   return status;
}

int load_highscores(Model *mp){
   assert(mp != NULL);

   FILE* fp = fopen(mp->highscoresFile, "r");

   if(fp == NULL){
      printf("Le fichier n'existe pas encore/ n'est pas chargé.");
      printf("(%s)\n", mp->highscoresFile);
      return -1;
   }

   //We (re)initialise the data stored in the former players array
   for(int i = 0; i < NB_PLAYERS; i++){
      mp->prevPlayers[i].score = 0;
      mp->prevPlayers[i].present = false;
      mp->prevPlayers[i].colour = none;
   }

   int stop = 0;
   unsigned i = 0;

   while(i < NB_PLAYERS && !feof(fp) && !stop){
	   if(fscanf(fp, "%s %u", mp->prevPlayers[i].name, &mp->prevPlayers[i].score) != 2){
         stop = 1;
      }
      else{
         mp->prevPlayers[i].present = true;
         ++i;
      }
   }

   fclose(fp);
   return 1;
}

int update_highscores_file(Model *mp, int rank){
   assert(mp != NULL);

   FILE* fp = fopen(mp->highscoresFile, "w");
   if(fp == NULL){
      printf("Erreur lors de la sauvegarde des meilleurs scores ");
      printf("(%s)\n", mp->highscoresFile); 
      return -1;
   }

   int status = 1;
   int placed = 0;
   int i = 0;

   /* The last player of the former list will be lost/excluded */
   while(i < NB_PLAYERS && status != -2){
      if(i == rank && !placed){
         if(fprintf(fp,"%s %u", mp->player.name, mp->player.score) < 0){
            status = -2;
         }
         /*  Like so, the next player at this rank i will be placed
            right after in the list. */
         placed = 1;
      }
      else{
         if(mp->prevPlayers[i].present){
            if(fprintf(fp,"%s %u", mp->prevPlayers[i].name, mp->prevPlayers[i].score) < 0){
               status = -2;
            }
         }
         ++i;
      }
      if(fprintf(fp,"\n") < 0){
         status = -2;
      }
   }

   fclose(fp);
   return status;
}

//------------ functions for the modes -------------

Boolean is_breakfast(Model *mp){
   assert(mp != NULL);

   return mp->mode.isBreakfast;
}

void change_breakfast(Model *mp){
   assert(mp != NULL);

   if(mp->mode.isBreakfast){
      mp->mode.isBreakfast = false;
   }
   else{
      mp->mode.isBreakfast = true;
   }
}

// ----------- STATIC FUNCTIONS --------------------

static int random_number(int upperLimit){
   assert(upperLimit > 0);

   srand(time(NULL));
   return rand() % upperLimit;
}
