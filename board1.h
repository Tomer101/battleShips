#ifndef _BOARD1_H
#define _BOARD1_H
#include <stdio.h>
#include <stdlib.h>
#include "files.h"

typedef enum {HIT=-2, MISS=-1, WATER=0} status;

/*create a new blank game board*/
void createBoard (int gameBoard[][COLS]);

/*print the game board*
 * HIT(X)             *
 * miss(m)            *
 * WATER(-)           *
 *                    */
void showBoard (int board[][COLS], int playerNum, FILE* resultFile);


/*mark the ships on the game board    *
 *(player cannot see the ship marking)*/
void markShip (int gameBoard[][COLS], int shipNumber, int shipsArray[], Coor start_cor, Coor end_coor, FILE* resultFile);

#endif _BOARD1_H

