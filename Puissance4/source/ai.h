/**
 * @file ia.h
 * 
 * @author Jiaxiang Yao S214174 & Alyssia Kayembe S211023
 * 
 * @brief Header of the file containing all the functions forming the "A.I."
 *  of a Connect 4
 * 
 * @remark Our functions check the boxes of a grid without knowing where the
 * limits of the latter actually are sometimes (i.e, i is higher than the 
 * number of columns and we want to check on the left).
 * Therefore, the user must be aware and careful before using these functions,
 * to avoid segmentation faults.
 * 
 * @date 05-05-2022
 */

#ifndef __AI__
#define __AI__

#include "model.h"

/**
 * @brief Checks in a grid if there is a sequence of elements
 *  underneath a "blank" spot.
 * 
 * @param range the number of elements we want to verify (2 or 3 underneath
 * in our case).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBLINES number of lines of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_down(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES);

/**
 * @brief Checks in a grid if there is a sequence of elements on the
 *  right of a "blank" spot.
 * 
 * @param range the number of elements we want to verify (2 or 3 elements
 *  on the right in our case).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBCOLUMNS);

/**
 * @brief Checks in a grid if there is a sequence of elements on the
 *  left of a "blank" spot.
 * 
 * @param range the number of elements we want to verify (2 or 3 elements
 *  on the left in our case).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_left(int range, Colour **grid, int* casesLeft, Colour colour, int i);

/**
 * @brief Checks in a grid if there is a sequence of elements in a diagonal
 * that starts at the bottom right of a "blank" spot.
 * 
 * @param range the number of elements we want to verify.
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBLINES number of lines of the grid.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_down_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES, const int NBCOLUMNS);

/**
 * @brief Checks in a grid if there is a sequence of elements in a diagonal
 * that starts at the bottom left of a "blank" spot.
 * 
 * @param range the number of elements we want to verify.
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBLINES number of lines of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_down_left(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBLINES);

/**
 * @brief Checks in a grid if there is a sequence of elements in a diagonal
 * that starts at the top right of a "blank" spot.
 * 
 * @param range the number of elements we want to verify.
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_up_right(int range, Colour **grid, int* casesLeft, Colour colour,
 int i, const int NBCOLUMNS);

/**
 * @brief Checks in a grid if there is a sequence of elements in a diagonal
 * that starts at the bottom left of a "blank" spot.
 * 
 * @param range the number of elements we want to verify.
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_up_left(int range, Colour **grid, int* casesLeft, Colour colour, int i);

/**
 * @brief Checks in a grid if an element forms a sequence with the elements
 * around it, in a row.
 * 
 * @param range the number of elements we want to verify
 *  (here it hhas to be 2 or 3).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_within_row(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBCOLUMNS);

/**
 * @brief Checks in a grid if an element forms a sequence with the elements
 * around it, in a diagonal with a negative slope.
 * 
 * @param range the number of elements we want to verify
 *  (here it has to be 2 or 3).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBLINES number of lines of the grid.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_within_diagonal_left(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBLINES, const int NBCOLUMNS);

/**
 * @brief Checks in a grid if an element forms a sequence with the elements
 * around it, in a diagonal with a positive slope.
 * 
 * @param range the number of elements we want to verify
 *  (here it has to be 2 or 3).
 * @param grid the grid we want to check.
 * @param casesLeft array containing for each column the position of the
 *  lowest blank spot in that column.
 * @param colour the value we want to check.
 * @param i index of the column where the blank spot is/from where we want to
 *  check.
 * @param NBLINES number of lines of the grid.
 * @param NBCOLUMNS number of columns of the grid.
 * 
 * @pre grid != NULL, casesLeft != NULL
 * @post returns the column index if a sequence of colour in that direction
 * has been found, -1 otherwise.
 * 
 * @return int i if a sequence has been found,
 *         int -1 if a sequence hasn't been found.
 */
int verify_within_diagonal_right(int range, int i, Colour **grid, int* casesLeft, Colour colour,
 const int NBLINES, const int NBCOLUMNS);

#endif //__AI__