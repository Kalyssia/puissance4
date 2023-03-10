// ---- model.c ----
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

// ---- model.h ----
/**
 * \brief Declaration of the Model opaque type
 *
 */
typedef struct model_t Model;