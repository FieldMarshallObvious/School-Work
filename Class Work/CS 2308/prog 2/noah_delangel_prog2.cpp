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

double MAX_MEMORY = 25;

struct Song
{
    string title,
           artist;
    float size;
};

/*======================= function prototypes ========================*/

int Count_songs ( ifstream &input_songs );
void Cleanup ( Song playlist[] );
bool Is_number( const string input);
int Rand_num_generator ( int chosen_songs[], int seed );
string Read_lines ( ifstream &input_songs );
void Remove_a_song( Song playlist[] );
void Run_ipod( Song playlist[], ifstream &input_songs );
void Show_playlist( Song playlist[] );
void Shuffle( Song playlist[] );
Song * Songs_array_mod ( ifstream &input_songs );
void Exit( Song playlist[] );

/*=====================================================================
 Function: main
 Description:
 Parameters:
 ======================================================================*/

int main ( )
{
    ifstream input_songs;
    
    input_songs.open( "input_song.txt" );
    
    //Checks if question bank file succesfully opened
    if( ! input_songs )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Songs file failed to open." << endl;
        
        return -1;
    }
    
    Songs_array_mod ( input_songs );
    
    input_songs.close();
    
    return 0;
}

/*=====================================================================
 Function: Count_songs
 Description:
 Parameters: ifstream input_songs
 ======================================================================*/
int Count_songs ( ifstream &input_songs )
{
    string cur_line;
    
    double mem_used,
           cntr = 0,
           num_songs = 0;
    
    while( mem_used <= MAX_MEMORY )
    {
        cntr++;
        cur_line = Read_lines( input_songs );
        
        
        if ( cur_line == " " )
        {
            break;
        }
        
        if( cntr == 3 )
        {
            if ( ( mem_used + stod( cur_line.c_str( ) ) ) <= MAX_MEMORY )
            {
                cntr = 0;
                num_songs++;
                mem_used+= stod( cur_line.c_str( ) );
            }
        }
    }
    
    return num_songs;
    
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
 Function: Is_number
 Description:
 Parameters: string input
 ======================================================================*/
bool Is_number( const string input )
{
    string::const_iterator it = input.begin();
    
    while( ( it != input.end( ) ) && isdigit(*it))
    {
        it++;
    }
    
    return ( ! input.empty() && ( it == input.end( ) ) );
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
            if( chosen_songs[cntr] == rand_int )
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
    string output = "",
           temp;
    
    //Reads lines from input file until it finds a non-blank line.
    //After the line has been determined to not be blank returns that line
    while ( getline( input_songs, temp ) && ( !input_songs.eof( ) ) )
    {
        output = temp;
        if ( ( strlen(temp.c_str( ) ) == 1 || strlen( temp.c_str( ) ) == 0 ) &&
             ( ! Is_number(temp) ) )
            continue;
        
        else
            break;
    }
    
    
    if ( ( strlen(temp.c_str( ) ) == 1 || strlen( temp.c_str( ) ) == 0 ) &&
        ( ! Is_number(temp) ) )
        output = " ";
    
    return output;
}


/*=====================================================================
 Function: Songs_array_mod
 Description:
 Parameters: ifstream input_songs
 ======================================================================*/
Song * Songs_array_mod ( ifstream &input_songs )
{
    //Varaibles declaration
    Song * new_array;
    string input;
    
    int size = Count_songs(input_songs);
    
    new_array = new Song[size];
    
    //reset file to the top of the stream
    input_songs.clear();
    
    input_songs.seekg(0, ios::beg );
    
    //Reads all songs into the array
    for( int i = 0; i < size; i++ )
    {
        new_array[i].title = Read_lines( input_songs );
                
        new_array[i].artist = Read_lines( input_songs );
        
        new_array[i].size = stod( Read_lines( input_songs ).c_str() );
    }
    
    for( int i = 0; i < size; i++)
    {
        cout << new_array[i].title << endl
             << new_array[i].artist << endl
             << new_array[i].size << endl;
    }
    
    return new_array;
}
