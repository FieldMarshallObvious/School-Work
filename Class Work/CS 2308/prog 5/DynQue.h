
/*=====================================================================
 Program: Prog 5
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 5/1/20
 Description: This portion of the program implements the Dynamic Que,
              using pointers. This class has the ability to enqueue an
              item to the que. It has the ability to dequeue the top
              item from the program, and return it to the passed var.
              The class also the funtionality to determine if the
              que is empty
 Input:
 Output:
 Compilation instructions:
 Usage:      The following is an example use case for an integer Dynque
             Dynque<int> newQue;
             int value;
             newQue.enqueue( 3 );
             newQue.dequeue( value );
             if( newQue.isEmpty( ) ) { cout << "It's empty" << endl ; }
 Modifications:
 Date Comment: 29/4/20
 ----------------------------------------------------
 ======================================================================*/

#ifndef DynQue_h
#define DynQue_h
#include<iostream>

using namespace std;

template<class T>
class Dynque
{
    private:
        struct QueueNode
        {
            T value;
            QueueNode *next;

        };
    
    QueueNode *front;
    QueueNode *rear;
    int numItems;
    
    public:
    Dynque();
    ~Dynque();
    void enqueue(T);
    void dequeue(T &);
    bool isEmpty();
    
};

/*=====================================================================
 Function: Dynque
 Description: Defualt constructor for the Dynque class
 Parameters:
 ======================================================================*/
template<class T>
Dynque<T>::Dynque( )
{

    front = NULL;
    rear = NULL;

    numItems = 0;
}

/*=====================================================================
 Function: ~Dynque
 Description: Destructor for the Dynque class
 Parameters:
 ======================================================================*/
template<class T>
Dynque<T>::~Dynque()
{
    //Variable declarations
    T value;
    
    //While their are items in the que
    while( !( isEmpty( ) ) )
    {
        dequeue(value);
    }
}

/*=====================================================================
 Function: enqueue
 Description: Adds an inputted item into the rear of the que
 Parameters: T num
 ======================================================================*/
template<class T>
void Dynque<T>::enqueue( T num )
{

    //Variable declarations
    QueueNode *newNode = new QueueNode;
    
    
    newNode->value = num;
    newNode->next = NULL;
    
    if ( isEmpty() )
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    
    numItems++;
    
}

/*=====================================================================
 Function: dequeue
 Description: Removes an item from the front of the que, and returns
              that item to the passed variable.
 Parameters: T & num
 ======================================================================*/
template<class T>
void Dynque<T>::dequeue( T & num )
{
    //Variable delcarations
    QueueNode *temp;
    
    if( isEmpty() )
    {
        cout << "The que is empty" << endl;
    }
    
    else
    {
        
        num = front->value;
        temp = front;
        
        front= front->next;
        
        delete temp;
        
        numItems--;
    }
}

/*=====================================================================
 Function: isEmpty
 Description: Determines whether the que has an items or not. If the que
              has items the functions returns false. If the que does not
              have items it returns true
 Parameters:
 ======================================================================*/
template<class T>
bool Dynque<T>::isEmpty( )
{
    bool output = true;
    
    if ( numItems > 0 )
        output = false;
    
    return output;
}

#endif /* DynQue_h */
