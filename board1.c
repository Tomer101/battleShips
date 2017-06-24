#include <math.h>
#include <string.h>
#include "board1.h"
#include "files.h"

/*create a new blank game board*/
void createBoard(int gameBoard[][COLS])
{
    int row = 0, column = 0;
    for(row=0 ; row < ROWS ; row++ )
        {
        for(column=0 ; column < COLS ; column++)
            gameBoard[row][column]=WATER;
        }
    return 0;
}

/*print the game board :  HIT(X) ,miss(m) or WATER(-)*/
void showBoard (int board[][COLS], int playerNum, FILE* resultFile)
{
    int row,col;
    fprintf(resultFile,"\n*%c==========[P L A Y E R  %d]============*\n",201, playerNum);
    printf("\n%c==========[P L A Y E R  %d]============%c\n",201, playerNum, 187);

    fprintf(resultFile,"\n\t  A B C D E F G H I J\n\n");
    printf("\n\t  A B C D E F G H I J\n\n");
    for(row=0; row<ROWS; row++)
    {
        fprintf(resultFile,"%d\t| ",row+1);
        printf("%d\t%c ",row+1,186);
        for(col=0; col<COLS; col++)
        {
            /*if there are ship or water then mark cell as WATER (~)*/
            if(board[row][col]>=0 && board[row][col]<11)
            {
                fprintf(resultFile,"~ ");
                printf("%c ",247);
            }

            else if(board[row][col]==HIT)
            {
                fprintf(resultFile,"x ");
                printf("x ");
            }
            else if(board[row][col]==MISS)
            {
                fprintf(resultFile,"o ");
                printf("o ");
            }
        }
        fprintf(resultFile,"|\n");
        printf("%c\n",186);
    }
        fprintf(resultFile,"\n\n");
        printf("\n%c======================================%c\n",200, 188);
        return;
}

/*mark the ships on the game board (player cannot see the ship marking)*/
void markShip(int gameBoard[][COLS], int shipNumber, int shipsArray[], Coor start_coor, Coor end_coor, FILE* resultFile)
{
    int i = 0, shipSize = 0;
    int row = start_coor->row;
    int col = start_coor->col;

    /*initialize VERTICAL ships (fill ROW tile with ship num)*/
    if(start_coor->col == end_coor->col)
    {
        /*ship size tell us how many time to iterate for marking the ship on the board*/
        shipSize = abs((start_coor->row) - (end_coor->row))+1;
        //printf("ship number %d LIVES: %d\n", shipNumber, shipSize);
        for(i=0 ; i<shipSize; i++, row++)
        {
            /*check if ship place on another ship - if so EXIT*/
            if(gameBoard[row][col] != WATER)
            {
                fprintf(resultFile,"ILLEGAL SHIP PLACEMENT!\n EXIT THE PROGRAM...\n");
                printf("ILLEGAL SHIP PLACEMENT!\n EXIT THE PROGRAM...\n");
                exit(-1);
            }
            /*we mark the board cells by the ship number - this is how we know which ship we HIT*/
            gameBoard[row][col]= shipNumber;
        }
    }
    /*initialize HORIZONTAL ships (fill col tile with ship num)*/
    else if(start_coor->row == end_coor->row)
    {
        /*ship size tell us how many time to iterate for marking the ship on the board*/
        shipSize = abs((start_coor->col) - (end_coor->col))+1;
        //printf("ship number %d LIVES: %d\n", shipNumber, shipSize);
        for(i=0; i<shipSize; i++, col++)
        {
            /*check if ship place on another ship - if so EXIT*/
            if(gameBoard[row][col] != WATER)
            {
                fprintf(resultFile,"ILLEGAL SHIP PLACEMENT!\n EXIT THE PROGRAM...\n");
                printf("ILLEGAL SHIP PLACEMENT!\n EXIT THE PROGRAM...\n");
                exit(-1);
            }
            /*we mark the board cells by the ship number - this is how we know which ship we HIT*/
            gameBoard[row][col]= shipNumber;
        }
    }
    /*check if ship is diagonal. if true then illegal move*/
    else
    {
         fprintf(resultFile,"illegal ship coordinate at (%c%d,%c%d)!!!\n EXIT THE PROGRAM...",
                start_coor->col+65, start_coor->row+1, end_coor->col, end_coor->row);
        printf("illegal ship coordinate at (%c%d,%c%d)!!!\n EXIT THE PROGRAM...",
                start_coor->col+65, start_coor->row+1, end_coor->col, end_coor->row);
        exit(-1);
    }
    /*and we also save the ship size == ship live*/
    shipsArray[shipNumber-1] = shipSize;
    return;
}


