// A template class for holding a stack

#ifndef DYNSTACK_H
#define DYNSTACK_H
#include<iostream>
#include<cstdlib>
using namespace std;

template <class T>
class DynStack
{
    private:
        struct StackNode //Node
        {
            T value;
            StackNode *next;
            
        };
        StackNode *top; //pointer to the top of the
                        //stack
    
    public:
        //Constructor
        DynStack();
    
        //Destructor
        ~DynStack();
    
        //Stack operations
        void push(T);
        void pop(T &);
    
    //Determine if the sack is empty
        bool isEmpty();
};

//**************************************************
// Defualt constructor for the DynStack class      *
//**************************************************
template <class T>
DynStack<T>::DynStack( )
{
    StackNode *newNode = new StackNode;
    
    top = newNode;
    
    top->value = -1;
    top->next = NULL;
}

//**************************************************
// Defualt destructor for the DynStack class       *
//**************************************************
template <class T>
DynStack<T>::~DynStack( )
{
    //Variable declarations
    StackNode *nodePtr = top;
    StackNode *nextNode;
    
    //While nodePtr is NULL
    while( nodePtr != NULL )
    {
        //Set the next to pointer to the
        //following node
        nextNode = nodePtr->next;
        
        //Delete the current node
        delete(nodePtr);
        
        //Set the current node to the next node
        nodePtr = nextNode;
    }
    
    //Set the destructor nodes to NULL
    nodePtr = NULL;
    nextNode = NULL;
}

//**************************************************
// Adds the passed value to the top of the stack   *
//**************************************************
template <class T>
void DynStack<T>::push ( T input )
{
    //Variable declarations
    StackNode * newNode = new StackNode;
    StackNode * oldNode = top;
    
    //Set newNode to given value
    newNode->value = input;
    
    //If the top exists and does not match the
    //initialization condition
    if ( ! top )
    {
        top = newNode;
    }
    else
    {
        //Add the new node to the head
        newNode->next = oldNode;
        top = newNode;
    }
}

//**************************************************
// Removes item from the top of the stack, and     *
// returns it to the value passed by reference.    *
//**************************************************
template <class T>
void DynStack<T>::pop ( T &num )
{
    //Variable declarations
    StackNode * topNode;
    StackNode * newTop;
    
    //If the top exist and does not match the
    //initialization condition
    if ( ! top  )
    {
        cout << "There are no items to pop" << endl;
    }
    else
    {
        //Set nodes to the top
        //and to the node after the top
        topNode = top;
        newTop = top->next;
        
        //Set top value to passed variable
        num = top->value;
        
        //Remove the top node
        delete( topNode );
        
        //Set top to next item
        top = newTop;
    }
}

//**************************************************
// Determines whether the stack has an items or    *
// not. If the stack has items the functions       *
// returns false. If the que does not have items   *
// it returns true.                                *
//**************************************************
template <class T>
bool DynStack<T>::isEmpty( )
{
    //Variable declarations
    bool empty = false;
    
    //If the top exist and does not match the
    //initialization condition
    if ( ! top )
        empty = true;
    
    return empty;
}

#endif /* DynStack_H */
