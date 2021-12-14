#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Prototypes
int checkBingo(int board, int space);

//Initialize Variables
int balls[100] = { 31, 88, 35, 24, 46, 48, 95, 42, 18, 43, 71, 32, 92, 62, 97, 63, 50, 2, 60, 58, 74, 66, 15, 87, 57, 34, 14, 3, 54, 93, 75, 22, 45, 10, 56, 12, 83, 30, 8, 76, 1, 78, 82, 39, 98, 37, 19, 26, 81, 64, 55, 41, 16, 4, 72, 5, 52, 80, 84, 67, 21, 86, 23, 91, 0, 68, 36, 13, 44, 20, 69, 40, 90, 96, 27, 77, 38, 49, 94, 47, 9, 65, 28, 59, 79, 6, 29, 61, 53, 11, 17, 73, 99, 25, 89, 51, 7, 33, 85, 70 };
int boards[100][25];
int bingoCount[100] = { 0 };
int bingoBoards = 0;
char spaceBuffer[2];
char currentChar;
int answer = 0;

int main(void)
{
    //Get some space to hold the datastream
    FILE* input = fopen("data", "r");

    //And make sure it exists lol or quit for sure
    if (!input)
    {
        printf("NULL POINTER\n");
        return 1;
    }

    //Look at one character at a time, unless it's the end
    while(currentChar != EOF)
    {
        //For each board
        for (int boardNumber = 0; boardNumber < 100; boardNumber++)
        {
            //Fill all the spaces on it
            for (int spaceNumber = 0; spaceNumber < 25; spaceNumber++)
            {
                //By getting the numbers one digit at a time
                currentChar = fgetc(input);
                if (currentChar == ' ' || currentChar == '\n')
                {
                    currentChar = fgetc(input);
                }
                spaceBuffer[0] = currentChar;
                currentChar = fgetc(input);
                spaceBuffer[1] = currentChar;
                //And convert the digits into an integer
                int spaceValue = atoi(spaceBuffer);
                //to finally store on the board's space
                boards[boardNumber][spaceNumber] = spaceValue;
            }
            currentChar = fgetc(input);
        }
    }

    //For each ball picked
    for (int ballNumber = 0; ballNumber < 100; ballNumber++)
    {
        int ball = balls[ballNumber];
        //Check each board
        for (int boardNumber = 0; boardNumber < 100; boardNumber++)
        {
            //to see if it matches any of the numbers
            for (int spaceNumber = 0; spaceNumber < 25; spaceNumber++)
            {
                if (ball == boards[boardNumber][spaceNumber])
                {
                    //If it does match, log that
                    boards[boardNumber][spaceNumber] = 100;
                    printf("MATCH FOUND FOR\nBALL %i: %i\nBOARD: %i\nSPACE: %i\n", ballNumber, ball, boardNumber, spaceNumber);
                    //And check if it makes a bingo
                    if (checkBingo(boardNumber, spaceNumber))
                    {
                        //If it does, log that and the board number
                        //that got the bingo
                        printf("BINGO BINGO BINGO\n BINGO BINGO BINGO\n  BINGO BINGO BINGO\n   BINGO BINGO BINGO\n    BINGO BINGO BINGO\n");
                        if (!bingoCount[boardNumber])
                        {
                            bingoBoards++;
                        }
                        bingoCount[boardNumber] = 1;
                        //If it's the last board than thats it!
                        if (bingoBoards == 100)
                        {
                            for (int i = 0; i < 25; i++)
                            {
                                if (boards[boardNumber][i] != 100)
                                {
                                    answer += boards[boardNumber][i];
                                }
                            }
                            printf("Sum: %i\n", answer);
                            printf("Multiplied by Winning Ball: %i\n", ball);
                            answer *= ball;
                            printf("Answer: %i\n", answer);
                            return 1;
                        }
                    }
                    }
            }
        }
    }
}
int checkBingo(int board, int space)
{
    //Rows
    switch(space)
    {
        case 0 :
        case 1 :
        case 2 :
        case 3 :
        case 4 :
            if (boards[board][0] == 100 && boards[board][1] == 100 && boards[board][2] == 100 && boards[board][3] == 100 && boards[board][4] == 100)
                {
                    printf("Row Bingo On Board: %i\n", board);
                    return 1;
                }
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
            if (boards[board][5] == 100 && boards[board][6] == 100 && boards[board][7] == 100 && boards[board][8] == 100 && boards[board][9] == 100)
                {
                    printf("Row Bingo On Board: %i\n", board);
                    return 1;
                }
        case 10 :
        case 11 :
        case 12 :
        case 13 :
        case 14 :
            if (boards[board][10] == 100 && boards[board][11] == 100 && boards[board][12] == 100 && boards[board][13] == 100 && boards[board][14] == 100)
                {
                    printf("Row Bingo On Board: %i\n", board);
                    return 1;
                }
        case 15 :
        case 16 :
        case 17 :
        case 18 :
        case 19 :
            if (boards[board][15] == 100 && boards[board][16] == 100 && boards[board][17] == 100 && boards[board][18] == 100 && boards[board][19] == 100)
                {
                    printf("Row Bingo On Board: %i\n", board);
                    return 1;
                }
        case 20 :
        case 21 :
        case 22 :
        case 23 :
        case 24 :
            if (boards[board][20] == 100 && boards[board][21] == 100 && boards[board][22] == 100 && boards[board][23] == 100 && boards[board][24] == 100)
                {
                    printf("Row Bingo On Board: %i\n", board);
                    return 1;
                }
      default :
         printf("No Row Bingo\n" );
   }
    //Columns
    switch(space)
    {
        case 0 :
        case 5 :
        case 10 :
        case 15 :
        case 20 :
            if (boards[board][0] == 100 && boards[board][5] == 100 && boards[board][10] == 100 && boards[board][15] == 100 && boards[board][20] == 100)
                {
                    printf("Column Bingo On Board: %i\n", board);
                }
            break;
        case 1 :
        case 6 :
        case 11 :
        case 16 :
        case 21 :
            if (boards[board][1] == 100 && boards[board][6] == 100 && boards[board][11] == 100 && boards[board][16] == 100 && boards[board][21] == 100)
                {
                    printf("Column Bingo On Board: %i\n", board);
                    return 1;
                }
        case 2 :
        case 7 :
        case 12 :
        case 17 :
        case 22 :
            if (boards[board][2] == 100 && boards[board][7] == 100 && boards[board][12] == 100 && boards[board][17] == 100 && boards[board][22] == 100)
                {
                    printf("Column Bingo On Board: %i\n", board);
                    return 1;
                }
        case 3 :
        case 8 :
        case 13 :
        case 18 :
        case 23 :
            if (boards[board][3] == 100 && boards[board][8] == 100 && boards[board][13] == 100 && boards[board][18] == 100 && boards[board][23] == 100)
                {
                    printf("Column Bingo On Board: %i\n", board);
                    return 1;
                }
        case 4 :
        case 9 :
        case 14 :
        case 19 :
        case 24 :
            if (boards[board][4] == 100 && boards[board][9] == 100 && boards[board][14] == 100 && boards[board][19] == 100 && boards[board][24] == 100)
                {
                    printf("Column Bingo On Board: %i\n", board);
                    return 1;
                }
      default :
         printf("No Column Bingo\n" );
   }
   return 0;
}