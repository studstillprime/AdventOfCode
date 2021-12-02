#include <stdio.h>
#include <string.h>

//Initialize Variables
char currentChar;
int floorCounter = 0;

int main(void)
{
    //Get some space to hold the datastream
    FILE* dataPOINTER = fopen("data", "r");
    
    //And make sure it exists lol
    if (!dataPOINTER)
    {
        printf("NULL POINTER\n");
        return 1;
    }

    //Look at one character at a time, unless it's the end
    while((currentChar = fgetc(dataPOINTER)) != EOF)
    {
        //And if it is '(' then go up one floor
        if (currentChar == '(')
        {
            floorCounter++;
        }
        //Else go down one
        else
        {
            floorCounter--;
        }
        //Print the route, floor to floor
        printf("%i\n", floorCounter);
    }


}