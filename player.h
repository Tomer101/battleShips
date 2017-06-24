#ifndef _PLAYER_H
#define _PLAYER_H
#include <math.h>
#include <string.h>

/*fireAt function get the attack coordinate from the simulation file*
 *it is then check the player game board                            *
 *if no ship in that coordinate then MISS                           *
 *if there is a ship then HIT                                       *
 */
void fireAt(int gameBoard[][COLS], int row, int col, int shipsArray[], FILE* resultFile);

/*ifWin function run through the player ships array      *
 *every index in the ships array holds the live of a ship*
 *if all ships live are zero then the other player win.  *
 */
void isWin(int gameBoard1[][COLS], int gameBoard2[][COLS] ,int shipArray[],char player[], FILE* resultFile);


/*PLAYER VS PLAYER MODE*/
void playerVSplayer (int gameBoard1[][COLS], int gameBoard2[][COLS] ,int shipArray1[],int shipArray2[], FILE* resultFile);

#endif _PLAYER_H
