/*=====================================================================
 Program: Program 2
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 3/10/20
 Description: A program that simulate an ipod player, by taking songs from a
              text file passed by the command line. The program determines
              the number of songs from the text file. The program can display
              the current playlist, remove a song, cleanup dynamically allocated
              memory, and shuffle the playlist.
 Input: input_song.txt
 Output:
         (Main menu)(to console)
            Welcome to My Ipod!
        Please choose your options:
            1. Show the playlist
            2. Remove a song
            3. Cleanup my ipod
            4. Shuffle the playlist
            5. Exit
        >

        (Playlist)(to console)
        Title: Come out and Play!!
        Author: Offspring
        Memory Size: 1

    Title:  Smells like the Teen Spirit
    Author: Nirvana
    Memory Size: 0.45

 Compilation instructions: All that is needed to do compile the program is to
                           run the g++ command with the file name. C++11 is not
                           required, thus you do not  need it compile the
                           program using C++11. You can change the name of the
                           output file, as this should have no effect. An
                           example of theg++ command is given below:
                           g++ noah_delangel_prog1.cpp
 Usage: In order to run the program you must execute in the output file in the
        order listed below:
        ./<output file> <songs.txt> <int seed>
 Modifications:
 Date Comment: 3/7/20
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
Song * Cleanup ( Song playlist[] );
bool Is_number( const string input);
int Rand_num_generator ( int chosen_songs[], int seed );
string Read_lines ( ifstream &input_songs );
Song * Remove_a_song( Song playlist[], string choice, int &size );
void Run_ipod( Song playlist[], ifstream &input_songs, int seed );
void Show_playlist( Song playlist[], int size );
Song * Shuffle( Song playlist[], int seed, int size );
Song * Songs_array_mod ( ifstream &input_songs, int &size );
void Exit( Song playlist[] );

/*=====================================================================
 Function: main
 Description: Ensure proper number of arguements was given to program
              at run time. Also ensure all fstream objects are
              initiliazed correctly. Then passes neccesary vars to
              Run_ipod function.
 Parameters: int argc, char[] argv
 ======================================================================*/

int main ( int argc, char * argv [ ] )
{
    //variable declarations
    Song playlist[1];

    string file_name;

    ifstream input_songs;

    int seed;


    //Checking to see if  number of arguments is correct
    if( argc != 3 )
    {
        cout << "***Program Terminated.***" << endl
        << "Invalid args." << endl
        << "This program requires the following arguements" << endl
        << " <songs file>.txt, int seed" << endl;

        return -1;
    }

    //Assign command line inputs to program variables
    file_name = argv[1];
    seed = atoi( argv[2] );

    input_songs.open( file_name.c_str ( ) );

    //Checks if question bank file succesfully opened
    if( ! input_songs )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Songs file failed to open." << endl;

        return -1;
    }


    Run_ipod( playlist, input_songs, seed );

    input_songs.close( );

    return 0;
}

/*=====================================================================
 Function: Count_songs
 Description: Reads the number of songs that can be entered into the
              iPod without exceeding the iPod's maxium allowed data.
              It then returns this number.
 Parameters: ifstream input_songs
 ======================================================================*/
int Count_songs ( ifstream &input_songs )
{
    //Variable declarations
    string cur_line;

    double mem_used,
           cntr = 0,
           num_songs = 0;

    //Counts number of songs read in, until
    //the max memory hass been reached.
    while( mem_used <= MAX_MEMORY )
    {
        //Creates end pointer for strtod function
        //call.
        char * end;

        cntr++;

        cur_line = Read_lines( input_songs );

        //If there is a blank line passed then the
        //program has reached the end of the file
        if ( cur_line == " " )
        {
            break;
        }

        //If the number of non-blank lines has
        //reached 3 then it is a song.
        if( cntr == 3 )
        {
            //If the memory of the new song plus the memory used
            //is less than the total memory available. Add the song.
            if ( ( mem_used + strtod( cur_line.c_str( ), &end ) ) <=
                 MAX_MEMORY )
            {
                cntr = 0;
                num_songs++;
                mem_used+= strtod( cur_line.c_str( ), &end );
            }
        }
    }

    return num_songs;

}

