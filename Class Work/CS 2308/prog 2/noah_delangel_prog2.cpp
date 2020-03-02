/*=====================================================================
 Program: Program 2
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 3/10/20
 Description:
 Input: input_song.txt
 Output:
 Compilation instructions: Usage:
 Modifications:
 Date Comment:
 ---- -----------------------------------------------
 ======================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>


/*====================== global symbolic constants ===================*/

using namespace std;


struct Song
{
    string title,
           artist;
    float size;
};

/*======================= function prototypes ========================*/

int Count_songs ( ifstream &input_songs );
void Cleanup ( Song playlist[] );
int Rand_num_generator ( int chosen_songs[], int seed );
string Read_lines ( ifstream &input_songs );
Song * Read_songs ( ifstream &input_songs );
void Remove_a_song( Song playlist[] );
void Run_ipod( Song playlist[], ifstream &input_songs );
void Show_playlist( Song playlist[] );
void Shuffle( Song playlist[] );
void Exit( Song playlist[] );

/*=====================================================================
 Function: main
 Description:
 Parameters:
 ======================================================================*/

int main ( )
{
    return 0;
}

/*=====================================================================
 Function: Cleanup
 Description:
 Parameters: Song[] playlist
 ======================================================================*/
void Cleanup( Song playlist[] )
{
    //Clears up dynamic memory space
    delete [] playlist;
}

/*=====================================================================
 Function: Rand_num_generator
 Description: Generates a random index that is unique from all indexes
              previsouly chosen. Then returns that integer.
 Parameters: int[] chosen_songs, int seed, int max
 ======================================================================*/
int Rand_num_generator ( int chosen_songs[], int seed, int max )
{
    //Variable declarations
    bool unique_item = false;
    
    int rand_int;
    
    //Initializes random time to system time
    srand( seed );
    
    //Finds random number between max and 1
    //Also ensures that the random number has not already been selected
    do {
        unique_item = true;
        
        rand_int = rand( ) % ( max-1 ) + 0;
        
        //Checks for every item in array to make sure it has not already been
        //selected
        for( int cntr = 0; cntr < max; cntr++ )
        {
            //If the index exists it sets the boolean value to repeat array
            //then breaks out of the for loop.
            if( chosen_questions[cntr] == rand_int )
            {
                unique_item = false;
                break;
            }
            
        }
        
        if ( unique_item == true )
            break;
        
    } while( unique_item == false );
    
    return rand_int;
}

/*=====================================================================
 Function: Read_lines
 Description:
 Parameters: ifstream input_songs
 ======================================================================*/
string Read_lines ( ifstream &input_songs )
{
    //Variable declarations
    string output = "";
    
    //Reads lines from input file until it finds a non-blank line.
    //After the line has been determined to not be blank returns that line
    while ( getline( input_file, output ) && ( !input_file.eof( ) ) )
    {
        if ( strlen(output.c_str( ) ) == 1 || strlen( output.c_str( ) ) == 0 )
            continue;
        
        else
            break;
    }
    
    return output;
}

Song * Read_Songs
