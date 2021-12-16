#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Man this one is done bad lol. I was just experimenting with some things
//So anyone reading this knows lmao this is for educational research.
//Prototypes
int max(int x, int y);
int min(int x, int y);

//Initialize Variables
char currentChar;
char buffer[3];
int oceanFloor[999][999] = { 0 };
int coordinates[500][4];
int coordinateCount = 0;
int ventCount = 0;
int answer = 0;

int main(void)
{
    //Get some space to hold the datastream
    FILE* input = fopen("data2", "r");

    //And make sure it exists lol or quit for sure
    if (!input)
    {
        printf("NULL POINTER\n");
        return 1;
    }
    //Look at one character at a time, unless it's the end
    currentChar = fgetc(input);
    while(currentChar != EOF)
    {
        int bufferCount = 0;
        int location = 0;
        //Get Integer Coordinate
        while (currentChar != '\n' && currentChar != EOF)
        {
            buffer[bufferCount] = currentChar;
            bufferCount++;
            currentChar = fgetc(input);
        }
        //And adjust if less than 3 digits.
        if (bufferCount != 3)
        {
            buffer[2] = buffer[1];
            buffer[1] = buffer[0];
            buffer[0] = '0';
        }
        location = atoi(buffer);
        //Store it in the vents array.
        coordinates[ventCount][coordinateCount] = location;
        printf("LOCATION %i\n", location);
        printf("Vent Count: %i\n", ventCount);
        coordinateCount++;
        if (coordinateCount == 4)
        {
            ventCount++;
            coordinateCount = 0;
        }
        currentChar = fgetc(input);
    }
    fclose(input);
    //Process coordinate array into ocean floor locations
    for (int i = 0; i < 500; i++)
    {
        if (coordinates[i][0] == coordinates[i][2])
        {
            printf("X=X, %i = %i\n", coordinates[i][0], coordinates[i][2]);
            if (coordinates[i][1] > coordinates[i][3])
            {
                int temp;
                temp = coordinates[i][3];
                coordinates[i][3] = coordinates[i][1];
                coordinates[i][1] = temp;
            }
            for (int length = coordinates[i][1]; length < coordinates[i][3] + 1; length++)
            {
                printf("LOGGING--> X: %i, Y: %i\n", coordinates[i][0], length);
                oceanFloor[coordinates[i][0]][length]++;
            }
        }
        else if(coordinates[i][1] == coordinates[i][3])
        {
            if (coordinates[i][0] > coordinates[i][2])
            {
                int temp;
                temp = coordinates[i][2];
                coordinates[i][2] = coordinates[i][0];
                coordinates[i][0] = temp;
            }
            printf("Y=Y, %i = %i\n", coordinates[i][1], coordinates[i][3]);
            for (int length = coordinates[i][0]; length < coordinates[i][2] + 1; length++)
            {
                printf("LOGGING--> X: %i, Y: %i\n", length, coordinates[i][1]);
                oceanFloor[length][coordinates[i][1]]++;
            }
        }
        else
        {
            float slope = (coordinates[i][3] - coordinates[i][1]) / (coordinates[i][2] - coordinates[i][0]) * 1.0;
            printf("SLOPE = %f\n", slope);
            if (slope == 1.0 || slope == -1.0)
            {
                int maxX = max(coordinates[i][0], coordinates[i][2]);
                int maxY = max(coordinates[i][1], coordinates[i][3]);
                int minX = min(coordinates[i][0], coordinates[i][2]);
                int minY = min(coordinates[i][1], coordinates[i][3]);
                printf("MAX - X\n\n%i\n\n", maxX);
                printf("MAX - Y\n\n%i\n\n", maxY);
                int height = 0;
                if (slope < 0)
                {
                    height = maxY;
                    printf("X,Y -> X,Y %i,%i -> %i,%i\n", minX, maxY, maxX, minY);
                    for (int length = minX; length < maxX + 1; length++)
                    {
                        printf("LOGGING--> X,Y -> X,Y %i,%i -> %i,%i\n", length, height, maxX, maxY);
                        oceanFloor[length][height]++;
                        height--;
                    }
                 }
                else
                {
                    height = minY;
                    printf("X,Y -> X,Y %i,%i -> %i,%i\n", minX, minY, maxX, maxY);
                    for (int length = minX; length < maxX + 1; length++)
                    {
                        printf("LOGGING--> X,Y -> X,Y %i,%i -> %i,%i\n", length, height, maxX, maxY);
                        oceanFloor[length][height]++;
                        height++;
                    }
                }
            }

        }
    }
    for (int x = 0; x < 999; x++)
    {
        for (int y = 0; y < 999; y++)
        {
            if (oceanFloor[x][y] > 1)
            {
                printf("VENT > 1 ---> %i,%i\n", x, y);
                answer++;
            }
        }
    }
    printf("ANSWER: %i\n", answer);
    return 1;
}
int max(int x, int y)
{
    int maxValue = x > y ? x : y;
    return maxValue;
}
int min(int x, int y)
{
    int minValue = x < y ? x : y;
    return minValue;
}