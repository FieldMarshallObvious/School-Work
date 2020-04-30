//
//  DynQue.h
//  
//
//  Created by Noah del Angel on 4/28/20.
//

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

template<class T>
Dynque<T>::Dynque( )
{

    front = NULL;
    rear = NULL;

    numItems = 0;
}

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

template<class T>
void Dynque<T>::dequeue( T & num )
{
    //Variable delcarations
    QueueNode *temp;
    
    if( isEmpty() )
    {
        num = -1;
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

template<class T>
bool Dynque<T>::isEmpty()
{
    bool output = true;
    
    if ( numItems > 0 )
        output = false;
    
    return output;
}

#endif /* DynQue_h */
