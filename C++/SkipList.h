/*
* SkipList.h
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a Skip List implementation using SkipListNode.
* Implementation is based on William Pugh's pseudocode in his paper titled
* "Skip Lists: A Probabilistic Alternative to Balanced Trees"
*
* This class is a friend class of SkipNode and therefore can access the private
* data members of SkipNode directly.
*
*/

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <sstream>
#include <time.h>
#include <ostream>
#include <fstream>
#include "SkipListNode.h"

using namespace std;


template <typename T>
class SkipList {
public:
    SkipList<T>(T min_key, T max_key);
    ~SkipList();

    void insert(T key);
    bool remove(T key);
    SkipNode<T> *search(T key);
        
    void print_list(ofstream& outFile);

    int heightGen();
        
    SkipNode<T> *head;
    SkipNode<T> *tail;
    float prob = 0.5;
    static const int max_height = 16;
    int max_curr_height;
};


template <typename T>
SkipList<T>::SkipList(T min_key, T max_key) {
    max_curr_height = 0;
    prob = 0.5;
    srand((unsigned int)time(0));

    head = new SkipNode<T>(min_key, max_height);
    tail = new SkipNode<T>(max_key, max_height);
    for (int i = 0; i < max_height; i++)
        head->forward[i] = tail;
}

template <typename T>
SkipList<T>::~SkipList() {
    SkipNode<T> *temp = this->head;
    SkipNode<T> *next;
    if (this->head) {
        while (temp != tail) {
            next = temp->forward[0];
            delete temp;
            temp = next;
        }
        delete temp;
    }
}

template <typename T>
int SkipList<T>::heightGen() {
    int height = 1;
    while ((rand() / (double)RAND_MAX) < prob && height < max_height) {
        height++;
    }
    return height;
}

template <typename T>
void SkipList<T>::insert(T key) {
    SkipNode<T> *update[max_height];
    SkipNode<T> *curr_node = head;


    for (int i = max_height - 1; i >= 0; i--) {
        while (curr_node->forward[i]->key < key) {
            curr_node = curr_node->forward[i];
        }
        update[i] = curr_node;
    }

    int height = heightGen();
    if (height > max_curr_height) {
        max_curr_height = height;
    }
    
    SkipNode<T> *new_node = new SkipNode<T>(key, height);
    for (int i = 0; i < height; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
}

template <typename T>
bool SkipList<T>::remove(T key) {
    SkipNode<T> *update[max_height];
    SkipNode<T> *curr_node = head;
    for (int i = max_curr_height - 1; i >= 0; i--) {
        while (curr_node->forward[i]->key < key) {
            curr_node = curr_node->forward[i];
        }
        update[i] = curr_node;
    }
    curr_node = curr_node->forward[0];
    if (curr_node->key == key) {
        for (int i = 0; i < curr_node->height; i++) {
            update[i]->forward[i] = curr_node->forward[i];
        }
        delete curr_node;
        // update max_curr_height
        while (max_curr_height > 0 && head->forward[max_curr_height - 1] == tail) {
            max_curr_height--;
        }
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
SkipNode<T> *SkipList<T>::search(T key) {
    SkipNode<T> *curr_node = head;
    for (int i = max_curr_height - 1; i >= 0; i--) {
        while (curr_node->forward[i]->key < key) {
            curr_node = curr_node->forward[i];
        }
    }
    curr_node = curr_node->forward[0];
    if (curr_node->key == key) {
        return curr_node;
    }
    else {
        return nullptr;
    }
}

template <typename T>
void SkipList<T>::print_list(ofstream& outFile) {
    // start at head
    char value[5] = "0000";

    SkipNode<T> *curr_node = head;
    for (int i = 0; i < max_height; i++) {
        outFile << "[HEAD]";
    }
    outFile << endl;
    for (int i = 0; i < max_height; i++) {
        snprintf(value, sizeof(value), "%04d", curr_node->forward[i]->key);
        outFile << "[" << value << "]";
    }
    outFile << endl << endl;


    //iterate through the skiplist
    while (curr_node->forward[0] != tail) {
        stringstream sstr;
        curr_node = curr_node->forward[0];
        for (int i = 0; i < curr_node->height; i++) {
            snprintf(value, sizeof(value), "%04d", curr_node->key);
            sstr << "[" << value << "]";
        }
        sstr << endl;
        for (int i = 0; i < curr_node->height; i++) {
            snprintf(value, sizeof(value), "%04d", curr_node->forward[i]->key);
            sstr << "[" << value << "]";
        }
        sstr << endl << endl;
        outFile << sstr.str();
    }

    // found tail
    for (int i = 0; i < max_height; i++)
    {
        outFile << "[TAIL]";
    }
    outFile << endl;
}


#endif
