//
//  test.cpp
//  
//
//  Created by Noah del Angel on 4/27/20.
//

#include <iostream>
#include <cstdlib>
#include "DynStack.h"

using namespace std;

int main ( )
{
    
    DynStack<int> stack;
    int poppedval = -2;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    while( poppedval != -1 )
    {
        stack.pop(poppedval);
        cout << "The popped value is : " << poppedval << endl;
    }
    return 0;
}