/*=====================================================================
 Function: Cleanup
 Description: Clears up all dynamic memory, and removes all items from
              the array.
 Parameters: Song[] playlist
 ======================================================================*/
Song * Cleanup( Song * playlist )
{
    //Clears up dynamic memory space
    delete [ ] playlist;

    //set the playlist pointer to NULL
    playlist = NULL;

    return playlist;
}

/*=====================================================================
 Function: Is_number
 Description: Checks to see if the inputed string is a number. Returns
              with a true boolean if the string is an int.
 Parameters: string input
 ======================================================================*/
bool Is_number( const string input )
{
    //Assign an iterator to the passed string
    string::const_iterator it = input.begin( );

    //Go through the iterator, as long the current iterator
    //value is a digit and it has not reached the end of
    //iterator.
    while( ( it != input.end( ) ) && isdigit( *it ) )
    {
        //increment the pointer to the next iterator
        //value.
        it++;
    }

    //return the value of if the iterator reached the end.
    return ( ! input.empty( ) && ( it == input.end( ) ) );
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

        rand_int = rand( ) % ( max ) + 0;

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

        //If the loop has not found a duplicate value
        //break the loop.
        if ( unique_item == true )
            break;

    } while( unique_item == false );

    return rand_int;
}

/*=====================================================================
 Function: Remove_a_song
 Description: Attempts to find the song the user wants to remove. If the
              function cannot find the song the user wants to remove it
              displays an error message indicating this. If the song is
              found the function removes the song from the passed array,
              then returns the new modified array.
 Parameters: Song[] playlist, string choice, int size
 ======================================================================*/
Song * Remove_a_song( Song playlist[], string choice, int &size  )
{
    //Variable declarations
    int index_to_remove = -1,
        offset = 0;
    size-=1;

    Song temp[size];

    //convert choice to to upper
    for( int i = 0; i < strlen( choice.c_str( ) ); i++ )
    {
        choice[i] = toupper( choice.c_str( )[i] );
    }


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
            index_to_remove = i;
            break;
        }
    }

    //Check to see if the users requested song was found
    if( index_to_remove == -1 )
    {
        cout << endl;

        cout << "The song you were looking for was not found" << endl;

        return playlist;
    }

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
            offset++;
        }
    }

    //Removes old items in array
    delete [] playlist;

    //Creates array with new size
    playlist = new Song [size];

    //Assings each element to new order from
    //temp.
    for( int i = 0; i < size; i++ )
    {
        playlist[i] = temp[i];
    }

    return playlist;
}

/*=====================================================================
 Function: Read_lines
 Description: Reads lines in the given input file stream, until it finds
               a non-blank line. After finding a non-blank line it
               it returns that line.
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
         ( ! Is_number( temp ) ) )
        output = " ";

    return output;
}

/*=====================================================================
 Function: Run_ipod
 Description: Runs all the methods, and choices, for iPod functionality.
 Parameters: Song playlist[], ifstream &input_songs, int seed
 ======================================================================*/
