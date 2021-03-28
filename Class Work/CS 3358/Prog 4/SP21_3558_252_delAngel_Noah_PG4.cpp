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

        void setData(T data);
        void appendData(T data);
        void insertData(T data, int pos);
        void removePos(int pos);
        void printList();

        node<T>* getHead()
        { return head; }

        T returnData(int pos);
        int returnSize();
};

template<typename T> T generateRanNum();
template<typename T> void populateArray( LinkedList<T> &inputList,
                                         int sizeOfList );
template<typename T> void populateArray( LinkedList<T> &inputList,
                                        LinkedList<T> list_1,
                                        LinkedList<T> list_2);
template<typename T> LinkedList<T> removeDups( LinkedList<T> inputList );
template<typename T> int numOfOccurrences( T data, LinkedList<T> inputList );
template<typename T> void swapHeadTail( LinkedList<T> &inputList );

int main()
{
    // Variable declarations
    LinkedList<char> list_1, list_2, list_3, list_4;

    // Create seed
    srand(time(NULL));

    // Populate linked lists
    populateArray<char>( list_1, 15);
    populateArray<char>( list_2, 15);
    populateArray<char>( list_3, list_1, list_2 );


    list_4 = removeDups<char>( list_3 );


    // Output list 1 and 2
    cout << "List 1: ";
    list_1.printList();
    cout << endl;
    cout << "List 2: ";
    list_2.printList();
    cout << endl;

    // Output first element of list 3
    // and number of occurences
    cout << "First element of List 3: " << list_3.returnData( 0 )
         << endl;

    cout << "Number of occurrences of that element: "
         << numOfOccurrences( list_3.returnData(0), list_3 ) << endl << endl;
    cout << "List 4: ";
    list_4.printList();


    cout << "Number of elements in List 4: " << list_4.returnSize() << endl
         << endl;

    // Swap head and tail of list 4 and print list
    swapHeadTail(list_4);
    cout << "Swapping head and tail..." << endl;
    cout << "New List 4: ";
    list_4.printList();

    return 0;
}

template<typename T> void populateArray( LinkedList<T> &inputList,
                                         int sizeOfList )
{

    for( int i = 0; i < sizeOfList; i++ )
        if( i == 0)
            inputList.setData( generateRanNum<T>( ) );
        else
            inputList.appendData( generateRanNum<T>( ) );

}

template<typename T> void populateArray( LinkedList<T> &inputList,
                                        LinkedList<T> list_1,
                                        LinkedList<T> list_2)
{
    // Variable declarations
    int sizeOfList = list_1.returnSize( ) + list_2.returnSize( ),
        index_list1 = 0,
        index_list2 = 0;

    for( int i = 0; i < sizeOfList; i++)
        if( i == 0 )
        {
            inputList.setData( list_1.returnData( index_list1 ) );
            index_list1++;
        }
        else
            if( i % 2 == 0 )
            {
                inputList.appendData( list_1.returnData( index_list1 ) );
                index_list1++;
            }
            else
            {
                inputList.appendData( list_2.returnData( index_list2 ) );
                index_list2++;
            }
}

template<typename T> LinkedList<T> removeDups( LinkedList<T> inputList )
{
    // Variable declarations
    LinkedList<T> newList;
    for( int i = 0; i < inputList.returnSize(); i++ )
    {
        if( i == 0 )
            newList.setData( inputList.returnData( i ) );
        else
            newList.appendData( inputList.returnData(i) );


        for( int j = 0; j < newList.returnSize() - 1; j++ )
            if( newList.returnData( j ) == newList.returnData( i ) && i != 0)
                newList.removePos( i );
    }

    return newList;
}

template<typename T> int numOfOccurrences(T data, LinkedList<T> inputList)
{
    // Variable declarations
    int numOfOccurrences = 0;

    for( int i = 0; i < inputList.returnSize( ); i++ )
    {
            if( data == inputList.returnData( i ) )
            {
                numOfOccurrences++;
            }
    }

    return numOfOccurrences;
}

template<typename T> void swapHeadTail( LinkedList<T> &inputList )
{
    //Variable declarations
    T head = inputList.returnData(0);
    T tail = inputList.returnData(inputList.returnSize() - 1);

    inputList.setData(tail);
    inputList.removePos(inputList.returnSize() - 1);
    inputList.appendData(head);
}

//**************************************************
// Generates random integer between 100 and 1
//
// returns random integer
//**************************************************
 template<typename T> T generateRanNum( )
{
    T output = (rand() % 26 ) + 'A';
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

template<typename T> void LinkedList<T>::setData(T data)
{
    head->data = data;
}

template<typename T> void LinkedList<T>::appendData(T data)
{
    // Variable declarations
    node<T> *curPtr = getHead();
    node<T> *newNode = new node<T>;

    //Initialize newNode
    newNode->next = nullptr;
    newNode->data = data;

    // Iterate until the end is reach
    while( curPtr->next != nullptr )
    {
        // Iterate into next item
        curPtr = curPtr->next;
    }

    // Create next node
    curPtr->next = newNode;
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
    while( curPtr->next != nullptr && index != pos )
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

template<typename T> void LinkedList<T>::removePos( int pos )
{
    // Variable declarations
    node<T> *curPtr = getHead();
    node<T> *prevPtr = curPtr;
    int index = 0;

    while( curPtr->next != nullptr && index != pos )
    {
        // Iterate to next item
        prevPtr = curPtr;
        curPtr = curPtr->next;
        index++;
    }

    // Remove curPtr from list
    prevPtr->next = curPtr->next;

    // Remove node
    delete curPtr;


}

template<typename T> void LinkedList<T>::printList()
{
    // Variable declarations
    node<T> *curPtr = getHead();

    // Print all data in the list
    while( curPtr != nullptr )
    {
        cout << curPtr->data << " ";

        curPtr = curPtr->next;
    }

    cout << endl;
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

template<typename T> int LinkedList<T>::returnSize()
{
    // Variable declarations
    node<T> *curPtr = getHead();
    int sizeOfList = 0;

    // Iterate till it finds the end
    while( curPtr != NULL )
    {
        // Iterate to next item
        curPtr = curPtr->next;
        sizeOfList++;
    }

    return sizeOfList;

}
