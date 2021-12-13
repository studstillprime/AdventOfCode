#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//Prototypes
void checkStringsInitial(void);
void clearBuffersInitial(void);
int checkDigit(char strings[1000][13], int digitToCheck, int length);

//Initialize Variables
const int bufferSize = 12;
char onesBuffer[1000][13];
char zeroesBuffer[1000][13];
char mostBuffer[1000][13];
char leastBuffer[1000][13];
char currentString[13] = { 0 };
char currentChar;
int onesBufferCount = 0;
int zeroesBufferCount = 0;
int mostBufferCount = 0;
int leastBufferCount = 0;
int checkMost = 1;
int counter = bufferSize;
int counter2 = 0;
int digitCounter = 0;
int oxygen = 0;
int carbon = 0;
int decimalFromBinary = 0;

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
        //On a per bit basis, count how many 1s there are
        fgets(currentString, 13, dataPOINTER);
        checkStringsInitial();
        currentChar = fgetc(dataPOINTER);
    }
    clearBuffersInitial();
    digitCounter++;
    while(!checkDigit(mostBuffer, digitCounter, mostBufferCount))
    {
        checkDigit(mostBuffer, digitCounter, mostBufferCount);
    }
    checkMost = 0;
    digitCounter = 1;
    while(!checkDigit(leastBuffer, digitCounter, leastBufferCount))
    {
        checkDigit(leastBuffer, digitCounter, leastBufferCount);
    }
    for (int i = 0; i < bufferSize; i++)
    {
        //Get the binary to decimal conversion value
        counter--;
        decimalFromBinary = pow(2, counter);
        if (mostBuffer[0][i] == 49)
        {
            oxygen += decimalFromBinary;
        }
        if (leastBuffer[0][i] == 49)
        {
            carbon += decimalFromBinary;
        }
    }
    printf("FINAL OXYGEN: %i\n", oxygen);
    printf("FINAL CARBON: %i\n", carbon);
    printf("ANSWER: %i\n", oxygen * carbon);
}
void checkStringsInitial(void)
{
    for (int i = digitCounter; i == digitCounter; i++)
        {
            if (currentString[i] == 49)
            {
                strcpy(onesBuffer[onesBufferCount], currentString);
                onesBufferCount++;
            }
            else
            {
                strcpy(zeroesBuffer[zeroesBufferCount], currentString);
                zeroesBufferCount++;
            }
        }
}
void clearBuffersInitial(void)
{
    if (onesBufferCount > zeroesBufferCount)
    {
        for (int i = 0; i < onesBufferCount; i++)
        {
            strcpy(mostBuffer[i], onesBuffer[i]);
            mostBufferCount = onesBufferCount;
        }
        for (int i = 0; i < zeroesBufferCount; i++)
        {
            strcpy(leastBuffer[i], zeroesBuffer[i]);
            leastBufferCount = zeroesBufferCount;
        }
    }
    else
    {
        for (int i = 0; i < zeroesBufferCount; i++)
        {
            strcpy(mostBuffer[i], zeroesBuffer[i]);
            mostBufferCount = zeroesBufferCount;
        }
        for (int i = 0; i < onesBufferCount; i++)
        {
            strcpy(leastBuffer[i], onesBuffer[i]);
            leastBufferCount = onesBufferCount;
        }
    }
    //Clear Ones and Zeroes
    memset(zeroesBuffer,0,sizeof(zeroesBuffer));
    memset(onesBuffer,0,sizeof(onesBuffer));
    onesBufferCount = 0;
    zeroesBufferCount = 0;
}
int checkDigit(char strings[1000][13], int digitToCheck, int length)
{
    if (length == 1)
    {
        if (checkMost)
        {
            printf("ANSWER OXYGEN: %s\n", strings[0]);
        }
        else
        {
            printf("ANSWER CARBON: %s\n", strings[0]);
        }
        return 1;
    }
    //Get Ones and Zeroes counts, and put the strings in
    //their respective arrays
    for (int i = 0; i < length; i++)
    {
        if (strings[i][digitToCheck] == 49)
        {
            strcpy(onesBuffer[onesBufferCount], strings[i]);
            onesBufferCount++;
        }
        else
        {
            strcpy(zeroesBuffer[zeroesBufferCount], strings[i]);
            zeroesBufferCount++;
        }
    }
    //If looking for most common
    if (checkMost)
    {
        if (onesBufferCount >= zeroesBufferCount)
        {
            for (int i = 0; i < onesBufferCount; i++)
            {
                strcpy(mostBuffer[i], onesBuffer[i]);
                mostBufferCount = onesBufferCount;
            }
        }
        else
        {
            for (int i = 0; i < zeroesBufferCount; i++)
            {
                strcpy(mostBuffer[i], zeroesBuffer[i]);
                mostBufferCount = zeroesBufferCount;
            }
        }
        memset(zeroesBuffer,0,sizeof(zeroesBuffer));
        memset(onesBuffer,0,sizeof(onesBuffer));
        onesBufferCount = 0;
        zeroesBufferCount = 0;
        digitCounter++;
        return 0;
    }
    //Or if looking for least common
    else 
    {
        if (onesBufferCount < zeroesBufferCount)
        {
            for (int i = 0; i < onesBufferCount; i++)
            {
                strcpy(leastBuffer[i], onesBuffer[i]);
                leastBufferCount = onesBufferCount;
            }
        }
        else
        {
            for (int i = 0; i < zeroesBufferCount; i++)
            {
                strcpy(leastBuffer[i], zeroesBuffer[i]);
                leastBufferCount = zeroesBufferCount;
            }
        }
        memset(zeroesBuffer,0,sizeof(zeroesBuffer));
        memset(onesBuffer,0,sizeof(onesBuffer));
        onesBufferCount = 0;
        zeroesBufferCount = 0;
        digitCounter++;
        return 0;
        checkDigit(leastBuffer, digitCounter, leastBufferCount);
    }
}