void Run_ipod( Song playlist[], ifstream &input_songs, int seed )
{
    string choice = " ";
    int size;
    playlist = Songs_array_mod ( input_songs, size );

    while( choice != "5" &&
           choice != "EXIT" )
    {
        cout << "   Welcome to My Ipod!" << endl
             << "Please choose your options:" << endl
             << "   1. Show the playlist" << endl
             << "   2. Remove a song" << endl
             << "   3. Cleanup my ipod" << endl
             << "   4. Shuffle the playlist" << endl
             << "   5. Exit" << endl;

        //Grabs the menu item the user wants to select
        cout << "> ";
        getline( cin, choice );

        cout << endl;

        //convert choice to to upper
        for( int i = 0; i < strlen( choice.c_str( ) ); i++ )
        {
            choice[i] = toupper( choice.c_str( )[i] );
        }

        //The following if branches determine what menu item
        //the user selected.
        if ( choice == "1" || choice == "SHOW THE PLAYLIST" )
        {
            Show_playlist( playlist, size );

            cout << endl;
        }

        else if ( choice == "2" || choice == "REMOVE A SONG" )
        {
            cout << endl;

            //Grabs the song the user wants to remove
            cout << "What song would you like to remove?" << endl;

            cout << "> ";
            getline( cin, choice );

            //Assign playlist to one with the removed song
            playlist = Remove_a_song( playlist, choice, size );

            cout << endl;
        }

        else if( choice == "3" || choice == "CLEANUP MY IPOD" )
        {
            //Assign playlist pointer to NULL
            playlist = Cleanup( playlist );

            //After cleaning all items in array, adjusts size to zero
            size = 0;

            cout << endl;
        }

        else if ( choice == "4" || choice == "SHUFFLE THE PLAYLIST" )
        {
            //Assign playlist pointer to new adjusted array
            playlist = Shuffle( playlist, seed, size );

            cout << endl;
        }

        else if( choice == "5" || choice == "EXIT" )
        {
            //Assign playlist ponter to NULL
            playlist = Cleanup( playlist );

            cout << endl;
        }

        //If the user's choice matched with none of the above branches
        //displays message that menu item the user attempted to select
        //was not found.
        else
        {
            cout << "Could not find that item." << endl
                 << "Please enter a valid option" << endl << endl;
        }

    }
}

/*=====================================================================
 Function: Show_playlist
 Description: Goes through each index of the array and outputs each
              struct's items.
 Parameters: Song[] playlist
 ======================================================================*/
void Show_playlist( Song * playlist, int size )
{
    for( int i = 0; i < size ; i++ )
    {
        cout << "Title: " << playlist[i].title << endl
             << "Author: " << playlist[i].artist << endl
             << "Memory Size: " << playlist[i].size << endl;

        //For spacing between each array item
        cout << endl << endl;
    }
}

/*=====================================================================
 Function: Shuffle
 Description: Reassigns elements of the playlist to random locations,
              based on the seed passed to the program at run-time. After
              this is done the function returns the new shuffled array.
 Parameters: Song[] playlist, int seed, int size
 ======================================================================*/
Song * Shuffle( Song playlist[], int seed, int size )
{
    //Variable declarations
    int randarray[size];

    Song temp[size];

    //Initializes values to the random array to prevent
    //random memory values from causing issues
    for( int i = 0; i < size; i++ )
    {
        randarray[i] = -1;
    }

    //Generate array of random indexes
    for( int i = 0; i < size; i++ )
    {
        randarray[i] = Rand_num_generator( randarray, seed, size );
    }

    //Assign random values to temporary array
    for( int i = 0; i < size; i++ )
    {
        temp[i] = playlist[randarray[i]];
    }

    //Copy over new value order to orginal array
    for( int i = 0; i < size; i++ )
    {
        playlist[i] = temp[i];
    }

    return playlist;
}

/*=====================================================================
 Function: Songs_array_mod
 Description: Reads size of the array from the the number of songs
              given by the Count_songs function. Then resets the fstream
              buffer to top of the file. Then reads the songs into the
              new array. After this complete, the function returns the
              new array.
 Parameters: ifstream input_songs, int size
 ======================================================================*/
Song * Songs_array_mod ( ifstream &input_songs, int &size )
{
    //Varaibles declaration
    Song * new_array;
    string input;

    size = Count_songs( input_songs );

    new_array = new Song[size];

    char * end;

    //reset file to the top of the stream, after reaching
    //end of file to determine song size
    input_songs.clear( );

    input_songs.seekg( 0, ios::beg );

    //Reads all songs into the array
    for( int i = 0; i < size; i++ )
    {
        new_array[i].title = Read_lines( input_songs );

        new_array[i].artist = Read_lines( input_songs );

        new_array[i].size = strtod( Read_lines( input_songs ).c_str( ), &end );
    }

    return new_array;
}
