#include "board1.h"
#include "player.h"
#include "files.h"
#define ROWS 10
#define COLS 10

/*read the coordinate from the file and transform it to int*/
Coor convertToCoor(char ch, int num)
{

    Coor coor = (Coor)malloc(sizeof(Coor));
    if(coor == NULL)
    {
        printf("ERROR!");
        return;
    }
    coor->col = ch - 'A';
    coor->row = num - 1;
    return coor;
}

/*read ships coordinate from file and send it to initialize on game board*/
void readInitFile (FILE* readFile,int gameBoard[][COLS], int shipsArray[], FILE* resultFile)
{
    ship shipNumber = ship1;
    char ch1,ch2,ch3;
    int num1,num2;
    char buff[250];

    while (!feof (readFile))
    {
        /*scan format from the file ex: C1-F1 */
        fscanf (readFile, "%c%d%c%c%d", &ch1,&num1,&ch2,&ch3,&num2);
        /*if line start with # or /n then skip to the next line*/
        if(ch1=='#' || ch1=='\n')
        {
            fgets(buff,500,readFile);
            continue;
        }
    /*sending the start and end coordinate to converting*/
    Coor start_coor = convertToCoor(ch1, num1);
    Coor end_coor = convertToCoor(ch3, num2);
    /*after we transform the coordinate data from the file we send the coordinate to mark ship on game board*/
    markShip(gameBoard, shipNumber, shipsArray, start_coor, end_coor, resultFile);
    /*count the ships number - it help us to know which ship we mark on the game board*/
    shipNumber++;
    /*go to the next line*/
    fgets(buff,1024,readFile);
    }
    return;
}

/*read and run the simulation file */
void runSimulation(FILE* simFile, int gameBoard1[][COLS],int gameBoard2[][COLS], int shipsArray1[], int shipsArray2[], FILE* resultFile)
{
    int num=0, row=0, col=0;
    char temp,temp2;
    char buff[1024];
    char cur_turn[50] = "0";
    char perv_turn[50] = "0";

    while (!feof (simFile))
    {
        fscanf (simFile, "%s%c", cur_turn,&temp);
        /*if line start with # or /n then skip it*/
        if(cur_turn[0]=='#' || cur_turn[0]=='\n')
        {
        fgets(buff,1024,simFile);
        continue;
        }
            /*get the attack coordinate from the simulation file*/
            fscanf (simFile, "%c%d",&temp2,&num);
            row = num-1;
            col = temp2-65;
        /*print the coordinate for tests*/
        /*printf("(%c%d)", temp2,num);*/

        /*check that players not play twice in a row. if so- move turn to next player*/
        if(strcmp(perv_turn, cur_turn)!=0)
        {
            /*player 1 attack*/
            if(strcmp(cur_turn,"PLAYER_1")==0)
            {
                fprintf(resultFile,"PLAYER 1: ");
                printf("PLAYER 1: ");
                fireAt(gameBoard2, row, col, shipsArray2, resultFile);
                isWin( gameBoard1, gameBoard2, shipsArray2, "PLAYER 1", resultFile);
            }
            /*player 2 attack*/
            else if(strcmp(cur_turn,"PLAYER_2")==0)
            {
                fprintf(resultFile,"PLAYER 2: ");
                printf("PLAYER 2: ");
                fireAt(gameBoard1, row, col, shipsArray1, resultFile);
                isWin( gameBoard1, gameBoard2, shipsArray1, "PLAYER 2", resultFile);
            }
            else if (strcmp(cur_turn,"PRINT_BOARD")==0)
            {
                showBoard(gameBoard1, 1, resultFile);
                showBoard(gameBoard2, 2, resultFile);
            }
        }

        else
        {
            fprintf(resultFile,"ILLEGAL MOVE!, turn goes to next player...\n");
            printf("ILLEGAL MOVE!, turn goes to next player...\n");
        }
        strcpy(perv_turn, cur_turn);
        /*go to the next line*/
        fgets(buff,1024,simFile);
    }
    return;
}

