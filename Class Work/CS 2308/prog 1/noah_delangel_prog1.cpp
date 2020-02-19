/*=====================================================================
 Program: Program 1
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 2/20/20
 Description: A program that quizzes users over C++ concepts and applications.
              After the user has answered 6 of such questions, it will show them
              their score, and rank them amongst their peers.
 Input: questions.txt, answers.txt, summary.txt
 Output:
        (to the console)
        Rank 1 Zilliang
               Score: 1000000
        Rank 2 Noah
               Score: 500000
 
        (to summary.txt)
        Noah
            Score: 500000
        Zilliang
            Score: 1000000
 Compilation instructions: All that is needed to do compile the program is to run the
                           g++ command with the file name. C++11 is required, thus you
                           will need it compile the program. You can change the name of
                           the output file, as this should have no effect. An example
                           of theg++ command is given below:
                           g++ noah_delangel_prog1.cpp
 Usage:
 Modifications:
 Date Comment: 2/19/2020
 ---- ------------------------------------------------
 ======================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

/*====================== global symbolic constants ===================*/
const int QUESTION_COLS = 5,
          MAX_NUM_OF_ROUNDS = 6;


using namespace std;

/*======================= function prototypes ========================*/
void Game_over ( string name, int score );
bool Player_try ( string answers_array[], string choice, int index );
void Play_game ( ifstream &answers_bank, ifstream &question_bank, fstream &summary );
int Randindex( int chosen_questions[], int max );
string Read_file ( ifstream &input_file );
int Summary_file_error ( fstream &file );
void Sort_score ( string name, int score, fstream &summary );
void Show_question ( string student, int q_num, string q_array[][5], int index );
void Show_question( string student, string choice, int q_num,
                    string q_array[][5], int index );



