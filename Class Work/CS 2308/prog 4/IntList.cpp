//
//  IntList.cpp
//  
//
//  Created by Noah del Angel on 4/11/20.
//
#include <cstdlib>
#include <iostream>

#include "IntList.h"

using namespace std;

//Global Variables


IntList::IntList()
{

    (*head).value = -1;
    
    (*head).next = NULL;
}

IntList::IntList(const IntList &List)
{
    head->next = List.head;
}

IntList::~IntList( )
{
    delete head;
    head = NULL;
}

void IntList::appendNode( int val )
{
    cout << "In the function" << endl;
    //Variable delcarations
    IntList *newNode;
    IntList *nodePtr;
    
    cout << "Things created" << endl;
    
    //Create new node
    newNode = new IntList();
    
    cout << "Node init'd" << endl;
    
    ( *newNode ).head->value = val;
    
    cout << "value assigned" << endl;
    
    if ( !head )
    {
        head = ( *newNode ).head;
    }
    
    else
    {
        ( *nodePtr ).head = head;
        
        while ( ( *nodePtr ).head->next )
        {
            ( *nodePtr ).head = ( *nodePtr ).head->next;
        }
        
        ( *nodePtr ).head->next = ( *newNode ).head;
    }
}

void IntList::removeByVal( int val )
{
    //Variable declarations
    IntList *nodePtr;
    IntList *previousNode;
    
    if ( !head )
        return;
    
    if( head->value == val )
    {
        ( *nodePtr ).head = head->next;
        
        delete head;
        
        head = (*nodePtr).head;
    }
    
    else
    {
        (*nodePtr).head = head;
        
        while ( ( *nodePtr ).head != NULL && ( *nodePtr ).head->value != val )
        {
            ( *previousNode ).head = ( *nodePtr ).head;
            
            (*nodePtr).head = (*nodePtr).head->next;
        }
    }
}

void IntList::displayList()
{
    //Variable declarations
    IntList *nodePtr;
    
    if( !head )
        return;
    else
    {
        ( *nodePtr ).head = head;
        while ( ( *nodePtr ).head != NULL )
        {
            cout << ( *nodePtr ).head->value;
            
            if( ( *nodePtr ).head->next != NULL )
                cout << " -> ";
        }
        cout << endl;
    }
}

void IntList::insertByPos(int val, int pos)
{
    
}

void IntList::removeByPos(int pos)
{
    
}

int IntList::search(int val)
{
    return 0;
}
