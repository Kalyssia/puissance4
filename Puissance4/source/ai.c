/**
 * @file ia.c
 * 
 * @author Jiaxiang Yao S214174 & Alyssia Kayembe S211023
 * 
 * @brief File implementing all the functions forming the "A.I."
 *  of a Connect 4
 * 
 * @date 05-05-2022
 */

#include <assert.h>
#include <stdlib.h>

#include "model.h"
#include "ai.h"

// --------- Functions that check the angles -------------

int verify_down(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the bottom
   if(!(0 <= casesLeft[i] && casesLeft[i] < NBLINES - range)){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i] + j][i] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the right
   if(!(0 <= i && i < NBCOLUMNS - range)){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i]][i + j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_left(int range, Colour **grid, int* casesLeft, Colour colour, int i){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the left
   if(!(range <= i)){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i]][i - j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_down_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES, const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the bottom right
   if(!(i < NBCOLUMNS - range && casesLeft[i] < NBLINES - range)){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i] + j][i + j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_down_left(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the bottom left
   if(!(range <= i && casesLeft[i] < NBLINES - range)){
     return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i] + j][i - j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_up_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the top right
   if(!(i < NBCOLUMNS - range && range <= casesLeft[i])){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i] - j][i + j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

int verify_up_left(int range, Colour **grid, int* casesLeft, Colour colour, int i){
   assert(grid != NULL && casesLeft != NULL);

   //checking if the empty spot is not too close to the top left
   if(!(range <= i && range <= casesLeft[i])){
      return -1;
   }

   int isTrue = 1;
   for(int j = 1; j <= range && isTrue; ++j){
      if(grid[casesLeft[i] - j][i - j] != colour){
         //the sequence is broken up and therefore it becomes false
         isTrue = 0;
      }
   }

   if(isTrue){
      return i;
   }
   else{
      return -1;
   }
}

// -------------- Functions that check a token within others -----------

int verify_within_row(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   if(i < 1 || i == (NBCOLUMNS - 1)){
      return -1;
   }

   int checkLeft = i >= (range - 1);
   int checkRight = i < (NBCOLUMNS - (range - 1));

   int isTrue = 0;
   if(grid[casesLeft[i]][i - 1] == colour && grid[casesLeft[i]][i + 1] == colour){
      isTrue = 1;
   }

   if(isTrue){
      if(range == 2){
         return i;
      }

      if(range == 3){
         //if checkLeft true, then we are allowed to check further on the left
         if(checkLeft){
            if(grid[casesLeft[i]][i - 2] == colour){
               return i;
            }
         }
         //if checkRight true, then we are allowed to check further on the right
         if(checkRight){
            if(grid[casesLeft[i]][i + 2] == colour){
               return i;
            }
         }
      }
   }

   //if the range or the sequence don't exist, we return -1 as a default value
   return -1;
}

int verify_within_diagonal_left(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBLINES, const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   //if the column index is too close to the sides, we don't need to check
   if(i < 1 || i == (NBCOLUMNS - 1)){
      return -1;
   }
   //idem if the line index is too close to the top or the bottom
   if(casesLeft[i] < 1 || casesLeft[i] == (NBLINES - 1)){
      return -1;
   }

   int checkLeft = i >= (range - 1);
   int checkRight = i < (NBCOLUMNS - (range - 1));
   int checkTop = casesLeft[i] >= (range - 1);
   int checkBottom = casesLeft[i] < (NBLINES - (range - 1));

   int isTrue = 0;
   if(grid[casesLeft[i] - 1][i - 1] == colour && grid[casesLeft[i] + 1][i + 1] == colour){
      isTrue = 1;
   }
   if(isTrue){
      if(range == 2){
         return i;
      }

      if(range == 3){
         //if true, then we are allowed to check further on the top left
         if(checkTop && checkLeft){
            if(grid[casesLeft[i] - 2][i - 2] == colour){
               return i;
            }
         }
         //if true, then we are allowed to check further on the bottom right
         if(checkBottom && checkRight){
            if(grid[casesLeft[i] + 2][i + 2] == colour){
               return i;
            }
         }
      }
   }

   return -1;
}

int verify_within_diagonal_right(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBLINES, const int NBCOLUMNS){
   assert(grid != NULL && casesLeft != NULL);

   //if the column index is too close to the sides, we don't need to check
   if(i < 1 || i == (NBCOLUMNS - 1)){
      return -1;
   }
   //idem if the line index is too close to the top or the bottom
   if(casesLeft[i] < 1 || casesLeft[i] == (NBLINES - 1)){
      return -1;
   }

   int checkLeft = i >= (range - 1);
   int checkRight = i < (NBCOLUMNS - (range - 1));
   int checkTop = casesLeft[i] >= (range - 1);
   int checkBottom = casesLeft[i] < (NBLINES - (range - 1));

   int isTrue = 0;
   if(grid[casesLeft[i] + 1][i - 1] == colour && grid[casesLeft[i] - 1][i + 1] == colour){
      isTrue = 1;
   }
   if(isTrue){
      if(range == 2){
         return i;
      }

      if(range == 3){
         //if it is true, then we are allowed to check farther down and left
         if(checkBottom && checkLeft){
            if(grid[casesLeft[i] + 2][i - 2] == colour){
               return i;
            }
         }
         //if it is true, then we are allowed to check farther up and right
         if(checkTop && checkRight){
            if(grid[casesLeft[i] - 2][i + 2] == colour){
               return i;
            }
         }
      }
   }

   return -1;
}
