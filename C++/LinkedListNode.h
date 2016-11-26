/*
* LinkedListNode.h
*
* original author:  jason9
*   from www.cplusplus.com/articles/E3wTURfi/
*
* secondary author: Jack Fletcher
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is the header file for the node class of a linked list.
* Everything is the same as Jason's original implementation except for
* the class names and #define name.
*
* This class is used to create the LinkedList class in LinkedList.h
*/

#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H


template <typename T>
class LinkedList;

template <typename T>
class LinkedListNode {
    friend class LinkedList<T>;

    public:
        LinkedListNode(T);
        T getData();

    private:
        T data; //templatized data stored in node
        LinkedListNode* nextPtr; //pointer to the next node in list
};

template <typename T>
LinkedListNode<T>::LinkedListNode(T dataIn) {
    data = dataIn; //stores data in node
    nextPtr = 0; //initializes point to next node to null
}

template <typename T>
T LinkedListNode<T>::getData() {
    return data;
}

#endif