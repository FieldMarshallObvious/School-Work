#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function prototypes
void stringRandomizer ( char *refString, int stringSize );
int LRU ( char refString[], int refStringSize, char frameTable[],
           int numOfFrames );
int findLRU ( int time[], int frameTableSize );
int optimal( char refString[], int refStringSize, char frameTable[],
              int numOfFrames );
int predict( char refString[], int refStringSize, char frameTable[],
             int frameTableSize, int index );


int main ( ) 
{
    int numOfFrames = 0;
    int i, j;
    int LRUPageFaults, OptimalPageFaults;


    printf("Please enter number of frames: ");
    scanf("%d", &numOfFrames);

    // Create the frame table size
    char frameTable[numOfFrames];

    // Initialize the frame table to 
    for ( i = 0; i < numOfFrames; i++ )
    {
        frameTable[i] = ' ';
    }

    // Generate random ref string size 
    srand(time(0));
    int refStringSize = (rand() % (19 - 2 + 2)) + 2;
    char refString[refStringSize];



    printf("String size %d \n", refStringSize);

    // Create the random ref string
    stringRandomizer( &refString, refStringSize );

    // Output the ref string
    printf("refString ");
    for ( i = 0; i < refStringSize; i++ )
    {
        printf("%c", refString[i]);
    }
    printf("\n");

    printf("-------   Using LRU Replacement Algorithim   -------\n");
    // Use the LRU method to 
    // load the pages
    LRUPageFaults = LRU( refString, refStringSize, frameTable, numOfFrames );
    printf("-------    End LRU Replacement Algorithim    -------\n");


    // reset frame table
    for ( i = 0; i < numOfFrames; i++ )
    {
        frameTable[i] = ' ';
    }
    printf("------- Using Optimal Replacement Algorithim -------\n");

    // Use the LRU method to 
    // load the pages
    OptimalPageFaults = optimal( refString, refStringSize, frameTable, numOfFrames );
    printf("------- End Optimal Replacement Algorithim -------\n");


    // Output summary
    printf("-------   Replacement Algorithim Results   -------\n");
    printf("LRU Page Faults: %d\n", LRUPageFaults);
    printf("Optimal Page Faults: %d\n", OptimalPageFaults);
    printf("-------                End                 -------\n");




 

} 

void stringRandomizer ( char *refString, int stringSize ) 
{
    int i;

    // Generate random numbers for refString
    srand(time(0));

    // Generate the random number, convert it 
    // to a char then append it to the ref
    for( i = 0; i < stringSize; i++ )
    {
        int randNumber = (rand() % (5 - 1 + 1)) + 1;
        char randChar = randNumber + '0';
        refString[i] = randChar;
    }
}


int LRU ( char refString[], int refStringSize, char frameTable[],
           int numOfFrames )
{
    int LRUIndex = 0;
    int index = 0;
    int pageFaults = 0;
    int time[numOfFrames];
    int counter = 0;
    int i;
    int j;
    bool framesFull = false;

    // initalize time array
    for( i = 0; i < numOfFrames; i++ )
    {
        time[i] = 0;
    }

    

    // Load all of the frames into the 
    // into the 'memory' using LRU
    for ( i = 0; i < refStringSize; i++ )
    {
        // See if the page has already been loaded
        for ( j = 0; j < numOfFrames; j++ )
        {
            // If the current index is the same as the one we are 
            // lloking for break the loop
            if (  frameTable[j] == refString[i] )
            {
                printf("Page hit!\n");
                printf("%c is already loaded\n", refString[i]);

                counter++;
                time[j] = counter;


                break;
            }

            // If the current index is empty, load the page
            if ( frameTable[j] == ' ' )
            {
                counter++;
                frameTable[j] = refString[i];
                break;
            }
            // If we are at the end of the array, 
            // trigger the frames full flag
            if( j == numOfFrames - 1 )
            {
                framesFull = true;
            }
        }

        // If the frame table is full, replace a frame
        if ( framesFull == true )
        {
            // Find the LRU
            LRUIndex = findLRU(time, numOfFrames);

            counter++;
            time[j] = counter;
            time[LRUIndex] = counter;
            
            printf("Seg fault\n");
            printf("Replacing %c with %c\n", frameTable[LRUIndex], refString[i]);
            printf("Index that is being replaced %d\n", LRUIndex);

            frameTable[LRUIndex] = refString[i];

            pageFaults++;
        }

        // output the current frame table
        printf("[");
        for ( j = 0; j < numOfFrames; j++ )
        {
            if( j != numOfFrames - 1 )
                printf("%c, ", frameTable[j] );
            else
                printf("%c", frameTable[j] );
        }
        printf("]\n");

        printf("\n");

        // Reset loaded frame 
        framesFull = false; 
    }

    printf("Total Page Faults: %d\n", pageFaults);

    // Send the page fauls to the main class
    return pageFaults;
}

