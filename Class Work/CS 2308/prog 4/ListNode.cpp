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
    //Create struct
    ListNode node;
    
    //Initialize value to a number
    node.value = -1;
    
    //Initialize pointer to an empty value
    node.next = NULL;
    
    //Assign head to struct
    this->head = &node;
}

IntList::IntList(const IntList &List)
{
    //Create struct
    ListNode node;
    
    node.next = &List;
}

void IntList::appendNode(int val)
{
    //Variable delcarations
    ListNode *newNode;
    ListNode *nodePtr;
    
    //Create new node
    newNode = new ListNode;

    
}

void IntList::removeByVal(int val)
{
    
}

void IntList::displayList()
{
    
}

void IntList::displayList()
{
    
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

