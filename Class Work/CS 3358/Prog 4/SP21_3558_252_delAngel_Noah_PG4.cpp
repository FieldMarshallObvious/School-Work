#include <iostream>
#include <time.h>


using namespace std;

template<typename T>
struct node
{
    node<T>* next;
    T data;
};

template<typename T>
class LinkedList
{
    private:
        node<T> *head;

    public:
        LinkedList();

        LinkedList(T data);

        void appendData(T data);
        void insertData(T data, int pos);
        void removePos(int pos);
        node<T>* getHead()
        { return head; }
        T returnData(int pos);
        void printList();
};


int main()
{
    LinkedList<int> newList(1);

    cout << newList.returnData(0) << endl;
    return 0;
}

template<typename T> void populateArray( LinkedList<T> &inputList,
                                         int sizeOfList )
{

    for( int i = 0; i < sizeOfList; i++ )
    {
        inputList.appendData( generateRanNum<T>( ) );
    }

    for( int i = 0; i < sizeOfList; i++ )
    {
        inputList.returnData(i);
    }
}

//**************************************************
// Generates random integer between 100 and 1
//
// returns random integer
//**************************************************
 template<typename T> T generateRanNum( )
{
    T output = (rand() % 100 ) + 1;
    return output;
}

template<typename T> LinkedList<T>::LinkedList()
{
    node<T> *tmp = new node<T>;
    tmp->data = NULL;
    tmp->next = NULL;

    head = tmp;
}
template<typename T> LinkedList<T>::LinkedList(T data)
{
    node<T> *tmp = new node<T>;
    tmp->data = data;
    tmp->next = NULL;

    head = tmp;
}

template<typename T> void LinkedList<T>::appendData(T data)
{
    // Variable declarations
    node<T> *curPtr = getHead();
    node<T> *newNode;

    //Initialize newNode
    newNode.next = nullptr;
    newNode.data = data;

    // Iterate until the end is reach
    while( curPtr.next != nullptr )
    {
        // Iterate into next item
        curPtr = curPtr->next;
    }

    // Create next node
    curPtr.next = newNode;
}


template<typename T> void LinkedList<T>::insertData( T data, int pos )
{
    // Variable declarations
    node<T> *curPtr = getHead();
    node<T> *prevPtr = curPtr;
    node<T> *newNode;
    int index = 0;

    //Initialize newNode
    newNode.next = nullptr;
    newNode.data = data;

    // Iterate until you reach the desired index
    while( curPtr.next != nullptr && index != pos )
    {
        // Iterate to next item
        prevPtr = curPtr;
        curPtr = curPtr->next;
        index++;
    }

    // Insert node between
    // previous pointer and next pointer
    prevPtr->next = newNode;
    newNode->next = curPtr;

}

template<typename T> T LinkedList<T>::returnData(int pos)
{
    // Variable declarations
    node<T> *curPtr = getHead();
    int index = 0;

    // Iterate to the position
    while( curPtr->next != nullptr && index != pos )
    {
        // Iterate to next item
        curPtr = curPtr->next;
        index++;
    }


    // return item at position
    return (curPtr->data);
}