int main( )
{
    //Variable declarations
    ifstream question_bank;
    
    question_bank.open( "questions.txt" );
    
    //Checks if question bank file succesfully opened
    if( ! question_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Question bank file failed to open." << endl;
        
        return -1;
    }
    
    ifstream answers_bank;
    
    answers_bank.open( "answers.txt" );

    //Checks if answer bank file succesfully opened
    if( ! answers_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -1;
    }
    
    fstream summary;
    
    summary.open( "summary.txt", ios::in );
    
    //Checks if summary file succesfully opened
    //If summary file does not exist then create it
    if ( ! summary )
    {
        summary.close( );
        
        ofstream temp;
        temp.open("summary.txt");
        
        if( ! temp )
        {
            cout << "***Program Terminated.***" << endl << endl
                 << "Answer bank file failed to open." << endl;
            return -1;
        }
       
        else
        {
            temp.close( );
            
            //If summary still fails to open, then return not normal
            summary.open( "summary.txt", ios::in );
            if( Summary_file_error( summary ) == -1  )
            {
                return -1;
            }
        }
    }
    
    //Runs game function
    Play_game( answers_bank, question_bank, summary );
    
    //Closes all files
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

/*=====================================================================
 Function: Game_Over
 Description: Prints to the screen that the game has ended. The function
              also informs the user of their score.
 Parameters: string name, int score
 ======================================================================*/

void Game_over ( string name, int score )
{
    //Displays end game message
    cout << "--- Game Over! ---" << endl;
    
    cout << name << " you scored " << score << " !" << endl
         << "Check summary.txt for your ranking!" << endl;
    
}

/*=====================================================================
 Function: Player_try
 Description: Cheks to see if the users input matches the answer choice,
              and is allowed to be selected. It will return a boolean
              that
 Parameters: string[] answers_array, string choice, int index
 ======================================================================*/
bool Player_try ( string answers_array[], string choice, int index )
{
    //Variable declarations
    string correct_choice = answers_array[index];
    
    bool output = false;
    
    //Checks to see if the users choice is correct regardless of case
    if( toupper( choice[0] ) == toupper( correct_choice[0] ) )
        output = true;
    
    return output;
}

/*=====================================================================
 Function: Player_game
 Description: Runs, and calls, all operations that run the overall
              structure of the game. As a result this function hanldes,
              and tracks all relevant varaibles to the game.
 Parameters: string[] answers_array, string choice, int index
 ======================================================================*/
void Play_game ( ifstream &answers_bank, ifstream &question_bank, fstream &summary )
{
    //Variable declarations
    const int POINT_MULTIPLE = 10,
              POINT_MULTIPLE_HALF = 5;
    
    int chosen_questions[50],
        q_num = 1,
        score = 0,
        total_ques = 0,
        total_ans = 0;
    
    string q_array[50][QUESTION_COLS],
           answers_array[50],
           student,
           choice;
    
    bool truth_value;
    
    cout << "What is your name?" << endl;
    getline(cin, student);
    
    cout << endl;
    
    //Question array creation
    for(int i = 0; i < 50; i++)
    {
        //Keeps track of total number of questions
        if( !question_bank.eof( ) )
            total_ques++;
        
        if( !answers_bank.eof( ) )
            total_ans++;
        
        for(int j = 0; j < 5; j++)
        {
            
            if(j == 0)
                q_array[i][j] = Read_file( question_bank );
            
            else
                q_array[i][j] = Read_file( question_bank );
        }
        
        
        answers_array[i] = Read_file( answers_bank );
    }
    
    
    //Checks to ensure same numbers of questions and answers
    if( total_ans > total_ques )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "There are more answers then there are questions." << endl;
        
        return;
    }
    
    else if ( total_ans < total_ques  )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "There are more questions then there are answers." << endl;
        
        return;
    }

    //Display questions and accept input from user
    while( q_num <= MAX_NUM_OF_ROUNDS )
    {
        //Variable declarations
        string retry_choice;
        
        int index = Randindex( chosen_questions, total_ques );

        //Display question first round
        Show_question( student, q_num, q_array, index );
        
        //Acquires answer choice from user
        cout << "Your choice? > ";
        cin >> choice;
        
        
        
        //Asses correctness of user choice
        truth_value = Player_try( answers_array, choice, index );
        
        cout << truth_value << endl;
        
        //If user gets question wrong it allows them to try again
        if( truth_value == false )
        {
            cout << "Would you try again? (Y/N)" << endl
                 << "> ";
            cin >> retry_choice;
            
            //If user picks yes then they can reattempt the question
            if ( toupper( retry_choice[0] ) == toupper( 'Y' ) )
            {
                //Displays question for second attempt
                Show_question ( student, choice, q_num, q_array, index );
            
                //Acquires choice from user
                cout << "Your choice? > ";
                cin >> choice;
            
                //Asses correctness of user choice
                truth_value = Player_try( answers_array, choice ,index );
            
                cout << truth_value << endl;
                
                //Assigns score if user got the question correct
                if ( truth_value == true )
                {
                    if( score >= 1)
                        score *= 5;
                    else
                        score = 5;
                }
                
                //Ends game if user got the question wrong
                else
                {
                    score = 0;
                    Sort_score(student, score, summary);
                    Game_over(student, score);
                    return;
                }
            }

        }
        
        //Assigns score if user got the question correct
        else
        {
            if( score >= 1 )
                score *= 10;
            else
                score = 10;
        }
        
        //Keeps track of chosen random indexes
        chosen_questions[q_num-1] = index;
        
        //Keeps track of number of questions displayed
        q_num++;
    }
    
    Sort_score( student, score, summary );
    
    Game_over( student, score );
    
}

/*=====================================================================
 Function: Randindex
 Description: Generates a random index that is unique from all indexes
              previsouly chosen. Then returns that integer.
 Parameters: int chosen_questions[], int max
 ======================================================================*/
int Randindex( int chosen_questions[], int max )
{
    //Variable declarations
    bool unique_item = false;
    
    int rand_int;
    
    //Initializes random time to system time
    srand( time(NULL) );
    
    //Finds random number between max and 1
    //Also ensures that the random number has not already been selected
    do {
        unique_item = true;
        
        rand_int = rand( ) % (max-1) + 0;
        
        //Checks for every item in array to make sure it has not already been selected
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
    } while( unique_item == false );
    
    return rand_int;
}

/*=====================================================================
 Function: Read_file
 Description: Outputs a single line from the requested file, if it is
              not blank.
 Parameters: ifstream input_file
 ======================================================================*/
string Read_file ( ifstream &input_file )
{
    //Variable declarations
    string output = "";
    
    //Reads lines from input file until it finds a non-blank line.
    //After the line has been determined to not be blank returns that line
    while ( getline(input_file, output) && (!input_file.eof()))
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0)
            continue;
        
        else
            break;
    }
    
    return output;
}

/*=====================================================================
 Function: Summary_file_error
 Description: Outputs a single line from the requested file, if it is
 not blank.
 Parameters: ifstream input_file
 ======================================================================*/
int Summary_file_error ( fstream &file )
{
    if ( ! file )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Summary file failed to open." << endl;
        
        return -1;
    }
    
    return 0;
}


