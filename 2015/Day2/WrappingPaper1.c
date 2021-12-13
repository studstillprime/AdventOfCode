#include <stdio.h>
#include <stdlib.h>

//Initialize Variables
char currentChar;
char counter = 0;
char x;
char buffer[] = "00";
int wrappingPurchaseTotal = 0;

//WP = SA + min1*min2
int main(void)
{
    //Get some space to hold the datastream
    FILE* dataPOINTER = fopen("data", "r");

    //And make sure it exists lol or quit for sure
    if (!dataPOINTER)
    {
        printf("NULL POINTER\n");
        return 1;
    }

    //Look at one character at a time, unless it's the end
    while(currentChar != EOF)
    {
        counter++;
        int surfaceArea = 0;
        int measurements[3] = { 0 };
        int sideAreas[3] = { 0 };
        for (int i = 0; i < 3; i++)
        {
            currentChar = fgetc(dataPOINTER);
            buffer[0] = currentChar;
            currentChar = fgetc(dataPOINTER);
            if (currentChar == 'x' || currentChar == '\n')
            {
                measurements[i] = buffer[0] - '0';
            }
            else
            {
                buffer[1] = currentChar;
                measurements[i] = atoi(buffer);
                currentChar = fgetc(dataPOINTER);
            }
            printf("MEASUREMENT TAKEN %i: %i\n", i + 1, measurements[i]);
        }
        sideAreas[0] = measurements[0] * measurements[1];
        sideAreas[1] = measurements[0] * measurements[2];
        sideAreas[2] = measurements[1] * measurements[2];
        int smallestSide = sideAreas[0];
        for (int i = 0; i < 3; i++)
        {
            surfaceArea += 2 * sideAreas[i];
            if (sideAreas[i] < smallestSide)
            {
                smallestSide = sideAreas[i];
            }
        }
        wrappingPurchaseTotal += surfaceArea + smallestSide;
        printf("TOTAL %i\n", wrappingPurchaseTotal);
    }
    printf("\nANSWER: %i\n", wrappingPurchaseTotal);
}