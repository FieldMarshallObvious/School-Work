/*=====================================================================
 Program: IntList.cpp
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 4/20/20
 Description: A program that creates a linked list of integers
 Input:
 Output: (to the console)
 2 -> 4 -> 6 -> 8 -> 10
 Compilation instructions: These compilation instructions assume you are running this
 program on a linux machine. Enter the command `make` into
 the console. Then enter ./a.out.
 Usage:
 Modifications:
 Date Comment: 4/16/20
 ----------------------------------------------------*/

#include <cstdlib>
#include <iostream>

#include "DynStack.h"

using namespace std;

template <class T> DynStack<T>::DynStack( )
{
    StackNode *newNode = new StackNode;
    
    top = newNode;
    
    top->value = -1;
    top->next = NULL;
}

template <class T> DynStack<T>::~DynStack( )
{
    
}

template <class T>  void DynStack<T>::push ( T input )
{
    //Variable declarations
    StackNode * newNode = new StackNode;
    StackNode * oldNode = top;
    
    //Set newNode to given value
    newNode->value = input;
    
    //If the top exists and does not match the
    //initialization condition
    if ( ! top && ( top->value != -1 && top->next !=
                     NULL ) )
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

template <class T> void DynStack<T>::pop ( T &num )
{
    //Variable declarations
    StackNode * topNode;
    StackNode * newTop;
    
    //If the top exist and does not match the
    //initialization condition
    if ( ! top && ( top->value != -500 && top->next !=
                   NULL ) )
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

template <class T> bool DynStack<T>::isEmpty( )
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
