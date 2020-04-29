//
//  test.cpp
//  
//
//  Created by Noah del Angel on 4/27/20.
//

#include <iostream>
#include <cstdlib>
#include "DynStack.h"
#include "DynQue.h"

using namespace std;

int main ( )
{
    
    //Test stack push and pop
    DynStack<int> stack;
    int poppedval = -2;
    cout << "Pushing to a stack" << endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    
    stack.pop(poppedval);
    for( ;poppedval != -1;  stack.pop(poppedval) )
    {
        cout << "The popped value is : " << poppedval << endl;
    }
    
    //Test Queue enqeue and dequeue
    Dynque<int> que;
    poppedval = -2;
    int cntr = 0;
    cout << "Pushing to a que" << endl;
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(2);
    que.enqueue(4);
    que.enqueue(5);
    
    for ( ; poppedval != -1; que.dequeue(poppedval) )
    {
        cntr ++;
        cout << "The dequeued value is s" << poppedval << endl;
        if( cntr >= 5 )
            break;
    }
    return 0;
}
