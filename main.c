#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#define ROWS 10
#define COLS 10
#define totalShips 10

void nameCredits()
{
    int a;
    for(a=1; a<=43; a++){
        printf("*");
    }
    printf("\n\n   TOMER 203289673 & SHOHAM 205530157 \n\n");
    for(a=1; a<=43; a++){
        printf("*");
    }
        printf("\n");
    return;
}

void showMenu()
{
    printf("\n\n\n\tM E N U");
    printf("\n- - - - - - - - - - - - - - -\n");
    printf("PRESS [1] run simulation file...\nPRESS [2] play 1 VS 1\nPRESS [0] EXIT!...\n");
    printf("- - - - - - - - - - - - - - -\n");
    return;
}

void printTitle(FILE* file)
{
fprintf(file,"___  ____ ___ ___ _    ____    ____ _  _ _ ___  ____\n");
fprintf(file,"|__] |__|  |   |  |    |___    [__  |__| | |__] [__ \n");
fprintf(file,"|__] |  |  |   |  |___ |___    ___] |  | | |    ___]\n");
fprintf(file,"=====================================================\n");
}

          /*-------------/
         /    M A I N   /
        /-------------*/

int main(int argc, char *argv[])
{
    int choice = 0;
    /* initialize player one and two game board*/
    int playerOneBoard[ROWS][COLS];
    createBoard (playerOneBoard);
    int playerTwoBoard[ROWS][COLS];
    createBoard (playerTwoBoard);

    /*initialize the players ships navy
    in each index holding the ship health*/
    int shipsArray1[totalShips] = {0};
    int shipsArray2[totalShips] = {0};

    FILE* initP1file = fopen(argv[1],"r");
    FILE* initP2file = fopen(argv[2],"r");
    FILE* simFile = fopen(argv[3],"r");
    FILE* resultFile = fopen(argv[4],"w");
    if(initP1file==NULL || initP2file==NULL || simFile==NULL || resultFile==NULL)
    {
        printf("File not found...\n");
        return 0;
    }

    nameCredits();
    showMenu();
    printTitle(resultFile);
    scanf("%d", &choice);
    fflush(stdin);
    switch(choice)
        {
        /*run the game configuration files*/
        case 1:
            readInitFile(initP1file, playerOneBoard, shipsArray1, resultFile);
            readInitFile(initP2file, playerTwoBoard, shipsArray2, resultFile);
            runSimulation(simFile, playerOneBoard, playerTwoBoard, shipsArray1, shipsArray2, resultFile);
            showBoard(playerOneBoard, 1, resultFile);
            showBoard(playerTwoBoard, 2, resultFile);
            fclose(resultFile);
            break;
        /*player VS player*/
        case 2:
            fclose(resultFile);/*we dont want to print to the file in this mode*/
            playerVSplayer(playerOneBoard, playerTwoBoard, shipsArray1, shipsArray2,resultFile);
            break;
        case 0:
            printf("EXIT THE PROGRAM...");
            break;
        default:
            printf("Select again...\n");
            break;
        }
    fclose(initP1file);
    fclose(initP2file);
    fclose(simFile);
    return;
}
//V7