void Sort_score ( string name, int score, fstream &summary )
{
    //Variable declarations
    int num_of_players = 0,
        min_score,
        min_index,
        line_num = 0;
    
    string input,
           temp_name,
           temp_score;
    
    bool swapped = false;
    
    //Determines how many previous entries there have been
    while( getline( summary, input ) && ( !summary.eof( ) ) )
    {
        cout << "in the loop " << endl;
        if (strlen( input.c_str( ) ) == 1 || strlen( input.c_str( ) ) == 0)
            continue;
        else
        {
            line_num++;
            cout << input << endl;
            cout << line_num << endl;
            if( line_num == 2)
            {
                num_of_players++;
                line_num = 0;
            }
        }
    }
    
    //Closes file as to bring it back to the top
    summary.close( );
    
    //Opens file after having it be closed
    summary.open( "summary.txt", ios::in );
    
    //Checks to make sure file has been opened succesfully
    if ( Summary_file_error ( summary ) == -1)
        return;
    
    //Creation of array for previous entries
    // The + 1 allows for the entry of the new user
    string summary_entries[num_of_players+1][2];
    
    cout << "Num of players is " << num_of_players+1 << endl;
    //Reads in data from file and assigns it to array
    for( int i = 0; i < num_of_players; i++ )
    {
        for( int j = 0; j < 2; j++ )
        {
            getline( summary, input );
        
            if(j == 0)
            {
                string temp_input( input, 0 );
                summary_entries[i][j] = temp_input;
            }
            else
            {
                string temp_input( input, 11 );
                
                if( temp_input[0] == ' ' )
                    string temp_input( input, 12 );
                
                summary_entries[i][j] = temp_input;
            }
            
        }
    }
    
    //Closes file as to bring it back to the top
    summary.close( );
    
    //Opens file after having it be closed
    summary.open( "summary.txt", ios::app );
    
    //Checks to make sure file has been opened succesfully
    if ( Summary_file_error ( summary ) == -1 )
        return;
    
    //Appends new entry to end of array
    summary_entries[num_of_players][0] = name;
    summary_entries[num_of_players][1] = score;
    
    //Appends new entry to summary file
    summary << summary_entries[num_of_players][0] << endl
            << "    Score: " << summary_entries[num_of_players][1] << endl;
    
    //Sorts array via selection sort
    do {
        swapped = false;
            for( int i = 0; i < num_of_players - 1; i++ )
            {

                if( atoi( summary_entries[i][1].c_str( ) ) <
                    atoi( summary_entries[i + 1][1].c_str( ) ) )
                {
                    temp_name = summary_entries[i][0];
                    temp_score = summary_entries[i][1];
                    
                    summary_entries[i][0] = summary_entries[i + 1][0];
                    summary_entries[i][1] = summary_entries[i + 1][1];
                    
                    summary_entries[i + 1][0] = temp_name;
                    summary_entries[i + 1][1] = temp_score;
                    swapped = true;
                }
            
            }
        
    }while(swapped);
    
    int cntr = 0;
    
    //Writes new order to summary file
    for( int i = num_of_players; i >= 0; i-- )
    {
        //Remove all empty spaces from string
        summary_entries[cntr][1].erase( remove( summary_entries[cntr][1].begin( ),
                                                summary_entries[cntr][1].end( ), ' ' ),
                                                summary_entries[cntr][1].end( ) );
        
        cout << "Rank " << i+1 << " " << summary_entries[i][0] << endl
             << "       Score: " << summary_entries[i][1] << endl;
        
        cntr++;
    }
    
    
}

void Show_question ( string student, int q_num, string q_array[][5], int index )
{
    //Variable declarations
    string multipe_choice[4] = {"A", "B", "C", "D"};
    
    //Outputs student's name with current question number
    cout << student << " Here's Question Number " << q_num << endl
         << q_array[index][0] << endl;
    
    //Outputs answers with multiple choice options
    for( int i = 1; i < 5; i++)
        cout << multipe_choice[i-1] << ". " << q_array[index][i] << endl;
    
}

void Show_question( string student, string choice, int q_num, string q_array[][5], int index )
{
    //Variable declarations
    string multipe_choice[4] = {"A", "B", "C", "D"};
    
    //Outputs students name with current question number, along with
    //an indiciation this is the second try
    cout << student << " Here's Question Number " << q_num << " (second try)" << endl
         << q_array[index][0] << endl;
    
    //Outputs answers with multiple choice options, but skips choice
    //already chosen by user
    for( int i = 1; i < 5; i++)
    {
        string current_index = multipe_choice[i-1];
        
        if( toupper( current_index[0] ) != toupper( choice[0] ) )
            cout << multipe_choice[i-1] << ". " << q_array[index][i] << endl;
        else {}
            
    }
}
