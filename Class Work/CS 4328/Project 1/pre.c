#include <stdio.h>
#include <string.h>

int main( )
{
    // Array of city values 
    char cityNames[21];
    int cityPops[10];

    // Array of inputted values 
    char nameInput[3];
    int *popInput;

    // Keep track of the number of inputted cities 
    int amountInput = 0;

    // For loop counters
    int i = 0;
    

    // Continue gathering inputs until EOF or max number of inputs 
    while( scanf("%*[^\n] %d", nameInput, &cityPops[i]) != EOF )
    {
        // Increment inputs 
        amountInput++;
        i++;

        printf("processing input: %d \n", amountInput);
        // Place inputs in array 
        strcat(cityNames, nameInput);
        //cityPops[amountInput-1] = popInput;
    } 

    printf("exit scanf \n");

    // display all pops that are greater than 10
    for(i = 0; i < amountInput; i++ )
    {
        printf("City pops: %d \n", cityPops[i]);
        if( cityPops[i] >= 10 )
            printf("%c %d",cityNames[i], cityPops[i+1]);
    }
    return 0;
}