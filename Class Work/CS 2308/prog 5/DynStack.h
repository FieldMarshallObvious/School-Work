//
//  DynStack.hpp
//  
//
//  Created by Noah del Angel on 4/26/20.
//

#ifndef DYNSTACK_H
#define DYNSTACK_H

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

#endif /* DynStack_H */