int findLRU ( int time[], int frameTableSize )
{
    int i, minimum = time[0], pos = 0;
 
   for (i = 1; i < frameTableSize; ++i)
   {
      if (time[i] < minimum)
      {
         minimum = time[i];
         pos = i;
      }
   }
 
   return pos;
}

int optimal( char refString[], int refStringSize, char frameTable[],
              int numOfFrames )
{
    int idexToReplace = 0;
    int pageFaults = 0;
    int i;
    int j;
    bool framesFull = false;


    

    // Load all of the frames into the 
    // into the 'memory' using LRU
    for ( i = 0; i < refStringSize; i++ )
    {
        // See if the page has already been loaded
        for ( j = 0; j < numOfFrames; j++ )
        {
            // If the current index is the same as the one we are 
            // lloking for break the loop
            if (  frameTable[j] == refString[i] )
            {
                printf("Page hit!\n");
                printf("%c is already loaded\n", refString[i]);

                break;
            }

            // If the current index is empty, load the page
            if ( frameTable[j] == ' ' )
            {
                frameTable[j] = refString[i];
                break;
            }
            // If we are at the end of the array, 
            // trigger the frames full flag
            if( j == numOfFrames - 1 )
            {
                framesFull = true;
            }
        }

        // If the frame table is full, replace a frame
        if ( framesFull == true )
        {
            // Find the LRU
            idexToReplace = predict( refString, refStringSize, frameTable,
                                     numOfFrames, i + 1 );
            
            printf("Seg fault\n");
            printf("Replacing %c with %c\n", frameTable[idexToReplace], refString[i]);
            printf("Index that is being replaced %d\n", idexToReplace);

            frameTable[idexToReplace] = refString[i];

            pageFaults++;
        }

        // output the current frame table
        printf("[");
        for ( j = 0; j < numOfFrames; j++ )
        {
            if( j != numOfFrames - 1 )
                printf("%c, ", frameTable[j] );
            else
                printf("%c", frameTable[j] );
        }
        printf("]\n");

        printf("\n");

        // Reset loaded frame 
        framesFull = false; 
    }

    printf("Total Page Faults: %d\n", pageFaults);

    // Send the page fauls to the main class
    return pageFaults;
}

int predict( char refString[], int refStringSize, char frameTable[],
             int frameTableSize, int index )
{
    int res = -1;
    int farthest = index;
    int i;

    for ( i = 0; i < frameTableSize; i++ )
    {

        int j;
        for( j = index; j < refStringSize; j++ )
        {
            if ( frameTable[i] == refString[j] )
            {
                // If there is a new farthest location
                // index keep note 
                if ( j > farthest ) 
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it
        if( j == refStringSize )
            return i;
    }

    //printf("res %d\n", res);

    // If all the frames were not used 
    // in the future then return 0 
    // If a frame is used in the future then return res
    return ( res == -1 ) ? 0 : res;
}