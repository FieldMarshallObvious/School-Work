/*=====================================================================
 Program: Prog 5
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 5/1/20
 Description: This portion of the program implements the Dynamic Stack,
              using pointers. This class has this ability to push an
              item to the stack. The class also contains functionality
              to pop the top item from the stack, and return it to the
              passed value. The class can determine if the stack is
              empty.
 Input:
 Output:
 Compilation instructions: If the header file is not being compiled
                           alongside a C++ file, then it can be
                           compiled with the following code:
                           g++ DynStack.h
 
 Usage: The following is an example use case for an integer Dynque
        DynStack<int> newStack;
        int value;
        newStack.push( 3 );
        newStack.pop( value );
        if( newStack.isEmpty( ) ) { cout << "It's empty" << endl ; }
 Modifications:
 Date Comment: 29/4/20
 ----------------------------------------------------
 ======================================================================*/

#ifndef DYNSTACK_H
#define DYNSTACK_H
#include<iostream>
#include<cstdlib>
using namespace std;

template <class T>
class DynStack
{
    private:
        struct StackNode
        {
            T value;
            StackNode *next;
            
        };
        StackNode *top;
    
    public:
        DynStack();
        ~DynStack();
        void push(T);
        void pop(T &);
        bool isEmpty();
};

template <class T>
DynStack<T>::DynStack( )
{
    StackNode *newNode = new StackNode;
    
    top = newNode;
    
    top->value = -1;
    top->next = NULL;
}

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
        num = -1;
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

template <class T>
bool DynStack<T>::isEmpty( )
{
    //Variable declarations
    bool empty = false;
    
    //If the top exist and does not match the
    //initialization condition
    if ( ! top && ( top->value != -500 && top->next !=
                   NULL ) )
        empty = true;
    
    return empty;
}

#endif /* DynStack_H */
