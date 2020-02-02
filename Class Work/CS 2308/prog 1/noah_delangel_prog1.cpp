/*
Documentation block
*/

#include <iostream>
#include <fstream>
#include <string>

//Global constants if needed

//Type declarations if needed


using namespace std;
//Function prototypes
string Get_answer ( ifstream &answers_bank );
string Read_questions ( ifstream &question_bank );
string Read_answers( ifstream &question_bank);
void Show_question( string student, int q_num, ifstream &question_bank, ifstream &answers_bank  );
bool Player_try( ifstream &answers_bank );
void Play_game( ifstream &question_bank, ifstream &answers_bank, ofstream &summary );
void Sort_score( );



int main ()
{
    //Create file in and out var
    ifstream question_bank;
    
    question_bank.open("questions.txt");
    
    if( ! question_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Question bank file failed to open." << endl;
        
        return -1;
    }
    
    ifstream answers_bank;
    
    answers_bank.open("questions.txt");
    
    if( ! answers_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -2;
    }
    
    ofstream summary;
    
    summary.open("summary.txt");
    
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -3;
    }
    
    Play_game(question_bank, answers_bank, summary);
    
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

string Get_answer ( ifstream &answers_bank )
{
    string output;
    
    getline(answers_bank, output);
    
    return output;
}

bool Player_try ( ifstream &answers_bank )
{
    string choice;
    string correct_choice = Get_answer( answers_bank );
    
    
    bool output = false;
    
    cout << "Your choice? > ";
    cin >> choice;
    
    if( choice == correct_choice )
        output = true;
    
    return output;
}

void Play_game ( ifstream &question_bank, ifstream &answers_bank, ofstream &summary )
{
    const int POINT_MULTIPLE = 10;
    const int POINT_MULTIPLE_HALF = 5;
    
    string q_array[50][4];
    string student;
    
    int q_num;
    
    cout << "What is your name?" << endl;
    getline(cin, student);
    
    cout << endl;
    
    Show_question(student, q_num, question_bank, answers_bank);
    
    cout << Player_try(answers_bank);
    
}

string Read_answers ( ifstream &answers_bank )
{
    string output;
    
    getline(answers_bank, output);
    
    return output;
}

string Read_questions ( ifstream &question_bank )
{
    string output;
    
    getline(question_bank, output);
    
    return output;
}

void Show_question ( string student, int q_num, ifstream &question_bank, ifstream &answers_bank )
{
    string multipe_choice[4] = {"A.", "B.", "C.", "D."};
    //Question existence check
    
    //Question answer loop check
    
    cout << student << " Here's Question Number " << q_num << endl
         << Read_questions(question_bank) << endl;
    
    for( int i = 0; i < 5; i++)
        cout << multipe_choice[i] << " " << Read_questions(question_bank) << endl;
    
    //cout << q_array[0] << " Here's Question Number " << q_array[1]<< endl
      //   << q_array[2] << endl;
    
    //Question options loop - using delimeter for endls
}
