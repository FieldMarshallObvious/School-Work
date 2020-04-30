// A template class for holding a que

#ifndef DynQue_h
#define DynQue_h
#include<iostream>

using namespace std;

template<class T>
class Dynque
{
    private:
        struct QueueNode //Node
        {
            T value;
            QueueNode *next;

        };
    
    QueueNode *front; //pointer to front of the que
    QueueNode *rear; //pointer to the last node of the que
    int numItems;   //total number of items in the que
    
    public:
    //Constructor
    Dynque();
    
    //Destructor
    ~Dynque();
    
    //Que operations
    void enqueue(T);
    void dequeue(T &);
    
    //Determine if the que is empty
    bool isEmpty();
    
};

//**************************************************
// Defualt constructor for the Dynque class        *
//**************************************************
template<class T>
Dynque<T>::Dynque( )
{
    //initialize the node pointers with NULL
    //values
    front = NULL;
    rear = NULL;
    
    //Start the list with zero items
    numItems = 0;
}

//**************************************************
// Destructor for the Dynque class                 *
//**************************************************
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

//**************************************************
// Adds an passed value to the rear of the que.    *
//**************************************************
template<class T>
void Dynque<T>::enqueue( T num )
{

    //Variable declarations
    QueueNode *newNode = new QueueNode;
    
    //Give the new node values
    newNode->value = num;
    newNode->next = NULL;
    
    //If the que is empty assign the
    //front and rear node to the newNode.
    if ( isEmpty() )
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        //Set the rear next to the new node
        rear->next = newNode;
        //Set the rear to the new Node
        rear = newNode;
    }
    
    //Increase the number of items
    numItems++;
    
}

//**************************************************
// Removes an item from the front of the que, and  *
// returns that item to the item passed by         *
// refrence.                                       *
//**************************************************
template<class T>
void Dynque<T>::dequeue( T & num )
{
    //Variable delcarations
    QueueNode *temp;
    
    //If the que is already empty inform the user
    if( isEmpty() )
    {
        cout << "The que is empty" << endl;
    }
    
    else
    {
        //Set the passed variable to value of the
        //top node
        num = front->value;
        
        //Assign the temp node to the front
        temp = front;
        
        //Set the temp node to the next value
        front = front->next;
        
        //Delete the old top value
        delete temp;
        
        //Decrease the number of items
        numItems--;
    }
}

//**************************************************
// Determines whether the que has an items or not. *
// If the que has items the functions returns      *
// false. If the que does not have items it        *
// returns true.                                   *
//**************************************************
template<class T>
bool Dynque<T>::isEmpty( )
{
    //Variable declarations
    bool output = true;
    
    //If the number of items is greater than zero
    //the que is not empty.
    if ( numItems > 0 )
        output = false;
    
    return output;
}

#endif /* DynQue_h */
