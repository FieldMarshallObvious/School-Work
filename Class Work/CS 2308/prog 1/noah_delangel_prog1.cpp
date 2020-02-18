/*
Documentation block
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

//Global constants
const int QUESTION_COLS = 5,
          MAX_NUM_OF_ROUNDS = 6;

//Type declarations if needed


using namespace std;
//Function prototypes
void Game_over ( string name, int score );
int Randindex( int chosen_questions[], int max );
string Read_questions ( ifstream &question_bank );
string Read_answers( ifstream &question_bank);
void Show_question( string student, int q_num, string q_array[][5], int index );
void Show_question( string student, string choice, int q_num, string q_array[][5], int index );
bool Player_try( string answers_array[], int index, string choice );
void Play_game( ifstream &question_bank, ifstream &answers_bank, fstream &summary );
void Sort_score( string name, int score, fstream &summary );



int main ()
{
    //Variable declarations
    ifstream question_bank;
    
    question_bank.open("questions.txt");
    
    //Checks if question bank file succesfully opened
    if( ! question_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Question bank file failed to open." << endl;
        
        return -1;
    }
    
    ifstream answers_bank;
    
    answers_bank.open("answers.txt");

    //Checks if answer bank file succesfully opened
    if( ! answers_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -1;
    }
    
    fstream summary;
    
    summary.open("summary.txt", ios::in | ios::out);
    
    //Checks if summary file succesfully opened
    //If summary file does not exist then create it
    if ( ! summary )
    {
        summary.close();
        
        ofstream temp;
        temp.open("summary.txt");
        
        if( ! temp )
        {
            cout << "***Program Terminated.***" << endl << endl
                << "Summary file failed to open." << endl;
            return -1;
        }
       
        else
        {
            temp.close();
            
            //If summary still fails to open, then return not normal
            summary.open("summary.txt", ios::in | ios::out);
            if( ! summary )
            {
                cout << "***Program Terminated.***" << endl << endl
                << "Summary file failed to open." << endl;
                return -1;
            }
        }
    }
    
    //Runs game function
    Play_game(question_bank, answers_bank, summary);
    
    //Closes all files
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

void Game_over ( string name, int score )
{
    //Displays end game message
    cout << "--- Game Over! ---" << endl;
    
    cout << name << " you scored " << score << " !" << endl
         << "Check summary.txt for your ranking!" << endl;
    
}

bool Player_try ( string answers_array[], int index, string choice )
{
    //Variable declarations
    string correct_choice = answers_array[index];
    
    bool output = false;
    
    //Checks to see if the users choice is correct regardless of case
    if( toupper(choice[0]) == toupper(correct_choice[0]) )
        output = true;
    
    return output;
}

void Play_game ( ifstream &question_bank, ifstream &answers_bank, fstream &summary )
{
    //Variable declarations
    const int POINT_MULTIPLE = 10,
              POINT_MULTIPLE_HALF = 5;
    
    string q_array[50][QUESTION_COLS],
           answers_array[50],
           student,
           choice;
    
    int chosen_questions[50],
        q_num = 1,
        score = 0,
        total_ques = 0,
        total_ans = 0;
    
    bool truth_value;
    
    cout << "What is your name?" << endl;
    getline(cin, student);
    
    cout << endl;
    
    //Question array creation
    for(int i = 0; i < 50; i++)
    {
        //Keeps track of total number of questions
        if( !question_bank.eof() )
            total_ques++;
        
        if( !answers_bank.eof() )
            total_ans++;
        
        for(int j = 0; j < 5; j++)
        {
            
            if(j == 0)
                q_array[i][j] = Read_questions( question_bank );
            
            else
                q_array[i][j] = Read_questions( question_bank );
        }
        
        
        answers_array[i] = Read_answers( answers_bank );
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
        
        int index = Randindex(chosen_questions, total_ques);

        //Display question first round
        Show_question( student, q_num, q_array, index );
        
        //Acquires answer choice from user
        cout << "Your choice? > ";
        cin >> choice;
        
        
        
        //Asses correctness of user choice
        truth_value = Player_try( answers_array, index, choice);
        
        cout << truth_value << endl;
        
        //If user gets question wrong it allows them to try again
        if( truth_value == false )
        {
            cout << "Would you try again? (Y/N)" << endl
                 << "> ";
            cin >> retry_choice;
            
            //If user picks yes then they can reattempt the question
            if ( toupper(retry_choice[0]) == toupper('Y'))
            {
                //Displays question for second attempt
                Show_question ( student, choice, q_num, q_array, index );
            
                //Acquires choice from user
                cout << "Your choice? > ";
                cin >> choice;
            
                //Asses correctness of user choice
                truth_value = Player_try( answers_array, index, choice);
            
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
    
    Sort_score(student, score, summary);
    
    Game_over(student, score);
    
}

int Randindex( int chosen_questions[], int max )
{
    //Variable declarations
    bool unique_item = false;
    
    int rand_int;
    
    //Initializes random time to system time
    srand(time(NULL));
    
    //Finds random number between max and 1
    //Also ensures that the random number has not already been selected
    do {
        unique_item = true;
        
        rand_int = rand() % (max-1) + 0;
        
        //Checks for every item in array to make sure it has not already been selected
        for( int cntr = 0; cntr < max; cntr++)
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

string Read_answers ( ifstream &answers_bank )
{
    //Variable declarations
    string output = "";
    
    //Reads lines from input file until it finds a non-blank line.
    //After the line has been determined to not be blank returns that line
    while ( getline(answers_bank, output) && (!answers_bank.eof()))
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0)
            continue;
        
        else
            break;
    }
    
    return output;
}

string Read_questions ( ifstream &question_bank )
{
    //Variable declarations
    string output = "";
    
    //Reads lines from input file until it finds a non-blank line.
    //After the line has been determined to not be blank returns that line
    while ( getline(question_bank, output) && (!question_bank.eof()) )
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0)
            continue;
        
        else
            break;
    }
    
    return output;
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
    
    //Determines how many previous entries there have been
    while( getline(summary, input) && (!summary.eof()))
    {
        if (strlen(input.c_str()) == 1 || strlen(input.c_str()) == 0)
            continue;
        else
        {
            line_num++;
            if( line_num == 2)
            {
                num_of_players++;
                line_num = 0;
            }
        }
    }
    
    //Closes file as to bring it back to the top
    summary.close();
    
    //Opens file after having it be closed
    summary.open("summary.txt", ios::in | ios::out);
    
    //Checks to make sure file has been opened succesfully
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Summary file failed to open." << endl;
        
        return;
    }
    
    //Creation of array for previous entries
    // The + 1 allows for the entry of the new user
    string summary_entries[num_of_players+1][2];
    
    cout << "Num of players is " << num_of_players+1 << endl;
    //Reads in data from file and assigns it to array
    for( int i = 0; i < num_of_players; i++ )
    {
        for( int j = 0; j < 2; j++)
        {
            getline(summary, input);
        
            if(j == 0)
            {
                string temp_input(input, 7);
                summary_entries[i][j] = temp_input;
            }
            else
            {
                string temp_input(input, 13);
                
                if(temp_input[0] == ' ')
                    string temp_input(input, 14);
                
                summary_entries[i][j] = temp_input;
            }
            
        }
    }
    
    //Closes file as to bring it back to the top
    summary.close();
    
    //Opens file after having it be closed
    summary.open("summary.txt", ios::in | ios::out);
    
    //Checks to make sure file has been opened succesfully
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Summary file failed to open." << endl;
        
        return;
    }
    
    //Appends new entry to end of array
    summary_entries[num_of_players][0] = name;
    summary_entries[num_of_players][1] = to_string(score);
    
    
    //Sorts array via selection sort
    for( int i = 0; i <= num_of_players; i++ )
    {
        min_index = i;
        min_score = stoi(summary_entries[i][1]);
        cout << "The new min_score " << min_score << endl;
        for(int j = 0; j <= num_of_players; j++)
        {
            cout << "J is " << j << endl;

            if( min_score >= stoi(summary_entries[j][1]))
            {
                min_index = j;
                cout << "Converting in inner loop" <<  summary_entries[j][1] << " to int"  << endl;
                min_score = stoi(summary_entries[j][1]);
                cout << "The new min_score " << min_score << endl;
                cout << "The new min index is " << min_index << endl;
            }
        }
        
        temp_name = summary_entries[i][0];
        temp_score = summary_entries[i][1];
        
        cout << "The temp name is " << temp_name << endl;
        cout << "The temp_score is " << temp_score << endl;
        
        summary_entries[i][0] = summary_entries[min_index][0];
        summary_entries[i][1] = summary_entries[min_index][1];
        
        summary_entries[min_index][0] = temp_name;
        summary_entries[min_index][1] =temp_score;
        
        cout << "The array is now" << endl;
        for( int x = 0; x <= num_of_players; x++ )
        {
            cout << summary_entries[x][0] << " " << summary_entries[x][1] << endl;
        }
    
    }
    
    //Writes new order to summary file
    for( int i = 0; i <= num_of_players; i++ )
    {
        
        summary << "Rank " << i+1 << " " << summary_entries[i][0] << endl
                << "       Score: " <<summary_entries[i][1] << endl;
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
