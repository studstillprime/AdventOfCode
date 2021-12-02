#include <stdio.h>
#include <string.h>

//Initialize Variables
char currentChar;
char currentMovement;
int movementAim = 0;
int movementAmount = 0;
int depthTracker = 0;
int distanceTracker = 0;

int main(void)
{
    //Get some space to hold the datastream
    FILE* dataPOINTER = fopen("navigationCommands", "r");

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
        //amount of the movement
        currentChar = fgetc(dataPOINTER);
        movementAmount = currentChar - '0';

        //If it is a "forward" command, change the distance by that
        //amount, and the depth by the amount multiplied by the aim
        if (currentMovement == 'f')
        {
            distanceTracker += movementAmount;
            depthTracker += movementAmount * movementAim;
        }
        //Else if it is not "forward", just adjust the aim and don't move
        else if (currentMovement == 'd')
        {
            movementAim += movementAmount;
        }
        else if (currentMovement == 'u')
        {
            movementAim -= movementAmount;
        }
        //Print the full navigational command
        //and the current position of the sub
        printf("--> %c\n", currentChar);
        printf("Depth: %i\nDistance: %i\nAim: %i\n", depthTracker, distanceTracker, movementAim);
        currentChar = fgetc(dataPOINTER);
    }

    //Print the final location and multiply for the answer!
    printf("Final Location\nDepth: %i\nDistance: %i\n", depthTracker, distanceTracker);
    int answer = depthTracker * distanceTracker;
    printf("\nANSWER: %i\n", answer);
}