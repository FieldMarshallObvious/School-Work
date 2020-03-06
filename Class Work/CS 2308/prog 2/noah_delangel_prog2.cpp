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
#include <algorithm>


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
Song *  Remove_a_song( Song playlist[], string choice, int &size, int seed );
void Run_ipod( Song playlist[], ifstream &input_songs, int seed );
void Show_playlist( Song playlist[], int size );
void Shuffle( Song playlist[] );
Song * Songs_array_mod ( ifstream &input_songs, int &size );
void Exit( Song playlist[] );

/*=====================================================================
 Function: main
 Description:
 Parameters:
 ======================================================================*/

int main ( )
{
    Song playlist[1];
    
    ifstream input_songs;
    
    input_songs.open( "input_song.txt" );
    
    //Checks if question bank file succesfully opened
    if( ! input_songs )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Songs file failed to open." << endl;
        
        return -1;
    }
    
    
    Run_ipod( playlist, input_songs, 1001 );
    
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
 Function: Remove_a_song
 Description:
 Parameters: Song[] playlist, string choice, int size, int seed
 ======================================================================*/
Song * Remove_a_song( Song playlist[], string choice, int &size, int seed )
{
    //Variable declarations
    int index_to_remove,
        offset = 0;
    size-=1;
    
    Song temp[size];
    
    //convert choice to to upper
    cout << "The string lenght is " << strlen( choice.c_str( ) ) << endl;
    for( int i = 0; i < strlen( choice.c_str( ) ); i++ )
    {
        choice[i] = toupper( choice.c_str( )[i] );
        cout << "The new char is " << endl;
    }
    
    cout << "The choice is " << choice << endl;
    
    //Find the index that needs to be removed
    for( int i = 0; i < size + 1; i++ )
    {
        string cur_string = playlist[i].title;

        
        //convert current string to upper
        for( int j = 0; j < strlen( playlist[i].title.c_str( ) ); j++ )
        {
            cur_string[j] = toupper( playlist[i].title.c_str( )[j] );
        }
        
        if( choice == cur_string )
        {
            cout << "Found index!" << endl;
            index_to_remove = i;
            break;
        }
        
        cout << "The caps title is " << cur_string << endl;
    }
    
    cout << "The index to remove is " << index_to_remove << endl;
    //Remove the specific index
    for( int i = 0; i < size; i++ )
    {
        if( i != index_to_remove )
        {
            temp[i] = playlist[i + offset];
        }
        else
        {
            temp[i] = playlist[i + 1];
            cout << "The current index " << i << endl;
            cout << "Current temp item " << temp[i].title << endl;
            offset++;
        }
    }
    
    cout << "The temp playlist is " << endl;
    
    Show_playlist( temp, size );
    
    delete [] playlist;
    
    playlist = new Song [size];
    
    cout << "The new size is " << size << endl;
    cout << "copying new playlist" << endl;
    
    for( int i = 0; i < size; i++ )
    {
        cout << "Current temp item " << temp[i].title << endl;

        playlist[i] = temp[i];
    }
    
    Show_playlist( playlist, size );
    
    cout << "end of function" << endl;
    
    return playlist;
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
 Function: Run_ipod
 Description:
 Parameters: Song playlist[], ifstream &input_songs, int seed
 ======================================================================*/
void Run_ipod( Song playlist[], ifstream &input_songs, int seed )
{
    string choice = " ";
    int size;
    playlist = Songs_array_mod ( input_songs, size );
    
    while( choice != "5" &&
           choice != "EXIT")
    {
        cout << "   Welcome to My Ipod!" << endl
             << "Please choose your options:" << endl
             << "   1. Show the playlist" << endl
             << "   2. Remove a song" << endl
             << "   3. Cleanup my ipod" << endl
             << "   4. Shuffle the playlist" << endl
             << "   5. Exit" << endl;
        
        cout << "> ";
        getline(cin, choice);
        
        //convert choice to to upper
        for( int i = 0; i < strlen( choice.c_str( ) ); i++ )
        {
            choice[i] = toupper( choice.c_str( )[i] );
        }
        
        //Check to see what menu item the use selected
        if ( choice == "1" || choice == "SHOW THE PLAYLIST" )
        {
            Show_playlist( playlist, size );
        }
        
        else if ( choice == "2" || choice == "REMOVE A SONG" )
        {
            //Create a line space
            cout << endl;
            
            cout << "What song would you like to remove?" << endl;
            
            cout << "> ";
            getline(cin, choice);
            
            playlist = Remove_a_song(playlist, choice, size, seed);
            
            cout << "Passed function" << endl;
        }
        
        else if( choice == "3" || choice == "CLEANUP MY IPOD" )
        {
            Cleanup(playlist);
            
            cout << endl << endl;
        }
        
        else if ( choice == "4" || choice == "SHUFFLE THE PLAYLIST" )
        {
            
        }
        
        else if( choice == "5" || choice == "EXIT" )
        {
            Cleanup(playlist);
            
            cout << endl;
        }
        

    }
}

/*=====================================================================
 Function: Show_playlist
 Description:
 Parameters: Song[] playlist
 ======================================================================*/
void Show_playlist( Song * playlist, int size )
{
    for( int i = 0; i < size ; i++ )
    {
        cout << "Title: " << playlist[i].title << endl
             << "Author: " << playlist[i].artist << endl
             << "Memory Size: " << playlist[i].size << endl;
        
        cout << endl << endl;
    }
}

/*=====================================================================
 Function: Songs_array_mod
 Description:
 Parameters: ifstream input_songs, int size
 ======================================================================*/
Song * Songs_array_mod ( ifstream &input_songs, int &size )
{
    //Varaibles declaration
    Song * new_array;
    string input;
    
    size = Count_songs(input_songs);
    
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
    
    return new_array;
}
