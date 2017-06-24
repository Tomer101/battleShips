#ifndef _FILES_H
#define _FILES_H
#define ROWS 10
#define COLS 10

/*hold the coordinate for the ship placement*/
struct Coordinate
{
    int row;
    int col;
};

typedef struct Coordinate* Coor;

/*we use enum the mark every cell in the game board with ship number*/
typedef enum {ship1=1,ship2,ship3,ship4,ship5,ship6,ship7,ship8,ship9,ship10}ship;

/*the readInitFile function reads the initialize file for placing each player ships*/
void readInitFile (FILE* readFile,int gameBoard[][COLS], int shipsArray[], FILE* resultFile);

/*the runSimulation function reads the simulation file and manage the game commends and attacks of each player*/
void runSimulation (FILE* simFile, int gameBoard1[][COLS],int gameBoard2[][COLS], int shipsArray1[], int shipsArray2[], FILE* resultFile);

#endif _FILES_H
