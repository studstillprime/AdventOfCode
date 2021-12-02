#include <stdio.h>
#include <string.h>

//Initialize Variables
char currentChar;
char currentMovement;
int movementAmount = 0;
int depthTracker = 0;
int distanceTracker = 0;

int main(void)
{
    //Get some space to hold the datastream
    FILE* dataPOINTER = fopen("data2", "r");

    //And make sure it exists lol or quit for sure
    if (!dataPOINTER)
    {
        printf("NULL POINTER\n");
        return 1;
    }

    //Look at one character at a time, unless it's the end
    while((currentChar = fgetc(dataPOINTER)) != EOF)
    {
        //Identify the direction by the first letter
        //"Forward" or "Up" or "Down"
        currentMovement = currentChar;

        //Capitalize the first letter for humans
        printf("%c", currentChar - 32);
        while(currentChar != ' ')
        {
            //and print the rest of the direction
            currentChar = fgetc(dataPOINTER);
            printf("%c", currentChar);
        }

        //Then, when there is a space, get the
        //amount of the movement and add it
        //to either the depth or the distance.
        currentChar = fgetc(dataPOINTER);
        movementAmount = currentChar - '0';
        if (currentMovement == 'f')
        {
            distanceTracker += movementAmount;;
        }
        else if (currentMovement == 'd')
        {
            depthTracker += movementAmount;
        }
        else if (currentMovement == 'u')
        {
            depthTracker -= movementAmount;
        }
        
        //Print the full navigational command
        //and the current position of the sub
        printf("--> %c\n", currentChar);
        printf("Depth: %i\nDistance: %i\n", depthTracker, distanceTracker);
        currentChar = fgetc(dataPOINTER);
    }

    //Print the final location and multiply for the answer!
    printf("Final Location\nDepth: %i\nDistance: %i\n", depthTracker, distanceTracker);
    int answer = depthTracker * distanceTracker;
    printf("\nANSWER: %i\n", answer);
}