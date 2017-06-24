#include <math.h>
#include <string.h>
#define totalShips 10
#include "board1.h"
//#include "files.h"
#include "player.h"

/*get the attack coordinate and attack the player board*/
void fireAt(int gameBoard[][COLS], int row, int col, int shipsArray[], FILE* resultFile)
{
   /*we always checks if the attack coordinate is out of board bounds*/
   if ((col<0 || col>9 ) || (row<0 || row>9))
   {
     fprintf(resultFile,"ILLEGAL ATTACK COORDINATE!\n");
     printf("ILLEGAL ATTACK COORDINATE!\n");
     return;
   }
   else
    {
       /*if player hit a ship then decrease the life of the ship and mark the cell as HIT*/
        if(gameBoard[row][col]>=ship1 && gameBoard[row][col]<=ship10)
        {
            shipsArray[gameBoard[row][col]-1]--;
            /*check if the ship destroyed*/
            if(shipsArray[gameBoard[row][col]-1]==0)
            {
                fprintf(resultFile,"YOU SANK BATTLESHIP %d!\n",gameBoard[row][col]);
                printf("YOU SANK BATTLESHIP %d!\n",gameBoard[row][col]);
                gameBoard[row][col]= HIT;
                return;
            }
            /*if player HIT a part of the ship*/
            fprintf(resultFile,"SHOT HIT!\n", gameBoard[row][col], shipsArray[gameBoard[row][col]-1]);
            printf("SHOT HIT!\n", gameBoard[row][col], shipsArray[gameBoard[row][col]-1]);
            gameBoard[row][col]= HIT;
        }
        /*if player take a shot and miss mark cell as MISS*/
        else if(gameBoard[row][col]==WATER)
        {
            fprintf(resultFile,"SHOOT MISS!\n");
            printf("SHOOT MISS!\n");
            gameBoard[row][col]= MISS;
        }
        /*optional if user want to check if space already hit*/
        else
        {
            fprintf(resultFile,"SHOOT ALREADY...\n");
            printf("SHOOT ALREADY...\n");
        }
   }
    return;
}

/*check if all the enemy ships were destroy - if so player WIN*/
void isWin(int gameBoard1[][COLS], int gameBoard2[][COLS] ,int shipsArray[],char player[], FILE* resultFile)
{
    int i;
    for(i=0;i<totalShips;i++)
    {
      if (shipsArray[i]!= 0)
        return;
    }
    fprintf(resultFile,"%s WIN THE GAME!\n", player);
    printf("%s WIN THE GAME!\n", player);
    showBoard(gameBoard1,1, resultFile);
    showBoard(gameBoard2,2, resultFile);
    exit(1);
}

/*run the player VS player game mode*/
void playerVSplayer(int playerOneBoard[][COLS],int playerTwoBoard[][COLS],int shipsArray1[],int shipsArray2[],FILE* resultFile)
{
    fflush(stdin);
    int turn = 0;
    int shipNumber=ship1;
    char col= NULL;
    int row = 0;
    Coor start_coor;
    Coor end_coor;


    printf("PLAYER 1 INITIALIZE SHIPS:\n");
    while(shipNumber<=totalShips)
    {
        fflush(stdin);
        printf("[SHIP %d]\n\n", shipNumber);
        printf("ENTER START COORDINATE:\n");
        scanf("%c%d", &col, &row);
        start_coor = convertToCoor(col,row);
        printf("ENTER END COORDINATE:\n");
        fflush(stdin);
        scanf("%c%d", &col, &row);
        end_coor = convertToCoor(col,row);
        markShip(playerOneBoard, shipNumber, shipsArray1, start_coor, end_coor,resultFile);
        shipNumber++;
    }

    shipNumber=ship1;

    printf("\nPLAYER 2 INITIALIZE SHIPS:\n");
    while(shipNumber<=totalShips)
    {
        fflush(stdin);
        printf("[SHIP %d]\n\n", shipNumber);
        printf("ENTER START COORDINATE:\n");
        scanf("%c%d", &col, &row);
        start_coor = convertToCoor(col,row);
        fflush(stdin);
        printf("ENTER END COORDINATE:\n");
        scanf("%c%d", &col, &row);
        end_coor = convertToCoor(col,row);
        markShip(playerTwoBoard, shipNumber, shipsArray2, start_coor, end_coor,resultFile);

        shipNumber++;
    }


    /*choose which player start randomly*/
    turn = rand()%2;
    while(1)
    {
        fflush(stdin);
        printf("PLAYER %d TURN...\n",turn+1);
        switch(turn)
        {
        /*player 1 turn*/
        case 0:
            fflush(stdin);
            printf("ENTER ATTACK COORDINATE:\n");
            scanf("%c%d", &col, &row);
            start_coor = convertToCoor(col,row);
            //printf("PLAYER 1: ");
            fireAt(playerTwoBoard, start_coor->row,start_coor->col,shipsArray2,resultFile);
            isWin(playerOneBoard,playerTwoBoard,shipsArray2,"PLAYER 1", resultFile);
            showBoard(playerTwoBoard,2, resultFile);
            break;
        case 1:
            fflush(stdin);
            printf("ENTER ATTACK COORDINATE:\n");
            scanf("%c%d", &col, &row);
            start_coor = convertToCoor(col,row);
            //printf("PLAYER 2: ");
            fireAt(playerOneBoard, start_coor->row,start_coor->col,shipsArray1,resultFile);
            isWin(playerOneBoard,playerTwoBoard,shipsArray1,"PLAYER 2", resultFile);
            showBoard(playerOneBoard,1, resultFile);
            break;
        }
        /*switch between players*/
        turn = (turn+1)%2;
    }
}
