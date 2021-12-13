#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Initialize Variables
const int bufferSize = 12;
const int countMetric = 500;
char currentChar;
int counter = bufferSize;
char x;
int gamma = 0;
int epsilon = 0;
int buffer[bufferSize] = { 0 };
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
        for (int i = 0; i < bufferSize; i++)
        {
            //On a per bit basis, count how many 1s there are
            currentChar = fgetc(dataPOINTER);
            if (currentChar == '1')
            {
                buffer[i] += 1;
            }

        }
        currentChar = fgetc(dataPOINTER);
    }
    for (int i = 0; i < bufferSize; i++)
    {
        //Get the binary to decimal conversion value
        counter--;
        decimalFromBinary = pow(2, counter);

        //If there are more 1s, this is a gamma
        if (buffer[i] > countMetric)
        {
            gamma += decimalFromBinary;
        }
        //else, this is an epsilon value
        else
        {
            epsilon += decimalFromBinary;
        }
    }
    printf("FINAL GAMMA: %i\n", gamma);
    printf("FINAL EPSILON: %i\n", epsilon);
    printf("ANSWER: %i\n", gamma * epsilon);
}