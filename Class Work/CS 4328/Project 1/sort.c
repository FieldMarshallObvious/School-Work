#include <stdio.h>
#include <string.h>

int main ( )
{
    // Array of city values 
    char cityNames[21];

    // Array of inputted values 
    char nameInput[3];

    // Keep track of the number of inputted cities 
    int amountInput = 0;
    
    // Loop counters
    int i = 0;
    int j = 0;

    // keep track of temp before sort 
    int temp = 0;

    // Continue gathering inputs until EOF or max number of inputs 
    while( scanf("%s", nameInput) != EOF )
    {
        // Increment inputs 
        amountInput++;

        // Place inputs in array 
        strcat(cityNames, nameInput);
    } 

    // Sort alphabetically through bubble sort 
    for( i = 0; i < (amountInput*2)-2; i+=2)
    {
        for( j = i; j < (amountInput*2)-2; j+=2 ) 
        {
            if( cityNames[j] > cityNames[j+2] )
            {
                // switch first letter
                temp = cityNames[j];
                cityNames[j] = cityNames[j+2];
                cityNames[j+2] = temp;

                // switch second letter
                temp = cityNames[j+1];
                cityNames[j+1] = cityNames[j+3];
                cityNames[j+3] = temp;
            }
        }
    }

    printf("\n\n");

    for( i = 0; i < amountInput*2; i+=2)
    {
        printf("%c%c \n", cityNames[i], cityNames[i+1]);
    }

    return 0;
}